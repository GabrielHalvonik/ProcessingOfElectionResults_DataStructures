#pragma once

#include "Sort.h"
#include "Table/UnsortedSequenceTable.h"
#include "Queue/ExplicitQueue.h"
#include "Data/Pair.h"
#include "App/Comparator.h"

namespace Structures {

	template <typename K, typename T>
	class MergeSort : public Sort<K, T> {
	public:
		void sort(UnsortedSequenceTable<K, T>& table) override;
		template <typename O>
		void sort(UnsortedSequenceTable<K, T>& table, const Comparator<O, T>&);

	private:
		void rozdel(int, ExplicitQueue<Pair<K, T>>&, ExplicitQueue<Pair<K, T>>&, ExplicitQueue<Pair<K, T>>&);
		void spoj(int, ExplicitQueue<Pair<K, T>>&, ExplicitQueue<Pair<K, T>>&, ExplicitQueue<Pair<K, T>>&);
	};

	template<typename K, typename T>
	inline void MergeSort<K, T>::sort(UnsortedSequenceTable<K, T>& table) {
		ExplicitQueue<Pair<K, T>> frontRozdel1;
		ExplicitQueue<Pair<K, T>> frontRozdel2;
		ExplicitQueue<Pair<K, T>> frontSpoj;

		for (TableItem<K, T>* temp : table) {
			frontSpoj.push({temp->getKey(), temp->accessData()});
		}
		int i = 1;

		while (i < table.size()) {
			this->rozdel(i, frontSpoj, frontRozdel1, frontRozdel2);
			this->spoj(i, frontSpoj, frontRozdel1, frontRozdel2);
			i *= 2;
		}
		this->rozdel(i, frontSpoj, frontRozdel1, frontRozdel2);
		this->spoj(i, frontSpoj, frontRozdel1, frontRozdel2);
		table.clear();

		while (!frontSpoj.isEmpty()) {
			Pair<K, T> par = frontSpoj.pop();
			table.insert(par.first, par.second);
		}
	}

	template<typename K, typename T>
	void MergeSort<K, T>::rozdel(int n, ExplicitQueue<Pair<K, T>>& spoj, ExplicitQueue<Pair<K, T>>& rozdel1, ExplicitQueue<Pair<K, T>>& rozdel2) {
		int pocet = 0;
		bool prvy = true;
		while (!spoj.isEmpty()) {
			if (pocet % n == 0) {
				pocet = 0;
				prvy = !prvy;
			}
			if (prvy == true) {
				rozdel1.push(spoj.pop());
			} else {
				rozdel2.push(spoj.pop());
			}
			++pocet;
		}
	}

	template<typename K, typename T>
	void MergeSort<K, T>::spoj(int n, ExplicitQueue<Pair<K, T>>& spoj, ExplicitQueue<Pair<K, T>>& rozdel1, ExplicitQueue<Pair<K, T>>& rozdel2) {
		int prvych = 0;
		int druhych = 0;

		do {
			if (prvych == 0 && druhych == 0) {
				prvych = (n < rozdel1.size()) ? n : rozdel1.size();
				druhych = (n < rozdel2.size()) ? n : rozdel2.size();
			}

			K* key1 = (prvych > 0) ? &rozdel1.peek().first : nullptr;
			K* key2 = (druhych > 0) ? &rozdel2.peek().first : nullptr;

			if (key1 != nullptr && key2 != nullptr) {
				if (*key1 < *key2) {
					--prvych;
					spoj.push(rozdel1.pop());
				} else {
					--druhych;
					spoj.push(rozdel2.pop());
				}
			} else {
				if (key1 != nullptr) {
					--prvych;
					spoj.push(rozdel1.pop());
				} else if (key2 != nullptr) {
					--druhych;
					spoj.push(rozdel2.pop());
				}
			}

		} while (!rozdel1.isEmpty() || !rozdel2.isEmpty());
	}

	template<typename K, typename T>
	template <typename O>
	inline void MergeSort<K, T>::sort(UnsortedSequenceTable<K, T>& table, const Comparator<O, T>& cmp) {

	}

}
