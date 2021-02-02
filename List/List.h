#pragma once

#include "Structure.h"
#include "StructureIterator.h"
#include "DSStructureTypes.h"

namespace Structures {

	template<typename T>
	class List : public Structure, public Iterable<T> {
	public:
		virtual Structure* clone() const override = 0;

		virtual size_t size() const override = 0;

		Structure& operator=(const Structure& other) override;
		virtual List<T>& operator=(const List<T>& other) = 0;

		virtual T& operator[](const int index) = 0;
		virtual const T operator[](const int index) const = 0;

		virtual void add(const T& data) = 0;
		virtual void insert(const T& data, const int index) = 0;
		virtual bool tryRemove(const T& data) = 0;
		virtual T removeAt(const int index) = 0;
		virtual int getIndexOf(const T& data) = 0;
		virtual void clear() = 0;

		virtual Iterator<T>* getBeginIterator() const override = 0;
		virtual Iterator<T>* getEndIterator() const override = 0;
	protected:
		List();
	};

	template<typename T>
	inline Structure& List<T>::operator=(const Structure & other) {
		if (this != &other) {
			*this = dynamic_cast<const List<T>&>(other);
		}
		return *this;
	}

	template<typename T>
	inline List<T>::List() : Structure(), Iterable<T>() {
	}

}
