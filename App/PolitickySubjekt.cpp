#include "PolitickySubjekt.h"
#include <iostream>

PolitickySubjekt::PolitickySubjekt(const PolitickySubjekt& other) :
	nazov(other.nazov), skratka(other.skratka), id(other.id), zlozene(other.zlozene), pocetKandidatov(other.pocetKandidatov) {
}

PolitickySubjekt::~PolitickySubjekt() {
	if (this->hlasyPreJednotky != nullptr) {
		delete this->hlasyPreJednotky;
		this->hlasyPreJednotky = nullptr;
	}
}

std::wstring PolitickySubjekt::getNazov() const {
	return this->nazov;
}

std::wstring PolitickySubjekt::getSkratka() const {
	return this->skratka;
}

int PolitickySubjekt::getId() const {
	return this->id;
}

int PolitickySubjekt::getZlozene() const {
	return this->zlozene;
}

int PolitickySubjekt::getPocetKandidatov() const {
	return this->pocetKandidatov;
}

//Pair<int, double> PolitickySubjekt::getHlasovPreUzemnuJednotku(int id) const {
//	return (*this->hlasyPreJednotky)[id];
//}

Pair<int, double> PolitickySubjekt::getHlasovPreUzemnuJednotku(UzemnaJednotka* jednotka) const {
	return (*this->hlasyPreJednotky)[jednotka];
}

SortedSequenceTable<UzemnaJednotka*, Pair<int, double> >* PolitickySubjekt::getHlasyPreJednotky() const {
	return hlasyPreJednotky;
}

std::wostream& operator<<(std::wostream& out, const PolitickySubjekt& obj) {
	out << "(" << obj.id << ") " << obj.nazov << "(" << obj.skratka << ") " << obj.zlozene << ", " << obj.pocetKandidatov;

	return out;
}
