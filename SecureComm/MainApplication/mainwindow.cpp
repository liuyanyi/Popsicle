#include "mainwindow.h"
#include "AboutWindow.h"
#include "ui_mainwindow.h"

#include "FramelessHelper.h"
#include "qtmaterialiconbutton.h"
#include "qtmaterialraisedbutton.h"
#include "qtmaterialscrollbar.h"

#include <QDebug>
#include <QFile>
#include <QMenu>
#include <QMessageBox>
#include <QMetaType>
#include <QStandardItemModel>

#include <thread>

#include "network/ChatService.h"
#include "network/netsignal.h"
#include "security/Util.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent, Qt::FramelessWindowHint), ui(new Ui::MainWindow) {

    qRegisterMetaType<History>("History");

    //要用的
    connect(this, &MainWindow::notify, this, &MainWindow::LogNotify);
    connect(this, &MainWindow::onUserAdd, this, &MainWindow::userAdd);
    connect(this, &MainWindow::onUserClear, this, &MainWindow::userClear);
    connect(this, &MainWindow::onUserBye, this, &MainWindow::userRemove);
    connect(this, &MainWindow::onMsgRecvd, this, &MainWindow::msgAdd);
    connect(this, &MainWindow::onErrorExit, this, &MainWindow::errorExit);
    connect(this, &MainWindow::onErrorBox, this, &MainWindow::errorBox, Qt::QueuedConnection);
    connect(this, &MainWindow::onAESPass, this, &MainWindow::aesPass);
    connect(this, &MainWindow::onFileRecv, this, &MainWindow::fileRecv);
    connect(this, &MainWindow::onFileUnlock, this, &MainWindow::fileUnlock);
    connect(this, &MainWindow::onWindowOK, this, &MainWindow::windowOk);

    ui->setupUi(this);

    emit onWindowOK();
}

void MainWindow::windowOk() {
    //存文件用的
    CreateDirectoryA("./Recv", nullptr);

    initUi();
    initNetworkAndThreads();
    initSecurityToolkit();

    if (errorCollect != nullptr)
        eBox();
}

void MainWindow::initUi() {
    //无边窗口
    this->setWindowTitle("Popsicle");
    auto helper = new FramelessHelper(this);
    helper->setDraggableMargins(3, 3, 3, 3);
    helper->setMaximizedMargins(3, 3, 3, 3);
    helper->setTitleBarHeight(40);
    helper->addExcludeItem(ui->closebutton);
    helper->addExcludeItem(ui->minbutton);
    helper->addExcludeItem(ui->maxbutton);
    helper->addExcludeItem(ui->settingsbutton);
    ui->maxbutton->setIcon(
        QIcon(QStringLiteral(":/res/extra/maximize-button1.png")));
    ui->settingsbutton->setStyleSheet(
        "QPushButton::menu-indicator{image:none;}"); //不显示下拉图片
    const QString ver = QSysInfo::productVersion();
    if (ver == "7sp1" || ver == "7")
        ui->centralWidget->setStyleSheet(
            "#centralWidget{"
            "background-color: rgb(250, 250, 250);"
            "border:3px groove;"
            "border-color: rgb(167, 192, 220);"
            "}");
    else {
        ui->centralWidget->setStyleSheet(
            "#centralWidget{"
            "background-color: rgb(250, 250, 250);"
            "}");
    }

    // Material滚动条
    auto bar1 = new QtMaterialScrollBar();
    bar1->setHideOnMouseOut(false);
    bar1->setSliderColor(QColor("#ff80ab"));
    ui->chatbox->setVerticalScrollBar((QScrollBar *) bar1);

    auto bar2 = new QtMaterialScrollBar;
    bar2->setHideOnMouseOut(false);
    bar2->setSliderColor(QColor("#ff80ab"));
    ui->inputbox->setVerticalScrollBar((QScrollBar *) bar2);

    auto bar3 = new QtMaterialScrollBar;
    bar3->setHideOnMouseOut(false);
    bar3->setSliderColor(QColor("#ff80ab"));
    ui->userTable->setVerticalScrollBar((QScrollBar *) bar3);

    auto bar4 = new QtMaterialScrollBar;
    bar4->setHideOnMouseOut(false);
    bar4->setSliderColor(QColor("#ff80ab"));
    ui->logbox->setVerticalScrollBar((QScrollBar *) bar4);

    // Material Button
    auto *send = new QtMaterialRaisedButton;
    send->setText("Send");
    send->setHaloVisible(false);
    send->setBackgroundColor("#ff80ab");
    send->setIcon(QIcon(":/res/send.svg"));
    send->setFont(QFont("Arial"));
    send->setFontSize(10);
    NetSignal *n = new NetSignal(this->ui);
    connect(send, &QtMaterialRaisedButton::clicked, n, &NetSignal::sendPublic);
    ui->buttonbox->addWidget(send);

    auto *sendPrivate = new QtMaterialRaisedButton;
    sendPrivate->setText("Send to");
    sendPrivate->setHaloVisible(false);
    sendPrivate->setBackgroundColor("#ff80ab");
    sendPrivate->setIcon(QIcon(":/res/send-lock.svg"));
    sendPrivate->setFont(QFont("Arial"));
    sendPrivate->setFontSize(10);
    //sendPrivate->setFont(QFont("Consolas"));
    connect(sendPrivate, &QtMaterialRaisedButton::clicked, n, &NetSignal::sendPrivate);
    ui->buttonbox->addWidget(sendPrivate);

    auto *sendFile = new QtMaterialRaisedButton;
    sendFile->setText("Send File");
    sendFile->setHaloVisible(false);
    sendFile->setBackgroundColor("#ff80ab");
    sendFile->setIcon(QIcon(":/res/file-send.svg"));
    sendFile->setFont(QFont("Arial"));
    sendFile->setFontSize(10);
    //sendPrivate->setFont(QFont("Consolas"));
    connect(sendFile, &QtMaterialRaisedButton::clicked, n, &NetSignal::sendFile);
    ui->buttonbox->addWidget(sendFile);

    //Material Icon Button
    QIcon *ref = new QIcon;
    ref->addFile(":/res/refresh.svg");
    auto *refresh = new QtMaterialIconButton(*ref);
    refresh->setFixedSize(25, 25);
    connect(refresh, &QtMaterialIconButton::clicked, this, &MainWindow::onRefreshClicked);
    ui->userTitle->addWidget(refresh);

    //用户列表
    auto *model = new QStandardItemModel();
    model->setColumnCount(2);
    model->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("IP"));
    model->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("Name"));
    ui->userTable->setModel(model);
    ui->userTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->userTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->userTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->userTable->setContextMenuPolicy(Qt::CustomContextMenu);

    //消息框
    ui->chatbox->setText("");

    //菜单
    auto          menu = new QMenu();
    const QString MenuStyle =
        " \
            QMenu{ padding:2px; border:none; border-radius:2px;} \
            QMenu::right-arrow{ background: url(:/tiny/lb_arrow_up_normal);} \
            QMenu::item{ padding:6px 30px 6px 30px;} \
            QMenu::item:selected{ background-color: #c7c7c7;}";
    menu->setStyleSheet(MenuStyle);
    menu->addAction(tr("Update RSA"), this, &MainWindow::updateRSA);
    menu->addAction(tr("About"), this, &MainWindow::test);
    menu->addAction(tr("About Qt"), this, &QApplication::aboutQt);
    ui->settingsbutton->setMenu(menu);
}

void MainWindow::initSecurityToolkit() {
    for (int i = 0; i < 2; i++) {
        key_pair *pair = Util::get_rsa_key("");
        if (pair == nullptr && i == 0) {
            emit notify("No RSA file, Generate RSA...");
            Util::gen_rsa_key_file("");
        } else if (pair == nullptr && i == 1) {
            emit onErrorExit("Generate RSA Failed");
            break;
        } else {
            break;
        }
    }

    dh_key *dh = Util::get_dh_key("");
    if (dh == nullptr) {
        emit onErrorExit("DH Failed");
    }
}

MainWindow::~MainWindow() { delete ui; }

bool MainWindow::event(QEvent *event) {
    if (event->type() == QEvent::WindowStateChange) {
        if (windowState() & Qt::WindowMaximized) {
            ui->maxbutton->setIcon(
                QIcon(QStringLiteral(":/res/extra/maximize-button2.png")));
            ui->maxbutton->setToolTip(tr("Restore"));
        } else {
            ui->maxbutton->setIcon(
                QIcon(QStringLiteral(":/res/extra/maximize-button1.png")));
            ui->maxbutton->setToolTip(tr("Maximize"));
        }
    }

    return QWidget::event(event);
}

void MainWindow::on_closebutton_clicked() {
    close();
    exit(0);
}

void MainWindow::on_maxbutton_clicked() {
    if (windowState() & Qt::WindowMaximized) {
        showNormal();
    } else {
        showMaximized();
    }
}

void MainWindow::on_minbutton_clicked() { showMinimized(); }

void MainWindow::onRefreshClicked() { refreshUserList(); }

MainWindow *MainWindow::getMainWindow() {
    foreach (QWidget *w, qApp->topLevelWidgets())
        if (auto *mainWin = qobject_cast<QMainWindow *>(w)) {
            return dynamic_cast<MainWindow *>(mainWin);
        }
    return nullptr;
}

void MainWindow::closeEvent(QCloseEvent *event) {
    sendByeToOthers();
    qDebug() << "Bye";
    //|窗口关闭之前需要的操作~
}

void MainWindow::test() {
    about = new AboutWindow();
    about->show();
}

void MainWindow::updateRSA() {
    NetSignal::updateRSA();
}

void MainWindow::LogNotify(QString log) const {
    if (log == nullptr)
        log = "//";
    ui->logbox->append(log);
}

void MainWindow::userAdd(const QString &ip, const QString &hostname) {
    QList<QStandardItem *> list;
    list << new QStandardItem(ip) << new QStandardItem(hostname);
    auto                   model = (QStandardItemModel *) ui->userTable->model();
    QList<QStandardItem *> tList = model->findItems(ip);

    if (tList.size() == 0)
        model->appendRow(list);
}

void MainWindow::userRemove(const QString &ip) {
    auto                   model = (QStandardItemModel *) ui->userTable->model();
    QList<QStandardItem *> tList = model->findItems(ip);
    QStandardItem *        tItem = tList.at(0);
    int                    row   = tItem->row();
    model->removeRow(row);
}

void MainWindow::userClear(const QString &ip, const QString &hostname) const {
    auto model = new QStandardItemModel();
    model->setColumnCount(2);

    model->setHeaderData(0, Qt::Horizontal, QString::fromLocal8Bit("IP"));
    model->setHeaderData(1, Qt::Horizontal, QString::fromLocal8Bit("Name"));

    model->setItem(0, 0, new QStandardItem(ip));
    model->setItem(0, 1, new QStandardItem(hostname));

    ui->userTable->setModel(model);
}

void MainWindow::msgAdd(const History &history) const {
    if (history.isPrivate) {
        if (history.isSend) {
            ui->chatbox->append("<b>Private message send to " + QString::fromStdString(history.senderName) + ":</b>");
        } else {
            ui->chatbox->append("<b>Private message from " + QString::fromStdString(history.senderName) + ":</b>");
        }
    } else {
        ui->chatbox->append("<b>" + QString::fromStdString(history.senderName) + ":</b>");
    }
    ui->chatbox->append(QString::fromStdString(history.message) + "\n");
}

void MainWindow::fileRecv(const QString &fileName, const QString &ip) const {
    std::lock_guard<std::mutex> lk(l_AllUserMutex);
    ui->chatbox->append("<b style=\" color: #66ccff \">Receive file: " + fileName +
                        " from " + QString::fromStdString(l_AllUser[ip.toStdString()]) + "</b>" + "\n");
}

void MainWindow::fileUnlock(const QString &fileName, const QString &ip, bool success) {
    std::lock_guard<std::mutex> lk(l_AllUserMutex);
    QString                     str = "<b style=\" color: ";
    if (success)
        str += "#259b24";
    else
        str += "#e51c23";

    str = str + " \">Unlock file: " + fileName +
          " from " + QString::fromStdString(l_AllUser[ip.toStdString()]);
    if (success)
        str += " success.</b>";
    else
        str += " failed.</b>";

    ui->chatbox->append(str + "\n");
}

void MainWindow::errorExit(const QString &error) {
    emit                        notify(error);
    std::lock_guard<std::mutex> lk(errMtx);
    errorCollect += error + "\n";
}

void MainWindow::errorBox() {
    std::lock_guard<std::mutex> lk(errMtx);
    QMessageBox                 message(QMessageBox::Critical, "错误",
                        errorCollect + "请检查网络或加密设置");

    message.show();
    if (message.exec() == QMessageBox::Ok) {
        close();
        exit(0);
    }
}

void MainWindow::aesPass(const QString &ip) {
    auto *model = dynamic_cast<QStandardItemModel *>(ui->userTable->model());
    // model->indexFromItem(new QStandardItem(ip));
    const QList<QStandardItem *> tList = model->findItems(ip);
    if (tList.empty())
        return;
    QStandardItem *tItem = tList.at(0);
    const int      row   = tItem->row();
    const QBrush   green(QColor("#259B24"));
    model->item(row, 0)->setForeground(green);
    model->item(row, 1)->setForeground(green);
}

void MainWindow::eBox() {
    Sleep(1000);
    emit MainWindow::getMainWindow()->onErrorBox();
}
