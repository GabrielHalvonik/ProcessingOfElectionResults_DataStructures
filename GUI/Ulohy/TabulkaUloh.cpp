#include "TabulkaUloh.h"
#include <QDebug>
#include <QKeyEvent>

TabulkaUloh::TabulkaUloh(Structures::SortedSequenceTable<int, UzemnaJednotka*>* jednotky,
						 Structures::SortedSequenceTable<int, PolitickySubjekt*>* subjekty,
						 QWidget* parent) : TableWidget(parent), tabulka(new TableWidget),
											jednotky(jednotky), subjekty(subjekty) {


}

TabulkaUloh::~TabulkaUloh() {
	delete this->tabulka;
	this->tabulka = nullptr;
}

void TabulkaUloh::keyPressEvent(QKeyEvent* event) {
	if (event->key() == Qt::Key_Enter) {
		this->filtruj();
	}
	QWidget::keyPressEvent(event);
}
