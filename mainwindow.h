#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"

#include<qlayout.h>
#include<qmessagebox.h>
#include<qtextedit.h>
#include<qlineedit.h>
#include<qtimer.h>
#include<qlabel.h>
#include<qline.h>
#include<qtablewidget.h>
#include<qpushbutton.h>
#include<qheaderview.h>
#include<qcheckbox.h>
#include<qdatetime.h>
#include<qtooltip.h>
#include<string>
#include"class.h"

#pragma execution_character_set("utf-8")

class mainwindow : public QMainWindow
{
	Q_OBJECT

public:
	mainwindow(QWidget *parent = Q_NULLPTR);
	QLineEdit *ansedit;
	QLineEdit *quesedit;
	QLabel *resttime;
	QPushButton *enterbutton;

	QCheckBox *modebox;
	int display_mode;

	int time;
	QTimer *timer;
	QLabel *ratelabel;
	QTableWidget *hislist;
	QTableWidget *scorelist;

	formula f;
	generator *gen;

	int all_count, right_count;

protected:
	void onEnterClicked();
	void onTimeOut();
	void onTypeChanged();
	void onStartClicked();
	void onEndClicked();
	void onTipClicked();

private:
	Ui::mainwindowClass ui;
};
