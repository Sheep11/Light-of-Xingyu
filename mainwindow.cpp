#include "mainwindow.h"

mainwindow::mainwindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	
	QLabel *queslabel = new QLabel("Question", ui.centralWidget);
	QLabel *anslabel = new QLabel("Answer", ui.centralWidget);
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
	QStringList header;
	header << tr("Question") << tr("Correct Answer") << tr("Your Answer");
	hislist->setHorizontalHeaderLabels(header);
	
	//���ñ�ͷ����Ӵ�
	QFont font = hislist->horizontalHeader()->font();
	font.setBold(true);
	hislist->horizontalHeader()->setFont(font);

	hislist->horizontalHeader()->setStretchLastSection(true); //���ó�������
	hislist->horizontalHeader()->resizeSection(0, 400);
	hislist->verticalHeader()->setDefaultSectionSize(10); //�����и�
	hislist->setFrameShape(QFrame::NoFrame); //�����ޱ߿�
	hislist->setShowGrid(false); //���ò���ʾ������
	hislist->verticalHeader()->setVisible(false); //���ô�ֱͷ���ɼ�
	hislist->setEditTriggers(QAbstractItemView::NoEditTriggers); //���ò��ɱ༭
	hislist->horizontalHeader()->setFixedHeight(25); //���ñ�ͷ�ĸ߶�


	QGridLayout *glayout = new QGridLayout(ui.centralWidget);
	glayout->addWidget(queslabel, 0, 0, 1, 2);
	glayout->addWidget(anslabel, 0, 10, 1, 2);
	glayout->addWidget(quesedit, 1, 0, 2, 7);
	glayout->addWidget(ansedit, 1, 10, 2, 3);
	glayout->addWidget(enterbutton, 1, 14, 2, 3);
	glayout->addWidget(line, 4, 0, 3, 17);
	glayout->addWidget(hislabel, 6, 0, 1, 2);
	glayout->addWidget(resttime, 6, 10, 1, 2);
	glayout->addWidget(hislist, 7, 0, 7, 11);

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

void mainwindow::onEnterClicked() {
	time = 20;
	timer->setInterval(1000);

	int count = hislist->rowCount();
	hislist->insertRow(count);

	hislist->setItem(count, 0, new QTableWidgetItem(QString::fromStdString(f.problem)));
	hislist->setItem(count, 1, new QTableWidgetItem(QString::fromStdString(f.answer)));
	QTableWidgetItem *ansitem = new QTableWidgetItem(ansedit->text());
	if (ansedit->text().toStdString() != f.answer)
		ansitem->setTextColor(Qt::red);
	hislist->setItem(count, 2, ansitem);
	ansitem->textColor();
	ansedit->clear();

	f = gen->get_formula();
	quesedit->setText(QString::fromStdString(f.problem));
}


