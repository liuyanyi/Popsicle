#include "ReceivingManager.h"
#include "ChatService.h"
#include "File.h"
#include "messageheader.h"
#include "TicToc.h"
#include "netsignal.h"

//#include "Resource.h"

#include <QDebug>
#include <WS2tcpip.h>

namespace inner_network
{
	void ReceivingManager::initReceivingManager(const int receivingPort)
	{
		//创建流式套接字
		SOCKET slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (slisten == INVALID_SOCKET)
		{
			printErrorAndExit(L"无法创建接听Socket");
		}

		//绑定IP和端口
		sockaddr_in sin;
		sin.sin_family = AF_INET;
		sin.sin_port = htons(receivingPort);
		//表示本机的所有ip
		sin.sin_addr.S_un.S_addr = INADDR_ANY;
		if (bind(slisten, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
		{
			printErrorAndExit(L"无法绑定接听端口！");
		}

		//开始监听
		if (listen(slisten, 5) == SOCKET_ERROR)
		{
			printErrorAndExit(L"无法开始监听");
		}

		// 开始循环接收消息
		receivingThread = std::thread(startReceivingLoop, slisten);
		receivingThread.detach();
	}

	void handleMessage(std::string msg, sockaddr_in addr)
	{
		// 获取ip
		char ip_buf[20];
		// 使用 inet_ntop 而不是 inet_ntoa 来保证安全
		//网路地址转化函数,地址的表达格式通常是ASCII字符串，数值格式则是存放到套接字地址结构的二进制值。
		inet_ntop(AF_INET, &addr.sin_addr, ip_buf, sizeof(ip_buf));
		//qDebug() << "1   " << QString::fromStdString(msg);

		if (msg[0] == MSG_REGULAR)
		{
			History history;
			history.isPrivate = false;
			history.isSend = false;
			history.message = msg.substr(1);
			history.senderName = getUserNameFromIp(ip_buf);
			history.time = std::chrono::system_clock::now();
			{
				std::lock_guard<std::mutex> lk(g_HistoryMutex);
				g_Histories.push_back(history);
				NetSignal::msgRecv(history);
				//add list
			}
			NetSignal::emitNotify("WM_RECOMMEND_REFRESH_HISTORIES:" + QString::fromStdString(msg));
			//PostMessage(g_hHWnd, WM_RECOMMEND_REFRESH_HISTORIES, NULL, NULL);
		}
		else if (msg[0] == MSG_TOC)
		{
			handleToc(msg, ip_buf);
			sendDicTo(ip_buf);
		}
		else if (msg[0] == MSG_DIC)
		{
			//qDebug() <<"DIC:  "<< QString::fromStdString(msg.substr(1));
			NetSignal::emitNotify("Receive DIC");
			handleDicdoc(msg, ip_buf);
			sendDocTo(ip_buf);
		}
		else if (msg[0] == MSG_DOC)
		{
			//qDebug() <<"DOC:  "<< QString::fromStdString(msg.substr(1));
			NetSignal::emitNotify("Receive DOC");
			handleDicdoc(msg, ip_buf);
		}
		else if (msg[0] == MSG_PRIVATE)
		{
			History history;
			history.isPrivate = true;
			history.isSend = false;
			std::string lock = msg.substr(1);
			std::string unlock = NetSignal::unlock(lock, ip_buf);
			history.message = unlock;
			history.senderName = getUserNameFromIp(ip_buf);
			history.time = std::chrono::system_clock::now();
			{
				//qDebug() << "1";
				std::lock_guard<std::mutex> lk(g_HistoryMutex);
				g_Histories.push_back(history);
				NetSignal::msgRecv(history);
			}
			NetSignal::emitNotify("WM_RECOMMEND_REFRESH_HISTORIES");
			//PostMessage(g_hHWnd, WM_RECOMMEND_REFRESH_HISTORIES, NULL, NULL);
		}
		else if (msg[0] == MSG_FILE)
		{
			// 会阻塞接收线程直到保存完文件
			handleFileMessage(msg, ip_buf);
		}
		else if (msg[0] == MSG_BYE)
		{
			// 某个客户端退出了列表，现在可以删除此客户端
			std::lock_guard<std::mutex> lk(l_AllUserMutex);
			const auto iter = l_AllUser.find(ip_buf);
			if (iter != l_AllUser.end())
			{
				l_AllUser.erase(iter);

				NetSignal::removeUser(QString(ip_buf));
				NetSignal::emitNotify("REMOVE" + QString(ip_buf));

				//PostMessage(g_hHWnd, WM_RECEIVE_TIC, NULL, NULL);

				//Remove one
				//RemoveUser(ip_buf);
			}
		}
	}

	void ReceivingManager::startReceivingLoop(SOCKET sListen)
	{
		WSADATA wsdata;
		//启动SOCKET库，版本为2.0；调用成功返回值为0
		WSAStartup(0x0202, &wsdata);

		std::string res;

		//循环接收数据
		SOCKET sClient;
		sockaddr_in remoteAddr;
		int nAddrlen = sizeof(remoteAddr);
		char buffer[256];
		while (true)
		{
			// 等待连接
			sClient = accept(sListen, (SOCKADDR*)&remoteAddr, &nAddrlen);
			if (sClient == INVALID_SOCKET)
			{
				NetSignal::emitNotify("WM_RECEIVE_MESSAGE_ERROR:Can't create receive connection");
				//PostMessage(g_hHWnd, WM_RECEIVE_MESSAGE_ERROR, 0, (LPARAM)"无法创建接收连接");
			}

			//接收数据
			while (true)
			{
				int ret = recv(sClient, buffer, 255, 0);
				if (ret > 0)
				{
					res.append(buffer, buffer + ret);
					static const size_t MSG_END_SIZE = strlen(MESSAGE_END);
					if (res.size() > MSG_END_SIZE && res.substr(res.size() - MSG_END_SIZE, MSG_END_SIZE) == MESSAGE_END)
					{
						// 已经读到结尾
						// res.pop_back();
						res.erase(res.size() - MSG_END_SIZE);
						break;
					}
				}
			}

			handleMessage(std::move(res), remoteAddr);

			closesocket(sClient);
		}
	}
} // namespace inner_network
