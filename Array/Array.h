#pragma once

#include "Structure.h"
#include "Vector/Vector.h"
#include "DSRoutines.h"
#include <initializer_list>

namespace Structures {

	template<typename T>
	class Array	: public Structure {
	public:
		Array(const size_t size);
		Array(const Array<T>& other);
		Array(const std::initializer_list<T>& other);
		Array(Array<T>&& other);
		~Array();

		Structure* clone() const override;
		size_t size() const override;

		Structure& operator=(const Structure& other) override;
		Array<T>& operator=(const Array<T>& other);
		Array<T>& operator=(Array<T>&& other);
		bool operator==(const Array<T>& other) const;
		T& operator[](const int index);
		const T operator[](const int index) const;

		static void copy(const Array<T>& src, const int srcStartIndex, Array<T>& dest, const int destStartIndex, const int length);

	private:
		Vector* vector;
		size_t size_;

	private:
		int mapFunction(const int index) const;
	};

	template<typename T>
	Array<T>::Array(const size_t size) : vector(new Vector(size * sizeof(T))), size_(size) {
	}

	template<typename T>
	Array<T>::Array(const Array<T>& other) : vector(new Vector(*(other.vector))), size_(other.size_) {
	}

	template<typename T>
	Array<T>::Array(const std::initializer_list<T>& other) : Array<T>(other.size()) {
		for (int i = 0; i < this->size_; ++i) {
			*this[i] = other[i];
		}
	}

	template<typename T>
	Array<T>::Array(Array<T>&& other) : vector(other.vector), size_(other.size_) {
		other.vector = nullptr;
		other.size_ = 0;
	}

	template<typename T>
	Array<T>::~Array() {
		delete this->vector;
		this->vector = nullptr;
		this->size_ = 0;
	}

	template<typename T>
	Structure* Array<T>::clone() const {
		return new Array<T>(*this);
	}

	template<typename T>
	Structure& Array<T>::operator=(const Structure& other) {
		if (this != &other) {
			*this = dynamic_cast<const Array<T>&>(other);
		}
		return *this;
	}

	template<typename T>
	Array<T>& Array<T>::operator=(const Array<T>& other) {
		if (this != &other) {
			if (this->size() == other.size_) {
				*this->vector = *other.vector;
			} else {
				throw std::invalid_argument("Array size differ!");
			}
		}
		return *this;
	}

	template<typename T>
	Array<T>& Array<T>::operator=(Array<T>&& other) {
		delete this->vector;
		this->vector = other.vector;
		other.vector = nullptr;

		this->size_ = other.size_;
		other.size_ = 0;

		return *this;
	}

	template<typename T>
	size_t Array<T>::size() const {
		return size_;
	}

	template<typename T>
	T& Array<T>::operator[](const int index) {
		return *reinterpret_cast<T*>(this->vector->getBytePointer(this->mapFunction(index)));
	}

	template<typename T>
	const T Array<T>::operator[](const int index) const {
		return *reinterpret_cast<T*>(this->vector->getBytePointer(this->mapFunction(index)));
	}

	template<typename T>
	inline bool Array<T>::operator==(const Array<T>& other) const {
		return *this->vector == *other.vector;
	}

	template<typename T>
	void Array<T>::copy(const Array<T>& src, const int srcStartIndex, Array<T>& dest, const int destStartIndex, const int length) {
		Vector::copy(*src.vector, src.mapFunction(srcStartIndex), *dest.vector, dest.mapFunction(destStartIndex), length * sizeof(T));
	}

	template<typename T>
	inline int Array<T>::mapFunction(const int index) const {
		return index * sizeof(T);
	}
}

