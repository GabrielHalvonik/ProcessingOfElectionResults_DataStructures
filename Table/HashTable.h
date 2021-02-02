#pragma once

#include "Table.h"
#include "LinkedTable.h"
#include "Array/Array.h"
#include "StructureIterator.h"
#include <stdexcept>

namespace Structures {

	template <typename K, typename T>
	class HashTable : public Table<K, T> {
	private:
		static const int DATA_ARRAY_SIZE = 100;
	public:
		HashTable();
		HashTable(const HashTable<K, T>& other);
		~HashTable();

		virtual Structure* clone() const;

		size_t size() const override;

		Table<K, T>& operator=(const Table<K, T>& other) override;
		virtual HashTable<K, T>& operator=(const HashTable<K, T>& other);

		T& operator[](const K key) override;
		const T operator[](const K key) const override;

		void insert(const K& key, const T& data) override;
		T remove(const K& key) override;

		bool tryFind(const K& key, T& data) override;
		bool containsKey(const K& key) override;
		void clear() override;

		Iterator<TableItem<K, T>*>* getBeginIterator() const override;
		Iterator<TableItem<K, T>*>* getEndIterator() const override;
	protected:
		Array<Table<K, T>*>* data;
		size_t size_;
	private:
		int hashFunction(const K& key) const;

	private:
		class HashTableIterator : public Iterator<TableItem<K, T>*>
		{
		public:
			HashTableIterator(const HashTable<K, T>* hashTable, int position);
			~HashTableIterator();

			Iterator<TableItem<K, T>*>& operator= (const Iterator<TableItem<K, T>*>& other) override;
			bool operator!=(const Iterator<TableItem<K, T>*>& other) override;
			TableItem<K, T>* const operator*() override;
			Iterator<TableItem<K, T>*>& operator++() override;
		private:
			const HashTable<K, T>* hashTable;
			int position;
			Iterator<TableItem<K, T>*>* iterCurr;
			Iterator<TableItem<K, T>*>* iterLast;

			void movePositionInArray();
		};
	};

	template<typename K, typename T>
	inline HashTable<K, T>::HashTable(): Table<K, T>(), data(new Array<Table<K, T>*>(DATA_ARRAY_SIZE)), size_(0) {
	}

	template<typename K, typename T>
	inline HashTable<K, T>::HashTable(const HashTable<K, T>& other): HashTable() {
		*this = other;
	}

	template<typename K, typename T>
	inline HashTable<K, T>::~HashTable() {
		this->clear();
		delete this->data;
		this->data = nullptr;
	}

	template<typename K, typename T>
	inline Structure * HashTable<K, T>::clone() const {
		return new HashTable<K, T>(*this);
	}

	template<typename K, typename T>
	inline size_t HashTable<K, T>::size() const {
		return this->size_;
	}

	template<typename K, typename T>
	inline Table<K, T>& HashTable<K, T>::operator=(const Table<K, T>& other) {
		if (this != &other) {
			*this = dynamic_cast<const HashTable<K, T>&>(other);
		}
		return *this;
	}

	template<typename K, typename T>
	inline HashTable<K, T>& HashTable<K, T>::operator=(const HashTable<K, T>& other) {
		if (this != &other) {
			this->clear();

			for (TableItem<K, T>* item : other) {
				this->insert(item->getKey(), item->accessData());
			}
		}
		return *this;
	}

	template<typename K, typename T>
	inline T & HashTable<K, T>::operator[](const K key) {
		int hash = this->hashFunction(key);

		Table<K, T>* table = (*this->data)[hash];

		if (table != nullptr) {
			 return (*table)[key];
		} else {
			throw std::out_of_range("Data not found!");
		}
	}

	template<typename K, typename T>
	inline const T HashTable<K, T>::operator[](const K key) const {
		int hash = this->hashFunction(key);

		Table<K, T>* table = (*this->data)[hash];

		if (table != nullptr) {
			return (*table)[key];
		} else {
			throw std::out_of_range("Data not found!");
		}
	}

	template<typename K, typename T>
	inline void HashTable<K, T>::insert(const K& key, const T& data) {
		int hash = this->hashFunction(key);

		Table<K, T>* table = (*this->data)[hash];

		if (table == nullptr) {
			table = new LinkedTable<K, T>();
			(*this->data)[hash] = table;
		}

		table->insert(key, data);
		++this->size_;
	}

	template<typename K, typename T>
	inline T HashTable<K, T>::remove(const K & key) {
		int hash = this->hashFunction(key);
		Table<K, T>* table = (*this->data)[hash];

		if (table != nullptr) {
			T result = table->remove(key);
			--this->size_;

			if (table->isEmpty()) {
				delete table;
				(*this->data)[hash] = nullptr;
			}
			return result;
		} else {
			throw std::logic_error("Key not found!");
		}
	}

	template<typename K, typename T>
	inline bool HashTable<K, T>::tryFind(const K & key, T & data) {
		int hash = this->hashFunction(key);

		Table<K, T>* table = (*this->data)[hash];

		return (table != nullptr) ? table->tryFind(key, data) : false;
	}

	template<typename K, typename T>
	inline bool HashTable<K, T>::containsKey(const K & key) {
		int hash = this->hashFunction(key);

		Table<K, T>* table = (*this->data)[hash];

		return (table != nullptr) ? table->containsKey(key) : false;
	}

	template<typename K, typename T>
	inline void HashTable<K, T>::clear() {
		for (int i = 0; i < DATA_ARRAY_SIZE; ++i) {
			Table<K, T>* table = (*this->data)[i];

			if (table != nullptr) {
				delete table;
				(*data)[i] = nullptr;
			}
		}
		this->size_ = 0;
	}

	template<typename K, typename T>
	inline Iterator<TableItem<K, T>*>* HashTable<K, T>::getBeginIterator() const {
		return new HashTableIterator(this, 0);
	}

	template<typename K, typename T>
	inline Iterator<TableItem<K, T>*>* HashTable<K, T>::getEndIterator() const {
		return new HashTableIterator(this, static_cast<int>(DATA_ARRAY_SIZE));
	}

	template<typename K, typename T>
	inline int HashTable<K, T>::hashFunction(const K & key) const {
		// Knuth Variant on Division: h(k) = k(k + 3) mod m.
		return (key * (key + 3)) % DATA_ARRAY_SIZE;
	}

	template<typename K, typename T>
	inline HashTable<K, T>::HashTableIterator::HashTableIterator(const HashTable<K, T>* hashTable, int position):
		Iterator<TableItem<K, T>*>(), hashTable(hashTable), position(position), iterCurr(nullptr), iterLast(nullptr) {
		movePositionInArray();
	}

	template<typename K, typename T>
	inline HashTable<K, T>::HashTableIterator::~HashTableIterator() {
		//TODO 09: HashTable<K, T>::HashTableIterator
	}

	template<typename K, typename T>
	inline Iterator<TableItem<K, T>*>& HashTable<K, T>::HashTableIterator::operator=(const Iterator<TableItem<K, T>*>& other) {
		//TODO 09: HashTable<K, T>::HashTableIterator
//		throw std::exception("HashTable<K, T>::HashTableIterator::operator=: Not implemented yet.");
	}

	template<typename K, typename T>
	inline bool HashTable<K, T>::HashTableIterator::operator!=(const Iterator<TableItem<K, T>*>& other) {
		//TODO 09: HashTable<K, T>::HashTableIterator
//		throw std::exception("HashTable<K, T>::HashTableIterator::operator!=: Not implemented yet.");
	}

	template<typename K, typename T>
	inline TableItem<K, T>* const HashTable<K, T>::HashTableIterator::operator*() {
		//TODO 09: HashTable<K, T>::HashTableIterator
//		throw std::exception("HashTable<K, T>::HashTableIterator::operator*: Not implemented yet.");
	}

	template<typename K, typename T>
	inline Iterator<TableItem<K, T>*>& HashTable<K, T>::HashTableIterator::operator++() {
		//TODO 09: HashTable<K, T>::HashTableIterator
//		throw std::exception("HashTable<K, T>::HashTableIterator::operator++: Not implemented yet.");
	}

	template<typename K, typename T>
	inline void HashTable<K, T>::HashTableIterator::movePositionInArray() {
		//TODO 09: HashTable<K, T>::HashTableIterator
//		throw std::exception("HashTable<K, T>::HashTableIterator::movePositionInArray: Not implemented yet.");
	}

}
