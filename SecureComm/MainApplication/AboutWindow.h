#pragma once

#include <QMainWindow>

namespace Ui
{
	class AboutWindow;
};

class AboutWindow : public QMainWindow
{
Q_OBJECT

public:
	AboutWindow(QWidget* parent = Q_NULLPTR);
	~AboutWindow();

private:
	Ui::AboutWindow* ui;

protected:
	bool event(QEvent* event) final;
	void closeEvent(QCloseEvent* event) override;

private slots:

	void on_closebutton_clicked();
	void on_maxbutton_clicked();
	void on_minbutton_clicked();
	void anchorClickedSlot(const QUrl& url);
};
