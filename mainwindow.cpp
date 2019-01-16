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
	ansedit->setFixedHeight(50);
	connect(ansedit, &QLineEdit::returnPressed, this, &mainwindow::onEnterClicked);
	QFrame *line = new QFrame(ui.centralWidget);
	line->setFrameShape(QFrame::HLine);
	line->setFrameShadow(QFrame::Sunken);
	QPushButton *enterbutton = new  QPushButton("Enter", ui.centralWidget);
	enterbutton->setFixedHeight(50);
	connect(enterbutton, &QPushButton::clicked, this, &mainwindow::onEnterClicked);
	resttime = new QLabel(ui.centralWidget);

	QLabel *hislabel = new QLabel("History", ui.centralWidget);
	hislist = new QTableWidget(ui.centralWidget);
	hislist->setColumnCount(3);
	ratelabel = new QLabel("Correct Rate:", ui.centralWidget);
	QStringList header;
	header << tr("Question") << tr("Correct Answer") << tr("Your Answer");
	hislist->setHorizontalHeaderLabels(header);
	
	//设置表头字体加粗
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


	QGridLayout *glayout = new QGridLayout(ui.centralWidget);
	glayout->addWidget(queslabel, 0, 0, 1, 1);
	glayout->addWidget(anslabel, 0, 10, 1, 1);
	glayout->addWidget(resttime, 1, 4, 1, 2);
	glayout->addWidget(modebox, 1, 0, 1, 2);
	glayout->addWidget(quesedit, 2, 0, 2, 7);
	glayout->addWidget(ansedit, 2, 10, 2, 3);
	glayout->addWidget(enterbutton, 2, 14, 2, 3);
	glayout->addWidget(line, 4, 0, 3, 17);
	glayout->addWidget(hislabel, 6, 0, 1, 2);
	glayout->addWidget(ratelabel, 6, 4, 1, 1);
	glayout->addWidget(hislist, 7, 0, 7, 8);

	gen = new generator();
	f = gen->get_formula();
	quesedit->setText(QString::fromStdString(f.problem));
	
	timer = new QTimer(ui.centralWidget);
	connect(timer, &QTimer::timeout, this, &mainwindow::onTimeOut);
	time = 20;
	timer->start(1000);
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

void mainwindow::onEnterClicked() {
	all_count++;

	time = 20;
	timer->setInterval(1000);

	int count = hislist->rowCount();
	hislist->insertRow(count);

	hislist->setItem(count, 0, new QTableWidgetItem(QString::fromStdString(f.problem)));
	hislist->setItem(count, 1, new QTableWidgetItem(QString::fromStdString(f.answer)));
	QTableWidgetItem *ansitem = new QTableWidgetItem(ansedit->text());
	if (ansedit->text().toStdString() != f.answer)
		ansitem->setTextColor(Qt::red);
	else
		right_count++;
	hislist->setItem(count, 2, ansitem);
	ansitem->textColor();
	ansedit->clear();

	f = gen->get_formula(display_mode);
	quesedit->setText(QString::fromStdString(f.problem));

	string rate_str = "Correct Rate:" + std::to_string(right_count) + "/" + std::to_string(all_count);
	ratelabel->setText(QString::fromStdString(rate_str));
}


