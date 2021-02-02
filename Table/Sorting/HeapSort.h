#pragma once

#include "Sort.h"
#include "Table/UnsortedSequenceTable.h"

namespace Structures {

	template <typename K, typename T>
	class HeapSort : public Sort<K, T> {
	public:
		void sort(UnsortedSequenceTable<K, T>& table) override;
	};

	template<typename K, typename T>
	inline void HeapSort<K, T>::sort(UnsortedSequenceTable<K, T>& table) {
		//TODO 12: HeapSort
//		throw std::exception("HeapSort<K, T>::sort: Not implemented yet.");
	}

}
