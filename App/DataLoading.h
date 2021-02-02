#pragma once

#include "UzemnaJednotka.h"
#include "PolitickySubjekt.h"
#include "Table/SequenceTable.h"

using Structures::SequenceTable;

class DataLoadings {
public:
	virtual void load() = 0;
};

class UzemnaJednotkaDataLoading : public DataLoadings {
public:
	UzemnaJednotkaDataLoading(SequenceTable<int, UzemnaJednotka*>*);
	void load() override;

private:
	SequenceTable<int, UzemnaJednotka*>* jednotky;
};

class VysledkyHlasovaniaOkrskovDataLoading : public DataLoadings {
public:
	VysledkyHlasovaniaOkrskovDataLoading(SequenceTable<int, UzemnaJednotka*>*);
	void load() override;

private:
	void vyplnDataVyssejJednotky(const TypUzemnejJednotky);

private:
	SequenceTable<int, UzemnaJednotka*>* jednotky;
};

class PolitickySubjektDataLoading : public DataLoadings {
public:
	PolitickySubjektDataLoading(SequenceTable<int, UzemnaJednotka*>*, SequenceTable<int, PolitickySubjekt*>*);

	void load() override;

private:
	SequenceTable<int, UzemnaJednotka*>* uzemneJednotky;
	SequenceTable<int, PolitickySubjekt*>* PolitickeSubjekty;
};

class HlasyPrePolitickeSubjektyLoading : public DataLoadings {
public:
	HlasyPrePolitickeSubjektyLoading(SequenceTable<int, UzemnaJednotka*>*, SequenceTable<int, PolitickySubjekt*>*);

	void load();

private:
	void vyplnDataVyssejJednotky(const TypUzemnejJednotky);

private:
	SequenceTable<int, UzemnaJednotka*>* uzemneJednotky;
	SequenceTable<int, PolitickySubjekt*>* politickeSubjekty;
};
