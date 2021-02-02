#include "UIRoutines.h"

std::wstring UIRoutines::getNazov(const TypUzemnejJednotky typ) {
	switch (typ) {
		case Obec:
			return L"Obec";
			break;
		case Okres:
			return L"Okres";
			break;
		case Kraj:
			return L"Kraj";
			break;
		case Stat:
			return L"Stat";
			break;
	}
}

std::wstring UIRoutines::getNazov(const TypyKriterii typ) {
	switch (typ) {
		case KritNazovUJ:
			return L"KritNazovUJ";
			break;
		case KritTypUJ:
			return L"KritTypUJ";
			break;
		case KritPrislusnostUJ:
			return L"KritPrislusnostUJ";
			break;
		case KritUcastUJ:
			return L"KritUcastUJ";
			break;
		case KritVoliciUJ:
			return L"KritVoliciUJ";
			break;
		case KritOdovzdaneObalkyUJ:
			return L"KritOdovzdaneObalkyUJ";
			break;
		case KritPodielPlatnychUJ:
			return L"KritPodielPlatnychUJ";
			break;
		case KritPocetPlatnychUJ:
			return L"KritPocetPlatnychUJ";
			break;
		case KritNazovSubjekt:
			return L"KritNazovSubjekt";
			break;
		case KritHlasySubjekt:
			return L"KritHlasySubjekt";
			break;
		case KritUspesnostSubjekt:
			return L"KritUspesnostSubjekt";
			break;
		case KritMenoKandidat:
			return L"KritMenoKandidat";
			break;
		case KritPrislusnostKandidat:
			return L"KritPrislusnostKandidat";
			break;
		case KritPrednostneHlasyKandidat:
			return L"KritPrednostneHlasyKandidat";
			break;
	}
}

std::wstring UIRoutines::getNazov(const DruhyFiltrov typ) {
	switch (typ) {
		case FilterForValue:
			return L"FilterValue";
			break;
		case FilterForRange:
			return L"FilterRange";
			break;
	}
}
