#pragma once

#include <initializer_list>
#include "List/ArrayList.h"
#include "SequenceTable.h"
#include "SortedSequenceTable.h"

namespace Structures {

	template <typename K, typename T>
	class UnsortedSequenceTable : public SequenceTable<K, T> {
	public:
		UnsortedSequenceTable();
		UnsortedSequenceTable(const std::initializer_list<std::pair<K, T>>&);
		UnsortedSequenceTable(const UnsortedSequenceTable<K, T>& other);
		UnsortedSequenceTable(const SortedSequenceTable<K, T>& other);
		UnsortedSequenceTable(const SequenceTable<K, T>& other);

		Structure* clone() const override;

		TableItem<K, T>& getItemAtIndex(int index);

		void swap(int indexFirst, int indexSecond);
		static void swap(TableItem<K, T>& first, TableItem<K, T>& second);
	};

	template<typename K, typename T>
	inline UnsortedSequenceTable<K, T>::UnsortedSequenceTable()	: SequenceTable<K, T>(new ArrayList<TableItem<K, T>*>()) {
	}

	template<typename K, typename T>
	UnsortedSequenceTable<K, T>::UnsortedSequenceTable(const std::initializer_list<std::pair<K, T>>& iList) : UnsortedSequenceTable<K, T>() {
		for (const std::pair<K, T>& temp : iList) {
			this->insert(temp.first, temp.second);
		}
	}

	template<typename K, typename T>
	inline UnsortedSequenceTable<K, T>::UnsortedSequenceTable(const UnsortedSequenceTable<K, T>& other) : UnsortedSequenceTable() {
		SequenceTable<K, T>::operator=(other);
	}

	template<typename K, typename T>
	inline UnsortedSequenceTable<K, T>::UnsortedSequenceTable(const SortedSequenceTable<K, T>& other) : UnsortedSequenceTable() {
		SequenceTable<K, T>::operator=(other);
	}

	template<typename K, typename T>
	inline UnsortedSequenceTable<K, T>::UnsortedSequenceTable(const SequenceTable<K, T>& other) : UnsortedSequenceTable() {
		SequenceTable<K, T>::operator=(other);
	}

	template<typename K, typename T>
	inline Structure * UnsortedSequenceTable<K, T>::clone() const {
		return new UnsortedSequenceTable<K, T>(*this);
	}

	template<typename K, typename T>
	inline TableItem<K, T>& UnsortedSequenceTable<K, T>::getItemAtIndex(int index) {
		return *(*this->list)[index];
	}

	template<typename K, typename T>
	inline void UnsortedSequenceTable<K, T>::swap(int indexFirst, int indexSecond) {
		this->swap(getItemAtIndex(indexFirst), getItemAtIndex(indexSecond));
	}

	template<typename K, typename T>
	inline void UnsortedSequenceTable<K, T>::swap(TableItem<K, T>& first, TableItem<K, T>& second) {
		TableItem<K, T> third = first;
		first = second;
		second = third;
	}

}
