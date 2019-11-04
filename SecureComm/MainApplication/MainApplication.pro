#-------------------------------------------------
#
# Project created by QtCreator 2019-07-26T15:11:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MainApplication
TEMPLATE = app

VERSION = 0.0.7.3

QMAKE_TARGET_PRODUCT = Popsicle
QMAKE_TARGET_COMPANY = Neu-Comm-Task
#QMAKE_TARGET_DESCRIPTION = 文件描述
QMAKE_TARGET_COPYRIGHT = Liuyanyi

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        aboutdlg.cpp \
        main.cpp \
        mainwindow.cpp \
        network/ChatService.cpp \
        network/ConcurrentSender.cpp \
        network/File.cpp \
        network/ReceivingManager.cpp \
        network/SendingManager.cpp \
        network/TicToc.cpp \
        network/netsignal.cpp \
        network/netutil.cpp \
        security/MD5.cpp \
        security/Util.cpp \
        security/aes.cpp \
        security/controller.cpp \
        security/rsa.cpp

HEADERS += \
        aboutdlg.h \
        mainwindow.h \
        network/ChatService.h \
        network/ConcurrentSender.h \
        network/File.h \
        network/MessageHeader.h \
        network/ReceivingManager.h \
        network/SendingManager.h \
        network/TicToc.h \
        network/netsignal.h \
        network/netutil.h \
        security/MD5.h \
        security/Util.h \
        security/aes.h \
        security/controller.h \
        security/rsa.h

FORMS += \
        aboutdlg.ui \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


include(FramelessHelper/FramelessHelper.pri)

LIBS += ../components/$(OBJECTS_DIR)/components.lib
LIBS += -lws2_32

INCLUDEPATH += ../components

PRE_TARGETDEPS += ../components/$(OBJECTS_DIR)/components.lib

RESOURCES += \
    res.qrc

RC_ICONS =./res/popsicle.ico

#INCLUDEPATH += D:/vcpkg/installed/x86-windows/include
#LIBS        += D:/vcpkg/installed/x86-windows/lib/mpir.lib

QMAKE_CFLAGS_RELEASE += -MD
QMAKE_CXXFLAGS_RELEASE += -MD
QMAKE_CFLAGS_DEBUG += -MDd
QMAKE_CXXFLAGS_DEBUG += -MDd
QMAKE_CXXFLAGS += -execution-charset:utf-8

win32: LIBS += -LD:/vcpkg/installed/x86-windows/lib/ -lmpir

INCLUDEPATH += D:/vcpkg/installed/x86-windows/include
DEPENDPATH += D:/vcpkg/installed/x86-windows/include
