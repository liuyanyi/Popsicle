#ifndef NETSIGNAL_H
#define NETSIGNAL_H

#include "ChatService.h"

#include <QObject>
#include <QTextEdit>
#include <mainwindow.h>

class NetSignal : public QObject
{
Q_OBJECT
public:
	explicit NetSignal(QObject* parent = nullptr);
	Ui::MainWindow* window;
	NetSignal(Ui::MainWindow* t);
	//void nettest(QString msg);
	static void emitNotify(QString log);
	static void addUser(QString ip, QString hostName);
	static void clearUser(QString ip, QString hostName);
	static void removeUser(QString ip);
	static void msgRecv(History history);
	static void errorExit(QString error);
	static std::list<History> getHis();
	//static void               sendPrivate(QString ip, QString msg);
	static std::string saveFile(QString fileName);
	//    static void t();
	static void setPass(QString ip);
	static std::string unlock(std::string lock, QString ip);
	static void unlockFile(std::wstring path, std::wstring fileName, std::string ip);
	static void deleteFile(std::wstring filePath);
	static void receiveFile(std::string fileName, std::string ip);
	static void unlockSignal(std::string fileName, std::string ip, bool success);
	static void updateRSA();
	static void fileThread(QString ip, QString inputFile, NetSignal* n);

signals:
	void net(QString msg);
	void fileOK(QString ip, QString path);

public slots:
	void sendPublic();
	void sendPrivate();
	//void sendPrivate(QString ip, QString msg);
	void sendFile();

	void sendLockFile(QString ip, QString path);

private:
	QString getCurrentIp();
};

#endif // NETSIGNAL_H
