/********************************************************************************
** Form generated from reading UI file 'AboutWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUTWINDOW_H
#define UI_ABOUTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AboutWindow
{
public:
    QWidget *centralWidget;
    QWidget *layoutWidget_2;
    QHBoxLayout *horizontalLayout_3;
    QFrame *line;
    QGridLayout *gridLayout;
    QWidget *topbox;
    QHBoxLayout *horizontalLayout;
    QLabel *Title;
    QLabel *label_2;
    QSpacerItem *verticalSpacer;
    QPushButton *minbutton;
    QPushButton *maxbutton;
    QPushButton *closebutton;
    QHBoxLayout *mainbox;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_3;
    QLabel *label_4;
    QSpacerItem *verticalSpacer_2;
    QTextBrowser *textBrowser;

    void setupUi(QMainWindow *AboutWindow)
    {
        if (AboutWindow->objectName().isEmpty())
            AboutWindow->setObjectName(QString::fromUtf8("AboutWindow"));
        AboutWindow->resize(714, 472);
        AboutWindow->setStyleSheet(QString::fromUtf8("#textBrowser {\n"
"	background-color: rgb(250, 250, 250);\n"
"	border-width: 0;\n"
"	border-style:outset\357\274\232\n"
"\n"
"}\n"
"#centralWidget{\n"
"	background-color: rgb(250, 250, 250);\n"
"}\n"
"\n"
"#topbox {\n"
"	/*background-color: rgb(105, 193, 253);*/\n"
"}\n"
"\n"
"#minbutton {\n"
"  image: url(:/res/extra/minimize-button1.png);\n"
"}\n"
"\n"
"#minbutton, #maxbutton {\n"
"  background-color: transparent;\n"
"  border-radius: 0px;\n"
"}\n"
"\n"
"#minbutton:hover, #maxbutton:hover {\n"
"  border-style: none;\n"
"  background-color: #80c7c7c7;\n"
"}\n"
"\n"
"#minbutton:pressed, #maxbutton:pressed {\n"
"  border-style: none;\n"
"  background-color: #80808080;\n"
"}\n"
"\n"
"#closebutton {\n"
"  image: url(:/res/extra/close-button1.png);\n"
"  background-color: transparent;\n"
"  border-radius: 0px;\n"
"}\n"
"\n"
"#closebutton:hover {\n"
"  image: url(:/res/extra/close-button2.png);\n"
"  border-style: none;\n"
"  background-color: #e81123;\n"
"}\n"
"\n"
"#closebutton:pressed {\n"
"  image: url(:/res/ex"
                        "tra/close-button2.png);\n"
"  border-style: none;\n"
"  background-color: #8c0a15;\n"
"}\n"
"\n"
"#line {\n"
"	color: #c7c7c7;\n"
"}"));
        centralWidget = new QWidget(AboutWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        layoutWidget_2 = new QWidget(centralWidget);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(230, 90, 2, 3));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget_2);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        line = new QFrame(layoutWidget_2);
        line->setObjectName(QString::fromUtf8("line"));
        line->setEnabled(false);
        line->setMaximumSize(QSize(16777215, 1));
        line->setStyleSheet(QString::fromUtf8(""));
        line->setFrameShadow(QFrame::Plain);
        line->setFrameShape(QFrame::HLine);

        horizontalLayout_3->addWidget(line);

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

        label_2 = new QLabel(topbox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font);
        label_2->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(label_2);

        verticalSpacer = new QSpacerItem(10000, 40, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout->addItem(verticalSpacer);

        minbutton = new QPushButton(topbox);
        minbutton->setObjectName(QString::fromUtf8("minbutton"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
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

        mainbox = new QHBoxLayout();
        mainbox->setSpacing(0);
        mainbox->setObjectName(QString::fromUtf8("mainbox"));
        mainbox->setContentsMargins(11, 5, 11, 11);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMinimumSize(QSize(150, 150));
        label->setMaximumSize(QSize(150, 150));
        label->setPixmap(QPixmap(QString::fromUtf8(":/res/popsicle.ico")));
        label->setScaledContents(true);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Consolas"));
        font1.setPointSize(14);
        font1.setBold(true);
        font1.setWeight(75);
        label_3->setFont(font1);
        label_3->setLayoutDirection(Qt::LeftToRight);
        label_3->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_3);

        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Consolas"));
        font2.setPointSize(12);
        font2.setBold(false);
        font2.setWeight(50);
        label_4->setFont(font2);
        label_4->setScaledContents(false);
        label_4->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_4);

        verticalSpacer_2 = new QSpacerItem(20, 2000000, QSizePolicy::Minimum, QSizePolicy::Maximum);

        verticalLayout->addItem(verticalSpacer_2);


        mainbox->addLayout(verticalLayout);

        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        QFont font3;
        font3.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font3.setPointSize(12);
        font3.setStyleStrategy(QFont::PreferAntialias);
        textBrowser->setFont(font3);
        textBrowser->setFocusPolicy(Qt::StrongFocus);
        textBrowser->setContextMenuPolicy(Qt::NoContextMenu);
        textBrowser->setAcceptDrops(false);
        textBrowser->setStyleSheet(QString::fromUtf8(""));
        textBrowser->setTextInteractionFlags(Qt::LinksAccessibleByKeyboard|Qt::LinksAccessibleByMouse);

        mainbox->addWidget(textBrowser);


        gridLayout->addLayout(mainbox, 1, 0, 1, 1);

        AboutWindow->setCentralWidget(centralWidget);

        retranslateUi(AboutWindow);

        QMetaObject::connectSlotsByName(AboutWindow);
    } // setupUi

    void retranslateUi(QMainWindow *AboutWindow)
    {
        AboutWindow->setWindowTitle(QCoreApplication::translate("AboutWindow", "AboutWindow", nullptr));
        Title->setText(QCoreApplication::translate("AboutWindow", "About", nullptr));
        label_2->setText(QString());
        minbutton->setText(QString());
        maxbutton->setText(QString());
        closebutton->setText(QString());
        label->setText(QString());
        label_3->setText(QCoreApplication::translate("AboutWindow", "Popsicle", nullptr));
        label_4->setText(QCoreApplication::translate("AboutWindow", "0.1.0.0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AboutWindow: public Ui_AboutWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUTWINDOW_H
