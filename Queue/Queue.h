#pragma once

#include "Structure.h"

namespace Structures {

	template<typename T>
	class Queue : public Structure {
	public:
		~Queue();

		Structure& operator=(const Structure& other) override;
		virtual Queue<T>& operator=(const Queue<T>& other) = 0;

		virtual Structure* clone() const override = 0;
		virtual size_t size() const override = 0;
		virtual void clear() = 0;

		virtual void push(const T& data) = 0;
		virtual T pop() = 0;
		virtual T& peek() = 0;
		virtual const T peek() const = 0;

	protected:
		Queue();
		Queue(const Queue<T> &other);
	};

	template<typename T>
	inline Queue<T>::~Queue() {
	}

	template<typename T>
	inline Structure & Queue<T>::operator=(const Structure & other) {
		if (this != &other) {
			*this = dynamic_cast<const Queue<T> &>(other);
		}
		return *this;
	}

	template<typename T>
	inline Queue<T>::Queue() : Structure() {
	}

	template<typename T>
	inline Queue<T>::Queue(const Queue<T> &) {
	}
}
