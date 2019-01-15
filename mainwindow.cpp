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
	//���ñ�ͷ����Ӵ�
	QFont font = hislist->horizontalHeader()->font();
	font.setBold(true);
	hislist->horizontalHeader()->setFont(font);

	hislist->horizontalHeader()->setStretchLastSection(true); //���ó�������
	hislist->verticalHeader()->setDefaultSectionSize(10); //�����и�
	hislist->setFrameShape(QFrame::NoFrame); //�����ޱ߿�
	hislist->setShowGrid(false); //���ò���ʾ������
	hislist->verticalHeader()->setVisible(false); //���ô�ֱͷ���ɼ�
	hislist->setEditTriggers(QAbstractItemView::NoEditTriggers); //���ò��ɱ༭
	hislist->horizontalHeader()->setFixedHeight(25); //���ñ�ͷ�ĸ߶�
	hislist->setStyleSheet("selection-background-color:lightblue;"); //����ѡ�б���ɫ


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
