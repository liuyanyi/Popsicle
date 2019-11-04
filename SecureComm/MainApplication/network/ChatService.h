﻿#pragma once

#include <WinSock2.h>
#include <algorithm>
#include <chrono>
#include <codecvt>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <string>

#include "SendingManager.h"
//#include "Resource.h"
#include "MessageHeader.h"

#pragma comment(lib, "ws2_32.lib")

struct History {
	/// <summary>
	/// 发送者的计算机名
	/// </summary>
	std::string senderName;

	/// <summary>
	/// 发送时间
	/// </summary>
	std::chrono::time_point<std::chrono::system_clock> time;

	/// <summary>
	/// 消息内容
	/// </summary>
	std::string message;

	/// <summary>
	/// 是否是私有消息
	/// </summary>
	bool isPrivate;

	bool isSend;
};

/// <summary>
/// 所有消息的历史记录
/// </summary>
extern std::list<History> g_Histories;
/// <summary>
/// 对历史记录的锁。在访问之前需要先锁定它，以防止并发争用
/// </summary>
extern std::mutex g_HistoryMutex;

/// <summary>
/// 所有的用户，key为ip，value为计算机名
/// </summary>
extern std::map<std::string, std::string> l_AllUser;
/// <summary>
/// 对用户列表的锁
/// </summary>
extern std::mutex l_AllUserMutex;

extern std::map<std::string, std::string> l_AllPublicKey;
extern std::map<std::string, std::string> l_AllAesKey;

/// <summary>
/// 从 ip 地址获取计算机名（此过程会加锁）。如果计算机名不存在，直接返回 ip
/// </summary>
std::string getUserNameFromIp(const std::string& ip);

/// <summary>
/// 获取所有的用户（会加锁）。格式： ip，用户名
/// </summary>
std::vector<std::pair<std::string, std::string>> getUsers();

std::vector<std::string> getIps();

/// <summary>
/// 接收消息的端口，向其他客户端发送消息时指定此端口
/// </summary>
const int MESSAGE_RECV_PORT = 7001;

/// <summary>
/// 接收 udp 消息的端口，用于 TicToc
/// </summary>
const int BROADCAST_RECV_PORT = 7002;

/// <summary>
/// 向指定的 ip 单发消息
/// </summary>
void SendMessageToIp(const char* message, const char* ip);

/// <summary>
/// 向指定的 ip 群发消息，collection 必须拥有 cbegin 和 cend 方法，每个元素都是一个ip的字符串（c_str）
/// </summary>
template <typename COLLECTION>
void BroadcastMessageToIps(const char* message, const COLLECTION collection) {
	std::string msg;
	msg.reserve(strlen(message) + 1); // 留出一位来存放消息类型
	msg += inner_network::MSG_REGULAR;
	msg += message;
	for (auto iter = collection.cbegin(); iter != collection.cend(); ++iter) {
		inner_network::SendingManager::send(*iter, MESSAGE_RECV_PORT, msg.c_str(), msg.size());
	}
}

/// <summary>
/// 初始化网络和线程，需要在主窗口的 Create 里面调用
/// </summary>
void initNetworkAndThreads();

/// <summary>
/// 广播消息，从而搜索其他主机
/// </summary>
void refreshUserList();

/// <summary>
/// 生成错误对话框并退出程序
/// </summary>
void printErrorAndExit(const wchar_t* errMsg);

/// <summary>
/// 给某个ip发送path指定的文件（文件必须有访问权限）
/// </summary>
void sendFileToIp(const wchar_t* filePath, const wchar_t* distIp);

/// <summary>
/// cstring 转换为 string
/// </summary>
/*
static void cstring2string(CString & src, std::string & dst) {
	wchar_t  * str = src.GetBuffer();
	dst = std::wstring_convert<std::codecvt_utf8<wchar_t> >().to_bytes(str);
	//dst.assign(wstr.begin(), wstr.end());
}
*/
/// <summary>
/// 保存文件的位置，在 File 命令的处理函数里面给这个变量赋值，函数结束之后就能将文件保存在这个位置了。
/// </summary>
extern std::wstring g_wsSaveFilePath;

/// <summary>
/// 设定消息的结尾
/// </summary>
static const char* MESSAGE_END = "\r\n--/\fEndMsg\f/--\r\n";

/// <summary>
/// 向其他所有客户端发送 Bye 消息，从他们的列表中删除本机
/// </summary>
void sendByeToOthers();
