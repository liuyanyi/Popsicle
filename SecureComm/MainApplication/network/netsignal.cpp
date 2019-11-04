#include "netsignal.h"
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <QStandardItemModel>
#include <mutex>
#include <string>

#include "ChatService.h"
#include "TicToc.h"
#include "mainwindow.h"
#include "security/controller.h"
#include "ui_mainwindow.h"

std::list<History> g_Histories;
std::mutex         g_HistoryMutex;

NetSignal::NetSignal(QObject *parent) : QObject(parent) {
    //delete it
}

NetSignal::NetSignal(Ui::MainWindow *t) {
    this->window = t;
}

//触发信号
void NetSignal::emitNotify(QString log) {
    emit MainWindow::getMainWindow()->notify(log);
}

void NetSignal::addUser(QString ip, QString hostName) {
    emit MainWindow::getMainWindow()->onUserAdd(ip, hostName);
}

void NetSignal::clearUser(QString ip, QString hostName) {
    emit MainWindow::getMainWindow()->onUserClear(ip, hostName);
}

void NetSignal::removeUser(QString ip) {
    emit MainWindow::getMainWindow()->onUserBye(ip);
}

void NetSignal::msgRecv(History history) {
    emit MainWindow::getMainWindow()->onMsgRecvd(history);
}

void NetSignal::setPass(QString ip) {
    emit MainWindow::getMainWindow()->onAESPass(ip);
}

void NetSignal::receiveFile(std::string fileName, std::string ip) {
    emit MainWindow::getMainWindow()->onFileRecv(QString::fromStdString(fileName), QString::fromStdString(ip));
}

void NetSignal::unlockSignal(std::string fileName, std::string ip, bool success) {
    emit MainWindow::getMainWindow()->onFileUnlock(QString::fromStdString(fileName), QString::fromStdString(ip), success);
}

void NetSignal::updateRSA() {
    if (QMessageBox::information(MainWindow::getMainWindow(), "Info", "Ready to Update RSA Key", QMessageBox::Ok, QMessageBox::Cancel) == QMessageBox::Ok) {
        Util::gen_rsa_key_file("");
        refreshUserList();
    }
}

void NetSignal::fileThread(QString ip, QString inputFile, NetSignal *n) {
    std::lock_guard<std::mutex> lk(l_AllUserMutex);

    controller::file_handle(inputFile.toStdWString(),
                            inputFile.toStdWString().append(L".lk"),
                            l_AllAesKey[ip.toStdString()], FILE_ENCRYPT);
    emit n->fileOK(ip, inputFile);
}

std::string NetSignal::unlock(std::string lock, QString ip) {
    std::lock_guard<std::mutex> lk(l_AllUserMutex);
    return controller::aes_decrypt(lock, l_AllAesKey[ip.toStdString()], AES_CBC);
}

void NetSignal::unlockFile(std::wstring path, std::wstring fileName, std::string ip) {
    std::lock_guard<std::mutex> lk(l_AllUserMutex);
    std::wstring                wF = QString::fromStdString("./Recv/").toStdWString() + fileName;
    bool                        ok = controller::file_handle(path, wF, l_AllAesKey[ip], FILE_DECRYPT);
    if (ok)
        NetSignal::emitNotify(QString::fromStdWString(fileName) + " unlock success");
    else
        NetSignal::emitNotify(QString::fromStdWString(fileName) + " unlock fail");
    NetSignal::unlockSignal(QString::fromStdWString(fileName).toStdString(), ip, ok);
}

void NetSignal::deleteFile(std::wstring filePath) {
    qDebug() << DeleteFileW(filePath.c_str());
}

void NetSignal::errorExit(QString error) {
    emit MainWindow::getMainWindow()->onErrorExit(error);
}

std::string NetSignal::saveFile(QString fileName) {
    QString     path = "./Recv/" + fileName;
    QMessageBox info(QMessageBox::Information, "File Recv",
                     "Receive " + fileName, QMessageBox::Ok | QMessageBox::Cancel);

    qDebug() << path;

    info.exec();
    if (info.exec() == QMessageBox::Ok) {
        return path.toStdString();
    }

    return "";
}

//》》》
std::list<History> NetSignal::getHis() {
    return g_Histories;
}

void NetSignal::sendPublic() {
    if (window->inputbox != nullptr) {

        QString msg = window->inputbox->toPlainText();
        if (msg.isEmpty()) {
            QMessageBox::information(MainWindow::getMainWindow(), "Info", "Input is Empty");
            return;
        }
        BroadcastMessageToIps(msg.toStdString().c_str(), getIps());
        window->inputbox->clear();
        //SendMessageToIp(msg.toStdString().c_str(),"192.168.56.2");
    } else {
        emitNotify("NO PTR");
    }
}

QString NetSignal::getCurrentIp() {
    if (window == nullptr)
        return "";

    QModelIndex indexIp /*, indexName*/;
    QString     ip /*, name*/;

    QStandardItemModel * model  = (QStandardItemModel *) window->userTable->model();
    QItemSelectionModel *sModel = window->userTable->selectionModel();
    //    QList<QStandardItem *> tList = model.;
    QModelIndex index = sModel->currentIndex();
    if (!sModel->isSelected(index)) {
        return "";
    }
    if (index.isValid()) {
        indexIp = index.sibling(index.row(), 0);
        //        indexName = index.sibling(index.row(), 1);
        qDebug() << model->itemData(indexIp).values()[0].toString();
        ip = model->itemData(indexIp).values()[0].toString();
        //        qDebug() << model->itemData(indexName).values()[0].toString();
        //        name = model->itemData(indexName).values()[0].toString();
        return ip;
    }
    return "";
}

void NetSignal::sendPrivate() {
    std::lock_guard<std::mutex> lk(l_AllUserMutex);

    QString ip = getCurrentIp();

    if (ip == "") {
        QMessageBox::information(MainWindow::getMainWindow(), "Info", "Please choose User");
    } else if (l_AllAesKey[ip.toStdString()].empty()) {
        QMessageBox::information(MainWindow::getMainWindow(), "Info", "No AES KEY SYNC");
        return;
    } else {
        QString msg = window->inputbox->toPlainText();
        if (msg.isEmpty()) {
            QMessageBox::information(MainWindow::getMainWindow(), "Info", "Input is Empty");
            return;
        }
        std::string lock = controller::aes_encrypt(msg.toStdString(),
                                                   l_AllAesKey[ip.toStdString()], AES_CBC);
        SendMessageToIp(lock.c_str(), ip.toStdString().c_str());
        History history;
        history.isPrivate  = true;
        history.isSend     = true;
        history.message    = msg.toStdString();
        history.senderName = getUserNameFromIp(ip.toStdString());
        history.time       = std::chrono::system_clock::now();
        {
            g_Histories.push_back(history);
            NetSignal::msgRecv(history);
            //add list
        }
        window->inputbox->clear();
    }
}

void NetSignal::sendFile() {

    QString ip = getCurrentIp();

    if (ip == "") {
        QMessageBox::information(MainWindow::getMainWindow(), "Info", "Please choose object");
    } else if (l_AllAesKey[ip.toStdString()].empty()) {
        QMessageBox::information(MainWindow::getMainWindow(), "Info", "No AES KEY SYNC");
        return;
    } else {
        QString path = QFileDialog::getOpenFileName(MainWindow::getMainWindow(), u8"choose file");
        if (path == "")
            return;
        connect(this, &NetSignal::fileOK, this, &NetSignal::sendLockFile);
        std::thread fTh(NetSignal::fileThread,ip,path,this);
        fTh.detach();
        /*controller::file_handle(path.toStdWString(),
                                path.toStdWString().append(L".lk"),
                                l_AllAesKey[ip.toStdString()], FILE_ENCRYPT);*/
    }
}

void NetSignal::sendLockFile(QString ip, QString path) {
    wchar_t *wIp   = new wchar_t[ip.size() + 10];
    wchar_t *wPath = new wchar_t[path.size() + 10];
    ip.toWCharArray(wIp);
    path.append(".lk").toWCharArray(wPath);
    wIp[ip.size()]     = 0;
    wPath[path.size()] = 0;

    sendFileToIp(wPath, wIp);
}
