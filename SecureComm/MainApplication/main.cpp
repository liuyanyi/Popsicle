﻿#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char* argv[])
{
	QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QApplication::setQuitOnLastWindowClosed(false);

	//    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
	QApplication a(argc, argv);
	MainWindow w;
	w.show();

	return a.exec();
}
