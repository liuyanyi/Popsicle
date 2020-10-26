#include "ChatService.h"
#include "File.h"
#include "MessageHeader.h"
#include "ReceivingManager.h"
#include "TicToc.h"
#include "netsignal.h"

#include <QDebug>
#include <WinSock2.h>
#include <comdef.h>
#include <string>
#include <thread>

//引用名空间
using namespace inner_network;

/**
* \brief 初始化网络和线程
*/
void initNetworkAndThreads()
{
	//初始化WSA
	//声明调用的Winsock版本；MAKEWORD(2,2)就是调用2.2版
	WORD sockVersion = MAKEWORD(2, 2);
	//WSADATA，一种数据结构。这个结构被用来存储被WSAStartup函数调用后返回的Windows Sockets数据
	//wsaData用来存储系统传回的关于WINSOCK的资料
	WSADATA wsaData;
	//WSAStartup，即WSA(Windows Sockets Asynchronous，Windows异步套接字)的启动命令。
	//WSAStartup必须是应用程序或DLL调用的第一个Windows Sockets函数。
	//返回值为“0”，成功；否则返回错误代码。
	if (WSAStartup(sockVersion, &wsaData) != 0)
	{
		printErrorAndExit(L"无法初始化 Socket");
		return;
	}

	// 初始化管理器
	SendingManager::initSendingManager();

	std::thread recvTicThread(startTicLoop, BROADCAST_RECV_PORT);
	recvTicThread.detach();

	ReceivingManager::initReceivingManager(MESSAGE_RECV_PORT);

	Sleep(100);
	//TODO: 删掉这里
	refreshUserList();
}

/**
	* \brief 从 ip 地址获取计算机名（此过程会加锁），返回值为ip。如果计算机名不存在，直接返回 ip
	* \param ip 此计算机的 ip 地址
	* \return 用户名字符串
*/
std::string getUserNameFromIp(const std::string& ip)
{
	//std::lock_guard<std::mutex> lk(l_AllUserMutex);
	try
	{
		return l_AllUser.at(ip);
	}
	catch (std::out_of_range)
	{
		return ip;
	}
}

/**
	* \brief 获取所有的用户（会加锁）。格式： ip，用户名
*/
std::vector<std::pair<std::string, std::string>> getUsers()
{
	using namespace std;
	//实例化以创建其析构函数解锁 mutex 的对象的模板
	lock_guard<mutex> lk(l_AllUserMutex);
	//pair结构提供了将两个对象视为单个对象的的功能
	using item_type = pair<string, string>;
	vector<item_type> res;
	res.reserve(l_AllUser.size());
	for (const item_type& item : l_AllUser)
	{
		res.push_back(item);
	}
	return res;
}

/**
	* \brief 获取所有的用户的ip（会加锁）。
*/
std::vector<std::string> getIps()
{
	using namespace std;
	//实例化以创建其析构函数解锁 mutex 的对象的模板
	lock_guard<mutex> lk(l_AllUserMutex);
	//pair结构提供了将两个对象视为单个对象的的功能
	vector<std::string> res;
	unsigned int size = l_AllUser.size();
	res.reserve(size);
	using item_type = pair<string, string>;
	for (const item_type& item : l_AllUser)
	{
		res.push_back(item.first);
	}
	return res;
}

/**
	* \brief 向ip发送消息（可能需要改动）
	* \param message 指向字符的常量指针
	* \param ip 指向字符的常量指针
*/
void SendMessageToIp(const char* message, const char* ip)
{
	std::string msg;
	// 留出一位来存放消息类型
	//为容器预留足够的空间，避免不必要的重复分配。预留空间大于等于字符串的长度。
	msg.reserve(strlen(message) + 1);
	msg += MSG_PRIVATE;
	msg += message;
	SendingManager::send(ip, MESSAGE_RECV_PORT, msg.c_str(), msg.size());
}

//刷新用户列表
void refreshUserList()
{
	char myName[128];
	//返回本地主机的标准主机名。

	gethostname(myName, 128);
	struct hostent* pHost = gethostbyname(myName);
	{
		std::lock_guard<std::mutex> lk(l_AllUserMutex);
		l_AllUser.clear();
		l_AllUser[inet_ntoa(*(struct in_addr*)(pHost->h_addr_list[0]))] = myName;

		NetSignal::clearUser(inet_ntoa(*(struct in_addr*)(pHost->h_addr_list[0])), myName);
	}
	//线程里(执行的函数，函数的参数)
	std::thread ticThread(broadcastTic, BROADCAST_RECV_PORT);
	//从ticThread分离执行的线程，允许执行独立地持续。
	ticThread.detach();
}

void printErrorAndExit(const wchar_t* errMsg)
{
	//qDebug()<<"FFUUCCKK";
	//MessageBox(g_hHWnd, errMsg, L"初始化错误", MB_OK);
	//NetSignal::emitNotify("Init Failed:" + QString::fromStdWString(errMsg));
	NetSignal::errorExit(QString::fromStdWString(errMsg));
	/*QMessageBox message(QMessageBox::Critical,"Error",QString::fromStdWString(errMsg));
		//message.setWindowFlags(windowFlags()|Qt::CustomizeWindowHint);
		//message.setStandardButtons(nullptr);
		message.show();

		//if (message.exec()==QMessageBox::Ok)
		//{
			//close();
			exit(0);
		//}
	//exit(0);*/
}

//向ip发送文件（可能需要改动）
void sendFileToIp(const wchar_t* filePath, const wchar_t* distIp)
{
	_bstr_t distIpB(distIp);
	//inner_network::sendFileToIp(filePath, distIpB);
	//qDebug() << "file" << distIp << filePath;
	std::thread sendFileThread(inner_network::sendFileToIp, filePath, distIpB);
	sendFileThread.detach();
	//delete[] filePath;
}

void sendByeToOthers()
{
	char bye[1];
	bye[0] = MSG_BYE;
	std::lock_guard<std::mutex> lk(l_AllUserMutex);
	for (auto item : l_AllUser)
	{
		SendingManager::send(item.first, MESSAGE_RECV_PORT, bye, 1, false);
	}
}
