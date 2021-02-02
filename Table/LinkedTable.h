#pragma once

#include "List/LinkedList.h"
#include "SequenceTable.h"

namespace Structures {

	template <typename K, typename T>
	class LinkedTable : public SequenceTable<K, T> {
	public:
		LinkedTable();
		LinkedTable(const LinkedTable<K, T>& other);

		Structure* clone() const override;

	};

	template<typename K, typename T>
	inline LinkedTable<K, T>::LinkedTable() : SequenceTable<K, T>(new LinkedList<TableItem<K, T>*>()) {
	}

	template<typename K, typename T>
	inline LinkedTable<K, T>::LinkedTable(const LinkedTable<K, T>& other) : LinkedTable() {
		*this = other;
	}

	template<typename K, typename T>
	inline Structure * LinkedTable<K, T>::clone() const {
		return new LinkedTable<K, T>(*this);
	}

}
