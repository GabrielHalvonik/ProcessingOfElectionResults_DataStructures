#pragma once

#include "Structure.h"

namespace Structures {

	template<typename T>
	class PriorityQueueItem : public DataItem<T> {
	public:
		PriorityQueueItem(int priority, T data);
		PriorityQueueItem(const PriorityQueueItem<T>& other);

		int getPriority();

	private:
		int priority_;
	};

	template<typename T>
	class PriorityQueue : public Structure {
	public:
		virtual Structure* clone() const override = 0;

		Structure& operator=(const Structure& other) override;
		virtual PriorityQueue<T>& operator=(const PriorityQueue<T>& other) = 0;

		virtual size_t size() const override = 0;
		virtual void clear() = 0;
		virtual void push(const int priority, const T& data) = 0;
		virtual T pop() = 0;
		virtual T& peek() = 0;
		virtual const T peek() const = 0;
		virtual int peekPriority() const = 0;
	protected:
		PriorityQueue();
		PriorityQueue(const PriorityQueue<T>& other);
		PriorityQueue(PriorityQueue<T>&& other);
	};

	template<typename T>
	inline PriorityQueueItem<T>::PriorityQueueItem(int priority, T data) : DataItem<T>(data), priority_(priority) {
	}

	template<typename T>
	inline PriorityQueueItem<T>::PriorityQueueItem(const PriorityQueueItem<T>& other) : DataItem<T>(other), priority_(other.priority_) {
	}

	template<typename T>
	inline int PriorityQueueItem<T>::getPriority() {
		return priority_;
	}

	template<typename T>
	inline Structure & PriorityQueue<T>::operator=(const Structure &other) {
		if (this != &other) {
			*this = dynamic_cast<const PriorityQueue<T>&>(other);
		}
		return *this;
	}

	template<typename T>
	inline PriorityQueue<T>::PriorityQueue() : Structure() {
	}

	template<typename T>
	inline PriorityQueue<T>::PriorityQueue(const PriorityQueue<T> &) {
	}
}
