#pragma once

#include <string>
#include "Table/SortedSequenceTable.h"
#include "Data/Pair.h"
#include "Vseobecne.h"
#include "UzemnaJednotka.h"

using Structures::SortedSequenceTable;
using Structures::Pair;

class PolitickySubjekt /*: public Vseobecne */{
public:
	PolitickySubjekt() = default;
	PolitickySubjekt(const PolitickySubjekt&);
	~PolitickySubjekt();


	std::wstring getNazov() const;
	std::wstring getSkratka() const;
	int getId() const;
	int getZlozene() const;
	int getPocetKandidatov() const;

//	Pair<int, double> getHlasovPreUzemnuJednotku(int) const ;
	Pair<int, double> getHlasovPreUzemnuJednotku(UzemnaJednotka*) const;

public:
	friend std::wostream &operator<<(std::wostream&, const PolitickySubjekt&);
	friend class PolitickySubjektDataLoading;
	friend class HlasyPrePolitickeSubjektyLoading;

	SortedSequenceTable<UzemnaJednotka*, Pair<int, double>>* getHlasyPreJednotky() const;

private:
	std::wstring nazov;
	std::wstring skratka;
	int id;
	int zlozene;
	int pocetKandidatov;

	SortedSequenceTable<UzemnaJednotka*, Pair<int, double>>* hlasyPreJednotky = nullptr;
	//	SortedSequenceTable<int, Pair<int, double>>* hlasyPreJednotky;
};



