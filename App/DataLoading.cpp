#include "DataLoading.h"
#include "DataLoader.h"
#include "Filter.h"
#include "Data/Pair.h"

using Structures::TableItem;
using Structures::Array;
using Structures::Pair;

UzemnaJednotkaDataLoading::UzemnaJednotkaDataLoading(SequenceTable<int, UzemnaJednotka*>* tab) : jednotky(tab) { }

void UzemnaJednotkaDataLoading::load() {
	DataLoader::open("uzemne_jednotky.csv");

//	Array<Pair<std::wstring, int>> jed(5);
	std::wstring jedS[5];
	int jedV[5];
	int pocetOkrskov;

	while (DataLoader::loadData(jedV[Kraj], jedS[Kraj], empty, empty, jedV[Okres], jedS[Okres], jedV[Obec], jedS[Obec], empty, pocetOkrskov)) {
		jedS[Stat] = (jedV[Kraj] > 8) ? L"Zahraničie" : L"Slovensko";
		for (int i = TypUzemnejJednotky::Obec; i <= TypUzemnejJednotky::Stat; ++i) {
			if (!this->jednotky->containsKey(jedV[i])) {
				this->jednotky->insert(jedV[i], new UzemnaJednotka(jedS[i], jedV[i], TypUzemnejJednotky(i), pocetOkrskov));
			}
		}

		for (int i = TypUzemnejJednotky::Obec, j = TypUzemnejJednotky::Stat; i < TypUzemnejJednotky::Stat; ++i, --j) {
			(*this->jednotky)[jedV[TypUzemnejJednotky(i)]]->vyssieUzemie =
			(*this->jednotky)[jedV[TypUzemnejJednotky(i + 1)]];

			(*this->jednotky)[jedV[TypUzemnejJednotky(j)]]->mensieUzemia->insert(jedV[TypUzemnejJednotky(j - 1)], (*this->jednotky)[jedV[TypUzemnejJednotky(j - 1)]]);
		}
	}
	DataLoader::close();
}


VysledkyHlasovaniaOkrskovDataLoading::VysledkyHlasovaniaOkrskovDataLoading(SequenceTable<int, UzemnaJednotka*>* tab) : jednotky(tab) { }

void VysledkyHlasovaniaOkrskovDataLoading::load() {
	DataLoader::open("vysledky_hlasovania_okrsky.csv");

	int id;
	int pocty[2];
	double podiel;
	int pocS[3];
	double podS[3];
	double pocetPlatnych;
	double podielPlatnych;
	while (DataLoader::loadData(id, empty, pocty[0], pocty[1], podiel, pocS[Osobne], podS[Osobne], pocS[Z_Cudziny], podS[Z_Cudziny], pocetPlatnych, podielPlatnych)) {
		UzemnaJednotka* obec = (*this->jednotky)[id];
		obec->pocetVolicov += pocty[0];
		obec->pocetZucastnenych += pocty[1];
		obec->ucastVolicov = (static_cast<double>(obec->pocetZucastnenych) / static_cast<double>(obec->pocetVolicov)) * 100.0;
		for (int i = SposobOdovzdania::Osobne; i <= SposobOdovzdania::Z_Cudziny; ++i) {
			obec->pocetOdovzdaniaObalokSposobmi[SposobOdovzdania(i)] = { pocS[i], podS[i] };
		}
		obec->pocetOdovzdaniaObalokSposobmi[Spolu] = { pocS[Osobne] + pocS[Z_Cudziny], podS[Osobne] + podS[Spolu] };

		(*this->jednotky)[id]->pocetPlatnychHlasov = pocetPlatnych;
		(*this->jednotky)[id]->podielPlatnychHlasov = podielPlatnych;
	}

	this->vyplnDataVyssejJednotky(TypUzemnejJednotky::Okres);
	this->vyplnDataVyssejJednotky(TypUzemnejJednotky::Kraj);
	this->vyplnDataVyssejJednotky(TypUzemnejJednotky::Stat);

	DataLoader::close();
}

void VysledkyHlasovaniaOkrskovDataLoading::vyplnDataVyssejJednotky(const TypUzemnejJednotky typ) {
	FilterValue<UzemnaJednotka, TypUzemnejJednotky> filter(KriteriumUzemnaJednotkaTyp(), typ);
	for (TableItem<int, UzemnaJednotka*>* temp : filter.vyfiltruj(*this->jednotky)) {
		UzemnaJednotka* current = temp->accessData();
		for (TableItem<int, UzemnaJednotka*>* temp2 : *current->mensieUzemia) {
			UzemnaJednotka* nizsia = temp2->accessData();
			current->pocetVolicov += nizsia->pocetVolicov;
			current->pocetZucastnenych += nizsia->pocetZucastnenych;
			current->ucastVolicov += nizsia->ucastVolicov;
			current->pocetOkrskov += nizsia->pocetOkrskov;
			current->pocetOdovzdaniaObalokSposobmi[Osobne].first += nizsia->pocetOdovzdaniaObalokSposobmi[Osobne].first;
			current->pocetOdovzdaniaObalokSposobmi[Osobne].second += nizsia->pocetOdovzdaniaObalokSposobmi[Osobne].second;
			current->pocetOdovzdaniaObalokSposobmi[Z_Cudziny].first += nizsia->pocetOdovzdaniaObalokSposobmi[Z_Cudziny].first;
			current->pocetOdovzdaniaObalokSposobmi[Z_Cudziny].second += nizsia->pocetOdovzdaniaObalokSposobmi[Z_Cudziny].second;
			current->pocetOdovzdaniaObalokSposobmi[Spolu].first += nizsia->pocetOdovzdaniaObalokSposobmi[Spolu].first;
			current->pocetOdovzdaniaObalokSposobmi[Spolu].second += nizsia->pocetOdovzdaniaObalokSposobmi[Spolu].second;
			temp->accessData()->pocetPlatnychHlasov += temp2->accessData()->pocetPlatnychHlasov;
			temp->accessData()->podielPlatnychHlasov += temp2->accessData()->podielPlatnychHlasov;
		}
		temp->accessData()->ucastVolicov = (static_cast<double>(temp->accessData()->pocetZucastnenych) / static_cast<double>(temp->accessData()->pocetVolicov)) * 100.0;
		temp->accessData()->pocetOdovzdaniaObalokSposobmi[Osobne].second /= static_cast<double>(temp->accessData()->mensieUzemia->size());
		temp->accessData()->pocetOdovzdaniaObalokSposobmi[Z_Cudziny].second /= static_cast<double>(temp->accessData()->mensieUzemia->size());
		temp->accessData()->pocetOdovzdaniaObalokSposobmi[Spolu].second /= static_cast<double>(temp->accessData()->mensieUzemia->size());
		temp->accessData()->podielPlatnychHlasov /= current->mensieUzemia->size();
//		temp->accessData()->podielPlatnychHlasov = static_cast<double>(temp->accessData()->pocetPlatnychHlasov) / temp->accessData()->pocetZucastnenych * 100.0;
	}
}

PolitickySubjektDataLoading::PolitickySubjektDataLoading(SequenceTable<int, UzemnaJednotka*>* tab1, SequenceTable<int, PolitickySubjekt*>* tab2)
	: uzemneJednotky(tab1), PolitickeSubjekty(tab2) { }

void PolitickySubjektDataLoading::load() {
	DataLoader::open("politicke_subjekty.csv");

	SortedSequenceTable<UzemnaJednotka*, Pair<int, double>> ucast;
	for (TableItem<int, UzemnaJednotka*>* temp : *this->uzemneJednotky) {
		ucast.insert(temp->accessData(), {{}, {}});
	}

	PolitickySubjekt subjekt;

	while (DataLoader::loadData(subjekt.id, subjekt.nazov, subjekt.skratka, subjekt.zlozene, subjekt.pocetKandidatov, empty)) {
		this->PolitickeSubjekty->insert(subjekt.id, new PolitickySubjekt(subjekt));
		(*this->PolitickeSubjekty)[subjekt.id]->hlasyPreJednotky = new SortedSequenceTable(ucast);
	}

	DataLoader::close();
}

HlasyPrePolitickeSubjektyLoading::HlasyPrePolitickeSubjektyLoading(SequenceTable<int, UzemnaJednotka*>* tab1, SequenceTable<int, PolitickySubjekt*>* tab2)
	: uzemneJednotky(tab1), politickeSubjekty(tab2) { }

void HlasyPrePolitickeSubjektyLoading::load() {
	DataLoader::open("hlasy_pre_subjekty.csv");

	int idObce, idSubjektu, pocetHlasov;
	double podielHlasov;
	while (DataLoader::loadData(idObce, empty, idSubjektu, pocetHlasov, podielHlasov, empty, empty)) {
		(*(*this->politickeSubjekty)[idSubjektu]->hlasyPreJednotky)[(*uzemneJednotky)[idObce]].first += pocetHlasov;
	}

	this->vyplnDataVyssejJednotky(TypUzemnejJednotky::Okres);
	this->vyplnDataVyssejJednotky(TypUzemnejJednotky::Kraj);
	this->vyplnDataVyssejJednotky(TypUzemnejJednotky::Stat);

//	for (TableItem<int, PolitickySubjekt*>* temp : *this->)
//	for (TableItem<UzemnaJednotka*, Pair<int, double>>* temp : )

	DataLoader::close();
}

void HlasyPrePolitickeSubjektyLoading::vyplnDataVyssejJednotky(const TypUzemnejJednotky typ) {

	FilterValue<UzemnaJednotka, TypUzemnejJednotky> filter(KriteriumUzemnaJednotkaTyp(), typ);

	for (TableItem<int, PolitickySubjekt*>* temp : *this->politickeSubjekty) {
		for (TableItem<int, UzemnaJednotka*>* temp2 : filter.vyfiltruj(*this->uzemneJednotky)) {
			for (TableItem<int, UzemnaJednotka*>* temp3 : *temp2->accessData()->mensieUzemia) {
				(*temp->accessData()->hlasyPreJednotky)[temp2->accessData()] += (*temp->accessData()->hlasyPreJednotky)[temp3->accessData()];
				(*temp->accessData()->hlasyPreJednotky)[temp3->accessData()].second = static_cast<double>((*temp->accessData()->hlasyPreJednotky)[temp3->accessData()].first) / temp3->accessData()->getPocetZucastnenych() * 100;
			}
		}
	}

}
