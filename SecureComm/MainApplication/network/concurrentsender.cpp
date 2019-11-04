#include "ConcurrentSender.h"
#include "ChatService.h"

#include <cstdlib>
#include <chrono>
#include <WS2tcpip.h>

namespace inner_network
{
	/**
		* \brief 在另一个线程发送Buffer
		* \param address 目标ip地址
		* \param port 目标端口
		* \param buffer 要发送的数据（一次性发完）
		* \param bufferSize 发送数据的大小
		* \param isSendingFile 发送的是否是文件
	*/
	ConcurrentSender::ConcurrentSender(const char* address, const int port, const char* buffer,
		const size_t bufferSize, bool isSendingFile)
		:address(address), port(port), bufferSize(bufferSize), _isSendingFile(isSendingFile)
	{
		this->buffer = new char[bufferSize];

		//从源内存地址（第二个参数）的起始位置开始拷贝bufferSize个字节到目标内存地址（第一个参数）中
		memcpy(this->buffer, buffer, bufferSize);
		//？
		this->future = std::async(&ConcurrentSender::startSend, this);
	}

	ConcurrentSender::~ConcurrentSender()
	{
		// this->future.wait();
		if (this->buffer != nullptr)
		{
			delete this->buffer;
		}
	}

	//检查是否发送完成，完成了返回ture，未完成返回false
	bool ConcurrentSender::checkDone()
	{
		using namespace std::chrono_literals;
		auto status = this->future.wait_for(0ms);

		return status == std::future_status::ready;
	}

	//阻塞当前线程，直到完成传输。只能调用一次，否则抛出异常。如果运行成功，返回 true，否则返回 false
	bool ConcurrentSender::waitDone()
	{
		return this->future.get();
	}

	bool ConcurrentSender::startSend()
	{
		WSADATA wsdata;
		//启动SOCKET库，版本为2.0
		WSAStartup(0x0202, &wsdata);

		SOCKET sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		//确认套接字创建成功
		if (sclient == INVALID_SOCKET)
			return false;
		//（结构体sockaddr_in的说明在文档里）
		sockaddr_in serAddr;
		serAddr.sin_family = AF_INET;
		serAddr.sin_port = htons(this->port);
		//IP地址转换，将“点分十进制”转化为“二进制整数”
		inet_pton(AF_INET, this->address.c_str(), (void*) & (serAddr.sin_addr));
		//判断请求连接是否成功，则返回0，否则返回错误码。
		if (connect(sclient, (sockaddr*)& serAddr, sizeof(serAddr)) == SOCKET_ERROR)
		{
			return false;
		}

		size_t begin_s = 0;
		while (begin_s < this->bufferSize)
		{
			//send()向一个已经连接的socket发送数据，如果无错误，返回值为所发送数据的总数，否则返回SOCKET_ERROR。
			size_t sended_len = send(sclient, this->buffer + begin_s, this->bufferSize - begin_s, 0);
			begin_s += sended_len;
		}

		begin_s = 0;
		const size_t MSG_END_LEN = strlen(MESSAGE_END);
		while (begin_s < MSG_END_LEN)
		{
			//向socket发送最后一段的数据
			size_t sended_len = send(sclient, MESSAGE_END + begin_s, MSG_END_LEN - begin_s, 0);
			begin_s += sended_len;
		}
		//关闭这个套接口
		closesocket(sclient);
		return true;
	}
}