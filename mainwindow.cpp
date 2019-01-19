#include "mainwindow.h"

mainwindow::mainwindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	
	QLabel *queslabel = new QLabel("Question", ui.centralWidget);
	QLabel *anslabel = new QLabel("Answer", ui.centralWidget);
	modebox = new QCheckBox("Switch Display Mode", ui.centralWidget);
	connect(modebox, &QCheckBox::stateChanged, this, &mainwindow::onTypeChanged);
	
	quesedit = new QLineEdit(ui.centralWidget);
	quesedit->setEnabled(false);
	quesedit->setFixedHeight(50);
	ansedit = new QLineEdit(ui.centralWidget);
	ansedit->setEnabled(false);
	ansedit->setFixedHeight(50);
	connect(ansedit, &QLineEdit::returnPressed, this, &mainwindow::onEnterClicked);
	QFrame *line = new QFrame(ui.centralWidget);
	line->setFrameShape(QFrame::HLine);
	line->setFrameShadow(QFrame::Sunken);
	enterbutton = new  QPushButton("Enter", ui.centralWidget);
	enterbutton->setEnabled(false);
	enterbutton->setFixedHeight(50);
	connect(enterbutton, &QPushButton::clicked, this, &mainwindow::onEnterClicked);
	resttime = new QLabel(ui.centralWidget);

	QPushButton *startbutton = new QPushButton("Start", ui.centralWidget);
	connect(startbutton, &QPushButton::clicked, this, &mainwindow::onStartClicked);
	QPushButton *endbutton = new QPushButton("End", ui.centralWidget);
	connect(endbutton, &QPushButton::clicked, this, &mainwindow::onEndClicked);

	QLabel *hislabel = new QLabel("History", ui.centralWidget);

	hislist = new QTableWidget(ui.centralWidget);
	hislist->setColumnCount(3);
	ratelabel = new QLabel("Correct Rate:", ui.centralWidget);
	QStringList header = { "Questioni","Correct Answer","Your Answer" };
	hislist->setHorizontalHeaderLabels(header);
	QFont font = hislist->horizontalHeader()->font();
	font.setBold(true);
	hislist->horizontalHeader()->setFont(font);
	hislist->horizontalHeader()->setStretchLastSection(true); //设置充满表宽度
	hislist->horizontalHeader()->resizeSection(0, 200);
	hislist->verticalHeader()->setDefaultSectionSize(10); //设置行高
	hislist->setFrameShape(QFrame::NoFrame); //设置无边框
	hislist->setShowGrid(false); //设置不显示格子线
	hislist->verticalHeader()->setVisible(false); //设置垂直头不可见
	hislist->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置不可编辑
	hislist->horizontalHeader()->setFixedHeight(25); //设置表头的高度

	scorelist = new QTableWidget(ui.centralWidget);
	scorelist->setColumnCount(2);
	scorelist->horizontalHeader()->setStretchLastSection(true);
	scorelist->setHorizontalHeaderLabels(QStringList({ "Data","Score" }));

	QGridLayout *glayout = new QGridLayout(ui.centralWidget);
	glayout->addWidget(queslabel, 0, 0, 1, 1);
	glayout->addWidget(anslabel, 0, 10, 1, 1);
	glayout->addWidget(resttime, 1, 4, 1, 2);
	glayout->addWidget(modebox, 1, 0, 1, 2);
	glayout->addWidget(quesedit, 2, 0, 2, 7);
	glayout->addWidget(ansedit, 2, 10, 2, 3);
	glayout->addWidget(enterbutton, 2, 14, 2, 3);
	glayout->addWidget(startbutton, 4, 3, 1, 2);
	glayout->addWidget(endbutton, 4, 9, 1, 2);
	glayout->addWidget(line, 4, 0, 3, 17);
	glayout->addWidget(hislabel, 6, 0, 1, 2);
	glayout->addWidget(ratelabel, 6, 4, 1, 1);
	glayout->addWidget(hislist, 7, 0, 7, 8);
	glayout->addWidget(scorelist, 7, 9, 7, 7);

	gen = new generator();
	
	timer = new QTimer(ui.centralWidget);
	connect(timer, &QTimer::timeout, this, &mainwindow::onTimeOut);
}

void mainwindow::onTimeOut()
{
	if (0 == time--)
		onEnterClicked();

	string str = "RestTime:" + std::to_string(time) + "s";
	resttime->setText(QString::fromStdString(str));
}

void mainwindow::onTypeChanged()
{
	display_mode = !display_mode;
}

void mainwindow::onStartClicked()
{
	f = gen->get_formula();
	quesedit->setText(QString::fromStdString(f.problem));

	ansedit->setEnabled(true);
	for (int i = hislist->rowCount(); i >= 0; i--)
		hislist->removeRow(i);

	time = 20;
	timer->start(1000);
	all_count = 0; right_count = 0;

	enterbutton->setEnabled(true);
}

void mainwindow::onEndClicked()
{
	ansedit->setEnabled(false);

	timer->stop();
	enterbutton->setEnabled(false);

	int count = scorelist->rowCount();
	scorelist->insertRow(count);
	scorelist->setItem(count, 0, new QTableWidgetItem(QDateTime::currentDateTime().toString()));
	scorelist->setItem(count, 1, new QTableWidgetItem(ratelabel->text()));
}

void mainwindow::onEnterClicked() {
	all_count++;	//增加做题总数

	//重置剩余时间
	time = 20;
	timer->setInterval(1000);

	//动态插入列表
	int count = hislist->rowCount();
	hislist->insertRow(count);
	hislist->setItem(count, 0, new QTableWidgetItem(QString::fromStdString(f.problem)));
	hislist->setItem(count, 1, new QTableWidgetItem(QString::fromStdString(f.answer)));
	QTableWidgetItem *ansitem = new QTableWidgetItem(ansedit->text());
	//判断正误
	if (ansedit->text().toStdString() != f.answer)
		ansitem->setTextColor(Qt::red);
	else
		right_count++;
	hislist->setItem(count, 2, ansitem);
	ansitem->textColor();
	ansedit->clear();

	//生成新题目
	f = gen->get_formula(display_mode);
	quesedit->setText(QString::fromStdString(f.problem));

	//更新正确率
	string rate_str = "Correct Rate:" + std::to_string(right_count) + "/" + std::to_string(all_count);
	ratelabel->setText(QString::fromStdString(rate_str));
}


