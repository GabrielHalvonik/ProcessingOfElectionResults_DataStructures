#include "TableWidget.h"
#include <QHeaderView>

TableWidget::TableWidget(QWidget* parent) : QTableWidget(parent) {
	this->setEditTriggers(QAbstractItemView::NoEditTriggers);

	QPalette pal;
	pal.setBrush(QPalette::ColorRole::Window, QColor(20, 20, 20));
	pal.setBrush(QPalette::ColorRole::Base, QColor(24, 20, 30));
	pal.setBrush(QPalette::ColorRole::AlternateBase, QColor(30, 24, 40));
	pal.setBrush(QPalette::ColorRole::Mid, QColor(200, 20, 20));
	pal.setBrush(QPalette::ColorRole::Text, QColor(200, 200, 200));
	pal.setBrush(QPalette::ColorRole::Button, QColor("#651fff"));
	pal.setBrush(QPalette::ColorRole::ButtonText, QColor(200, 200, 200));

	this->setFont(QFont({}, 18));

	this->horizontalHeader()->setPalette(pal);
	this->verticalHeader()->setVisible(false);
	this->setPalette(pal);
	this->setSortingEnabled(false);
	this->horizontalHeader()->setResizeContentsPrecision(1);

	this->horizontalHeader()->setPalette(pal);
	this->horizontalHeader()->setFixedHeight(30);

	this->setShowGrid(false);
	this->setAlternatingRowColors(true);

}
