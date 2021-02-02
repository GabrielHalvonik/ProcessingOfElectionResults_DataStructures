#include "TabulkaUlohPrva.h"

#include <QHeaderView>
#include <QInputDialog>
#include <QDebug>
#include <iostream>

#include <Table/Sorting/QuickSort.h>

TabulkaUlohPrva::TabulkaUlohPrva(Structures::SortedSequenceTable<int, UzemnaJednotka*>* jednotky,
								 Structures::SortedSequenceTable<int, PolitickySubjekt*>* subjekty,
								 QWidget* parent) : TabulkaUloh(jednotky, subjekty, parent),
								 unsortedTable(new Structures::UnsortedSequenceTable<int, UzemnaJednotka*>(*jednotky)),
								 actualTable(unsortedTable),
								 activeFilter(nullptr),
	columnNames({"Obec", "Okres", "Kraj", "Ucast", "Volici", "Zucastneni", "ObalkyOsobne", "ObalkyCudzina", "ObalkySpolu", "PodielPlatnych"}) {

	this->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::Interactive);

	this->zobrazTabulku(this->jednotky);
	this->setColumnWidth(0, 210);
	this->setColumnWidth(1, 175);
	this->setColumnWidth(2, 190);
	this->setColumnWidth(3, 95);
	this->setColumnWidth(4, 95);
	this->setColumnWidth(5, 110);
	this->setColumnWidth(6, 145);
	this->setColumnWidth(7, 145);
	this->setColumnWidth(8, 130);
	this->setColumnWidth(9, 140);


	QObject::connect(this->horizontalHeader(), &QHeaderView::sectionDoubleClicked, this, [=](int k) {
		Structures::QuickSort<int, UzemnaJednotka*> sort;
		switch (k) {
			case 0 :
				sort.sort(*this->actualTable, Comparator<std::wstring, UzemnaJednotka*>(this->asc[0], kriteria.kritNazovObecUJ));
				this->asc[0] = !this->asc[0];
				break;
			case 1 :
				sort.sort(*this->actualTable, Comparator<std::wstring, UzemnaJednotka*>(this->asc[1], kriteria.kritNazovOkresUJ));
				this->asc[1] = !this->asc[1];
				break;
			case 2 :
				sort.sort(*this->actualTable, Comparator<std::wstring, UzemnaJednotka*>(this->asc[2], kriteria.kritNazovKrajUJ));
				this->asc[2] = !this->asc[2];
				break;
			case 3 :
				sort.sort(*this->actualTable, Comparator<double, UzemnaJednotka*>(this->asc[3], kriteria.kritUcastUJ));
				this->asc[3] = !this->asc[3];
				break;
			case 4 :
				sort.sort(*this->actualTable, Comparator<int, UzemnaJednotka*>(this->asc[4], kriteria.kritVoliciUJ));
				this->asc[4] = !this->asc[4];
				break;
			case 5 :
				sort.sort(*this->actualTable, Comparator<int, UzemnaJednotka*>(this->asc[5], kriteria.kritZucastneniUJ));
				this->asc[5] = !this->asc[5];
				break;
			case 6 :
				sort.sort(*this->actualTable, Comparator<int, UzemnaJednotka*>(this->asc[6], kriteria.kritObalkyOsobneUJ));
				this->asc[6] = !this->asc[6];
				break;
			case 7 :
				sort.sort(*this->actualTable, Comparator<int, UzemnaJednotka*>(this->asc[7], kriteria.kritObalkyCudzinaUJ));
				this->asc[7] = !this->asc[7];
				break;
			case 8 :
				sort.sort(*this->actualTable, Comparator<int, UzemnaJednotka*>(this->asc[8], kriteria.kritObalkySpoluUJ));
				this->asc[8] = !this->asc[8];
				break;
			case 9 :
				sort.sort(*this->actualTable, Comparator<double, UzemnaJednotka*>(this->asc[9], kriteria.kritPodielPlatnychUJ));
				this->asc[9] = !this->asc[9];
				break;
		}

		this->zobrazTabulku(this->actualTable);});

	QObject::connect(this->horizontalHeader(), &QHeaderView::sectionClicked, this, [=](int k) {
		bool ok;
		QString vstup = QInputDialog::getText(this, "Filter", "Zadajte kriterium", QLineEdit::Normal, {}, &ok);
		if (ok && !vstup.isEmpty()) {
			Filter<UzemnaJednotka>* fi;
			switch (k) {
				case 0 :
					fi = new FilterValue<UzemnaJednotka, std::wstring>(kriteria.kritNazovObecUJ, vstup.toStdWString());
					break;
				case 1 :
					fi = new FilterValue<UzemnaJednotka, std::wstring>(kriteria.kritNazovOkresUJ, vstup.toStdWString());
					break;
				case 2 :
					fi = new FilterValue<UzemnaJednotka, std::wstring>(kriteria.kritNazovKrajUJ, vstup.toStdWString());
					break;
				case 3 :
					if (!vstup.contains(">>")) {
						fi = new FilterValue<UzemnaJednotka, double>(kriteria.kritUcastUJ, vstup.toDouble());
					} else {
						fi = new FilterRange<UzemnaJednotka, double>(kriteria.kritUcastUJ, vstup.split(">>").at(0).toDouble(), vstup.split(">>").at(1).toDouble());
					}
					break;
				case 4 :
					if (!vstup.contains(">>")) {
						fi = new FilterValue<UzemnaJednotka, int>(kriteria.kritVoliciUJ, vstup.toDouble());
					} else {
						fi = new FilterRange<UzemnaJednotka, int>(kriteria.kritVoliciUJ, vstup.split(">>").at(0).toInt(), vstup.split(">>").at(1).toInt());
					}
					break;
				case 5 :
					if (!vstup.contains(">>")) {
						fi = new FilterValue<UzemnaJednotka, int>(kriteria.kritZucastneniUJ, vstup.toDouble());
					} else {
						fi = new FilterRange<UzemnaJednotka, int>(kriteria.kritZucastneniUJ, vstup.split(">>").at(0).toInt(), vstup.split(">>").at(1).toInt());
					}
					break;
			}

			if (this->activeFilter != nullptr) {
				FilterAnd<UzemnaJednotka>* filAnd = new FilterAnd(*this->activeFilter, *fi);
				this->filStack.push(fi);
				this->activeFilter = filAnd;
			} else {
				this->activeFilter = fi;
			}
			this->filStack.push(this->activeFilter);
		}});



}

TabulkaUlohPrva::~TabulkaUlohPrva() {
	if (this->actualTable != nullptr && this->actualTable != this->unsortedTable) {
		delete this->actualTable;
		this->actualTable = nullptr;
	}
	delete this->unsortedTable;
	this->unsortedTable = nullptr;
	while (!this->filStack.isEmpty()) {
		if (this->filStack.peek() != nullptr) {
			delete this->filStack.pop();
		} else {
			this->filStack.pop();
		}
	}
}

void TabulkaUlohPrva::filtruj() {
	if (this->activeFilter != nullptr) {
		if (this->actualTable != nullptr && this->actualTable != this->unsortedTable) {
			delete this->actualTable;
		}
		this->actualTable = new Structures::UnsortedSequenceTable<int, UzemnaJednotka*>(this->activeFilter->vyfiltruj(*this->unsortedTable));
	} else {
		if (this->actualTable != nullptr && this->actualTable != this->unsortedTable) {
			delete this->actualTable;
		}
		this->actualTable = this->unsortedTable;
	}
	this->zobrazTabulku(this->actualTable);
}

void TabulkaUlohPrva::zobrazTabulku(Structures::SequenceTable<int, UzemnaJednotka*>* tabulka) {
	if (this->activeFilter) {
		this->activeFilter = nullptr;
	}
	this->clear();
	this->setColumnCount(this->columnNames.size());
	this->setHorizontalHeaderLabels(this->columnNames);
	int row = 0;
	int column = 0;

	this->setRowCount(tabulka->size());

	for (Structures::TableItem<int, UzemnaJednotka*>* temp : *tabulka) {
		column = 0;
		this->setItem(row, column++, new QTableWidgetItem(QString::fromStdWString(kriteria.kritNazovObecUJ(temp->accessData()))));
		this->setItem(row, column++, new QTableWidgetItem(QString::fromStdWString(kriteria.kritNazovOkresUJ(temp->accessData()))));
		this->setItem(row, column++, new QTableWidgetItem(QString::fromStdWString(kriteria.kritNazovKrajUJ(temp->accessData()))));
		this->setItem(row, column++, new QTableWidgetItem(QString::number(kriteria.kritUcastUJ(temp->accessData()), 'f', 2)));
		this->setItem(row, column++, new QTableWidgetItem(QString("%1").arg(kriteria.kritVoliciUJ(temp->accessData()))));
		this->setItem(row, column++, new QTableWidgetItem(QString("%1").arg(kriteria.kritZucastneniUJ(temp->accessData()))));
		this->setItem(row, column++, new QTableWidgetItem(QString("%1").arg(kriteria.kritObalkyOsobneUJ(temp->accessData()))));
		this->setItem(row, column++, new QTableWidgetItem(QString("%1").arg(kriteria.kritObalkyCudzinaUJ(temp->accessData()))));
		this->setItem(row, column++, new QTableWidgetItem(QString("%1").arg(kriteria.kritObalkySpoluUJ(temp->accessData()))));
		this->setItem(row++, column, new QTableWidgetItem(QString::number(kriteria.kritPodielPlatnychUJ(temp->accessData()), 'f', 2)));
	}
}
