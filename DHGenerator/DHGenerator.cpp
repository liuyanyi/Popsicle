#include "DHGenerator.h"
#include "../SecureComm/components/qtmaterialraisedbutton.h"
#include "security/Util.h"
#include <QMessageBox>
#include "FramelessHelper/FramelessHelper.h"

DHGenerator::DHGenerator(QWidget* parent)
	: QMainWindow(parent, Qt::FramelessWindowHint)
{
	ui->setupUi(this);
	setFixedSize(500,300);
	this->setWindowTitle("Popsicle DH Key Generator");
	FramelessHelper* helper = new FramelessHelper(this);
	helper->setTitleBarHeight(40);
	helper->addExcludeItem(ui->closebutton);
	helper->addExcludeItem(ui->minbutton);

	QString ver = QSysInfo::productVersion();
	//qDebug() << ver;
	//emit notify(ver);
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

	// Material Button
	QtMaterialRaisedButton* gen = new QtMaterialRaisedButton;
	gen->setText("Generate");
	gen->setHaloVisible(false);
	gen->setBackgroundColor("#03a9f4");
	//send->setIcon(QIcon(":/res/send.svg"));
	gen->setFont(QFont("Arial"));
	gen->setFontSize(10);
	//NetSignal* n = new NetSignal(this->ui);
	connect(gen, &QtMaterialRaisedButton::clicked, this, &DHGenerator::gen_clicked);
	ui->verticalLayout->addWidget(gen);
}


void DHGenerator::on_closebutton_clicked() {
	close();
	exit(0);
}

void DHGenerator::on_minbutton_clicked() { showMinimized(); }

void DHGenerator::gen_clicked()
{
	Util::gen_dh_key_file("");
	QMessageBox::information(this, "Info", "Generate Success");
}
