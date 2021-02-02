#pragma once

#include "Queue.h"
#include "List/LinkedList.h"

namespace Structures {

	template<typename T>
	class ExplicitQueue : public Queue<T> {
	public:
		ExplicitQueue();
		ExplicitQueue(const ExplicitQueue<T>& other);
		~ExplicitQueue();

		Structure* clone() const override;
		size_t size() const override;

		Queue<T>& operator=(const Queue<T>& other) override;
		ExplicitQueue<T>& operator=(const ExplicitQueue<T>& other);

		void clear() override;

		void push(const T& data) override;
		T pop() override;
		T& peek() override;
		const T peek() const override;

	protected:
		LinkedList<T>* list;
	};

	template<typename T>
	ExplicitQueue<T>::ExplicitQueue() : Queue<T>(), list(new LinkedList<T>()) {
	}

	template<typename T>
	ExplicitQueue<T>::ExplicitQueue(const ExplicitQueue<T>& other) : ExplicitQueue() {
		*this = other;
	}

	template<typename T>
	ExplicitQueue<T>::~ExplicitQueue() {
		delete this->list;
		this->list = nullptr;
	}

	template<typename T>
	inline Queue<T>& ExplicitQueue<T>::operator=(const Queue<T>& other) {
		if (this != &other) {
			*this = dynamic_cast<const ExplicitQueue<T>&>(other);
		}
		return *this;
	}

	template<typename T>
	inline ExplicitQueue<T>& ExplicitQueue<T>::operator=(const ExplicitQueue<T>& other) {
		if (this != &other) {
			*this->list = *(other.list);
		}
		return *this;
	}

	template<typename T>
	inline Structure * ExplicitQueue<T>::clone() const {
		return new ExplicitQueue<T>(*this);
	}

	template<typename T>
	size_t ExplicitQueue<T>::size() const {
		return this->list->size();
	}

	template<typename T>
	inline void ExplicitQueue<T>::clear() {
		this->list->clear();
	}

	template<typename T>
	inline void ExplicitQueue<T>::push(const T& data) {
		this->list->add(data);
	}

	template<typename T>
	inline T ExplicitQueue<T>::pop() {
		if (this->list->isEmpty()) {
			throw std::out_of_range("Explicit Queue is empty.");
		}
		return this->list->removeAt(0);
	}

	template<typename T>
	inline T& ExplicitQueue<T>::peek() {
		if (this->list->isEmpty()) {
			throw std::out_of_range("Explicit Queue is empty.");
		}
		return (*this->list)[0];
	}

	template<typename T>
	inline const T ExplicitQueue<T>::peek() const {
		if (this->list->isEmpty()) {
			throw std::out_of_range("Explicit Queue is empty.");
		}
		return (*this->list)[0];
	}
}
