#include <QDebug>
#include <WS2tcpip.h>
#include <WinSock2.h>
#include <cstring>
#include <vector>

#include "ChatService.h"
#include "TicToc.h"
//#include "Resource.h"
#include "MessageHeader.h"

#include "netsignal.h"
#include "netutil.h"

#pragma comment(lib, "ws2_32.lib")

//声明全局变量
//所有的用户，key为ip，value为用户名
std::map<std::string, std::string> l_AllUser;
std::mutex                         l_AllUserMutex;
std::map<std::string, std::string> l_AllPublicKey;
std::map<std::string, std::string> l_AllAesKey;

namespace inner_network {

//广播Tic出现错误
void sendBroadcastError(const char *msg) {
    NetSignal::emitNotify("BROADCAST_TIC_ERROR:" + QString(msg));
    //SendMessage(g_hHWnd, WM_BROADCAST_TIC_ERROR, NULL, (LPARAM)msg);
}

//广播Tic
void broadcastTic(const int port) {
    WSADATA wsdata;
    //启动SOCKET库，版本为2.0
    WSAStartup(0x0202, &wsdata);

    SOCKET sock;
    //DatagramSocket使用的UDP连接,客户端不需要先连接数据,可以直接发送给指定服务端。
    //这里的WSASocket的第二个参数为SOCK_DGRAM，所以是保证使用UDP连接。
    //使用 UDP 广播一个连接请求 Tic
    if ((sock = WSASocket(AF_INET, SOCK_DGRAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED)) < 0) {
        return sendBroadcastError("刷新失败，无法创建广播 socket");
    }

    int ret;

    /*char bufferOut[128];
    bufferOut[0] = MSG_TIC;
    ret          = gethostname(bufferOut + 1, 127);*/
    //assert(ret == 0);

    std::string tt = NetUtil::buildTictoc(TIC);



    struct sockaddr_in addr;
    //将addr所在的内存清零
    memset(&addr, 0, sizeof(addr));
    addr.sin_port        = htons(port);
    addr.sin_family      = AF_INET;
    addr.sin_addr.s_addr = INADDR_BROADCAST;
    //inet_pton(AF_INET, "192.168.1.3", (void *)&(addr.sin_addr));

    bool opt = true;
    //设置该套接字为广播类型(UDP)
    setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char FAR *) &opt, sizeof(opt));

    int addr_len = sizeof(addr);
    int tts      = tt.length();
    //qDebug()<<QString::fromStdString(tt);
    ret = sendto(sock, tt.c_str(), tts, 0, (struct sockaddr *) &addr, addr_len);
    //ret = sendto(sock, bufferOut, strlen(bufferOut), 0, (struct sockaddr *)&addr, addr_len);
    if (ret == SOCKET_ERROR) {
        sendBroadcastError("刷新失败，Send Error");
    }

    Sleep(500);
    closesocket(sock);
}

//处理一个Tic
void handleTic(const char *msg, const char *ip) {
    {

        std::lock_guard<std::mutex> lk(l_AllUserMutex);
        std::vector<std::string>    res = NetUtil::unpackTictoc(msg);
        //            l_AllUser[ip] = msg + 1;
        l_AllUser[ip]      = res[0];
        l_AllPublicKey[ip] = res[1];

        //Add one
        NetSignal::addUser(ip, QString::fromStdString(l_AllUser[ip]));
        //NetSignal::emitNotify("rsa:"+QString::fromStdString(res[1]));

        //AddUser(ip,l_AllUser[ip];
    }

    sendTocTo(ip);
    //保证内存安全，这里必须用 send
    //将指定的消息发送到一个或多个窗口。此函数为指定的窗口调用窗口程序，直到窗口程序处理完消息再返回。
    //NetSignal* s = new NetSignal();
    //s->nettest("Receive Tic"+QString(ip));
    NetSignal::emitNotify("Receive Tic");
    //SendMessage(g_hHWnd, WM_RECEIVE_TIC, NULL, (LPARAM)ip);
}

void startTicLoop(const int port) {
    WSADATA wsdata;
    //启动SOCKET库，版本为2.0
    WSAStartup(0x0202, &wsdata);

    static constexpr int BUFLEN = 4096;

    SOCKET             s;
    struct sockaddr_in server, si_other;
    int                slen, recv_len;
    char               buf[BUFLEN];

    //将server和si_other所在的内存清零
    memset(&server, 0, sizeof(server));
    memset(&si_other, 0, sizeof(si_other));

    slen = sizeof(si_other);

    //创建一个数据报套接字
    if ((s = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
        printErrorAndExit(L"无法创建UDP Server");
        return;
    }

    //准备server和si_other   sockaddr_in结构体
    server.sin_family      = AF_INET;
    server.sin_addr.s_addr = 0;
    server.sin_port        = htons(port);

    si_other.sin_family      = AF_INET;
    si_other.sin_addr.s_addr = INADDR_BROADCAST;
    si_other.sin_port        = htons(5050);

    //设置套接字为广播类型,允许发送广播消息
    bool so_broadcast = true;
    int  ret          = setsockopt(s, SOL_SOCKET, SO_BROADCAST, (char *) &so_broadcast, sizeof(so_broadcast));
    if (ret < 0) {
        printErrorAndExit(L"无法把套接字设为广播类型");
        return;
    }

    //套接字绑定“服务器”端口
    if (::bind(s, (struct sockaddr *) &server, sizeof server) == SOCKET_ERROR) {
        printErrorAndExit(L"无法绑定UDP端口");
        return;
    }

    //监听用户端数据
    while (true) {
        //缓存区清零, 之前可能收到了数据
        memset(buf, '\0', BUFLEN);

        //接收更多数据, this is a blocking call
        if ((recv_len = recvfrom(s, buf, BUFLEN - 1, 0, (struct sockaddr *) &si_other, &slen)) == SOCKET_ERROR) {
            NetSignal::emitNotify("Can't Read Tic Data");
            //PostMessage(g_hHWnd, WM_RECEIVE_TIC_ERROR, NULL, (LPARAM)"无法读取Tic数据");
            continue;
        }

        if (buf[0] == MSG_TIC) {
            char ip_buf[20]; // 使用 inet_ntop 而不是 inet_ntoa 来保证安全
            inet_ntop(AF_INET, &si_other.sin_addr, ip_buf, sizeof(ip_buf));
            handleTic(buf, ip_buf);
        }
    }

    closesocket(s);
}

//用TCP回复Toc到发送Tic方
void sendTocTo(const char *ip) {
    /*char bufferOut[128];
    bufferOut[0] = MSG_TOC;
    int res      = gethostname(bufferOut + 1, 127);*/

    std::string tocStr = NetUtil::buildTictoc(TOC);
    //buildTictoc(char*);
    //下面这条对gethostname返回值的判断好像可以有，但是给的原码里也注释掉了（gethostname()在文档里有）
    //assert(res == 0);
    //向指定ip发送hostname（加入待发送队列）
    SendingManager::send(ip, MESSAGE_RECV_PORT, tocStr.c_str(), tocStr.length());
    //        SendingManager::send(ip, MESSAGE_RECV_PORT, bufferOut, strlen(bufferOut));
}

//处理Toc消息
void handleToc(const std::string &msg, const char *ip) {
    std::vector<std::string> res = NetUtil::unpackTictoc(msg);

    std::lock_guard<std::mutex> lk(l_AllUserMutex);
    l_AllUser[ip] = res[0];
    //        l_AllUser[ip] = msg.substr(1);
    l_AllPublicKey[ip] = res[1];

    //Add one
    NetSignal::addUser(ip, QString::fromStdString(l_AllUser[ip]));
    //AddUser(ip,l_AllUser[ip];

    //NetSignal* s = new NetSignal();
    NetSignal::emitNotify("RECEIVE_TOC");
    //NetSignal::emitNotify("rsa:"+QString::fromStdString(res[1]));
    //PostMessage(g_hHWnd, WM_RECEIVE_TOC, NULL, NULL);
}

void sendDicTo(const char *ip) {
    std::string dicStr = NetUtil::buildDicdoc(DIC);
    //qDebug() <<"Dic:  "<< QString::fromStdString(dicStr);
    //qDebug() << dicStr.size();
    SendingManager::send(ip, MESSAGE_RECV_PORT, dicStr.c_str(), dicStr.size());
}

void handleDicdoc(const std::string &msg, const char *ip) {
    std::string                 aes = NetUtil::unpackDictoc(msg,ip);
    std::lock_guard<std::mutex> lk(l_AllUserMutex);
    l_AllAesKey[ip] = aes;
    qDebug() <<"AES:  "<< QString::fromStdString(aes);
    NetSignal::setPass(QString(ip));
    //处理变色
}

void sendDocTo(const char *ip) {
    std::string docStr = NetUtil::buildDicdoc(DOC);
    //qDebug() << "Doc:  " << QString::fromStdString(docStr);

    SendingManager::send(ip, MESSAGE_RECV_PORT, docStr.c_str(), docStr.length());
}

} // namespace inner_network