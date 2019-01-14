#include "mainwindow.h"

mainwindow::mainwindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	cwidget = new QWidget(this);
	setCentralWidget(cwidget);
	setWindowTitle("Enter your age");

	spinBox = new QSpinBox(cwidget);
	slider = new QSlider(Qt::Horizontal, cwidget);
	spinBox->setRange(0, 130);
	slider->setRange(0, 130);

	QObject::connect(slider, &QSlider::valueChanged, spinBox, &QSpinBox::setValue);
	void (QSpinBox:: *spinBoxSignal)(int) = &QSpinBox::valueChanged;
	QObject::connect(spinBox, spinBoxSignal, slider, &QSlider::setValue);
	spinBox->setValue(35);

	text = new QTextEdit(cwidget);
	text->installEventFilter(this);

	layout = new QHBoxLayout;
	layout->addWidget(spinBox);
	layout->addWidget(slider);
	cwidget->setLayout(layout);
}

void QWidget::keyPressEvent(QKeyEvent *event) {
	QMessageBox::information(this, "222", "222");
}

void QTextEdit::keyPressEvent(QKeyEvent *event) {
	QMessageBox::information(this, "11", "111");
}

bool mainwindow::eventFilter(QObject *obj, QEvent *event) {
	if (obj == text)
		if (event->type() == QEvent::KeyPress) {
			event->ignore();
			return true;
		}
		else return false;
}
