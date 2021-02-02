#pragma once

#include "PriorityQueueList.h"
#include "List/LinkedList.h"

namespace Structures {

	template<typename T>
	class PriorityQueueLinkedList : public PriorityQueueList<T> {
	public:
		PriorityQueueLinkedList();
		PriorityQueueLinkedList(const PriorityQueueLinkedList<T>& other);

		Structure* clone() const override;

		virtual PriorityQueueList<T>& operator=(const PriorityQueueList<T>& other) override;
		virtual PriorityQueueLinkedList<T>& operator=(const PriorityQueueLinkedList<T>& other);

		void push(const int priority, const T& data) override;
	};

	template<typename T>
	PriorityQueueLinkedList<T>::PriorityQueueLinkedList() : PriorityQueueList<T>(new LinkedList<PriorityQueueItem<T>*>()) {
	}

	template<typename T>
	PriorityQueueLinkedList<T>::PriorityQueueLinkedList(const PriorityQueueLinkedList<T>& other) : PriorityQueueLinkedList<T>() {
		*this = other;
	}

	template<typename T>
	inline Structure * PriorityQueueLinkedList<T>::clone() const {
		return new PriorityQueueLinkedList(*this);
	}

	template<typename T>
	inline PriorityQueueList<T>& PriorityQueueLinkedList<T>::operator=(const PriorityQueueList<T>& other) {
		return *this = dynamic_cast<const PriorityQueueLinkedList<T>&>(other);
	}

	template<typename T>
	inline PriorityQueueLinkedList<T>& PriorityQueueLinkedList<T>::operator=(const PriorityQueueLinkedList<T>& other) {
		if (this != &other) {
			PriorityQueueList<T>::operator=(other);
		}
		return *this;
	}

	template<typename T>
	inline void PriorityQueueLinkedList<T>::push(const int priority, const T & data) {
		this->list->add(new PriorityQueueItem<T>(priority, data));
	}
}
