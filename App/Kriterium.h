#pragma once

#include "UzemnaJednotka.h"
#include "PolitickySubjekt.h"

template <typename O, typename T>
class Kriterium {
public:
	T operator()(const O& obj) const {
		return this->vyber(obj);
	}

	T operator()(const O* obj) const {
		return this->vyber(*obj);
	}

	T operator()(T(*fun)(const O&), const O&obj) const {
		return fun(obj);
	}

	virtual T vyber(const O&) const = 0;
};

template <typename O, typename T>
class KriteriumLambda : public Kriterium<O, T> {
public:
	T vyber(const O&) const override { return {}; }
	T vyber(T(*fun)(O), O obj) const {
		return fun(obj);
	}
};

template <typename T>
class KriteriumUzemnaJednotka : public Kriterium<UzemnaJednotka, T> {
public:
	virtual T vyber(const UzemnaJednotka&) const override = 0;
};

class KriteriumUzemnaJednotkaNazovObec : public KriteriumUzemnaJednotka<std::wstring> {
public:
	std::wstring vyber(const UzemnaJednotka& jednotka) const override {
		switch (jednotka.getTyp()) {
			case TypUzemnejJednotky::Obec :
				return jednotka.getNazov();
			case TypUzemnejJednotky::Okres :
			case TypUzemnejJednotky::Kraj :
			case TypUzemnejJednotky::Stat :
				return {};
		}
	}
};

class KriteriumUzemnaJednotkaNazovOkres : public KriteriumUzemnaJednotka<std::wstring> {
public:
	std::wstring vyber(const UzemnaJednotka& jednotka) const override {
		switch (jednotka.getTyp()) {
			case TypUzemnejJednotky::Obec :
				return jednotka.getVyssieUzemie()->getNazov();
			case TypUzemnejJednotky::Okres :
				return jednotka.getNazov();
			case TypUzemnejJednotky::Kraj :
			case TypUzemnejJednotky::Stat :
				return {};
		}
	}
};

class KriteriumUzemnaJednotkaNazovKraj : public KriteriumUzemnaJednotka<std::wstring> {
public:
	std::wstring vyber(const UzemnaJednotka& jednotka) const override {
		switch (jednotka.getTyp()) {
			case TypUzemnejJednotky::Obec :
				return jednotka.getVyssieUzemie()->getVyssieUzemie()->getNazov();
			case TypUzemnejJednotky::Okres :
				return jednotka.getVyssieUzemie()->getNazov();
			case TypUzemnejJednotky::Kraj :
				return jednotka.getNazov();
			case TypUzemnejJednotky::Stat :
				return {};
		}
	}
};

class KriteriumUzemnaJednotkaNazovStat : public KriteriumUzemnaJednotka<std::wstring> {
public:
	std::wstring vyber(const UzemnaJednotka& jednotka) const override {
		switch (jednotka.getTyp()) {
			case TypUzemnejJednotky::Obec :
				return jednotka.getVyssieUzemie()->getVyssieUzemie()->getVyssieUzemie()->getNazov();
			case TypUzemnejJednotky::Okres :
				return jednotka.getVyssieUzemie()->getVyssieUzemie()->getNazov();
			case TypUzemnejJednotky::Kraj :
				return jednotka.getVyssieUzemie()->getNazov();
			case TypUzemnejJednotky::Stat :
				return jednotka.getNazov();
		}
	}
};

class KriteriumUzemnaJednotkaTyp : public KriteriumUzemnaJednotka<TypUzemnejJednotky> {
public:
	TypUzemnejJednotky vyber(const UzemnaJednotka& jednotka) const override {
		return jednotka.getTyp();
	}
};

class KriteriumUzemnaJednotkaPrislusnost : public KriteriumUzemnaJednotka<bool> {
public:
	KriteriumUzemnaJednotkaPrislusnost(UzemnaJednotka& vyssiCelok) : vyssiCelok(vyssiCelok) {}

	~KriteriumUzemnaJednotkaPrislusnost() {}

	bool vyber(const UzemnaJednotka& jednotka) const override {
		return jednotka.patriPodVyssieUzemie(this->vyssiCelok);
	}

private:
	UzemnaJednotka& vyssiCelok;
};

class KriteriumUzemnaJednotkaUcast : public KriteriumUzemnaJednotka<double> {
public:
	double vyber(const UzemnaJednotka& jednotka) const override {
		return jednotka.getUcastVolicov();
	}
};

class KriteriumUzemnaJednotkaVolici : public KriteriumUzemnaJednotka<int> {
public:
	int vyber(const UzemnaJednotka& jednotka) const override {
		return jednotka.getPocetVolicov();
	}
};

class KriteriumUzemnaJednotkaZucastneniVolici : public KriteriumUzemnaJednotka<int> {
public:
	int vyber(const UzemnaJednotka& jednotka) const override {
		return jednotka.getPocetZucastnenych();
	}
};

class KriteriumUzemnaJednotkaOdovzdaneObalky : public KriteriumUzemnaJednotka<int> {
public:
	KriteriumUzemnaJednotkaOdovzdaneObalky(const SposobOdovzdania spos) : sposob(spos) {}

	int vyber(const UzemnaJednotka& jednotka) const override {
		return jednotka.getPocetOdovzdaniaObalokSposobom(this->sposob);
	}
private:
	SposobOdovzdania sposob;
};

class KriteriumUzemnaJednotkaPodielPlatnychHlasov : public KriteriumUzemnaJednotka<double> {
public:
	double vyber(const UzemnaJednotka& jednotka) const override {
		return jednotka.getPodielPlatnychHlasov();
	}
};

class KriteriumUzemnaJednotkaPocetPlatnychHlasov : public KriteriumUzemnaJednotka<int> {
public:
	int vyber(const UzemnaJednotka& jednotka) const override {
		return jednotka.getPocetPlatnychHlasov();
	}
};

template <typename T>
class KriteriumPolitickySubjekt : public Kriterium<PolitickySubjekt, T> {
public:
	virtual T vyber(const PolitickySubjekt&) const override = 0;
};

class KriteriumPolitickySubjektNazov : public KriteriumPolitickySubjekt<std::wstring> {
public:
	std::wstring vyber(const PolitickySubjekt& subjekt) const override {
		return subjekt.getSkratka();
	}
};

template <typename O, typename T, typename P>
class KriteriumParametrizovane : public Kriterium<O, T> {
public:
	void parametrizuj(P* jednotka) {
		this->parameter = jednotka;
	}

	virtual T vyber(const O&) const override = 0;

protected:
	P* parameter;
};

class KriteriumPolitickySubjektZiskaneHlasy : public KriteriumParametrizovane<PolitickySubjekt, int, UzemnaJednotka> {
public:
	int vyber(const PolitickySubjekt& subjekt) const override {
		return subjekt.getHlasovPreUzemnuJednotku(this->parameter).first;
	}
};

class KriteriumPolitickySubjektUspesnost : public KriteriumParametrizovane<PolitickySubjekt, double, UzemnaJednotka> {
public:
	double vyber(const PolitickySubjekt& subjekt) const override {
		return static_cast<double>(subjekt.getHlasovPreUzemnuJednotku(this->parameter).first) / this->parameter->getPocetZucastnenych() * 100;
	}
};

class KriteriumPolitickySubjektUspesnostUzemnychJednotiek : public KriteriumParametrizovane<PolitickySubjekt, Structures::UnsortedSequenceTable<UzemnaJednotka*, Pair<int, double>>, Structures::SequenceTable<int, UzemnaJednotka*>> {
public:
	Structures::UnsortedSequenceTable<UzemnaJednotka*, Pair<int, double>> vyber(const PolitickySubjekt& subjekt) const override {
		Structures::UnsortedSequenceTable<UzemnaJednotka*, Pair<int, double>> result;
		for (Structures::TableItem<int, UzemnaJednotka*>* temp : *this->parameter) {
			result.insert(temp->accessData(), subjekt.getHlasovPreUzemnuJednotku(temp->accessData()));
		}
		return result;
	}
};

template <typename O, typename T, typename K>
class VyberoveKriteriumMin : public KriteriumParametrizovane<Structures::SequenceTable<K, O>, O, Kriterium<O, T>> {
public:
	O vyber(const Structures::SequenceTable<K, O>& tab) const override {
		O res {};
		K min {};
		for (Structures::TableItem<K, O>* temp : tab) {
			K doc = this->parameter->vyber(temp->accessData());
			if (min > doc) {
				min = doc;
				res = temp->accessData();
			}
		}
		return res;
	}
	O* vyber(const Structures::SequenceTable<K, O*>& tab) const {
		O* res {};
		K min {};
		for (Structures::TableItem<K, O*>* temp : tab) {
			K doc = this->parameter->vyber(*temp->accessData());
			if (res == nullptr || min > doc) {
				min = doc;
				res = temp->accessData();
			}
		}
		return res;
	}
};

//class KriteriumUzemnaJednotkaUcastPrePolitickySubjekt : public KriteriumParametrizovane<UzemnaJednotka, PolitickySubjekt*, PolitickySubjekt> {
//public:
//	PolitickySubjekt* vyber(const UzemnaJednotka& jednotka) const override {
//		return this->parameter->getHlasovPreUzemnuJednotku(&jednotka).
//	}
//};

template <typename O, typename T, typename K>
class VyberoveKriteriumMax : public KriteriumParametrizovane<Structures::SequenceTable<K, O>, O, Kriterium<O, T>> {
public:
	O vyber(const Structures::SequenceTable<K, O>& tab) const override {
		O res {};
		K max {};
		for (Structures::TableItem<K, O>* temp : tab) {
			K doc = this->parameter->vyber(temp->accessData());
			if (max < doc) {
				max = doc;
				res = temp->accessData();
			}
		}
		return res;
	}
	O* vyber(const Structures::SequenceTable<K, O*>& tab) const {
		O* res {};
		K max {};
		for (Structures::TableItem<K, O*>* temp : tab) {
			K doc = this->parameter->vyber(*temp->accessData());
			if (max < doc) {
				max = doc;
				res = temp->accessData();
			}
		}
		return res;
	}
};

//template <typename O, typename T, typename K>
//template<>
//class VyberoveKriteriumMax<PolitickySubjekt*, UzemnaJednotka*, Pair<int, double>> : public KriteriumParametrizovane<Structures::SequenceTable<Pair<int, double>, PolitickySubjekt*>, PolitickySubjekt*, Kriterium<PolitickySubjekt*, Pair<int, double>>> {
//public:
//	PolitickySubjekt* vyber(const SequenceTable<Pair<int, double>, PolitickySubjekt*> &) const override {} //vyber(const Structures::SequenceTable<K, O>& tab) const override {
//		O res {};
//		K max {};
//		for (Structures::TableItem<K, O>* temp : tab) {
//			K doc = this->parameter->vyber(temp->accessData());
//			if (max < doc) {
//				max = doc;
//				res = temp->accessData();
//			}
//		}
//		return res;
//	}
//	O* vyber(const Structures::SequenceTable<K, O*>& tab) const {
//		O* res {};
//		K max {};
//		for (Structures::TableItem<K, O*>* temp : tab) {
//			K doc = this->parameter->vyber(*temp->accessData());
//			if (max < doc) {
//				max = doc;
//				res = temp->accessData();
//			}
//		}
//		return res;
//	}
//};

class KriteriumZiskaneHlasyPreSubjekt : public Kriterium<Pair<int, double>, int> {
public:
	int vyber(const Pair<int, double>& pair) const override {
		return pair.first;
	}
};

class KriteriumZiskaneHlasyPodielPreSubjekt : public Kriterium<Pair<int, double>, double> {
public:
	double vyber(const Pair<int, double>& pair) const override {
		return pair.second;
	}
};
