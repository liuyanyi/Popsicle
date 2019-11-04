#include "File.h"
#include "ChatService.h"
#include "MessageHeader.h"
#include "netsignal.h"

#include <QDebug>
#include <QMessageBox>
#include <codecvt>
#include <fstream>
#include <locale>
#include <sstream>
#include <string>
#include <utility>

// 声明的全局变量（跨文件）
std::wstring g_wsSaveFilePath;

namespace inner_network {
std::string getFileNameFromPath(const std::wstring &filePath) {
    auto idx      = filePath.find_last_of(L'/');
    auto fileName = filePath.substr(idx + 1);

    // 用 utf-8 编码转换
    using convert_type = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_type, wchar_t> converter;

    return converter.to_bytes(fileName);
}

void sendFileToIp(const std::wstring &filePath, const char *distIp) {
    std::ifstream      fin(filePath, std::ios::in | std::ios::binary);
    std::ostringstream os;

    os << MSG_FILE << getFileNameFromPath(filePath) << "\r" << fin.rdbuf();

    std::string buf = os.str();
    fin.close();
    SendingManager::send(distIp, MESSAGE_RECV_PORT, buf.c_str(), buf.size(), true);
    NetSignal::deleteFile(filePath);
}

void handleFileMessage(const std::string &message , std::string ip) {
    size_t      fileNameEnd = message.find_first_of('\r');
    std::string fileNamelk    = message.substr(1, fileNameEnd - 1);
    std::string fileName = fileNamelk.substr(0, fileNamelk.size() - 3);

    // 用 utf-8 编码转换
    using convert_type = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_type, wchar_t> converter;

    std::wstring wFileName = converter.from_bytes(fileName);
    // 阻塞发送消息，这样就可以在主消息循环处理完文件位置之后直接返回并保存文件了。
    NetSignal::emitNotify("RECEIVE Locked FILE " + QString::fromStdString(fileName));
    NetSignal::receiveFile(fileName, ip);

    std::string path = "./Recv/" + fileNamelk;
    std::wstring wPath = QString::fromStdString(path).toStdWString();
    //NetSignal::emitNotify(QString::fromStdString(path));
    //        return; // 在主线程中将变量设为 “” 可以取消保存
    //qDebug() << QString::fromStdString(path);
    if (path.empty())
        return; // 在主线程中将变量设为 “” 可以取消保存
    std::ofstream out(wPath, std::ios::out | std::ios::binary);
    out << message.substr(fileNameEnd + 1);
    out.close();
    NetSignal::unlockFile(wPath, wFileName, std::move(ip));
}
} // namespace inner_network