#pragma once

#include "Queue.h"
#include "Array/Array.h"

#include <stdexcept>

namespace Structures {

	template<typename T>
	class ImplicitQueue : public Queue<T> {
	public:
		ImplicitQueue();
		ImplicitQueue(const size_t capacity);
		ImplicitQueue(const ImplicitQueue<T>& other);
		~ImplicitQueue();

		Structure* clone() const override;
		size_t size() const override;

		Queue<T>& operator=(const Queue<T>& other) override;
		ImplicitQueue<T>& operator=(const ImplicitQueue<T>& other);

		void clear() override;
		void push(const T& data) override;
		T pop() override;
		T& peek() override;
		const T peek() const override;

	protected:
		Array<T>* array_;
		int startIndex_;
		size_t size_;
	};

	template<typename T>
	ImplicitQueue<T>::ImplicitQueue() : ImplicitQueue(10) {
	}

	template<typename T>
	ImplicitQueue<T>::ImplicitQueue(const size_t capacity) : Queue<T>(), array_(new Array<T>(capacity)), startIndex_(0), size_(0) {
	}

	template<typename T>
	ImplicitQueue<T>::ImplicitQueue(const ImplicitQueue<T>& other) : Queue<T>(other), array_(new Array<T>(*other.array_)), startIndex_(other.startIndex_), size_(other.size_) {
	}

	template<typename T>
	ImplicitQueue<T>::~ImplicitQueue() {
		delete this->array_;
		this->array_ = nullptr;
	}

	template<typename T>
	inline Queue<T>& ImplicitQueue<T>::operator=(const Queue<T>& other) {
		if (this != &other) {
			*this = dynamic_cast<const ImplicitQueue<T>&>(other);
		}
		return *this;
	}

	template<typename T>
	inline ImplicitQueue<T>& ImplicitQueue<T>::operator=(const ImplicitQueue<T>& other) {
		if (this != &other) {
			*this->array_ = *(other.array_);
			this->size_ = other.size_;
			this->startIndex_ = other.startIndex_;
		}
		return *this;
	}

	template<typename T>
	inline Structure * ImplicitQueue<T>::clone() const {
		return new ImplicitQueue<T>(*this);
	}

	template<typename T>
	size_t ImplicitQueue<T>::size() const {
		return this->size_;
	}

	template<typename T>
	inline void ImplicitQueue<T>::clear() {
		delete this->array_;
		this->array_ = nullptr;

		this->startIndex_ = 0;
		this->size_ = 0;
	}

	template<typename T>
	inline void ImplicitQueue<T>::push(const T& data) {
		if (this->size_ == this->array_->size()) {
			throw std::out_of_range("Implicit queue is full.");
		}
		(*this->array_)[static_cast<int>(this->startIndex_ + this->size_) % this->array_->size()] = data;
		++this->size_;
	}


	template<typename T>
	inline T ImplicitQueue<T>::pop() {
		if (this->size_ < 1) {
			throw std::out_of_range("Implicit queue is empty.");
		}
		--this->size_;
		T& data = (*this->array_)[this->startIndex_];
		this->startIndex_ = ++this->startIndex_ % this->array_->size();
		return data;
	}

	template<typename T>
	inline T& ImplicitQueue<T>::peek() {
		if (this->size_ < 1) {
			throw std::out_of_range("Implicit queue is empty.");
		}
		return (*this->array_)[this->startIndex_];
	}

	template<typename T>
	inline const T ImplicitQueue<T>::peek() const {
		if (this->size_ < 1) {
			throw std::out_of_range("Implicit queue is empty.");
		}
		return (*this->array_)[this->startIndex_];
	}
}
