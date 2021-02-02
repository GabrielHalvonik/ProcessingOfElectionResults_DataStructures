#pragma once

#include <string>
#include "TypUzemnejJednotky.h"
#include "Array/Array.h"
#include "Queue/ExplicitQueue.h"
#include "Table/Treap.h"
#include "Table/SortedSequenceTable.h"
#include "Table/UnsortedSequenceTable.h"
#include "Vseobecne.h"

class UzemnaJednotka /*: public Vseobecne*/ {
public:
	UzemnaJednotka() = default;
	UzemnaJednotka(const std::wstring&, const int, const TypUzemnejJednotky, int = 0);
	~UzemnaJednotka();

	bool patriPodVyssieUzemie(const std::wstring&) const;
	bool patriPodVyssieUzemie(const UzemnaJednotka&) const;

	double getUcastVolicov() const;
	int getPocetVolicov() const;
	int getPocetZucastnenych() const;
	double getPodielPlatnychHlasov() const;
	int getPocetPlatnychHlasov() const;

	std::wstring getNazov() const;
	TypUzemnejJednotky getTyp() const;

	int getId() const;

	int getPocetOdovzdaniaObalokSposobom(SposobOdovzdania) const;

	UzemnaJednotka* getVyssieUzemie() const;
	Structures::ExplicitQueue<UzemnaJednotka*> getVyssieUzemia() const;
	Structures::SortedSequenceTable<int, UzemnaJednotka*>* getMensieUzemia() const;

public:

	friend class UzemnaJednotkaDataLoading;
	friend class VysledkyHlasovaniaOkrskovDataLoading;
	friend class HlasyPrePolitickeSubjektyLoading;

	friend std::wostream &operator<<(std::wostream&, const UzemnaJednotka&);


protected:
	int pocetVolicov = 0;
	double ucastVolicov = 0.0;
	int pocetZucastnenych = 0;
	int pocetOkrskov = 0;

	int pocetPlatnychHlasov = 0;
	double podielPlatnychHlasov = 0.0;

	int idUzemnejJednotky = 0;

	std::wstring nazov;
	TypUzemnejJednotky typ;

	UzemnaJednotka* vyssieUzemie;
	Structures::SortedSequenceTable<int, UzemnaJednotka*>* mensieUzemia;

	Structures::Array<std::pair<int, double>> pocetOdovzdaniaObalokSposobmi {3};
};

