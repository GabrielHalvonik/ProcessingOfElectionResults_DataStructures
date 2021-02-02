#pragma once

#include "Structure.h"

namespace Structures {
	template<typename T>
	class Stack : public Structure {
	public:
		Stack();
		~Stack();

		Structure& operator=(const Structure& other) override;
		virtual Stack<T>& operator=(const Stack<T>& other) = 0;

		Structure* clone() const = 0;
		size_t size() const = 0;
		virtual void clear() = 0;
		virtual void push(const T& data) = 0;
		virtual T pop() = 0;
		virtual T& peek() = 0;
		virtual const T peek() const = 0;
	};

	template<typename T>
	inline Structure & Stack<T>::operator=(const Structure & other) {
		if (this != &other) {
			*this = dynamic_cast<const Stack<T>&>(other);
		}
		return *this;
	}

	template<typename T>
	inline Stack<T>::Stack() : Structure() {
	}

	template<typename T>
	inline Stack<T>::~Stack() {
	}
}
