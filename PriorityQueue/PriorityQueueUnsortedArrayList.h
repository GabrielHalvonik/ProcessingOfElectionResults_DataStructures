#pragma once

#include "PriorityQueueList.h"
#include "List/ArrayList.h"

namespace Structures {

	template<typename T>
	class PriorityQueueUnsortedArrayList : public PriorityQueueList<T> {
	public:
		PriorityQueueUnsortedArrayList();
		PriorityQueueUnsortedArrayList(const PriorityQueueUnsortedArrayList<T>& other);

		Structure* clone() const override;

		virtual PriorityQueueList<T>& operator=(const PriorityQueueList<T>& other) override;
		virtual PriorityQueueUnsortedArrayList<T>& operator=(const PriorityQueueUnsortedArrayList<T>& other);

		void push(const int priority, const T& data) override;
		T pop() override;
	};

	template<typename T>
	PriorityQueueUnsortedArrayList<T>::PriorityQueueUnsortedArrayList() : PriorityQueueList<T>(new ArrayList<PriorityQueueItem<T>*>()) {
	}

	template<typename T>
	PriorityQueueUnsortedArrayList<T>::PriorityQueueUnsortedArrayList(const PriorityQueueUnsortedArrayList<T>& other) : PriorityQueueUnsortedArrayList<T>() {
		*this = other;
	}

	template<typename T>
	Structure* PriorityQueueUnsortedArrayList<T>::clone() const {
		return new PriorityQueueUnsortedArrayList<T>(*this);
	}

	template<typename T>
	inline PriorityQueueList<T> &PriorityQueueUnsortedArrayList<T>::operator=(const PriorityQueueList<T>& other) {
		return *this = dynamic_cast<const PriorityQueueUnsortedArrayList<T>&>(other);
	}

	template<typename T>
	inline PriorityQueueUnsortedArrayList<T>& PriorityQueueUnsortedArrayList<T>::operator=(const PriorityQueueUnsortedArrayList<T> &other) {
		if (this != &other) {
			PriorityQueueList<T>::operator=(other);
		}
		return *this;
	}

	template<typename T>
	void PriorityQueueUnsortedArrayList<T>::push(const int priority, const T & data) {
		this->list->add(new PriorityQueueItem<T>(priority, data));
	}

	template<typename T>
	inline T PriorityQueueUnsortedArrayList<T>::pop() {
		int index = PriorityQueueList<T>::indexOfPeek();
		if (this->size() > 1) {
			DSRoutines::swap((*this->list)[index], (*this->list)[this->list->size() - 1]);
		}
		PriorityQueueItem<T>* item = this->list->removeAt(this->list->size() - 1);

		T data = item->accessData();
		delete item;
		return data;
	}
}
