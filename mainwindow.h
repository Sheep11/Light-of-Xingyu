#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"

#include<qspinbox.h>
#include<qslider.h>
#include<qlayout.h>
#include<qmessagebox.h>
#include<qtextedit.h>

class mainwindow : public QMainWindow
{
	Q_OBJECT

public:
	mainwindow(QWidget *parent = Q_NULLPTR);
	QSpinBox *spinBox;
	QSlider *slider;
	QTextEdit *text;
	QWidget *cwidget;
	QHBoxLayout *layout;

protected:
	bool eventFilter(QObject *obj, QEvent *event);

private:
	Ui::mainwindowClass ui;
};
