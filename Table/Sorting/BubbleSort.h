#pragma once

#include "Sort.h"
#include "Table/UnsortedSequenceTable.h"
#include "App/Comparator.h"

namespace Structures {

	template <typename K, typename T>
	class BubbleSort : public Sort<K, T> {
	public:
		void sort(UnsortedSequenceTable<K, T>& table) override;
		template <typename O>
		void sort(UnsortedSequenceTable<K, T>&, const Comparator<O, T>&);
	};

	template<typename K, typename T>
	inline void BubbleSort<K, T>::sort(UnsortedSequenceTable<K, T>& table) {
		bool wasSwap;
		do {
			wasSwap = false;

			for (int i = 0; i < table.size() - 1; ++i) {
				if (table.getItemAtIndex(i).getKey() > table.getItemAtIndex(i + 1).getKey()) {
					table.swap(i, i + 1);
					wasSwap = true;
					this->notify();
				}
			}

		} while (wasSwap);
	}

	template<typename K, typename T>
	template <typename O>
	inline void BubbleSort<K, T>::sort(UnsortedSequenceTable<K, T>& table, const Comparator<O, T>& cmp) {
		bool wasSwap;
		do {
			wasSwap = false;

			for (int i = 0; i < table.size() - 1; ++i) {
				if (cmp(table.getItemAtIndex(i).accessData(), table.getItemAtIndex(i + 1).accessData()) == 1) {
					table.swap(i, i + 1);
					wasSwap = true;
					this->notify();
				}
			}

		} while (wasSwap);
	}

}
