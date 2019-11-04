/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QWidget *topbox;
    QHBoxLayout *horizontalLayout;
    QLabel *Title;
    QLabel *pass;
    QLabel *label_2;
    QSpacerItem *verticalSpacer;
    QPushButton *settingsbutton;
    QPushButton *minbutton;
    QPushButton *maxbutton;
    QPushButton *closebutton;
    QHBoxLayout *horizontalLayout_3;
    QFrame *line;
    QHBoxLayout *mainbox;
    QVBoxLayout *leftbox;
    QLabel *label_4;
    QTextBrowser *chatbox;
    QLabel *label;
    QTextEdit *inputbox;
    QHBoxLayout *buttonbox;
    QVBoxLayout *rightbox;
    QHBoxLayout *userTitle;
    QLabel *usr;
    QTableView *userTable;
    QLabel *label_3;
    QTextBrowser *logbox;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(818, 686);
        MainWindow->setStyleSheet(QString::fromUtf8("#chatbox:focus, #inputbox:focus, #logbox:focus,#userTable:focus {\n"
"	border-style:solid;\n"
"	border-width: 1px;\n"
"	border-color: rgb(255, 128, 171);\n"
"}\n"
"\n"
"#label_2{\n"
"	color: rgb(255, 0, 0);\n"
"}\n"
"\n"
"#centralWidget{\n"
"	background-color: rgb(250, 250, 250);\n"
"}\n"
"\n"
"#topbox {\n"
"	/*background-color: rgb(105, 193, 253);*/\n"
"}\n"
"#pass {\n"
"	color:rgb(76, 175, 80)\n"
"}\n"
"\n"
"#minbutton {\n"
"  image: url(:/res/extra/minimize-button1.png);\n"
"}\n"
"\n"
"#minbutton, #maxbutton, #settingsbutton {\n"
"  background-color: transparent;\n"
"  border-radius: 0px;\n"
"}\n"
"\n"
"#minbutton:hover, #maxbutton:hover, #settingsbutton:hover {\n"
"  border-style: none;\n"
"  background-color: #80c7c7c7;\n"
"}\n"
"\n"
"#minbutton:pressed, #maxbutton:pressed, #settingsbutton:pressed {\n"
"  border-style: none;\n"
"  background-color: #80808080;\n"
"}\n"
"\n"
"#closebutton {\n"
"  image: url(:/res/extra/close-button1.png);\n"
"  background-color: transparent;\n"
"  border-radius: 0px;\n"
"}\n"
""
                        "\n"
"#closebutton:hover {\n"
"  image: url(:/res/extra/close-button2.png);\n"
"  border-style: none;\n"
"  background-color: #e81123;\n"
"}\n"
"\n"
"#closebutton:pressed {\n"
"  image: url(:/res/extra/close-button2.png);\n"
"  border-style: none;\n"
"  background-color: #8c0a15;\n"
"}\n"
"\n"
"#settingsbutton {\n"
"	image: url(:/res/extra/settings-button1.png);\n"
"}\n"
"\n"
"#line {\n"
"	color: #c7c7c7;\n"
"}"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setStyleSheet(QString::fromUtf8(""));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        topbox = new QWidget(centralWidget);
        topbox->setObjectName(QString::fromUtf8("topbox"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(topbox->sizePolicy().hasHeightForWidth());
        topbox->setSizePolicy(sizePolicy);
        topbox->setMinimumSize(QSize(100, 0));
        topbox->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout = new QHBoxLayout(topbox);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(11, 0, 0, 0);
        Title = new QLabel(topbox);
        Title->setObjectName(QString::fromUtf8("Title"));
        sizePolicy.setHeightForWidth(Title->sizePolicy().hasHeightForWidth());
        Title->setSizePolicy(sizePolicy);
        Title->setMaximumSize(QSize(16777215, 40));
        QFont font;
        font.setFamily(QString::fromUtf8("Consolas"));
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        Title->setFont(font);
        Title->setLayoutDirection(Qt::LeftToRight);
        Title->setFrameShape(QFrame::NoFrame);
        Title->setFrameShadow(QFrame::Plain);
        Title->setTextFormat(Qt::RichText);
        Title->setScaledContents(false);
        Title->setAlignment(Qt::AlignCenter);
        Title->setWordWrap(false);
        Title->setMargin(0);

        horizontalLayout->addWidget(Title);

        pass = new QLabel(topbox);
        pass->setObjectName(QString::fromUtf8("pass"));
        sizePolicy.setHeightForWidth(pass->sizePolicy().hasHeightForWidth());
        pass->setSizePolicy(sizePolicy);
        pass->setMaximumSize(QSize(16777215, 40));
        pass->setFont(font);
        pass->setMouseTracking(true);
        pass->setStyleSheet(QString::fromUtf8(""));
        pass->setTextFormat(Qt::RichText);

        horizontalLayout->addWidget(pass);

        label_2 = new QLabel(topbox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);
        label_2->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(label_2);

        verticalSpacer = new QSpacerItem(10000, 40, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout->addItem(verticalSpacer);

        settingsbutton = new QPushButton(topbox);
        settingsbutton->setObjectName(QString::fromUtf8("settingsbutton"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(settingsbutton->sizePolicy().hasHeightForWidth());
        settingsbutton->setSizePolicy(sizePolicy1);
        settingsbutton->setMinimumSize(QSize(50, 40));
        settingsbutton->setMaximumSize(QSize(50, 40));
        settingsbutton->setStyleSheet(QString::fromUtf8(""));
        settingsbutton->setFlat(true);

        horizontalLayout->addWidget(settingsbutton);

        minbutton = new QPushButton(topbox);
        minbutton->setObjectName(QString::fromUtf8("minbutton"));
        sizePolicy1.setHeightForWidth(minbutton->sizePolicy().hasHeightForWidth());
        minbutton->setSizePolicy(sizePolicy1);
        minbutton->setMinimumSize(QSize(50, 40));
        minbutton->setMaximumSize(QSize(50, 40));
        minbutton->setStyleSheet(QString::fromUtf8(""));
        minbutton->setIconSize(QSize(50, 30));
        minbutton->setFlat(true);

        horizontalLayout->addWidget(minbutton);

        maxbutton = new QPushButton(topbox);
        maxbutton->setObjectName(QString::fromUtf8("maxbutton"));
        sizePolicy1.setHeightForWidth(maxbutton->sizePolicy().hasHeightForWidth());
        maxbutton->setSizePolicy(sizePolicy1);
        maxbutton->setMinimumSize(QSize(50, 40));
        maxbutton->setMaximumSize(QSize(50, 40));
        maxbutton->setStyleSheet(QString::fromUtf8(""));
        maxbutton->setIconSize(QSize(50, 30));
        maxbutton->setFlat(true);

        horizontalLayout->addWidget(maxbutton);

        closebutton = new QPushButton(topbox);
        closebutton->setObjectName(QString::fromUtf8("closebutton"));
        sizePolicy1.setHeightForWidth(closebutton->sizePolicy().hasHeightForWidth());
        closebutton->setSizePolicy(sizePolicy1);
        closebutton->setMinimumSize(QSize(50, 40));
        closebutton->setMaximumSize(QSize(50, 40));
        closebutton->setStyleSheet(QString::fromUtf8(""));
        closebutton->setIconSize(QSize(50, 30));
        closebutton->setFlat(true);

        horizontalLayout->addWidget(closebutton);


        gridLayout->addWidget(topbox, 0, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        line = new QFrame(centralWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setEnabled(false);
        line->setMaximumSize(QSize(16777215, 1));
        line->setStyleSheet(QString::fromUtf8(""));
        line->setFrameShadow(QFrame::Plain);
        line->setFrameShape(QFrame::HLine);

        horizontalLayout_3->addWidget(line);


        gridLayout->addLayout(horizontalLayout_3, 1, 0, 1, 1);

        mainbox = new QHBoxLayout();
        mainbox->setSpacing(0);
        mainbox->setObjectName(QString::fromUtf8("mainbox"));
        mainbox->setContentsMargins(0, 0, 0, 11);
        leftbox = new QVBoxLayout();
        leftbox->setSpacing(5);
        leftbox->setObjectName(QString::fromUtf8("leftbox"));
        leftbox->setContentsMargins(11, 11, 11, 11);
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Consolas"));
        font1.setPointSize(10);
        label_4->setFont(font1);

        leftbox->addWidget(label_4);

        chatbox = new QTextBrowser(centralWidget);
        chatbox->setObjectName(QString::fromUtf8("chatbox"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font2.setPointSize(12);
        chatbox->setFont(font2);
        chatbox->setStyleSheet(QString::fromUtf8(""));

        leftbox->addWidget(chatbox);

        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setFont(font1);

        leftbox->addWidget(label);

        inputbox = new QTextEdit(centralWidget);
        inputbox->setObjectName(QString::fromUtf8("inputbox"));
        inputbox->setMaximumSize(QSize(16777215, 250));
        inputbox->setFont(font2);

        leftbox->addWidget(inputbox);

        buttonbox = new QHBoxLayout();
        buttonbox->setSpacing(7);
        buttonbox->setObjectName(QString::fromUtf8("buttonbox"));

        leftbox->addLayout(buttonbox);


        mainbox->addLayout(leftbox);

        rightbox = new QVBoxLayout();
        rightbox->setSpacing(5);
        rightbox->setObjectName(QString::fromUtf8("rightbox"));
        rightbox->setContentsMargins(11, 11, 11, 11);
        userTitle = new QHBoxLayout();
        userTitle->setSpacing(0);
        userTitle->setObjectName(QString::fromUtf8("userTitle"));
        userTitle->setContentsMargins(-1, -1, 11, -1);
        usr = new QLabel(centralWidget);
        usr->setObjectName(QString::fromUtf8("usr"));
        usr->setFont(font1);

        userTitle->addWidget(usr);


        rightbox->addLayout(userTitle);

        userTable = new QTableView(centralWidget);
        userTable->setObjectName(QString::fromUtf8("userTable"));
        QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(userTable->sizePolicy().hasHeightForWidth());
        userTable->setSizePolicy(sizePolicy2);

        rightbox->addWidget(userTable);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        QSizePolicy sizePolicy3(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy3);
        label_3->setFont(font1);

        rightbox->addWidget(label_3);

        logbox = new QTextBrowser(centralWidget);
        logbox->setObjectName(QString::fromUtf8("logbox"));
        sizePolicy2.setHeightForWidth(logbox->sizePolicy().hasHeightForWidth());
        logbox->setSizePolicy(sizePolicy2);
        logbox->setMaximumSize(QSize(16777215, 200));

        rightbox->addWidget(logbox);


        mainbox->addLayout(rightbox);


        gridLayout->addLayout(mainbox, 5, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        Title->setText(QCoreApplication::translate("MainWindow", "Popsicle 0.1.0 ", nullptr));
        pass->setText(QString());
        label_2->setText(QString());
        settingsbutton->setText(QString());
        minbutton->setText(QString());
        maxbutton->setText(QString());
        closebutton->setText(QString());
        label_4->setText(QCoreApplication::translate("MainWindow", "Chat Box", nullptr));
        chatbox->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'\345\256\213\344\275\223'; font-size:12pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'SimSun'; font-size:7.2pt;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:7pt;\">a</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:7pt;\">a</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-blo"
                        "ck-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:7pt;\">a</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:7pt;\">a</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:7pt;\">a</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:7pt;\">a</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:7pt;\">a</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSu"
                        "n'; font-size:7pt;\">a</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:7pt;\">a</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:7pt;\">a</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:7pt;\">a</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:7pt;\">a</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:7pt;\">a</span></p>\n"
"<p style=\" margin-top:0px;"
                        " margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:7pt;\">a</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:7pt;\">a</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:7pt;\">a</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:7pt;\">a</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:7pt;\">a</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-"
                        "indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:7pt;\">a</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:7pt;\">a</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:7pt;\">a</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:7pt;\">a</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:7pt;\">a</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun';"
                        " font-size:7pt;\">a</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:7pt;\">a</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:7pt;\">a</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:7pt;\">a</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:7pt;\">a</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:7pt;\">a</span></p>\n"
"<p style=\" margin-top:0px; ma"
                        "rgin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:7pt;\">a</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:7pt;\">a</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:7pt;\">a</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:7pt;\">a</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:7pt;\">a</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-ind"
                        "ent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:7pt;\">a</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:7pt;\">a</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:7pt;\">a</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:7pt;\">a</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:7pt;\">a</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; fo"
                        "nt-size:7pt;\">a</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:7pt;\">a</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:7pt;\">a</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:7pt;\">a</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:7pt;\">a</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:7pt;\">a</span></p>\n"
"<p style=\" margin-top:0px; margi"
                        "n-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:7pt;\">a</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:7pt;\">a</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:7pt;\">a</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:7pt;\">a</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:7pt;\">a</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent"
                        ":0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:7pt;\">a</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:7pt;\">a</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:7pt;\">a</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:7pt;\">a</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:7pt;\">a</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-"
                        "size:7pt;\">a</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:7pt;\">a</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:7pt;\">a</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:7pt;\">a</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:7pt;\">a</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:7pt;\">a</span></p>\n"
"<p style=\" margin-top:0px; margin-b"
                        "ottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:7pt;\">a</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:7pt;\">a</span></p></body></html>", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Input", nullptr));
        usr->setText(QCoreApplication::translate("MainWindow", "User List", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Log Box", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
