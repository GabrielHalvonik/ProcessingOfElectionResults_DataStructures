#include "TabulkaUlohDruha.h"

#include "Table/Sorting/QuickSort.h"
#include <QHeaderView>
#include <QInputDialog>
#include <QKeyEvent>
#include <QDebug>

TabulkaUlohDruha::TabulkaUlohDruha(Structures::SortedSequenceTable<int, UzemnaJednotka*>* jednotky,
								   Structures::SortedSequenceTable<int, PolitickySubjekt*>* subjekty,
								   QWidget* parent) : TabulkaUloh(jednotky, subjekty, parent),
								   unsortedJednotky(new Structures::UnsortedSequenceTable<int, UzemnaJednotka*>(*jednotky)),
								   unsortedSubjekty(new Structures::UnsortedSequenceTable<int, PolitickySubjekt*>(*subjekty)),
								   actualJednotky(unsortedJednotky),
								   actualSubjekty(unsortedSubjekty),
								   unsortedJednotkySubjektu(new Structures::Array<Structures::UnsortedSequenceTable<UzemnaJednotka*, Pair<int, double>>*>(subjekty->size())),
								   activeFilterUJ(nullptr),
								   activeFilterPS(nullptr),
								   sortedHlasy(false),
	  columnNames({"Strana", "PocetHlasov", "Uspesnost", "Obec", "Okres", "Kraj", "Ucast", "Volici", "Zucastneni", "PodielPlatnych"}) {


	this->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::Interactive);

	this->zobrazTabulku(this->jednotky, this->subjekty);
	this->setColumnWidth(0, 190);
	this->setColumnWidth(1, 125);
	this->setColumnWidth(2, 110);
	this->setColumnWidth(3, 235);
	this->setColumnWidth(4, 160);
	this->setColumnWidth(5, 160);
	this->setColumnWidth(6, 90);
	this->setColumnWidth(7, 110);
	this->setColumnWidth(8, 120);
	this->setColumnWidth(9, 136);

	QObject::connect(this->horizontalHeader(), &QHeaderView::sectionDoubleClicked, this, [=](int k) {
		Structures::QuickSort<int, UzemnaJednotka*> sortUJ;
		Structures::QuickSort<int, PolitickySubjekt*> sortPS;
		Structures::QuickSort<UzemnaJednotka*, Pair<int, double>> sortSS;
		switch (k) {
			case 0 :
				sortPS.sort(*this->actualSubjekty, Comparator<std::wstring, PolitickySubjekt*>(this->asc[0], kriteria.kritNazovPS));
				this->asc[0] = !this->asc[0];
				break;
			case 1 :
				sortPS.sort(*this->actualSubjekty, Comparator<std::wstring, PolitickySubjekt*>(true, kriteria.kritNazovPS));
				for (Structures::TableItem<int , PolitickySubjekt*>* temp : *this->actualSubjekty) {
					kriteria.kritUspesnostUzemnychJednotiekSubjektu.parametrizuj(this->actualJednotky);
					if ((*this->unsortedJednotkySubjektu)[temp->getKey() - 1] != nullptr ) delete (*this->unsortedJednotkySubjektu)[temp->getKey() - 1];
					(*this->unsortedJednotkySubjektu)[temp->getKey() - 1] = new Structures::UnsortedSequenceTable(kriteria.kritUspesnostUzemnychJednotiekSubjektu.vyber(*temp->accessData()));
					sortSS.sort(*(*this->unsortedJednotkySubjektu)[temp->getKey() - 1], Comparator(this->asc[1], KriteriumZiskaneHlasyPreSubjekt()));
				}
				this->asc[1] = !this->asc[1];
				this->sortedHlasy = true;
				break;
			case 2 :
				sortPS.sort(*this->actualSubjekty, Comparator<std::wstring, PolitickySubjekt*>(true, kriteria.kritNazovPS));
				for (Structures::TableItem<int , PolitickySubjekt*>* temp : *this->actualSubjekty) {
					kriteria.kritUspesnostUzemnychJednotiekSubjektu.parametrizuj(this->actualJednotky);
					if ((*this->unsortedJednotkySubjektu)[temp->getKey() - 1] != nullptr ) delete (*this->unsortedJednotkySubjektu)[temp->getKey() - 1];
					(*this->unsortedJednotkySubjektu)[temp->getKey() - 1] = new Structures::UnsortedSequenceTable(kriteria.kritUspesnostUzemnychJednotiekSubjektu.vyber(*temp->accessData()));
					sortSS.sort(*(*this->unsortedJednotkySubjektu)[temp->getKey() - 1], Comparator(this->asc[2], KriteriumZiskaneHlasyPodielPreSubjekt()));

				}
				this->sortedHlasy = true;
				this->asc[2] = !this->asc[2];
				break;
			case 3 :
				sortUJ.sort(*this->actualJednotky, Comparator<std::wstring, UzemnaJednotka*>(this->asc[3], kriteria.kritNazovObecUJ));
				this->asc[3] = !this->asc[3];
				break;
			case 4 :
				sortUJ.sort(*this->actualJednotky, Comparator<std::wstring, UzemnaJednotka*>(this->asc[4], kriteria.kritNazovOkresUJ));
				this->asc[4] = !this->asc[4];
				break;
			case 5 :
				sortUJ.sort(*this->actualJednotky, Comparator<std::wstring, UzemnaJednotka*>(this->asc[5], kriteria.kritNazovKrajUJ));
				this->asc[5] = !this->asc[5];
				break;
			case 6 :
				sortUJ.sort(*this->actualJednotky, Comparator<double, UzemnaJednotka*>(this->asc[6], kriteria.kritUcastUJ));
				this->asc[6] = !this->asc[6];
				break;
			case 7 :
				sortUJ.sort(*this->actualJednotky, Comparator<int, UzemnaJednotka*>(this->asc[7], kriteria.kritVoliciUJ));
				this->asc[7] = !this->asc[7];
				break;
			case 8 :
				sortUJ.sort(*this->actualJednotky, Comparator<int, UzemnaJednotka*>(this->asc[8], kriteria.kritZucastneniUJ));
				this->asc[8] = !this->asc[8];
				break;
			case 9 :
				sortUJ.sort(*this->actualJednotky, Comparator<double, UzemnaJednotka*>(this->asc[9], kriteria.kritPodielPlatnychUJ));
				this->asc[9] = !this->asc[9];
				break;
		}

		this->zobrazTabulku(this->actualJednotky, this->actualSubjekty);});



	QObject::connect(this->horizontalHeader(), &QHeaderView::sectionClicked, this, [=](int k) {
		bool ok;
		QString vstup = QInputDialog::getText(this, "Filter", "Zadajte kriterium", QLineEdit::Normal, {}, &ok);
		if (ok && !vstup.isEmpty()) {
			Filter<UzemnaJednotka>* fiUJ = nullptr;
			Filter<PolitickySubjekt>* fiPS = nullptr;
			switch (k) {
				case 0 :
					fiPS = new FilterValue<PolitickySubjekt, std::wstring>(kriteria.kritNazovPS, vstup.toStdWString());
					break;
				case 1 :
					if (!vstup.contains(">>")) {
						fiPS = new FilterValue<PolitickySubjekt, int>(kriteria.kritHlasyPS, vstup.toInt());
					} else {
						fiPS = new FilterRange<PolitickySubjekt, int>(kriteria.kritHlasyPS, vstup.split(">>").at(0).toInt(), vstup.split(">>").at(1).toInt());
					}
					break;
				case 2 :
					if (!vstup.contains(">>")) {
						fiPS = new FilterValue<PolitickySubjekt, double>(kriteria.kritUspesnostPS, vstup.toDouble());
					} else {
						fiPS = new FilterRange<PolitickySubjekt, double>(kriteria.kritUspesnostPS, vstup.split(">>").at(0).toDouble(), vstup.split(">>").at(1).toDouble());
					}
					break;
				case 3 :
					fiUJ = new FilterValue<UzemnaJednotka, std::wstring>(kriteria.kritNazovObecUJ, vstup.toStdWString());
					break;
				case 4 :
					fiUJ = new FilterValue<UzemnaJednotka, std::wstring>(kriteria.kritNazovOkresUJ, vstup.toStdWString());
					break;
				case 5 :
					fiUJ = new FilterValue<UzemnaJednotka, std::wstring>(kriteria.kritNazovKrajUJ, vstup.toStdWString());
					break;
				case 6 :
					if (!vstup.contains(">>")) {
						fiUJ = new FilterValue<UzemnaJednotka, double>(kriteria.kritUcastUJ, vstup.toDouble());
					} else {
						fiUJ = new FilterRange<UzemnaJednotka, double>(kriteria.kritUcastUJ, vstup.split(">>").at(0).toDouble(), vstup.split(">>").at(1).toDouble());
					}
					break;
				case 7 :
					if (!vstup.contains(">>")) {
						fiUJ = new FilterValue<UzemnaJednotka, int>(kriteria.kritVoliciUJ, vstup.toDouble());
					} else {
						fiUJ = new FilterRange<UzemnaJednotka, int>(kriteria.kritVoliciUJ, vstup.split(">>").at(0).toInt(), vstup.split(">>").at(1).toInt());
					}
					break;
				case 8 :
					if (!vstup.contains(">>")) {
						fiUJ = new FilterValue<UzemnaJednotka, int>(kriteria.kritZucastneniUJ, vstup.toDouble());
					} else {
						fiUJ = new FilterRange<UzemnaJednotka, int>(kriteria.kritZucastneniUJ, vstup.split(">>").at(0).toInt(), vstup.split(">>").at(1).toInt());
					}
					break;
				case 9 :
					if (!vstup.contains(">>")) {
						fiUJ = new FilterValue<UzemnaJednotka, double>(kriteria.kritPodielPlatnychUJ, vstup.toDouble());
					} else {
						fiUJ = new FilterRange<UzemnaJednotka, double>(kriteria.kritPodielPlatnychUJ, vstup.split(">>").at(0).toDouble(), vstup.split(">>").at(1).toDouble());
					}
					break;
			}

			if (this->activeFilterUJ != nullptr && fiUJ != nullptr) {
				FilterAnd<UzemnaJednotka>* filAnd = new FilterAnd(*this->activeFilterUJ, *fiUJ);
				this->filUJStack.push(fiUJ);
				this->activeFilterUJ = filAnd;
				this->filUJStack.push(this->activeFilterUJ);
			} else if (fiUJ != nullptr) {
				this->activeFilterUJ = fiUJ;
				this->filUJStack.push(this->activeFilterUJ);
			}

			if (this->activeFilterPS != nullptr && fiPS != nullptr) {
				FilterAnd<PolitickySubjekt>* filAnd = new FilterAnd(*this->activeFilterPS, *fiPS);
				this->filPSStack.push(fiPS);
				this->activeFilterPS = filAnd;
				this->filPSStack.push(this->activeFilterPS);
			} else if (fiPS != nullptr) {
				this->activeFilterPS = fiPS;
				this->filPSStack.push(this->activeFilterPS);
			}
		}});

}

TabulkaUlohDruha::~TabulkaUlohDruha() {
	if (this->actualJednotky != nullptr && this->actualJednotky != this->unsortedJednotky) {
		delete this->actualJednotky;
		this->actualJednotky = nullptr;
	}
	delete this->unsortedJednotky;
	this->unsortedJednotky = nullptr;

	if (this->actualSubjekty != nullptr && this->actualSubjekty != this->unsortedSubjekty) {
		delete this->actualSubjekty;
		this->actualSubjekty = nullptr;
	}
	delete this->unsortedSubjekty;
	this->unsortedSubjekty = nullptr;

	for (size_t i = 0; i < this->unsortedJednotkySubjektu->size(); ++i) {
		if ((*this->unsortedJednotkySubjektu)[i] != nullptr) {
			delete (*this->unsortedJednotkySubjektu)[i];
		}
	}

	if (this->unsortedJednotkySubjektu != nullptr) {
		delete this->unsortedJednotkySubjektu;
	}


	while (!this->filUJStack.isEmpty()) {
		if (this->filUJStack.peek() != nullptr) {
			delete this->filUJStack.pop();
		} else {
			this->filUJStack.pop();
		}
	}

	while (!this->filPSStack.isEmpty()) {
		if (this->filPSStack.peek() != nullptr) {
			delete this->filPSStack.pop();
		} else {
			this->filPSStack.pop();
		}
	}
}


void TabulkaUlohDruha::filtruj() {
	if (this->activeFilterUJ != nullptr) {
		if (this->actualJednotky != nullptr && this->actualJednotky != this->unsortedJednotky) {
			delete this->actualJednotky;
		}
		this->actualJednotky = new Structures::UnsortedSequenceTable<int, UzemnaJednotka*>(this->activeFilterUJ->vyfiltruj(*this->unsortedJednotky));
	} else {
		if (this->actualJednotky != nullptr && this->actualJednotky != this->unsortedJednotky) {
			delete this->actualJednotky;
		}
		this->actualJednotky = this->unsortedJednotky;
	}
	if (this->activeFilterPS != nullptr) {
		if (this->actualSubjekty != nullptr && this->actualSubjekty != this->unsortedSubjekty) {
			delete this->actualSubjekty;
		}
		this->actualSubjekty = new Structures::UnsortedSequenceTable<int, PolitickySubjekt*>(this->activeFilterPS->vyfiltruj(*this->unsortedSubjekty));
	} else {
		if (this->actualSubjekty != nullptr && this->actualSubjekty != this->unsortedSubjekty) {
			delete this->actualSubjekty;
		}
		this->actualSubjekty = this->unsortedSubjekty;
	}
	this->zobrazTabulku(this->actualJednotky, this->actualSubjekty);
}

void TabulkaUlohDruha::keyPressEvent(QKeyEvent* event) {
	if (event->key() == Qt::Key::Key_Up) {
		this->clear();
		KriteriumLambda<Pair<UzemnaJednotka*, Structures::UnsortedSequenceTable<int, PolitickySubjekt*>*>, PolitickySubjekt*> krit;
		int i = 0;
		for (Structures::TableItem<int, UzemnaJednotka*>* temp : *this->actualJednotky) {
			Pair pair(temp->accessData(), this->actualSubjekty);
			PolitickySubjekt* best = krit.vyber([](Pair<UzemnaJednotka*, Structures::UnsortedSequenceTable<int, PolitickySubjekt*>*> vstup) -> PolitickySubjekt* {
				PolitickySubjekt* best {};
				int bestVotes = 0;
				for (Structures::TableItem<int, PolitickySubjekt*>* temp : *vstup.second) {
					int currentVotes = temp->accessData()->getHlasovPreUzemnuJednotku(vstup.first).first;
					if (best == nullptr || bestVotes < currentVotes) {
						bestVotes = currentVotes;
						best = temp->accessData();
					}
				}
				return best;}, pair);
			this->zobrazTiadok(temp->accessData(), best, i++);
		}
	} else if (event->key() == Qt::Key::Key_Down) {
		this->clear();
		KriteriumLambda<Pair<UzemnaJednotka*, Structures::UnsortedSequenceTable<int, PolitickySubjekt*>*>, PolitickySubjekt*> krit;
		int i = 0;
		for (Structures::TableItem<int, UzemnaJednotka*>* temp : *this->actualJednotky) {
			Pair pair(temp->accessData(), this->actualSubjekty);
			PolitickySubjekt* best = krit.vyber([](Pair<UzemnaJednotka*, Structures::UnsortedSequenceTable<int, PolitickySubjekt*>*> vstup) -> PolitickySubjekt* {
				PolitickySubjekt* best {};
				int bestVotes = INT_MAX;
				for (Structures::TableItem<int, PolitickySubjekt*>* temp : *vstup.second) {
					int currentVotes = temp->accessData()->getHlasovPreUzemnuJednotku(vstup.first).first;
					if (best == nullptr || bestVotes > currentVotes) {
						bestVotes = currentVotes;
						best = temp->accessData();
					}
				}
				return best;}, pair);
			this->zobrazTiadok(temp->accessData(), best, i++);
		}

	}
	TabulkaUloh::keyPressEvent(event);
}

void TabulkaUlohDruha::zobrazTabulku(Structures::SequenceTable<int, UzemnaJednotka*>* tabulkaUJ, Structures::SequenceTable<int, PolitickySubjekt*>* tabulkaPS) {
	if (this->activeFilterUJ) {
		this->activeFilterUJ = nullptr;
	}
	if (this->activeFilterPS) {
		this->activeFilterPS = nullptr;
	}
	this->clear();
	this->setColumnCount(this->columnNames.size());
	this->setHorizontalHeaderLabels(this->columnNames);
	int row = 0;
	int column = 0;

	this->setRowCount(tabulkaUJ->size() * tabulkaPS->size());
	if (!this->sortedHlasy) {
		for (Structures::TableItem<int, PolitickySubjekt*>* temp : *tabulkaPS) {
			for (Structures::TableItem<int, UzemnaJednotka*>* temp2 : *tabulkaUJ) {
			column = 0;
			this->setItem(row, column++, new QTableWidgetItem(QString::fromStdWString(kriteria.kritNazovPS(temp->accessData()))));
			kriteria.kritHlasyPS.parametrizuj(temp2->accessData());
			this->setItem(row, column++, new QTableWidgetItem(QString("%1").arg(kriteria.kritHlasyPS(temp->accessData()))));
			kriteria.kritUspesnostPS.parametrizuj(temp2->accessData());
			this->setItem(row, column++, new QTableWidgetItem(QString::number(kriteria.kritUspesnostPS(temp->accessData()), 'f', 2)));
			this->setItem(row, column++, new QTableWidgetItem(QString::fromStdWString(kriteria.kritNazovObecUJ(temp2->accessData()))));
			this->setItem(row, column++, new QTableWidgetItem(QString::fromStdWString(kriteria.kritNazovOkresUJ(temp2->accessData()))));
			this->setItem(row, column++, new QTableWidgetItem(QString::fromStdWString(kriteria.kritNazovKrajUJ(temp2->accessData()))));
			this->setItem(row, column++, new QTableWidgetItem(QString::number(kriteria.kritUcastUJ(temp2->accessData()), 'f', 2)));
			this->setItem(row, column++, new QTableWidgetItem(QString("%1").arg(kriteria.kritVoliciUJ(temp2->accessData()))));
			this->setItem(row, column++, new QTableWidgetItem(QString("%1").arg(kriteria.kritZucastneniUJ(temp2->accessData()))));
			this->setItem(row++, column, new QTableWidgetItem(QString::number(kriteria.kritPodielPlatnychUJ(temp2->accessData()), 'f', 2)));
			}
		}
	} else {
		for (Structures::TableItem<int, PolitickySubjekt*>* temp : *this->actualSubjekty) {
			for (Structures::TableItem<UzemnaJednotka*, Pair<int, double>>* temp2 : *(*this->unsortedJednotkySubjektu)[temp->getKey() - 1]) {
				column = 0;
				this->setItem(row, column++, new QTableWidgetItem(QString::fromStdWString(kriteria.kritNazovPS(temp->accessData()))));
				kriteria.kritHlasyPS.parametrizuj(temp2->getKey());
				this->setItem(row, column++, new QTableWidgetItem(QString("%1").arg(kriteria.kritHlasyPS(temp->accessData()))));
				kriteria.kritUspesnostPS.parametrizuj(temp2->getKey());
				this->setItem(row, column++, new QTableWidgetItem(QString::number(kriteria.kritUspesnostPS(temp->accessData()), 'f', 2)));
				this->setItem(row, column++, new QTableWidgetItem(QString::fromStdWString(kriteria.kritNazovObecUJ(temp2->getKey()))));
				this->setItem(row, column++, new QTableWidgetItem(QString::fromStdWString(kriteria.kritNazovOkresUJ(temp2->getKey()))));
				this->setItem(row, column++, new QTableWidgetItem(QString::fromStdWString(kriteria.kritNazovKrajUJ(temp2->getKey()))));
				this->setItem(row, column++, new QTableWidgetItem(QString::number(kriteria.kritUcastUJ(temp2->getKey()), 'f', 2)));
				this->setItem(row, column++, new QTableWidgetItem(QString("%1").arg(kriteria.kritVoliciUJ(temp2->getKey()))));
				this->setItem(row, column++, new QTableWidgetItem(QString("%1").arg(kriteria.kritZucastneniUJ(temp2->getKey()))));
				this->setItem(row++, column, new QTableWidgetItem(QString::number(kriteria.kritPodielPlatnychUJ(temp2->getKey()), 'f', 2)));
			}
		}
		this->sortedHlasy = false;
	}
}

void TabulkaUlohDruha::zobrazTiadok(UzemnaJednotka* jednotka, PolitickySubjekt* subjekt, int row) {
	this->setRowCount(row + 1);
	this->setColumnCount(this->columnNames.size());
	this->setHorizontalHeaderLabels(this->columnNames);
	int column = 0;
	this->setItem(row, column++, new QTableWidgetItem(QString::fromStdWString(kriteria.kritNazovPS(subjekt))));
	kriteria.kritHlasyPS.parametrizuj(jednotka);
	this->setItem(row, column++, new QTableWidgetItem(QString("%1").arg(kriteria.kritHlasyPS(subjekt))));
	kriteria.kritUspesnostPS.parametrizuj(jednotka);
	this->setItem(row, column++, new QTableWidgetItem(QString::number(kriteria.kritUspesnostPS(subjekt), 'f', 2)));
	this->setItem(row, column++, new QTableWidgetItem(QString::fromStdWString(kriteria.kritNazovObecUJ(jednotka))));
	this->setItem(row, column++, new QTableWidgetItem(QString::fromStdWString(kriteria.kritNazovOkresUJ(jednotka))));
	this->setItem(row, column++, new QTableWidgetItem(QString::fromStdWString(kriteria.kritNazovKrajUJ(jednotka))));
	this->setItem(row, column++, new QTableWidgetItem(QString::number(kriteria.kritUcastUJ(jednotka), 'f', 2)));
	this->setItem(row, column++, new QTableWidgetItem(QString("%1").arg(kriteria.kritVoliciUJ(jednotka))));
	this->setItem(row, column++, new QTableWidgetItem(QString("%1").arg(kriteria.kritZucastneniUJ(jednotka))));
	this->setItem(row, column, new QTableWidgetItem(QString::number(kriteria.kritPodielPlatnychUJ(jednotka), 'f', 2)));
}
