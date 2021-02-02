#include "Vector.h"
#include "DSRoutines.h"
#include <cstdlib>
#include <cstring>

namespace Structures {

	Vector::Vector(size_t size) : memory(calloc(size, 1)), size_(size) {
	}

	Vector::Vector(const Vector& other) : Vector(other.size_) {
		std::memcpy(this->memory, other.memory, this->size_);
	}

	Vector::Vector(Vector&& other) : memory(other.memory), size_(other.size_) {
		other.memory = nullptr;
		other.size_ = 0;
	}

	Vector::~Vector() {
		std::free(this->memory);
		this->memory = nullptr;
		this->size_ = 0;
	}

	Structure* Vector::clone() const {
		return new Vector(*this);
	}

	size_t Vector::size() const {
		return size_;
	}

	Structure & Vector::operator=(const Structure & other) {
		if (this != &other) {
			*this = dynamic_cast<const Vector&>(other);
		}
		return *this;
	}

	Vector& Vector::operator=(const Vector& other) {
		if (this != &other) {
			this->size_ = other.size_;
			this->memory = realloc(this->memory, this->size_);
			memcpy(this->memory, other.memory, this->size_);
		}
		return *this;
	}

	Vector& Vector::operator=(Vector&& other) {
		free(this->memory);
		this->memory = other.memory;
		other.memory = nullptr;

		this->size_ = other.size_;
		other.size_ = 0;

		return *this;
	}

	bool Vector::operator==(const Vector& other) const {
		return (this == &other) ? true : (this->size_ == other.size_) && memcmp(this->memory, other.memory, this->size_) == 0;
	}

	byte& Vector::operator[](const int index) {
//		DSRoutines::rangeCheckExcept(index, this->size_, "Out of bounds!");
		return *(reinterpret_cast<byte*>(this->memory) + index);
	}

	byte Vector::operator[](const int index) const {
//		DSRoutines::rangeCheckExcept(index, this->size_, "Out of bounds!");
		return *(reinterpret_cast<byte*>(this->memory) + index);
	}

	byte& Vector::readBytes(const int index, const int count, byte& dest) {
//		DSRoutines::rangeCheckExcept(index + count, this->size_ + 1, "Out of bounds!");

		std::memcpy(&dest, this->getBytePointer(index), count);
		return dest;
	}

	void Vector::copy(const Vector& src, const int srcStartIndex, Vector& dest, const int destStartIndex, const int length) {
		if (length <= 0) {
			return;
		}

//		DSRoutines::rangeCheckExcept(srcStartIndex + length, src.size_ + 1, "Out of bounds!");
//		DSRoutines::rangeCheckExcept(destStartIndex + length, dest.size_ + 1, "Out of bounds!");

		if (&src == &dest && destStartIndex >= srcStartIndex && destStartIndex < srcStartIndex + length) {
			memmove(dest.getBytePointer(destStartIndex), src.getBytePointer(srcStartIndex), length);
		}
		else {
			memcpy(dest.getBytePointer(destStartIndex), src.getBytePointer(srcStartIndex), length);
		}
	}

	byte* Vector::getBytePointer(const int index) const {
//		DSRoutines::rangeCheckExcept(index, this->size_, "Vector::getBytePointer...Out of bounds!");
		return (reinterpret_cast<byte*>(this->memory) + index);
	}

}
