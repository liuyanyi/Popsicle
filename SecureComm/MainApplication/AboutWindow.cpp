#include "AboutWindow.h"
#include "FramelessHelper.h"
#include "ui_AboutWindow.h"
#include <QFileDialog>
#include <QTextCodec>
#include <QTextStream>
#include "qtmaterialscrollbar.h"
#include <Windows.h>

AboutWindow::AboutWindow(QWidget* parent)
	: QMainWindow(parent, Qt::FramelessWindowHint)
{
	ui = new Ui::AboutWindow();
	ui->setupUi(this);

	QFile file(":/res/About.html");

	if (file.open(QFile::ReadOnly | QFile::Text))
	{
		QTextStream textStream(&file);
		textStream.setCodec(QTextCodec::codecForName("utf-8"));
		ui->textBrowser->setHtml((textStream.readAll()));
	}

	// Material滚动条
	QtMaterialScrollBar* mscrollerbar = new QtMaterialScrollBar;
	mscrollerbar->setHideOnMouseOut(false);
	mscrollerbar->setSliderColor(QColor("#ff80ab"));

	ui->textBrowser->setVerticalScrollBar(static_cast<QScrollBar*>(mscrollerbar));

	ui->textBrowser->setOpenLinks(false);
	connect(ui->textBrowser, &QTextBrowser::anchorClicked, this, &AboutWindow::anchorClickedSlot);

	//无边窗口
	this->setWindowTitle("About");
	FramelessHelper* helper = new FramelessHelper(this);
	helper->setDraggableMargins(3, 3, 3, 3);
	helper->setMaximizedMargins(3, 3, 3, 3);
	helper->setTitleBarHeight(40);
	helper->addExcludeItem(ui->closebutton);
	helper->addExcludeItem(ui->minbutton);
	helper->addExcludeItem(ui->maxbutton);
	// helper->addExcludeItem(ui->toolButton);
	ui->maxbutton->setIcon(
		QIcon(QStringLiteral(":/res/extra/maximize-button1.png")));
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
	else
	{
		ui->centralWidget->setStyleSheet(
			"#centralWidget{"
			"background-color: rgb(250, 250, 250);"
			"}");
	}
}

bool AboutWindow::event(QEvent* event)
{
	if (event->type() == QEvent::WindowStateChange)
	{
		if (windowState() & Qt::WindowMaximized)
		{
			ui->maxbutton->setIcon(
				QIcon(QStringLiteral(":/res/extra/maximize-button2.png")));
			ui->maxbutton->setToolTip(tr("Restore"));
		}
		else
		{
			ui->maxbutton->setIcon(
				QIcon(QStringLiteral(":/res/extra/maximize-button1.png")));
			ui->maxbutton->setToolTip(tr("Maximize"));
		}
	}

	return QWidget::event(event);
}

void AboutWindow::closeEvent(QCloseEvent* event)
{
	delete this;
	//|窗口关闭之前需要的操作~
}

AboutWindow::~AboutWindow()
{
	delete ui;
}

void AboutWindow::on_closebutton_clicked()
{
	close();
}

void AboutWindow::on_maxbutton_clicked()
{
	if (windowState() & Qt::WindowMaximized)
	{
		showNormal();
	}
	else
	{
		showMaximized();
	}
}

void AboutWindow::on_minbutton_clicked() { showMinimized(); }

void AboutWindow::anchorClickedSlot(const QUrl& url)
{
	ShellExecuteA(nullptr, "open", url.toString().toStdString().c_str(), "", "", SW_SHOW);
}
