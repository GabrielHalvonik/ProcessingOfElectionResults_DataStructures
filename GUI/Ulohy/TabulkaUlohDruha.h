#pragma once

#include "TabulkaUloh.h"
#include "App/Filter.h"
#include "Stack/ExplicitStack.h"

class TabulkaUlohDruha : public TabulkaUloh {
public:
	TabulkaUlohDruha(Structures::SortedSequenceTable<int, UzemnaJednotka*>*, Structures::SortedSequenceTable<int, PolitickySubjekt*>*, QWidget* parent = nullptr);
	~TabulkaUlohDruha();

	void filtruj() override;

protected:
	void keyPressEvent(QKeyEvent* event) override;

private:
	void zobrazTabulku(Structures::SequenceTable<int, UzemnaJednotka*>*, Structures::SequenceTable<int, PolitickySubjekt*>*);
	void zobrazTiadok(UzemnaJednotka*, PolitickySubjekt*, int);

private:
	Kriteria kriteria;
	Structures::UnsortedSequenceTable<int, UzemnaJednotka*>* unsortedJednotky;
	Structures::UnsortedSequenceTable<int, PolitickySubjekt*>* unsortedSubjekty;
	Structures::UnsortedSequenceTable<int, UzemnaJednotka*>* actualJednotky;
	Structures::UnsortedSequenceTable<int, PolitickySubjekt*>* actualSubjekty;
	Structures::Array<Structures::UnsortedSequenceTable<UzemnaJednotka*, Pair<int, double>>*>* unsortedJednotkySubjektu;
	Filter<UzemnaJednotka>* activeFilterUJ;
	Filter<PolitickySubjekt>* activeFilterPS;
	Structures::ExplicitStack<Filter<UzemnaJednotka>*> filUJStack;
	Structures::ExplicitStack<Filter<PolitickySubjekt>*> filPSStack;
	bool asc[10];
	bool sortedHlasy;
	QStringList columnNames;
};

