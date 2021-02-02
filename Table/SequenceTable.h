#pragma once

#include "Table.h"
#include "List/List.h"
#include <stdexcept>

namespace Structures  {

	template <typename K, typename T>
	class SequenceTable : public Table<K, T> {
	public:
		~SequenceTable();

		virtual Structure* clone() const = 0;

		size_t size() const override;

		Table<K, T>& operator=(const Table<K, T>& other) override;
		SequenceTable<K, T>& operator=(const SequenceTable<K, T>& other);

		T& operator[](const K key) override;
		const T operator[](const K key) const override;

		void insert(const K& key, const T& data) override;
		T remove(const K& key) override;
		bool tryFind(const K & key, T & data);
		bool containsKey(const K& key) override;
		void clear() override;

		Iterator<TableItem<K, T>*>* getBeginIterator() const override;
		Iterator<TableItem<K, T>*>* getEndIterator() const override;
	protected:
		SequenceTable(List<TableItem<K, T>*>* list);

		virtual TableItem<K, T>* findTableItem(const K& key) const;
	protected:
		List<TableItem<K, T>*>* list;
	};

	template<typename K, typename T>
	inline SequenceTable<K, T>::~SequenceTable() {
		this->clear();
		delete this->list;
		this->list = nullptr;
	}

	template<typename K, typename T>
	inline size_t SequenceTable<K, T>::size() const {
		return list->size();
	}

	template<typename K, typename T>
	inline Table<K, T>& SequenceTable<K, T>::operator=(const Table<K, T>& other) {
		if (this != &other) {
			*this = dynamic_cast<const SequenceTable<K, T>&>(other);
		}
		return *this;
	}

	template<typename K, typename T>
	inline SequenceTable<K, T>& SequenceTable<K, T>::operator=(const SequenceTable<K, T>& other) {
		if (this != &other) {
			this->clear();
			for (TableItem<K, T>* item : *other.list) {
				this->list->add(new TableItem<K, T>(*item));
			}
		}
		return *this;
	}

	template<typename K, typename T>
	inline T & SequenceTable<K, T>::operator[](const K key) {
		TableItem<K, T>* item = this->findTableItem(key);
		if (item != nullptr) {
			 return item->accessData();
		} else {
			throw std::out_of_range("SequenceTable<K, T>::operator[]...Data not found.");
		}
	}

	template<typename K, typename T>
	inline const T SequenceTable<K, T>::operator[](const K key) const {
		TableItem<K, T>* item = this->findTableItem(key);
		if (item != nullptr) {
			return item->accessData();
		} else {
			throw std::out_of_range("SequenceTable<K, T>::operator[]...Data not found.");
		}
	}

	template<typename K, typename T>
	inline void SequenceTable<K, T>::insert(const K& key, const T& data) {
		if (!this->containsKey(key)) {
			TableItem<K, T>* tableItem = new TableItem<K, T>(key, data);
			this->list->add(tableItem);
		} else {
			throw std::out_of_range("SequenceTable<K, T>::insert...Table already contains key.");
		}
	}

	template<typename K, typename T>
	inline T SequenceTable<K, T>::remove(const K& key) {
		TableItem<K, T>* tableItem = this->findTableItem(key);

		if (tableItem != nullptr) {
			this->list->tryRemove(tableItem);
			T result = tableItem->accessData();
			delete tableItem;
			tableItem = nullptr;
			return result;
		} else {
			throw std::out_of_range("SequenceTable<K, T>::remove...Key not found.");
		}
	}

	template<typename K, typename T>
	inline bool SequenceTable<K, T>::tryFind(const K& key, T& data) {
		TableItem<K, T>* item = this->findTableItem(key);
		if (item != nullptr) {
			data = item->accessData();
			return true;
		}
		return false;
	}

	template<typename K, typename T>
	inline bool SequenceTable<K, T>::containsKey(const K& key) {
		return this->findTableItem(key) != nullptr;
	}

	template<typename K, typename T>
	inline void SequenceTable<K, T>::clear() {
		for (TableItem<K, T>* item : *this->list) {
			delete item;
			item = nullptr;
		}
		this->list->clear();
	}

	template<typename K, typename T>
	inline Iterator<TableItem<K, T>*>* SequenceTable<K, T>::getBeginIterator() const {
		return this->list->getBeginIterator();
	}

	template<typename K, typename T>
	inline Iterator<TableItem<K, T>*>* SequenceTable<K, T>::getEndIterator() const {
		return this->list->getEndIterator();
	}

	template<typename K, typename T>
	inline SequenceTable<K, T>::SequenceTable(List<TableItem<K, T>*>* list) : Table<K, T>(), list(list) {
	}

	template<typename K, typename T>
	inline TableItem<K, T>* SequenceTable<K, T>::findTableItem(const K& key) const {
		for (TableItem<K, T>* item : *this->list) {
			if (item->getKey() == key) {
				return item;
			}
		}
		return nullptr;
	}

}
