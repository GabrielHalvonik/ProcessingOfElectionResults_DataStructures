#pragma once

#include "Kriterium.h"
#include "Table/SequenceTable.h"

template <class O>
class Filter {
public:
	template <typename K>
	Structures::UnsortedSequenceTable<K, O*> vyfiltruj(Structures::SequenceTable<K, O*>& vstup) const {
		Structures::UnsortedSequenceTable<K, O*> result;
		for (Structures::TableItem<K, O*>* temp : vstup) {
			if (this->splnaFilter(*temp->accessData())) {
				result.insert(temp->getKey(), temp->accessData());
			}
		}
		return result;
	}

	virtual ~Filter() = default;

public:
	virtual bool splnaFilter(const O&) const = 0;
};

template <typename O, typename T>
class FilterValue : public Filter<O> {
public:
	FilterValue(const Kriterium<O, T>& kt, const T& alp) : Filter<O>(), kriterium(kt), alpha(alp) {}

	bool splnaFilter(const O& obj) const override {
		return this->kriterium.vyber(obj) == alpha;
	}

	void setValue(const T& alpha) { this->alpha = alpha; }

private:
	const Kriterium<O, T>& kriterium;
	T alpha;
};

template <typename O>
class FilterValue<O, std::wstring> : public Filter<O> {
public:
	FilterValue(const Kriterium<O, std::wstring>& kt, const std::wstring& alp) : Filter<O>(), kriterium(kt), alpha(alp) {}

public:
	bool splnaFilter(const O& obj) const override {
		return (this->kriterium.vyber(obj).find(alpha) != std::wstring::npos);
	}

	void setValue(const std::wstring& alpha) { this->alpha = alpha; }

private:
	const Kriterium<O, std::wstring>& kriterium;
	std::wstring alpha;
};

template <typename O, typename T>
class FilterRange : public Filter<O> {
public:
	FilterRange(const Kriterium<O, T>& kt, T min, T max) : Filter<O>(), kriterium(kt), alpha(min), beta(max) {}

	bool splnaFilter(const O& obj) const override {
		T hodnota = this->kriterium.vyber(obj);
		return alpha <= hodnota && hodnota <= beta;
	}

	void setValues(const T&min, const T&max) { this->alpha = min; this->beta = max; }

private:
	const Kriterium<O, T>& kriterium;
	T alpha;
	T beta;
};

template <typename O>
class FilterAnd : public Filter<O> {
public:
	FilterAnd(const Filter<O>& f1, const Filter<O>& f2) : first(f1), second(f2) {}

public:
	bool splnaFilter(const O& obj) const override {
		return first.splnaFilter(obj) && second.splnaFilter(obj);
	}

private:
	const Filter<O>& first;
	const Filter<O>& second;
};

template <typename O>
class FilterOr : public Filter<O> {
public:
	FilterOr(const Filter<O>& f1, const Filter<O>& f2) : first(f1), second(f2) {}

public:
	bool splnaFilter(const O& obj) const override {
		return first.splnaFilter(obj) || second.splnaFilter(obj);
	}

private:
	const Filter<O>& first;
	const Filter<O>& second;
};

template <typename O>
class FilterNot : public Filter<O> {
public:
	FilterNot(const Filter<O>& f1) : first(f1) {}

public:
	bool splnaFilter(const O& obj) const override {
		return !first.splnaFilter(obj);
	}

private:
	const Filter<O>& first;
};

template <typename O>
FilterAnd<O> operator&&(const Filter<O>& first, const Filter<O>& second) {
	return FilterAnd<O>(first, second);
}

template <typename O>
FilterOr<O> operator||(const Filter<O>& first, const Filter<O>& second) {
	return FilterOr<O>(first, second);
}

template <typename O>
FilterNot<O> operator!(const Filter<O>& first) {
	return FilterNot<O>(first);
}


