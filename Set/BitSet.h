#pragma once

#include "Structure.h"
#include "BaseSet.h"
#include "MemoryRoutines.h"
#include <cmath>
#include <bit>
#include <iostream>

namespace Structures {

	template <typename T>
	class BitSet : public Structure {
	public:
		BitSet(BaseSet<T>*);
		BitSet(const BitSet&);
		BitSet(BitSet&&);
		~BitSet();

		BitSet& operator=(const BitSet&);
		Structure& operator=(const Structure& other) override;

		Structure* clone() const override;
		size_t size() const override;

		bool operator[](const size_t) const;
		bool operator[](const T&) const;
		bool operator==(const BitSet&) const;
		BitSet operator-(const BitSet&) const;

		bool hasSubset(const BitSet&) const;
		BitSet intersectionWith(const BitSet&) const;
		BitSet unionWith(const BitSet&) const;
		BitSet substract(const BitSet&) const;

		void insert(const T&) const;
		void extract(const T&) const;
		bool contains(const T&) const;

		void reset();
		void set();

		void print() const;

		template <typename R>
		friend std::ostream &operator<<(std::ostream& out, const BitSet<R>& set);

	private:
		BaseSet<T>* base;
		byte* bitSet;
		size_t byteSize;
	};

	template<typename T>
	BitSet<T>::BitSet(BaseSet<T>* base) : base(base), byteSize(std::ceil(base->size() / 8.0)) {
		this->bitSet = new byte[byteSize];
	}

	template<typename T>
	BitSet<T>::BitSet(const BitSet& other) : base(other.base), byteSize(other.byteSize) {
		this->bitSet = new byte(this->byteSize);
		memcpy(this->bitSet, other.bitSet, this->byteSize);
	}

	template<typename T>
	BitSet<T>::BitSet(BitSet&& other) : base(other.base), bitSet(other.bitSet), byteSize(other.byteSize) {
		other.base = nullptr;
		other.bitSet = nullptr;
		other.byteSize = 0;
	}

	template<typename T>
	BitSet<T>::~BitSet() {
		delete[] this->bitSet;
		this->bitSet = nullptr;
		this->byteSize = 0;
	}

	template<typename T>
	BitSet<T>& BitSet<T>::operator=(const BitSet& other) {
		if (this != &other) {
			this->byteSize = other.byteSize;
			this->base = other.base;
			delete this->bitSet;
			this->bitSet = new byte[this->byteSize];
			memcpy(this->bitSet, other.bitSet, this->byteSize);
		}
		return *this;
	}

	template<typename T>
	Structure& BitSet<T>::operator=(const Structure& other) {
		if (this != &other) {
			*this = dynamic_cast<const BitSet&>(other);
		}
		return *this;
	}

	template<typename T>
	Structure* BitSet<T>::clone() const {
		return new BitSet(*this);
	}

	template<typename T>
	size_t BitSet<T>::size() const {
		return this->base->size();
	}

	template<typename T>
	bool BitSet<T>::operator[](const size_t index) const {
		if (index >= this->base->size()) {
			throw std::out_of_range("BitSet<T>::operator[]...Out of bounds!");
		}
		return MemoryRoutines::byteNthBitGet(this->bitSet[index / 8], index % 8);
	}

	template<typename T>
	bool BitSet<T>::operator[](const T& data) const {
		return this->contains(data);
	}

	template<typename T>
	bool BitSet<T>::operator==(const BitSet& second) const {
		if (this->base == second.base) {
			return (std::memcmp(this->bitSet, second.bitSet, this->byteSize) == 0);
		}
		return 0;
	}

	template<typename T>
	BitSet<T> BitSet<T>::operator-(const BitSet& second) const {
		return this->substract(second);
	}

	template<typename T>
	bool BitSet<T>::hasSubset(const BitSet& second) const {
//		if (this->base != second.base) {
//			return false;
//		}
		for (size_t i = 0; i < this->byteSize; ++i) {
			if ((second.bitSet[i] ^ (this->bitSet[i] & second.bitSet[i])) != 0) {
				return false;
			}
		}
		return true;
	}

	template<typename T>
	BitSet<T> BitSet<T>::intersectionWith(const BitSet& second) const {
//		if (this->base != second.base) {
//			throw std::logic_error("BitSet<T>::intersectionWith...Different bases.");
//		}

		BitSet<T> newSet(this->base);
		for (size_t i = 0; i < this->byteSize; ++i) {
			newSet.bitSet[i] = this->bitSet[i] & second.bitSet[i];
		}
		return newSet;

	}

	template<typename T>
	BitSet<T> BitSet<T>::unionWith(const BitSet<T>& second) const {
//		if (this->base != second.base) {
//			throw std::logic_error("BitSet<T>::intersectionWith...Different bases.");
//		}

		BitSet<T> newSet(this->base);
		for (size_t i = 0; i < this->byteSize; ++i) {
			newSet.bitSet[i] = this->bitSet[i] | second.bitSet[i];
		}
		return newSet;
	}

	template<typename T>
	BitSet<T> BitSet<T>::substract(const BitSet<T>& second) const {
//		if (this->base != second.base) {
//			throw std::logic_error("BitSet<T>::intersectionWith...Different bases.");
//		}

		BitSet<T> newSet(this->base);
		for (size_t i = 0; i < this->byteSize; ++i) {
			newSet.bitSet[i] = this->bitSet[i] ^ (this->bitSet[i] & second.bitSet[i]);
		}
		return newSet;
	}

	template<typename T>
	void BitSet<T>::insert(const T& data) const {
		int index = this->base->getIndexOf(data);
		if (index != -1) {
			MemoryRoutines::byteNthBitTo1(this->bitSet[index / 8], index % 8);
		}
	}

	template<typename T>
	void BitSet<T>::extract(const T& data) const {
		int index = this->base->getIndexOf(data);
		if (index != -1) {
			MemoryRoutines::byteNthBitTo0(this->bitSet[index / 8], index % 8);
		}
	}

	template<typename T>
	bool BitSet<T>::contains(const T& data) const {
		int index = this->base->getIndexOf(data);
		if (index == -1) {
			return false;
		}
		return MemoryRoutines::byteNthBitGet(this->bitSet[index / 8], index % 8);
	}

	template<typename T>
	void BitSet<T>::set() {
		memset(this->bitSet, 0xFF, this->byteSize);
	}

	template<typename T>
	void BitSet<T>::reset() {
		memset(this->bitSet, 0, this->byteSize);
	}

	template<typename T>
	void BitSet<T>::print() const {
		for (size_t i = 0; i < this->byteSize; ++i) {
			for (size_t j = 0; j < 8; ++j) {
				std::cout << MemoryRoutines::byteNthBitGet(this->bitSet[i], j);
			}
			std::cout << " ";
		}
		std::cout << std::endl;
	}

	template<typename R>
	std::ostream& operator<<(std::ostream& out, const BitSet<R>& set) {
		for (size_t i = 0; i < set.base->size(); ++i) {
			if (set[i]) {
				out << (*set.base)[i] << " ";
			}
		}
		return out;
	}

}

