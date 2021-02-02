#include "MainWindow.h"
#include <QKeyEvent>
#include <QDebug>
#include "Ulohy/TabulkaUlohPrva.h"
#include "Ulohy/TabulkaUlohDruha.h"


MainWindow::MainWindow(SortedSequenceTable<int, UzemnaJednotka*>* jednotky, SortedSequenceTable<int, PolitickySubjekt*>* subjekty, QWidget* parent) :
	QMainWindow(parent),
	uloha(0),
	bar(new ToolBar),
	jednotky(jednotky),
	subjekty(subjekty) {

	this->ulohy = new TabulkaUloh*[2];
	this->ulohy[0] = new TabulkaUlohPrva(this->jednotky, nullptr);
	this->ulohy[1] = new TabulkaUlohDruha(this->jednotky, this->subjekty);

	this->addToolBar(Qt::ToolBarArea::BottomToolBarArea, this->bar);

	QObject::connect(bar, &ToolBar::stlacene, this, &MainWindow::reaguj);

	this->nastavPaletu();
}

MainWindow::~MainWindow() {
	for ( Structures::TableItem<int, UzemnaJednotka*>* temp : *this->jednotky) {
		delete temp->accessData();
		temp->accessData() = nullptr;
	}
	for ( Structures::TableItem<int, PolitickySubjekt*>* temp : *this->subjekty) {
		delete temp->accessData();
		temp->accessData() = nullptr;
	}
	delete this->bar;
	this->bar = nullptr;
	delete this->ulohy[0];
	this->ulohy[0] = nullptr;
	delete this->ulohy[1];
	this->ulohy[1] = nullptr;
	delete this->ulohy;
	this->ulohy = nullptr;
}

TableWidget* MainWindow::getTable() const {
	return this->ulohy[uloha];
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
	if (event->key() == Qt::Key::Key_Space) {
		this->ulohy[uloha]->filtruj();
	}
}

void MainWindow::nastavPaletu()
{
	QPalette pal;
	pal.setBrush(QPalette::ColorRole::Window, QColor(30, 24, 40));
	pal.setBrush(QPalette::ColorRole::Base, QColor(24, 20, 30));
	pal.setColor(QPalette::ColorRole::Text, QColor(230, 220, 230));
	this->setPalette(pal);
}

void MainWindow::reaguj(int k) {
	this->uloha = k;
	this->takeCentralWidget();
	this->setCentralWidget(this->ulohy[k]);
	this->nastavPaletu();
}
