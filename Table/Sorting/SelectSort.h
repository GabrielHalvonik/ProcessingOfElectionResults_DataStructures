#pragma once

#include "Sort.h"
#include "Table/UnsortedSequenceTable.h"

namespace Structures {

	template <typename K, typename T>
	class SelectSort : public Sort<K, T> {
	public:
		void sort(UnsortedSequenceTable<K, T>& table) override;
	};

	template<typename K, typename T>
	inline void SelectSort<K, T>::sort(UnsortedSequenceTable<K, T>& table) {
		for (int i = 0; i < table.size() - 1; ++i) {
			int min	= i;
			for (int j = 0; j < table.size(); ++j) {
				if (table.getItemAtIndex(j).getKey() < table.getItemAtIndex(min).getKey()) {
					min = j;
				}
			}
			table.swap(i, min);
			this->notify();
		}
	}

}
