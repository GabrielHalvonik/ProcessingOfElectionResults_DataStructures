#pragma once

#include "Sort.h"
#include "Table/UnsortedSequenceTable.h"
#include "App/Comparator.h"

namespace Structures {

	template <typename K, typename T>
	class QuickSort : public Sort<K, T> {
	public:
		void sort(UnsortedSequenceTable<K, T>& table) override;
		template <typename O>
		void sort(UnsortedSequenceTable<K, T>& table, const Comparator<O, T>&);

	private:
		void quick(UnsortedSequenceTable<K, T>&, int, int);
		template <typename O>
		void quick(UnsortedSequenceTable<K, T>&, int, int, const Comparator<O, T>&);
	};

	template<typename K, typename T>
	inline void QuickSort<K, T>::sort(UnsortedSequenceTable<K, T>& table) {
		this->quick(table, 0, table.size() - 1);
	}

	template<typename K, typename T>
	template <typename O>
	inline void QuickSort<K, T>::sort(UnsortedSequenceTable<K, T>& table, const Comparator<O, T>& cmp) {
		this->quick(table, 0, table.size() - 1, cmp);
	}

	template<typename K, typename T>
	void QuickSort<K, T>::quick(UnsortedSequenceTable<K, T>& table, int min, int max) {
		K pivot = table.getItemAtIndex((min + max) / 2).getKey();
		int lavy = min;
		int pravy = max;
		do {
			while (table.getItemAtIndex(lavy).getKey() < pivot) {
				++lavy;
			}
			while (table.getItemAtIndex(pravy).getKey() > pivot) {
				--pravy;
			}

			if (lavy <= pravy) {
				table.swap(lavy, pravy);
				++lavy;
				--pravy;
				this->notify();
			}

		} while(lavy <= pravy);

		if (min < pravy) {
			this->quick(table, min, pravy);
		}
		if (lavy < max) {
			this->quick(table, lavy, max);
		}
	}

	template<typename K, typename T>
	template <typename O>
	void QuickSort<K, T>::quick(UnsortedSequenceTable<K, T>& table, int min, int max, const Comparator<O, T>& cmp) {
		T pivot = table.getItemAtIndex((min + max) / 2).accessData();
		int lavy = min;
		int pravy = max;
		do {
			while ((cmp.isAsc()) ? cmp(pivot, table.getItemAtIndex(lavy).accessData()) == 1 : cmp(pivot, table.getItemAtIndex(lavy).accessData()) == -1) {
				++lavy;
			}
			while ((cmp.isAsc()) ? cmp(table.getItemAtIndex(pravy).accessData(), pivot) == 1 : cmp(table.getItemAtIndex(pravy).accessData(), pivot) == -1) {
				--pravy;
			}

			if (lavy <= pravy) {
				table.swap(lavy, pravy);
				++lavy;
				--pravy;
				this->notify();
			}

		} while(lavy <= pravy);

		if (min < pravy) {
			this->quick(table, min, pravy, cmp);
		}
		if (lavy < max) {
			this->quick(table, lavy, max, cmp);
		}
	}
}
