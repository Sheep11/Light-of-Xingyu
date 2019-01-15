#include "mainwindow.h"

mainwindow::mainwindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	
	QLabel *queslabel = new QLabel("Question", ui.centralWidget);
	QLabel *anslabel = new QLabel("Answer", ui.centralWidget);
	QLineEdit *quesedit = new QLineEdit(ui.centralWidget);
	quesedit->setEnabled(false);
	quesedit->setFixedHeight(50);
	QLineEdit *ansedit = new QLineEdit(ui.centralWidget);
	ansedit->setFixedHeight(50);
	QFrame *line = new QFrame(ui.centralWidget);
	line->setFrameShape(QFrame::HLine);
	line->setFrameShadow(QFrame::Sunken);
	QPushButton *enterbutton = new  QPushButton("Enter", ui.centralWidget);
	enterbutton->setFixedHeight(50);

	QLabel *hislabel = new QLabel("History", ui.centralWidget);
	QTableWidget *hislist = new QTableWidget(ui.centralWidget);
	QStringList *header = new QStringList();
	*header << "1" << "2" << "3";
	
	hislist->setColumnCount(3);
	//设置表头字体加粗
	QFont font = hislist->horizontalHeader()->font();
	font.setBold(true);
	hislist->horizontalHeader()->setFont(font);

	hislist->horizontalHeader()->setStretchLastSection(true); //设置充满表宽度
	hislist->verticalHeader()->setDefaultSectionSize(10); //设置行高
	hislist->setFrameShape(QFrame::NoFrame); //设置无边框
	hislist->setShowGrid(false); //设置不显示格子线
	hislist->verticalHeader()->setVisible(false); //设置垂直头不可见
	hislist->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置不可编辑
	hislist->horizontalHeader()->setFixedHeight(25); //设置表头的高度
	hislist->setStyleSheet("selection-background-color:lightblue;"); //设置选中背景色


	QGridLayout *glayout = new QGridLayout(ui.centralWidget);
	glayout->addWidget(queslabel, 0, 0, 1, 2);
	glayout->addWidget(anslabel, 0, 10, 1, 2);
	glayout->addWidget(quesedit, 1, 0, 2, 7);
	glayout->addWidget(ansedit, 1, 10, 2, 3);
	glayout->addWidget(enterbutton, 1, 14, 2, 3);
	glayout->addWidget(line, 4, 0, 3, 17);
	glayout->addWidget(hislabel, 6, 0, 1, 2);
	glayout->addWidget(hislist, 7, 0, 7, 9);
	
	hislist->insertRow(0);
	hislist->insertRow(1);
	hislist->setItem(0, 0, new QTableWidgetItem("123"));
	hislist->setItem(1, 0, new QTableWidgetItem("123"));

	timer = new QTimer(ui.centralWidget);
	connect(timer, &QTimer::timeout, this, &mainwindow::onTimeOut);
	timer->start(20000);
}

void mainwindow::onTimeOut()
{
	//undo
}
