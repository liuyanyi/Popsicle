#include "SendingManager.h"
//#include "Resource.h"
//#include "ChatService.h"
#include "netsignal.h"

namespace inner_network {
void SendingManager::startLoop() {
    while (true) {
        std::shared_ptr<ConcurrentSender> ptr;
        {
            // 锁定线程共享的队列从而取出一个 Sender
            std::unique_lock<std::mutex> lk(SendingManager::mut);
            SendingManager::dataCond.wait(lk, [&] { return !SendingManager::sendingQueue.empty(); });
            ptr = SendingManager::sendingQueue.front();
            SendingManager::sendingQueue.pop();
        }
        // 解锁之后再执行 Sender，防止在执行时锁定队列并阻塞主线程
        bool success = ptr->waitDone();
        if (success) {
            // 只有传输的是文件的时候才会发送通知
            if (ptr->isSendingFile()) {
                //将一个消息放入（寄送）到与指定窗口创建的线程相联系消息队列里
                //不等待线程处理消息就返回，是异步消息模式。
                NetSignal::emitNotify("WM_SEND_FILE_DONE");
                //PostMessage(g_hHWnd, WM_SEND_FILE_DONE, 0, 0);
            }
        } else {
            //auto msg = (LPARAM) "发送失败";
            if (ptr->isSendingFile()) {
                // 防止引用失效，在发送此消息的时候阻塞线程，避免释放 SocketException 中的 string 内存
                NetSignal::emitNotify("WM_SEND_FILE_ERROR");
                //SendMessage(g_hHWnd, WM_SEND_FILE_ERROR, 0, msg);
            } else {
                NetSignal::emitNotify("WM_SEND_MESSAGE_ERROR");
                //SendMessage(g_hHWnd, WM_SEND_MESSAGE_ERROR, 0, msg);
            }
        }
    }
}

void SendingManager::send(const std::string address, int port, const char *buffer, size_t bufferSize, bool isFile) {
    //在构造函数中进行加锁，析构函数中进行解锁。
    std::lock_guard<std::mutex> lk(SendingManager::mut);
    SendingManager::sendingQueue.emplace(new ConcurrentSender(address.c_str(), port, buffer, bufferSize, isFile));
    SendingManager::dataCond.notify_one();
}
} // namespace inner_network