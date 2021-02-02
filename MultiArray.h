#pragma once
#include "Structure.h"

template <typename T>
class MultiArray {
public:
	template <typename ...size_t>
	MultiArray(size_t...);
	~MultiArray();

	template <typename ...size_t>
	T& set(size_t...);

	template <typename ...size_t>
	T get(size_t...);

	template <typename ...uint32_t>
	T& operator()(uint32_t&&...);

	size_t size() const;
	uint8_t dimensionSize(uint8_t) const;

private:
	template <typename ...uint32_t>
	size_t mapFunction(uint32_t...);

	T* array;
	uint8_t* dimensions;
	size_t size_;
};

template <typename T>
template<typename ...size_t>
MultiArray<T>::MultiArray(size_t...args) : dimensions(new uint8_t[sizeof...(args)]), size_(1) {
	uint8_t i = 0;
	for (auto&& x : { args... }) {
		this->dimensions[i++] = x;
		this->size_ *= x;
	}
	this->array = new T[this->size_];
	memset(this->array, 0, this->size_ * sizeof(T));
}

template<typename T>
MultiArray<T>::~MultiArray() {
	delete this->array;
	this->array = nullptr;
	delete this->dimensions;
	this->dimensions = nullptr;
}

template <typename T>
size_t MultiArray<T>::size() const {
	return this->size_;
}

template<typename T>
uint8_t MultiArray<T>::dimensionSize(uint8_t index) const {
	return this->dimensions[index];
}

template<typename T>
template<typename ...uint32_t>
T& MultiArray<T>::operator()(uint32_t&&...args) {
	return this->array[this->mapFunction(args...)];
}

template <typename T>
template<typename ...size_t>
T& MultiArray<T>::set(size_t...args) {
	return this->array[this->mapFunction(args...)];
}

template <typename T>
template <typename ...size_t>
T MultiArray<T>::get(size_t...args) {
	return this->array[this->mapFunction(args...)];
};


template <typename T>
template <typename ...uint32_t>
size_t MultiArray<T>::mapFunction(uint32_t...args) {
	size_t i = 0, index = 1;
	for (auto&& x : { args... }) {
		index += x * this->dimensions[i++];
	}
	return index;
}

