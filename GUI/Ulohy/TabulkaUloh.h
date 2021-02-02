#pragma once

#include <QWidget>
#include "GUI/TableWidget.h"
#include "GUI/Instances.h"

class TabulkaUloh : public TableWidget {
public:
	TabulkaUloh(Structures::SortedSequenceTable<int, UzemnaJednotka*>*, Structures::SortedSequenceTable<int, PolitickySubjekt*>*, QWidget* parent = nullptr);
	virtual ~TabulkaUloh();

	virtual void filtruj() = 0;

protected:
	void keyPressEvent(QKeyEvent*) override;

public slots:
	void filtrujTabulku();

protected:
	TableWidget* tabulka;
	Structures::SortedSequenceTable<int, UzemnaJednotka*>* jednotky;
	Structures::SortedSequenceTable<int, PolitickySubjekt*>* subjekty;
};

