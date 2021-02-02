#pragma once

#include "Sort.h"
#include "Table/UnsortedSequenceTable.h"
#include <random>
#include <chrono>

namespace Structures {

	template <typename K, typename T>
	class Shuffle : public Sort<K, T> {
	public:
		void sort(UnsortedSequenceTable<K, T>& table) override;
	};

	template<typename K, typename T>
	inline void Shuffle<K, T>::sort(UnsortedSequenceTable<K, T>& table) {
		int size = static_cast<int>(table.size());
		unsigned seed = static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count());
		std::default_random_engine generator(seed);
		std::uniform_int_distribution<int> uniform(0, size - 1);

		for (int i = 0; i < size * 2; i++) {
			table.swap(uniform(generator), uniform(generator));
			this->notify();
		}
	}

}
