#pragma once

#include "PriorityQueue.h"
#include "List/List.h"
#include <stdexcept>

namespace Structures {

	template<typename T>
	class PriorityQueueList : public PriorityQueue<T> {
	public:
		~PriorityQueueList();

		PriorityQueue<T>& operator=(const PriorityQueue<T>& other) override;
		virtual PriorityQueueList<T>& operator=(const PriorityQueueList<T>& other);

		size_t size() const override;
		void clear() override;

		T pop() override;
		T& peek() override;
		const T peek() const override;
		int peekPriority() const override;

	protected:
		PriorityQueueList(List<PriorityQueueItem<T>*> *list);
		PriorityQueueList(const PriorityQueueList<T> &other);

		virtual int indexOfPeek() const;

	protected:
		List<PriorityQueueItem<T>*> *list;
	};

	template<typename T>
	inline PriorityQueueList<T>::PriorityQueueList(List<PriorityQueueItem<T>*> *list) : PriorityQueue<T>(), list(list) {
	}

	template<typename T>
	inline PriorityQueueList<T>::PriorityQueueList(const PriorityQueueList<T> &other) : PriorityQueueList<T>(dynamic_cast<List<PriorityQueueItem<T>*>*>(other.list->clone())) {
		this->list->clear();
		*this = other;
	}

	template<typename T>
	inline PriorityQueueList<T>::~PriorityQueueList() {
		this->clear();
		delete this->list;
		this->list = nullptr;
	}

	template<typename T>
	inline PriorityQueue<T>& PriorityQueueList<T>::operator=(const PriorityQueue<T> &other) {
		if (this != &other) {
			*this = dynamic_cast<const PriorityQueueList<T>&>(other);
		}
		return *this;
	}

	template<typename T>
	inline PriorityQueueList<T>& PriorityQueueList<T>::operator=(const PriorityQueueList<T>& other) {
		if (this != &other) {
			this->clear();
			for (PriorityQueueItem<T> *item : *other.list) {
				this->list->add(new PriorityQueueItem<T>(*item));
			}
		}
		return *this;
	}

	template<typename T>
	inline size_t PriorityQueueList<T>::size() const {
		return this->list->size();
	}

	template<typename T>
	inline void PriorityQueueList<T>::clear() {
		for (PriorityQueueItem<T> *item : *this->list) {
			delete item;
			item = nullptr;
		}
		this->list->clear();
	}

	template<typename T>
	inline int PriorityQueueList<T>::indexOfPeek() const {
		int bestPriority = (*this->list)[0]->getPriority();
		int peekIndex = 0;
		int indexOfPeek = 0;

		for (PriorityQueueItem<T> *item : *this->list) {
			if (bestPriority > item->getPriority()) {
				bestPriority = item->getPriority();
				peekIndex = indexOfPeek;
			}
			++indexOfPeek;
		}
		return peekIndex;
	}

	template<typename T>
	inline T PriorityQueueList<T>::pop() {
		PriorityQueueItem<T> *item = this->list->removeAt(this->indexOfPeek());
		T itemData = item->accessData();
		delete item;
		item = nullptr;

		return itemData;
	}

	template<typename T>
	inline T & PriorityQueueList<T>::peek() {
		return (*this->list)[this->indexOfPeek()]->accessData();
	}

	template<typename T>
	inline const T PriorityQueueList<T>::peek() const {
		return (*this->list)[this->indexOfPeek()]->accessData();
	}

	template<typename T>
	inline int PriorityQueueList<T>::peekPriority() const {
		return (*this->list)[this->indexOfPeek()]->getPriority();
	}
}
