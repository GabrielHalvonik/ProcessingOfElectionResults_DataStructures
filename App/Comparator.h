#pragma once

#include "UzemnaJednotka.h"
#include "Kriterium.h"

template <typename R, typename T>
class Comparator {
public:
	Comparator(bool, const Kriterium<T, R>&);

	int operator()(const T&, const T&) const;

	bool isAsc() const;
	void setAsc(bool value);

protected:
	int compare(const T&, const T&) const;

private:
	bool asc;
	const Kriterium<T, R>& krit;
};

template <typename R, typename T>
Comparator<R, T>::Comparator(bool asc, const Kriterium<T, R>& krit) : asc(asc), krit(krit) { }

template <typename R, typename T>
int Comparator<R, T>::operator()(const T& a, const T& b) const {
	return this->compare(a, b);
}

template <typename R, typename T>
bool Comparator<R, T>::isAsc() const {
	return this->asc;
}

template <typename R, typename T>
void Comparator<R, T>::setAsc(bool value) {
	this->asc = value;
}

template <typename R, typename T>
int Comparator<R, T>::compare(const T& a, const T& b) const {
	return (krit(a) < krit(b)) ? -1 : (krit(a) > krit(b)) ? 1 : 0;
}





template <typename R, typename T>
class Comparator<R, T*> : public Comparator<R, T> {
public:
	Comparator(bool asc, const Kriterium<T, R>& krit) : Comparator<R, T>(asc, krit) {}
	int operator()(T*, T*) const;
};

template<typename R, typename T>
int Comparator<R, T*>::operator()(T* a, T* b) const {
	return Comparator<R, T>::compare(*a, *b);
}

//template <typename R, typename T, typename P>
//class ComparatorPointer : public Comparator<R, T> {
//public:
//	ComparatorPointer(bool asc, const Kriterium<T, R>& krit) : Comparator<R, T>(asc, krit) { }
//};

//template <typename O, typename T>
//class ComparatorPtr : public Comparator<O, T> {
//public:
//	ComparatorPtr(bool, const Kriterium<T*, O>&);
//	int operator()(T*, T*) const;

//	bool isAsc() const;
//	void setAsc(bool value);

//protected:
//	virtual int compare(const T&, const T&) const;

//private:
//	bool asc;
//	const Kriterium<T*, O>& krit;
//};

//template<typename O, typename T>
//ComparatorPtr<O, T>::ComparatorPtr(bool asc, const Kriterium<T*, O>& krit) : asc(asc), krit(krit) { }

//template<typename O, typename T>
//int ComparatorPtr<O, T>::operator()(T* a, T* b) const {
//	return asc ? this->compare(*a, *b) : this->compare(*a, *b) * -1;
//}

//template<typename O, typename T>
//bool ComparatorPtr<O, T>::isAsc() const {
//	return this->asc;
//}
//template<typename O, typename T>
//void ComparatorPtr<O, T>::setAsc(bool value) {
//	this->asc = value;
//}

//template<typename O, typename T>
//int ComparatorPtr<O, T>::compare(const T& a, const T& b) const {
//	return (krit(a) < krit(b)) ? -1 : (krit(a) > krit(b)) ? 1 : 0;
//}


//class IntComparator : public Comparator<int> {
//public:
//	IntComparator(bool asc) : Comparator<int>(asc) {}
//protected:
//	int compare(const int&, const int&) const override;
//};

//int IntComparator::compare(const int& a, const int& b) const {
//	return a - b;
//}

//template <typename T>
//class UzemnaJednotkaComparator : public Comparator<UzemnaJednotka> {
//public:
//	UzemnaJednotkaComparator(bool asc, const KriteriumUzemnaJednotka<T>& krit) : Comparator(asc), kriterium(krit) {}

//	int compare(const UzemnaJednotka&, const UzemnaJednotka&) const override;
//private:
//	const KriteriumUzemnaJednotka<T>& kriterium;
//};

//template<typename T>
//int UzemnaJednotkaComparator<T>::compare(const UzemnaJednotka& a, const UzemnaJednotka& b) {
//	return this->kriterium.vyber(a) - this->kriterium->vyber(b);
//}


