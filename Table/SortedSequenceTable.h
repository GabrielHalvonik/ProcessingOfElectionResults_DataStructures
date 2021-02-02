#pragma once

#include "List/ArrayList.h"
#include "Table/SequenceTable.h"

namespace Structures {

	template <typename K, typename T>
	class SortedSequenceTable : public SequenceTable<K, T> {
	public:
		SortedSequenceTable();
		SortedSequenceTable(const SortedSequenceTable<K, T>& other);

		Structure* clone() const override;

		void insert(const K& key, const T& data) override;
	protected:
		TableItem<K, T>* findTableItem(const K& key) const override;
	private:
		int indexOfKey(const K& key, int indexStart, int indexEnd, bool& found) const;
	};

	template<typename K, typename T>
	inline SortedSequenceTable<K, T>::SortedSequenceTable() : SequenceTable<K, T>(new ArrayList<TableItem<K, T>*>()) {
	}

	template<typename K, typename T>
	inline SortedSequenceTable<K, T>::SortedSequenceTable(const SortedSequenceTable<K, T>& other) : SortedSequenceTable() {
		SequenceTable<K, T>::operator=(other);
//		*this = other;
	}

	template<typename K, typename T>
	inline Structure * SortedSequenceTable<K, T>::clone() const {
		return new SortedSequenceTable<K, T>(*this);
	}

	template<typename K, typename T>
	inline void SortedSequenceTable<K, T>::insert(const K & key, const T & data) {
		bool found = false;
		int index =  this->indexOfKey(key, 0 ,static_cast<int>(this->size()), found);
		if (!found) {
			TableItem<K, T>* item = new TableItem<K, T>(key, data);
			this->list->insert(item, index);
		} else {
			std::logic_error("SortedSequenceTable<K, T>::insert...sequence already contains key.");
		}
	}

	template<typename K, typename T>
	inline TableItem<K, T>* SortedSequenceTable<K, T>::findTableItem(const K & key) const {
		if (this->size() == 0) {
			return nullptr;
		} else {
			bool found = false;
			int index =	this->indexOfKey(key, 0, static_cast<int>(this->size()), found);
			return found ? (*this->list)[index] : nullptr;
		}
	}

	template<typename K, typename T>
	inline int SortedSequenceTable<K, T>::indexOfKey(const K & key, int indexStart, int indexEnd, bool & found) const {
		int indexSize = static_cast<int>(this->size());
		if (indexStart == indexSize) {
			found = false;
			return indexSize;
		}

		int pivot = (indexStart + indexEnd) / 2;
		K keyAtPivot = (*this->list)[pivot]->getKey();

		if (keyAtPivot == key) {
			found = true;
			return pivot;
		} else {
			if (indexStart == indexEnd) {
				found = false;
				return (key < keyAtPivot) ? pivot : pivot + 1;
			} else {
				if (keyAtPivot < key) {
					indexStart = pivot + 1;
				} else {
					indexEnd = pivot;
				}
				return this->indexOfKey(key, indexStart, indexEnd, found);
			}
		}
	}
}
