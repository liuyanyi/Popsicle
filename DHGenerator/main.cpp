#include "DHGenerator.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	DHGenerator w;
	w.show();
	return a.exec();
}
