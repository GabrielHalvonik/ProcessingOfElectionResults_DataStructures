#pragma once

#include <QObject>

enum TypUzemnejJednotky { Obec, Okres, Kraj, Stat };

//enum TypObce { Mesto, MestskaCast, Obec, Zahranicie };

enum SposobOdovzdania { Osobne, Z_Cudziny, Spolu };

enum TypyKriterii { KritNazovUJ,
					KritTypUJ,
					KritPrislusnostUJ,
					KritUcastUJ,
					KritVoliciUJ,
					KritOdovzdaneObalkyUJ,
					KritPodielPlatnychUJ,
					KritPocetPlatnychUJ,
					KritNazovSubjekt,
					KritHlasySubjekt,
					KritUspesnostSubjekt,
					KritMenoKandidat,
					KritPrislusnostKandidat,
					KritPrednostneHlasyKandidat };

enum DruhyFiltrov { FilterForValue,
					FilterForRange,
					FilterForAnd };

enum TypyFiltrov { FilterWstring,
				   FilterInt,
				   FilterDouble,
				   Other };

enum SelectedFilter { FilterUzemnaJednotka,
					  FilterPolitickySubjet,
					  FilterKandidat };


//Q_ENUMS(TypUzemnejJednotky)
//Q_ENUMS(SposobOdovzdania)
//Q_ENUMS(TypyKriterii)
//Q_ENUMS(TypyFiltrov)
