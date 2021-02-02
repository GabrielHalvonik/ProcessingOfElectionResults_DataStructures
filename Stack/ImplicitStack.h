#pragma once

#include "Stack.h"
#include "List/ArrayList.h"

namespace Structures {

	template<typename T>
	class ImplicitStack : public Stack<T> {
	public:
		ImplicitStack();
		ImplicitStack(const ImplicitStack<T>& other);
		~ImplicitStack();

		Structure* clone() const override;
		size_t size() const override;

		Stack<T>& operator=(const Stack<T>& other) override;
		ImplicitStack<T>& operator=(const ImplicitStack<T>& other);

		void clear() override;
		void push(const T& data) override;
		T pop() override;
		T& peek() override;
		const T peek() const override;

	protected:
		ArrayList<T>* list_;
	};

	template<typename T>
	ImplicitStack<T>::ImplicitStack() : Stack<T>(), list_(new ArrayList<T>()) {
	}

	template<typename T>
	ImplicitStack<T>::ImplicitStack(const ImplicitStack<T>& other) : Stack<T>(), list_(new ArrayList<T>(*other.list_)) {
	}

	template<typename T>
	ImplicitStack<T>::~ImplicitStack() {
		delete this->list_;
		this->list_ = nullptr;
	}

	template<typename T>
	inline Stack<T> &ImplicitStack<T>::operator=(const Stack<T>& other) {
		if (this != &other) {
			*this = dynamic_cast<const ImplicitStack<T>&>(other);
		}
		return *this;
	}

	template<typename T>
	inline ImplicitStack<T> &ImplicitStack<T>::operator=(const ImplicitStack<T>& other) {
		if (this != &other) {
			*this->list_ = *(other.list_);
		}
		return *this;
	}

	template<typename T>
	inline Structure * ImplicitStack<T>::clone() const {
		return new ImplicitStack<T>(*this);
	}

	template<typename T>
	size_t ImplicitStack<T>::size() const {
		return this->list_->size();
	}

	template<typename T>
	inline void ImplicitStack<T>::clear() {
		this->list_->clear();
	}

	template<typename T>
	inline void ImplicitStack<T>::push(const T& data) {
		this->list_->add(data);
	}

	template<typename T>
	inline T ImplicitStack<T>::pop() {
		if (this->list_->isEmpty()) {
			throw std::logic_error("Stack is empty!");
		}
		return this->list_->removeAt(static_cast<int>(this->size()) - 1);
	}

	template<typename T>
	inline T& ImplicitStack<T>::peek() {
		if (this->list_->isEmpty()) {
			throw std::logic_error("Stack is empty!");
		}
		return (*this->list_)[static_cast<int>(this->size()) - 1];
	}

	template<typename T>
	inline const T ImplicitStack<T>::peek() const {
		if (this->list_->isEmpty()) {
			throw std::logic_error("Stack is empty!");
		}
		return (*this->list_)[static_cast<int>(this->size()) - 1];
	}
}
