#pragma once

#include "PriorityQueueSortedArrayList.h"
#include <stdexcept>

namespace Structures {

	template<typename T>
	class PriorityQueueLimitedSortedArrayList : public PriorityQueueSortedArrayList<T> {
	public:
		PriorityQueueLimitedSortedArrayList(size_t capacity = 4);
		PriorityQueueLimitedSortedArrayList(const PriorityQueueLimitedSortedArrayList<T>& other);

		Structure* clone() const override;

		virtual PriorityQueueSortedArrayList<T>& operator=(const PriorityQueueSortedArrayList<T>& other) override;
		virtual PriorityQueueLimitedSortedArrayList<T>& operator=(const PriorityQueueLimitedSortedArrayList<T>& other);

		void push(const int priority, const T& data) override;
		PriorityQueueItem<T>* pushAndRemove(const int priority, const T& data);
		int minPriority() const;
		bool trySetCapacity(size_t capacity);

		size_t getCapacity() const;

	private:
		size_t capacity;
		size_t defaultCapacity;
	};

	template<typename T>
	PriorityQueueLimitedSortedArrayList<T>::PriorityQueueLimitedSortedArrayList(size_t capacity) : PriorityQueueSortedArrayList<T>(), defaultCapacity(capacity), capacity(capacity) {
	}

	template<typename T>
	PriorityQueueLimitedSortedArrayList<T>::PriorityQueueLimitedSortedArrayList(const PriorityQueueLimitedSortedArrayList<T>& other)
	: PriorityQueueSortedArrayList<T>(other), capacity(other.capacity) { }

	template<typename T>
	Structure* PriorityQueueLimitedSortedArrayList<T>::clone() const {
		return new PriorityQueueLimitedSortedArrayList<T>(*this);
	}

	template<typename T>
	inline PriorityQueueSortedArrayList<T>& PriorityQueueLimitedSortedArrayList<T>::operator=(const PriorityQueueSortedArrayList<T>& other) {
		return *this = dynamic_cast<const PriorityQueueLimitedSortedArrayList<T>&>(other);
	}

	template<typename T>
	inline PriorityQueueLimitedSortedArrayList<T>& PriorityQueueLimitedSortedArrayList<T>::operator=(const PriorityQueueLimitedSortedArrayList<T>& other) {
		if (this != &other) {
			PriorityQueueLimitedSortedArrayList<T>::operator=(other);
			this->capacity = other.capacity;
		}
		return *this;
	}

	template<typename T>
	void PriorityQueueLimitedSortedArrayList<T>::push(const int priority, const T & data) {
		if (this->list->size() == this->capacity) {
			throw std::logic_error("PriorityQueueLimitedSortedArrayList<T>::push...List is full...");
		}

		PriorityQueueSortedArrayList<T>::push(priority, data);
	}

	template<typename T>
	inline PriorityQueueItem<T>* PriorityQueueLimitedSortedArrayList<T>::pushAndRemove(const int priority, const T &data) {
		PriorityQueueItem<T>* itemWithWorstPriority = nullptr;
		if (this->list->size() == this->capacity) {
			if (priority > (*this->list)[0]->getPriority()) {
				itemWithWorstPriority = new PriorityQueueItem<T>(priority, data);
				return itemWithWorstPriority;

			} else {
				itemWithWorstPriority = (*this->list)[0];
				this->list->removeAt(0);
			}
		}

		PriorityQueueSortedArrayList<T>::push(priority, data);

		return itemWithWorstPriority;
	}

	template<typename T>
	inline int PriorityQueueLimitedSortedArrayList<T>::minPriority() const {
//		if (this->list->isEmpty()) {
//			throw std::logic_error("PriorityQueueLimitedSortedArrayList<T>::minPriority()...List is empty...");
//		}
		return (*this->list)[0]->getPriority();
	}

	template<typename T>
	inline bool PriorityQueueLimitedSortedArrayList<T>::trySetCapacity(size_t capacity) {
		if (this->list->size() > capacity || capacity < this->defaultCapacity) {
			return false;
		}
		this->capacity = capacity;
		return true;
	}

	template<typename T>
	size_t PriorityQueueLimitedSortedArrayList<T>::getCapacity() const {
		return this->capacity;
	}
}
