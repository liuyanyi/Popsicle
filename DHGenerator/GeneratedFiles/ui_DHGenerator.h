/********************************************************************************
** Form generated from reading UI file 'DHGenerator.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DHGENERATOR_H
#define UI_DHGENERATOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DHGeneratorClass
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
    QPushButton *minbutton;
    QPushButton *closebutton;
    QHBoxLayout *horizontalLayout_3;
    QFrame *line;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer_3;
    QLabel *label;
    QLabel *label_3;
    QSpacerItem *verticalSpacer_2;
    QVBoxLayout *verticalLayout;
    QLabel *label_4;

    void setupUi(QMainWindow *DHGeneratorClass)
    {
        if (DHGeneratorClass->objectName().isEmpty())
            DHGeneratorClass->setObjectName(QString::fromUtf8("DHGeneratorClass"));
        DHGeneratorClass->resize(623, 356);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(DHGeneratorClass->sizePolicy().hasHeightForWidth());
        DHGeneratorClass->setSizePolicy(sizePolicy);
        DHGeneratorClass->setStyleSheet(QString::fromUtf8("#MainWindow{\n"
"\n"
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
"#minbutton, #maxbutton {\n"
"  background-color: transparent;\n"
"  border-radius: 0px;\n"
"}\n"
"\n"
"#minbutton:hover, #maxbutton:hover{\n"
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
"  image: url(:/res/ext"
                        "ra/close-button2.png);\n"
"  border-style: none;\n"
"  background-color: #8c0a15;\n"
"}\n"
"\n"
"#line {\n"
"	color: #c7c7c7;\n"
"}"));
        centralWidget = new QWidget(DHGeneratorClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        topbox = new QWidget(centralWidget);
        topbox->setObjectName(QString::fromUtf8("topbox"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(topbox->sizePolicy().hasHeightForWidth());
        topbox->setSizePolicy(sizePolicy1);
        topbox->setMinimumSize(QSize(100, 0));
        topbox->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout = new QHBoxLayout(topbox);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(11, 0, 0, 0);
        Title = new QLabel(topbox);
        Title->setObjectName(QString::fromUtf8("Title"));
        sizePolicy1.setHeightForWidth(Title->sizePolicy().hasHeightForWidth());
        Title->setSizePolicy(sizePolicy1);
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
        sizePolicy1.setHeightForWidth(pass->sizePolicy().hasHeightForWidth());
        pass->setSizePolicy(sizePolicy1);
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

        minbutton = new QPushButton(topbox);
        minbutton->setObjectName(QString::fromUtf8("minbutton"));
        QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(minbutton->sizePolicy().hasHeightForWidth());
        minbutton->setSizePolicy(sizePolicy2);
        minbutton->setMinimumSize(QSize(50, 40));
        minbutton->setMaximumSize(QSize(50, 40));
        minbutton->setStyleSheet(QString::fromUtf8(""));
        minbutton->setIconSize(QSize(50, 30));
        minbutton->setFlat(true);

        horizontalLayout->addWidget(minbutton);

        closebutton = new QPushButton(topbox);
        closebutton->setObjectName(QString::fromUtf8("closebutton"));
        sizePolicy2.setHeightForWidth(closebutton->sizePolicy().hasHeightForWidth());
        closebutton->setSizePolicy(sizePolicy2);
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

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_3);

        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setMinimumSize(QSize(150, 150));
        label->setMaximumSize(QSize(150, 150));
        label->setPixmap(QPixmap(QString::fromUtf8(":/res/popsicle.ico")));
        label->setScaledContents(true);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label);

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

        verticalLayout_2->addWidget(label_3);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);


        horizontalLayout_2->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy3);
        QFont font2;
        font2.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font2.setPointSize(14);
        label_4->setFont(font2);
        label_4->setContextMenuPolicy(Qt::NoContextMenu);
        label_4->setWordWrap(true);

        verticalLayout->addWidget(label_4);


        horizontalLayout_2->addLayout(verticalLayout);


        gridLayout->addLayout(horizontalLayout_2, 2, 0, 1, 1);

        DHGeneratorClass->setCentralWidget(centralWidget);

        retranslateUi(DHGeneratorClass);

        QMetaObject::connectSlotsByName(DHGeneratorClass);
    } // setupUi

    void retranslateUi(QMainWindow *DHGeneratorClass)
    {
        DHGeneratorClass->setWindowTitle(QCoreApplication::translate("DHGeneratorClass", "DHGenerator", nullptr));
        Title->setText(QCoreApplication::translate("DHGeneratorClass", "Popsicle DH Key Generator", nullptr));
        pass->setText(QString());
        label_2->setText(QString());
        minbutton->setText(QString());
        closebutton->setText(QString());
        label->setText(QString());
        label_3->setText(QCoreApplication::translate("DHGeneratorClass", "Popsicle", nullptr));
        label_4->setText(QCoreApplication::translate("DHGeneratorClass", "DH Key\346\226\207\344\273\266\346\230\257\344\277\235\350\257\201\345\244\232\344\270\252Popsicle\345\256\242\346\210\267\347\253\257\346\255\243\345\270\270\344\272\244\346\215\242\345\257\206\351\222\245\347\232\204\345\277\205\350\246\201\346\226\207\344\273\266\357\274\214\347\224\237\346\210\220\345\220\216\345\212\241\345\277\205\344\277\235\350\257\201\345\220\204\344\270\252\345\256\242\346\210\267\347\253\257\347\232\204DH\346\226\207\344\273\266\345\256\214\345\205\250\344\270\200\350\207\264\343\200\202", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DHGeneratorClass: public Ui_DHGeneratorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DHGENERATOR_H
