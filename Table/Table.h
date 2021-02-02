#pragma once

#include "Structure.h"
#include "StructureIterator.h"

namespace Structures {

	template <typename K, typename T>
	class TableItem : public DataItem<T> {
	public:
		TableItem(K key, T data);

		K getKey();
	private:
		K key;
	};

	template <typename K, typename T>
	class Table : public Structure, public Iterable<TableItem<K, T>*> {
	public:
		virtual Structure* clone() const override = 0;

		virtual size_t size() const override = 0;

		Structure& operator=(const Structure& other) override;
		virtual Table<K, T>& operator=(const Table<K, T>& other) = 0;

		virtual T& operator[](const K key) = 0;
		virtual const T operator[](const K key) const = 0;

		virtual void insert(const K& key, const T& data) = 0;
		virtual T remove(const K& key) = 0;
		virtual bool tryFind(const K& key, T& value) = 0;
		virtual bool containsKey(const K& key) = 0;

		virtual void clear() = 0;

		virtual Iterator<TableItem<K, T>*>* getBeginIterator() const override = 0;
		virtual Iterator<TableItem<K, T>*>* getEndIterator() const override = 0;
	protected:
		Table();
	};

	template<typename K, typename T>
	inline TableItem<K, T>::TableItem(K key, T data): DataItem<T>(data), key(key) {
	}

	template<typename K, typename T>
	inline K TableItem<K, T>::getKey() {
		return this->key;
	}

	template<typename K, typename T>
	inline Table<K, T>::Table(): Structure(), Iterable<TableItem<K, T>*>() {
	}

	template<typename K, typename T>
	inline Structure& Table<K, T>::operator=(const Structure & other) {
		if (this != &other) {
			*this = dynamic_cast<const Table<K, T>&>(other);
		}
		return *this;
	}

}

