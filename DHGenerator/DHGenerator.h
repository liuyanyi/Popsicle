#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_DHGenerator.h"

class DHGenerator : public QMainWindow
{
	Q_OBJECT

public:
	DHGenerator(QWidget *parent = Q_NULLPTR);

private:
	Ui::DHGeneratorClass* ui;

private slots:
	void on_closebutton_clicked();

	void on_minbutton_clicked();
	void gen_clicked();
};
