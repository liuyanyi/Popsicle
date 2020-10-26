#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QItemSelection>
#include <QMainWindow>
#include <mutex>
#include <network/ChatService.h>
#include "AboutWindow.h"

namespace Ui
{
	class MainWindow;
}

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
	explicit MainWindow(QWidget* parent = nullptr);
	~MainWindow();
	static MainWindow* getMainWindow();

signals:
	void onWindowOK();

	//Log
	void notify(QString log);

	//用户
	void onUserAdd(QString ip, QString hostname);
	void onUserClear(QString ip, QString hostname);
	void onUserBye(QString ip);

	//聊天
	void onMsgRecvd(History history);
	void onFileRecv(QString fileName, QString ip);
	void onFileUnlock(QString fileName, QString ip, bool success);

	//MessageBox
	void onErrorExit(QString error);
	void onErrorBox();

	//AES
	void onAESPass(QString ip);

public slots:
	void windowOk();

	void test();
	void updateRSA();
	void LogNotify(QString log) const;

	void userAdd(const QString& ip, const QString& hostname);
	void userClear(const QString& ip, const QString& hostname) const;
	void userRemove(const QString& ip);

	void msgAdd(const History& history) const;
	void fileRecv(const QString& fileName, const QString& ip) const;
	void fileUnlock(const QString& fileName, const QString& ip, bool success);

	void errorExit(const QString& error);
	void errorBox();
	void aesPass(const QString& ip);

protected:
	bool event(QEvent* event) final;
	void closeEvent(QCloseEvent* event) override;

private slots:

	void on_closebutton_clicked();
	void on_maxbutton_clicked();
	void on_minbutton_clicked();

	void onRefreshClicked();

	//void on_userTable_doubleClicked(const QModelIndex &index);

private:
	Ui::MainWindow* ui;
	AboutWindow* about;

	QString errorCollect;
	std::mutex errMtx;

	void initUi();
	void initSecurityToolkit();
	static void eBox();
};

#endif // MAINWINDOW_H
