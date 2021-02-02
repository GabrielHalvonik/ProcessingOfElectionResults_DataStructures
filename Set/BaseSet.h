#pragma once

#include "Structure.h"
#include <cstring>
#include <stdexcept>
#include <initializer_list>

namespace Structures {

	template <typename T>
	class BaseSet {
	public:
		BaseSet(const size_t);
		BaseSet(const std::initializer_list<T>&);
		BaseSet(const BaseSet&);
		~BaseSet();

		BaseSet& operator=(const BaseSet&);
		T& operator[](const size_t);
		const T& operator[](const size_t) const;

		int getIndexOf(const T&);

		size_t size() const;

	private:
		T* base;
		size_t size_;
	};

	template<typename T>
	BaseSet<T>::BaseSet(const size_t size) : size_(size), base(new T[size]) {
	}

	template<typename T>
	BaseSet<T>::BaseSet(const std::initializer_list<T>& baseList) : base(new T[baseList.size()]), size_(baseList.size()) {
		size_t index = 0;
		for (const T& temp : baseList) {
			this->base[index++] = temp;
		}
	}

	template<typename T>
	BaseSet<T>::BaseSet(const BaseSet& other) : size_(other.size_), base(new T[other.size_]) {
		memcpy(this->base, other.base, this->size_ * sizeof(T));
	}

	template<typename T>
	BaseSet<T>::~BaseSet() {
		delete[] this->base;
		this->base = nullptr;
		this->size_ = 0;
	}

	template<typename T>
	BaseSet<T>& BaseSet<T>::operator=(const BaseSet& other) {
		if (this != &other) {
			if (this->size_ != other.size_) {
				this->size_ = other.size_;
				delete[] this->base;
				this->base = new T[this->size_];
			}
			std::memcpy(this->base, other.base, this->size_ * sizeof(T));
		}
		return *this;
	}

	template<typename T>
	T& BaseSet<T>::operator[](const size_t index) {
		if (index > this->size_) {
			throw std::out_of_range("BaseSet<T>::operator[]...Out of Bounds!");
		}
		return this->base[index];
	}

	template<typename T>
	const T& BaseSet<T>::operator[](const size_t index) const {
		if (index >= this->size_) {
			throw std::out_of_range("BaseSet<T>::operator[]...Out of Bounds!");
		}
		return this->base[index];
	}

	template<typename T>
	int BaseSet<T>::getIndexOf(const T& data) {
		for (size_t i = 0; i < this->size_; ++i) {
			if (this->base[i] == data) {
				return i;
			}
		}
		return -1;
	}

	template<typename T>
	size_t BaseSet<T>::size() const {
		return this->size_;
	}

}
