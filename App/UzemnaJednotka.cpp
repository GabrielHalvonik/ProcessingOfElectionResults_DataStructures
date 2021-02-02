#include "UzemnaJednotka.h"

using namespace	Structures;

//UzemnaJednotka::UzemnaJednotka() /*: pocetOdovzdaniaObalokSposobmi(3)*/ {
//}

UzemnaJednotka::UzemnaJednotka(const std::wstring& nazov, const int id, const TypUzemnejJednotky typ, int pocetOkrskov) :
	pocetOkrskov(pocetOkrskov), idUzemnejJednotky(id), nazov(nazov), typ(typ),
	vyssieUzemie(nullptr), mensieUzemia(new SortedSequenceTable<int, UzemnaJednotka*>), pocetOdovzdaniaObalokSposobmi(3) { }

UzemnaJednotka::~UzemnaJednotka() {
	delete this->mensieUzemia;
	this->mensieUzemia = nullptr;
}

bool UzemnaJednotka::patriPodVyssieUzemie(const std::wstring& param) const {

	UzemnaJednotka* vyssie = this->vyssieUzemie;
	while (vyssie != nullptr) {
		if (vyssie->nazov == param) {
			return true;
		}
		vyssie = vyssie->vyssieUzemie;
	}

	return false;
}

bool UzemnaJednotka::patriPodVyssieUzemie(const UzemnaJednotka& param) const {
	return this->patriPodVyssieUzemie(param.getNazov());
}

double UzemnaJednotka::getUcastVolicov() const {
	return this->ucastVolicov;
}

int UzemnaJednotka::getPocetVolicov() const {
	return this->pocetVolicov;
}

int UzemnaJednotka::getPocetZucastnenych() const {
	return this->pocetZucastnenych;
}

int UzemnaJednotka::getPocetPlatnychHlasov() const {
	return this->pocetPlatnychHlasov;
}

double UzemnaJednotka::getPodielPlatnychHlasov() const {
	return this->podielPlatnychHlasov;
}

std::wstring UzemnaJednotka::getNazov() const {
	return this->nazov;
}

TypUzemnejJednotky UzemnaJednotka::getTyp() const {
	return this->typ;
}

int UzemnaJednotka::getId() const {
	return this->idUzemnejJednotky;
}

int UzemnaJednotka::getPocetOdovzdaniaObalokSposobom(const SposobOdovzdania sposob) const {
	return this->pocetOdovzdaniaObalokSposobmi[sposob].first;
}

Structures::SortedSequenceTable<int, UzemnaJednotka*>* UzemnaJednotka::getMensieUzemia() const {
	return this->mensieUzemia;
}

UzemnaJednotka* UzemnaJednotka::getVyssieUzemie() const {
	return this->vyssieUzemie;
}

Structures::ExplicitQueue<UzemnaJednotka*> UzemnaJednotka::getVyssieUzemia() const {
	ExplicitQueue<UzemnaJednotka*> result;
	UzemnaJednotka* current = this->vyssieUzemie;
	while (current != nullptr) {
		result.push(current);
		current = current->vyssieUzemie;
	}
	return result;
}


std::wostream& operator<<(std::wostream& out, const UzemnaJednotka& obj) {
	out << obj.nazov << "(" << obj.idUzemnejJednotky << ")[" << obj.typ << "] : " << obj.pocetZucastnenych
		<< "/" << obj.pocetVolicov << "(" << obj.ucastVolicov << ")";

	return out;
}

//int Okres::getPocetOkrskov() const {
//	return this->pocetOkrskov;
//}

//Obec::Obec() : UzemnaJednotka() {
//	this->typ = TypUzemnejJednotky::Obec;
//}

//Okres::Okres() : UzemnaJednotka() {
//	this->typ = TypUzemnejJednotky::Okres;
//}

//Kraj::Kraj() : UzemnaJednotka() {
//	this->typ = TypUzemnejJednotky::Kraj;
//}

//Stat::Stat() : UzemnaJednotka() {
//	this->typ = TypUzemnejJednotky::Stat;
//}
