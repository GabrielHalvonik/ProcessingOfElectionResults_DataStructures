#include "ToolBar.h"

#include <QToolButton>
#include <QDebug>

ToolBar::ToolBar(QWidget* parent) : QToolBar(parent), btnGroup(new QButtonGroup) {
	QToolButton* btn = new QToolButton;
	QToolButton* btn2 = new QToolButton;
	btn->setFixedSize(100, 20);
	btn2->setFixedSize(100, 20);
	btn->setText(QString("Uloha 1 - 4"));
	btn2->setText(QString("Uloha 5 - 8"));
	this->addWidget(btn);
	this->addWidget(btn2);
	btnGroup->addButton(btn, 0);
	btnGroup->addButton(btn2, 1);
	QPalette pal;
	pal.setBrush(QPalette::ColorRole::Window, QColor(30, 24, 40));
	pal.setBrush(QPalette::ColorRole::Base, QColor(24, 20, 30));
	pal.setBrush(QPalette::ColorRole::Button, QColor(24, 20, 30));
	pal.setColor(QPalette::ColorRole::Text, QColor(230, 220, 230));
	this->setPalette(pal);
	QObject::connect(btnGroup, SIGNAL(buttonClicked(int)), this, SIGNAL(stlacene(int)));
}

ToolBar::~ToolBar() {
	delete this->btnGroup;
	this->btnGroup = nullptr;
}

