#pragma once

#include "List/List.h"
#include "DSRoutines.h"
#include <cstring>

namespace Structures {

	template <typename T>
	class ArrayListRaw : public List<T> {
	public:
		ArrayListRaw();
		ArrayListRaw(size_t size);
		ArrayListRaw(const ArrayListRaw<T>& other);
		~ArrayListRaw();

		Structure *clone() const override;
		size_t size() const override;

		List<T>& operator=(const List<T> &other) override;
		ArrayListRaw<T>& operator=(const ArrayListRaw<T> &other);

		T &operator[](const int index) override;
		const T operator[](const int index) const override;

		void add(const T &data) override;
		void insert(const T &data, const int index) override;
		bool tryRemove(const T &data) override;
		T removeAt(const int index) override;
		int getIndexOf(const T &data) override;
		void clear() override;

		Iterator<T> *getBeginIterator() const override;
		Iterator<T> *getEndIterator() const override;
	private:
		T* array;
		size_t size_;
		size_t reserved;
	private:
		void enlarge();

		class ArrayListIterator : public Iterator<T> {
		public:
			ArrayListIterator(const ArrayListRaw<T> *arrayList, int position);
			~ArrayListIterator();
			Iterator<T> &operator=(const Iterator<T> &other) override;
			bool operator!=(const Iterator<T> &other) override;
			const T operator*() override;
			Iterator<T> &operator++() override;
		private:
			const ArrayListRaw<T>* arrayList_;
			int position_;
		};
	};

	template<typename T>
	inline ArrayListRaw<T>::ArrayListRaw(): List<T>(), array(new T[4]), size_(0), reserved(4) {
	}

	template<typename T>
	inline ArrayListRaw<T>::ArrayListRaw(size_t size): List<T>(), array(new T[size]), size_(0), reserved(size) {
	}

	template<typename T>
	inline ArrayListRaw<T>::ArrayListRaw(const ArrayListRaw<T>& other): List<T>(), array(new T[other.reserved]), size_(other.size_), reserved(other.reserved) {
		for (int i = 0; i < other.size_; ++i) {
			this->array[i] = other.array[i];
		}
	}

	template<typename T>
	inline ArrayListRaw<T>::~ArrayListRaw() {
		delete[] this->array;
		this->array = nullptr;
		this->size_ = 0;
	}

	template<typename T>
	inline Structure * ArrayListRaw<T>::clone() const {
		return new ArrayListRaw<T>(*this);
	}

	template<typename T>
	inline size_t ArrayListRaw<T>::size() const {
		return size_;
	}

	template<typename T>
	inline List<T>& ArrayListRaw<T>::operator=(const List<T>& other) {
		if (this != &other) {
			*this = dynamic_cast<const ArrayListRaw<T>&>(other);
		}
		return *this;
	}

	template<typename T>
	inline ArrayListRaw<T>& ArrayListRaw<T>::operator=(const ArrayListRaw<T>& other) {
		if (this != &other) {
			if (this->reserved != other.reserved) {
				delete this->array;
				this->array = new T[other.reserved];
				this->size_ = other.size_;
				this->reserved = other.reserved;

			}
			for (int i = 0; i < other.size_; ++i) {
				this->array[i] = other.array[i];
			}
		}
		return *this;
	}

	template<typename T>
	inline T& ArrayListRaw<T>::operator[](const int index) {
//		DSRoutines::rangeCheckExcept(index, this->size_, "ArrayList<T>::operator[]...Invalid index!");
		return this->array[index];
	}

	template<typename T>
	inline const T ArrayListRaw<T>::operator[](const int index) const {
//		DSRoutines::rangeCheckExcept(index, this->size_, "ArrayList<T>::operator[] const...Invalid index!");
		return this->array[index];
	}

	template<typename T>
	inline void ArrayListRaw<T>::add(const T & data) {
		if (this->size_ == this->reserved) {
			this->enlarge();
		}
		this->array[this->size_++] = data;
	}

	template<typename T>
	inline void ArrayListRaw<T>::insert(const T & data, const int index) {
//		DSRoutines::rangeCheckExcept(index, this->reserved + 1, "ArrayList<T>::insert...Invalid index!");
		if (index == this->size_) {
			this->add(data);
		} else {
			if (this->size_ == this->reserved) {
				this->enlarge();
			}
			std::memcpy(&this->array[index + 1], &this->array[index], (this->size_ - index) * sizeof(T));
			this->array[index] = data;
			++this->size_;
		}
	}

	template<typename T>
	inline bool ArrayListRaw<T>::tryRemove(const T& data) {
		int index = this->getIndexOf(data);
		if (index != -1) {
			this->removeAt(index);
			return true;
		}
		return false;
	}

	template<typename T>
	inline T ArrayListRaw<T>::removeAt(const int index) {
//		DSRoutines::rangeCheckExcept(index, this->size_, "ArrayList<T>::removeAt...Invalid range!");
		T kopia = this->array[index];
		if (index < size_ - 1) {
			std::memcpy(&this->array[index], &this->array[index + 1], (this->size_ - index - 1) * sizeof(T));
		}
		--this->size_;
		return kopia;
	}

	template<typename T>
	inline int ArrayListRaw<T>::getIndexOf(const T& data) {
		for (int i = 0; i < this->size_; ++i) {
			if (this->array[i] == data) {
				return i;
			}
		}
//		int index = 0;
//		for (T temp : *this) {
//			if (temp == data) {
//				return index;
//			}
//			++index;
//		}
		return -1;
	}

	template<typename T>
	inline void ArrayListRaw<T>::clear() {
		this->size_ = 0;
	}

	template<typename T>
	inline Iterator<T>* ArrayListRaw<T>::getBeginIterator() const {
		return new ArrayListRaw<T>::ArrayListIterator(this, 0);
	}

	template<typename T>
	inline Iterator<T>* ArrayListRaw<T>::getEndIterator() const {
		return new ArrayListRaw<T>::ArrayListIterator(this, this->size_);
	}

	template<typename T>
	inline void ArrayListRaw<T>::enlarge() {
		this->reserved *= 2;
		T* newArray = new T[this->reserved];
		std::memcpy(newArray, this->array, this->size_ * sizeof(T));
		delete[] this->array;
		this->array = newArray;
	}

	template<typename T>
	inline ArrayListRaw<T>::ArrayListIterator::ArrayListIterator(const ArrayListRaw<T> *arrayList, int position) : arrayList_(arrayList), position_(position) {
	}

	template<typename T>
	inline ArrayListRaw<T>::ArrayListIterator::~ArrayListIterator() {
		this->position_ = 0;
	}

	template<typename T>
	inline Iterator<T> &ArrayListRaw<T>::ArrayListIterator::operator=(const Iterator<T>& other) {
		if (this != &other) {
			const ArrayListRaw<T>::ArrayListIterator temp = dynamic_cast<const ArrayListRaw<T>::ArrayListIterator &>(other);
			this->arrayList_ = temp.arrayList_;
			this->position_ = temp.position_;
		}
		return *this;
	}

	template<typename T>
	inline bool ArrayListRaw<T>::ArrayListIterator::operator!=(const Iterator<T> &other) {
		const ArrayListRaw<T>::ArrayListIterator temp = dynamic_cast<const ArrayListRaw<T>::ArrayListIterator &>(other);
		return this->position_ != temp.position_;
	}

	template<typename T>
	inline const T ArrayListRaw<T>::ArrayListIterator::operator*() {
		return (*this->arrayList_)[this->position_];
	}

	template<typename T>
	inline Iterator<T>& ArrayListRaw<T>::ArrayListIterator::operator++() {
		++this->position_;
		return *this;
	}

}
