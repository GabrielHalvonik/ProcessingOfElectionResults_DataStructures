#pragma once

#include "TabulkaUloh.h"
#include "App/Filter.h"
#include "Stack/ExplicitStack.h"

class TabulkaUlohPrva : public TabulkaUloh {
public:
	TabulkaUlohPrva(Structures::SortedSequenceTable<int, UzemnaJednotka*>*, Structures::SortedSequenceTable<int, PolitickySubjekt*>*, QWidget* parent = nullptr);
	~TabulkaUlohPrva();

public:
	void filtruj() override;

private:
	void zobrazTabulku(Structures::SequenceTable<int, UzemnaJednotka*>*);

private:
	Kriteria kriteria;
	Structures::UnsortedSequenceTable<int, UzemnaJednotka*>* unsortedTable;
	Structures::UnsortedSequenceTable<int, UzemnaJednotka*>* actualTable;
	Filter<UzemnaJednotka>* activeFilter;
	Structures::ExplicitStack<Filter<UzemnaJednotka>*> filStack;
	bool asc[10];
	QStringList columnNames;
};

