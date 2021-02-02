#pragma once

#include "PriorityQueue.h"
#include "PriorityQueueLimitedSortedArrayList.h"
#include "List/LinkedList.h"
#include <cmath>

namespace Structures {

	template<typename T>
	class PriorityQueueTwoLists : public PriorityQueue<T> {
	public:
		PriorityQueueTwoLists(size_t capacity = 4);

		PriorityQueueTwoLists(const PriorityQueueTwoLists<T>& other);
		~PriorityQueueTwoLists();

		Structure* clone() const override;

		PriorityQueue<T>& operator=(const PriorityQueue<T>& other) override;
		PriorityQueueTwoLists<T>& operator=(const PriorityQueueTwoLists<T>& other);

		size_t size() const override;
		void clear() override;

		void push(const int priority, const T& data) override;
		T pop() override;

		T& peek() override;
		const T peek() const override;
		int peekPriority() const override;

	private:
		PriorityQueueLimitedSortedArrayList<T>* shortList;
		LinkedList<PriorityQueueItem<T>*>* longList;
	};

	template<typename T>
	PriorityQueueTwoLists<T>::PriorityQueueTwoLists(size_t capacity) : PriorityQueue<T>(), shortList(new PriorityQueueLimitedSortedArrayList<T>(capacity)),
	longList(new LinkedList<PriorityQueueItem<T>*>) { }

	template<typename T>
	PriorityQueueTwoLists<T>::PriorityQueueTwoLists(const PriorityQueueTwoLists<T>& other) : PriorityQueueTwoLists<T>() {
		*this = other;
	}

	template<typename T>
	PriorityQueueTwoLists<T>::~PriorityQueueTwoLists() {
		this->clear();
		delete this->shortList;
		this->shortList = nullptr;
		delete this->longList;
		this->longList = nullptr;
	}

	template<typename T>
	Structure * PriorityQueueTwoLists<T>::clone() const {
		return new PriorityQueueTwoLists<T>(*this);
	}

	template<typename T>
	PriorityQueue<T>& PriorityQueueTwoLists<T>::operator=(const PriorityQueue<T>& other) {
		return *this = dynamic_cast<const PriorityQueueTwoLists<T>&>(other);
	}

	template<typename T>
	PriorityQueueTwoLists<T>& PriorityQueueTwoLists<T>::operator=(const PriorityQueueTwoLists<T>& other) {
		if (this != &other) {
			this->clear();
			delete this->shortList;
			delete this->longList;

			this->shortList = new PriorityQueueLimitedSortedArrayList<T>(*other.shortList);
			this->longList = new LinkedList<PriorityQueueItem<T>*>;

			for (PriorityQueueItem<T>* item : *other.longList) {
				this->longList->add(new PriorityQueueItem<T>(*item));
			}
		}
		return *this;
	}

	template<typename T>
	size_t PriorityQueueTwoLists<T>::size() const {
		return this->shortList->size() + this->longList->size();
	}

	template<typename T>
	void PriorityQueueTwoLists<T>::clear() {
		this->shortList->clear();

		for (PriorityQueueItem<T> *item : *this->longList) {
			delete item;
			item = nullptr;
		}

		this->longList->clear();
	}

	template<typename T>
	void PriorityQueueTwoLists<T>::push(const int priority, const T & data) {
		if (this->longList->isEmpty() || priority < this->shortList->minPriority()) {
			PriorityQueueItem<T> *removedItem = this->shortList->pushAndRemove(priority, data);
			if (removedItem != nullptr) {
				this->longList->add(removedItem);
			}
		} else {
			this->longList->add(new PriorityQueueItem<T>(priority, data));
		}
	}

	template<typename T>
	T PriorityQueueTwoLists<T>::pop() {
		if (this->isEmpty()) {
			throw std::logic_error("PriorityQueueTwoLists<T>::pop...List is empty...");
		}

		T data = this->shortList->pop();

		if (this->shortList->isEmpty() && !this->longList->isEmpty()) {
			std::size_t newCapacity = static_cast<std::size_t>(std::sqrt(this->longList->size()));
//			if (newCapacity > shortList->getCapacity()) {
				this->shortList->trySetCapacity(newCapacity);
//			}

			LinkedList<PriorityQueueItem<T>*>* tempLongList = new LinkedList<PriorityQueueItem<T>*>;
			PriorityQueueItem<T> *tempItem = nullptr;

			for (PriorityQueueItem<T> *item : *this->longList) {
				tempItem = this->shortList->pushAndRemove(item->getPriority(), item->accessData());
				if (tempItem != nullptr) {
					tempLongList->add(tempItem);
				}
				delete item;
				item = nullptr;
			}
			delete this->longList;
			this->longList = tempLongList;
		}
		return data;
	}

	template<typename T>
	T &PriorityQueueTwoLists<T>::peek() {
		if (this->shortList->isEmpty()) {
			throw std::logic_error("PriorityQueueTwoLists<T>::peek()...List is empty...");
		}
		return this->shortList->peek();
	}

	template<typename T>
	const T PriorityQueueTwoLists<T>::peek() const {
		if (this->shortList->isEmpty()) {
			throw std::logic_error("PriorityQueueTwoLists<T>::peek()...List is empty...");
		}
		return this->shortList->peek();
	}

	template<typename T>
	int PriorityQueueTwoLists<T>::peekPriority() const {
		if (this->shortList->isEmpty()) {
			throw std::logic_error("PriorityQueueTwoLists<T>::peek()...List is empty...");
		}
		return this->shortList->peekPriority();
	}
}
