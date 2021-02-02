#pragma once

#include "PriorityQueueList.h"
#include "List/ArrayList.h"
#include <stdexcept>

namespace Structures {

	template<typename T>
	class PriorityQueueSortedArrayList : public PriorityQueueList<T> {
	public:
		PriorityQueueSortedArrayList();
		PriorityQueueSortedArrayList(const PriorityQueueSortedArrayList<T>& other);

		Structure* clone() const override;

		virtual PriorityQueueList<T>& operator=(const PriorityQueueList<T>& other) override;
		virtual PriorityQueueSortedArrayList<T>& operator=(const PriorityQueueSortedArrayList<T>& other);

		void push(const int priority, const T& data) override;

	protected:
		int indexOfPeek() const override;
	};

	template<typename T>
	inline PriorityQueueSortedArrayList<T>::PriorityQueueSortedArrayList() : PriorityQueueList<T>(new ArrayList<PriorityQueueItem<T>*>()) {
	}

	template<typename T>
	inline PriorityQueueSortedArrayList<T>::PriorityQueueSortedArrayList(const PriorityQueueSortedArrayList<T> &other) : PriorityQueueSortedArrayList<T>() {
		*this = other;
	}

	template<typename T>
	inline Structure* PriorityQueueSortedArrayList<T>::clone() const {
		return new PriorityQueueSortedArrayList<T>(*this);
	}

	template<typename T>
	inline PriorityQueueList<T> &PriorityQueueSortedArrayList<T>::operator=(const PriorityQueueList<T> &other) {
		return *this = dynamic_cast<const PriorityQueueSortedArrayList<T>&>(other);
	}

	template<typename T>
	inline PriorityQueueSortedArrayList<T>& PriorityQueueSortedArrayList<T>::operator=(const PriorityQueueSortedArrayList<T>& other) {
		if (this != &other) {
			PriorityQueueList<T>::operator=(other);
		}
		return *this;
	}

	template<typename T>
	inline void PriorityQueueSortedArrayList<T>::push(const int priority, const T& data) {
		if (this->list->isEmpty() || priority <= this->peekPriority()) {
			this->list->add(new PriorityQueueItem<T>(priority, data));
		} else {
			int index;
			for (index = 0; (*this->list)[index]->getPriority() > priority; index++) {}
				this->list->insert(new PriorityQueueItem<T>(priority, data), index);
		}
	}

	template<typename T>
	inline int PriorityQueueSortedArrayList<T>::indexOfPeek() const {
//		if (this->list->isEmpty()) {
//			throw std::logic_error("PriorityQueueSortedArrayList<T>::indexOfPeek(), PriorityQueue is empty.");
//		}
		return this->list->size() - 1;
	}

}
