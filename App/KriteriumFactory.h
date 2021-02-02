#pragma once

#include "Kriterium.h"
#include "TypUzemnejJednotky.h"

class KriteriumFactory {
public:
	KriteriumFactory() = delete;

	template <typename O, typename T>
	static Kriterium<O, T>* createInstance(const TypyKriterii);
};

template<typename O, typename T>
Kriterium<O, T>* KriteriumFactory::createInstance(const TypyKriterii typ) {
	switch (typ) {
		case KritNazovUJ:
			return new KriteriumUzemnaJednotkaNazovObec;
			break;
		case KritTypUJ:
			return new KriteriumUzemnaJednotkaTyp;
			break;
		case KritPrislusnostUJ:
//			return new KriteriumUzemnaJednotkaPrislusnost();
			break;
		case KritUcastUJ:
			return new KriteriumUzemnaJednotkaUcast;
			break;
		case KritVoliciUJ:
			return new KriteriumUzemnaJednotkaVolici;
			break;
		case KritOdovzdaneObalkyUJ:
//			return new KriteriumUzemnaJednotkaOdovzdaneObalky({});
			break;
		case KritPodielPlatnychUJ:
			return new KriteriumUzemnaJednotkaPodielPlatnychHlasov;
			break;
		case KritPocetPlatnychUJ:
			return new KriteriumUzemnaJednotkaPocetPlatnychHlasov;
			break;
		case KritNazovSubjekt:
			return new KriteriumPolitickySubjektNazov;
			break;
		case KritHlasySubjekt:
			return new KriteriumPolitickySubjektZiskaneHlasy;
			break;
		case KritUspesnostSubjekt:
//			return new KriteriumPolitickySubjekt;
			break;
		case KritMenoKandidat:
			break;
		case KritPrislusnostKandidat:
			break;
		case KritPrednostneHlasyKandidat:
			break;

	}
}

