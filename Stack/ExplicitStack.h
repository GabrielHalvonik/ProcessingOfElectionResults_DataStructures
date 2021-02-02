#pragma once

#include "Stack.h"
#include "List/LinkedList.h"

namespace Structures {

	template<typename T>
	class ExplicitStack : public Stack<T> {
	public:
		ExplicitStack();
		ExplicitStack(const ExplicitStack<T>& other);
		~ExplicitStack();

		Structure* clone() const override;
		size_t size() const override;

		Stack<T>& operator=(const Stack<T>& other) override;
		ExplicitStack<T>& operator=(const ExplicitStack<T>& other);

		void clear() override;
		void push(const T& data) override;
		T pop() override;
		T& peek() override;
		const T peek() const override;

	protected:
		LinkedList<T>* list_;
	};

	template<typename T>
	ExplicitStack<T>::ExplicitStack() : Stack<T>(), list_(new LinkedList<T>()) {
	}

	template<typename T>
	ExplicitStack<T>::ExplicitStack(const ExplicitStack<T>& other) : ExplicitStack() {
		*this = other;
	}

	template<typename T>
	ExplicitStack<T>::~ExplicitStack() {
		delete this->list_;
		this->list_ = nullptr;
	}

	template<typename T>
	inline Stack<T>& ExplicitStack<T>::operator=(const Stack<T>& other) {
		if (this != &other) {
			*this = dynamic_cast<const ExplicitStack<T>&>(other);
		}
		return *this;
	}

	template<typename T>
	inline ExplicitStack<T>& ExplicitStack<T>::operator=(const ExplicitStack<T>& other) {
		if (this != &other) {
			*this->list_ = *(other.list_);
		}
		return *this;
	}

	template<typename T>
	inline Structure * ExplicitStack<T>::clone() const {
		return new ExplicitStack<T>(*this);
	}

	template<typename T>
	size_t ExplicitStack<T>::size() const {
		return this->list_->size();
	}

	template<typename T>
	inline void ExplicitStack<T>::clear() {
		this->list_->clear();
	}

	template<typename T>
	inline void ExplicitStack<T>::push(const T& data) {
		this->list_->insert(data, 0);
	}

	template<typename T>
	inline T ExplicitStack<T>::pop() {
		return this->list_->removeAt(0);
	}

	template<typename T>
	inline T& ExplicitStack<T>::peek() {
		return (*this->list_)[0];
	}

	template<typename T>
	inline const T ExplicitStack<T>::peek() const {
		return (*this->list_)[0];
	}
}
