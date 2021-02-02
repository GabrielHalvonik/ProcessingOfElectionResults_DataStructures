#pragma once

#include "List.h"
#include "StructureIterator.h"
#include "Array/Array.h"

namespace Structures {

	template<typename T>
	class ArrayList : public List<T> {
	public:
		ArrayList();
		ArrayList(size_t size);
		ArrayList(const ArrayList<T>& other);
		ArrayList(ArrayList<T>&& other);
		~ArrayList();

		Structure *clone() const override;
		size_t size() const override;

		List<T>& operator=(const List<T>& other) override;
		ArrayList<T>& operator=(const ArrayList<T>& other);
		ArrayList<T>& operator=(ArrayList<T>&& other);

		T &operator[](const int index) override;
		const T operator[](const int index) const override;

		void add(const T &data) override;
		void insert(const T &data, const int index) override;
		bool tryRemove(const T &data) override;
		T removeAt(const int index) override;
		int getIndexOf(const T &data) override;
		void clear() override;

		Iterator<T>* getBeginIterator()	const override;
		Iterator<T>* getEndIterator() const override;
	private:
		Array<T>* array_;
		size_t size_;
	private:
		void enlarge();

		class ArrayListIterator : public Iterator<T> {
		public:
			ArrayListIterator(const ArrayList<T> *arrayList, int position);
			~ArrayListIterator();
			Iterator<T> &operator=(const Iterator<T> &other) override;
			bool operator!=(const Iterator<T> &other) override;
			const T operator*() override;
			Iterator<T> &operator++() override;
		private:
			const ArrayList<T>* arrayList_;
			int position_;
		};
	};

	template<typename T>
	inline ArrayList<T>::ArrayList(): List<T>(), array_(new Array<T>(4)), size_(0) {
	}

	template<typename T>
	inline ArrayList<T>::ArrayList(size_t size): List<T>(), array_(new Array<T>(size)), size_(0) {
	}

	template<typename T>
	inline ArrayList<T>::ArrayList(const ArrayList<T>& other): List<T>(), array_(new Array<T>(*other.array_)), size_(other.size_) {
	}

	template<typename T>
	inline ArrayList<T>::ArrayList(ArrayList<T>&& other): List<T>(), array_(other.array_), size_(other.size_) {
		other.array_ = nullptr;
		other.size_ = 0;
	}

	template<typename T>
	inline ArrayList<T>::~ArrayList() {
		delete this->array_;
		this->array_ = nullptr;
		this->size_ = 0;
	}

	template<typename T>
	inline Structure * ArrayList<T>::clone() const {
		return new ArrayList<T>(*this);
	}

	template<typename T>
	inline size_t ArrayList<T>::size() const {
		return size_;
	}

	template<typename T>
	inline List<T>& ArrayList<T>::operator=(const List<T>& other) {
		if (this != &other) {
			*this = dynamic_cast<const ArrayList<T>&>(other);
		}
		return *this;
	}

	template<typename T>
	inline ArrayList<T>& ArrayList<T>::operator=(const ArrayList<T>& other) {
		if (this != &other) {
			if (this->array_->size() == other.array_->size()) {
				*this->array_ = *(other.array_);
			} else {
				delete this->array_;
				this->array_ = new Array<T>(*(other.array_));
				this->size_ = other.size_;
			}
		}
		return *this;
	}

	template<typename T>
	inline ArrayList<T>& ArrayList<T>::operator=(ArrayList<T>&& other) {
		this->clear();
		delete this->array_;

		this->array_ = other.array_;
		other.array_ = nullptr;

		this->size_ = other.size_;
		other.size_ = 0;

		return *this;
	}

	template<typename T>
	inline T& ArrayList<T>::operator[](const int index) {
//		DSRoutines::rangeCheckExcept(index, this->size_, "ArrayList<T>::operator[]...Invalid index!");
		return (*this->array_)[index];
	}

	template<typename T>
	inline const T ArrayList<T>::operator[](const int index) const {
//		DSRoutines::rangeCheckExcept(index, this->size_, "ArrayList<T>::operator[] const...Invalid index!");
		return (*this->array_)[index];
	}

	template<typename T>
	inline void ArrayList<T>::add(const T & data) {
		if (this->size_ == this->array_->size()) {
			this->enlarge();
		}
		(*this->array_)[this->size_++] = data;
	}

	template<typename T>
	inline void ArrayList<T>::insert(const T & data, const int index) {
//		DSRoutines::rangeCheckExcept(index, this->array_->size() + 1, "ArrayList<T>::insert...Invalid index!");
		if (index == this->size_) {
			this->add(data);
		} else {
			if (this->size_ == this->array_->size()) {
				this->enlarge();
			}
			Array<T>::copy(*this->array_, index, *this->array_, index + 1, this->size_ - index);
			(*this->array_)[index] = data;
			this->size_++;
		}
	}

	template<typename T>
	inline bool ArrayList<T>::tryRemove(const T& data) {
		int index = this->getIndexOf(data);
		if (index != -1) {
			this->removeAt(index);
			return true;
		}
		return false;
	}

	template<typename T>
	inline T ArrayList<T>::removeAt(const int index) {
//		DSRoutines::rangeCheckExcept(index, this->size_, "ArrayList<T>::removeAt...Invalid range!");
		T kopia = (*this->array_)[index];
		if (index < size_ - 1) {
			Array<T>::copy(*this->array_, index + 1, *this->array_, index, this->size_ - index - 1);
		}
		--this->size_;
		return kopia;
	}

	template<typename T>
	inline int ArrayList<T>::getIndexOf(const T& data) {
		int index = 0;
		for (int i = 0; i < this->size_; i++) {
			if ((*this->array_)[i] == data)
				return index;
			++index;
		}
//		for (auto temp : *this) {
//			if (temp == data)
//				return index;
//			++index;
//		}
		return -1;
	}

	template<typename T>
	inline void ArrayList<T>::clear() {
		this->size_ = 0;
	}

	template<typename T>
	inline Iterator<T>* ArrayList<T>::getBeginIterator() const {
		return new ArrayList<T>::ArrayListIterator(this, 0);
	}

	template<typename T>
	inline Iterator<T>* ArrayList<T>::getEndIterator() const {
		return new ArrayList<T>::ArrayListIterator(this, static_cast<int>(this->size_));
	}

	template<typename T>
	inline void ArrayList<T>::enlarge() {
		Array<T>* newArray = new Array<T>(this->array_->size() * 2);
		Array<T>::copy(*this->array_, 0, *newArray, 0, this->size_);
		delete this->array_;
		this->array_ = newArray;
	}

	template<typename T>
	inline ArrayList<T>::ArrayListIterator::ArrayListIterator(const ArrayList<T> *arrayList, int position) : arrayList_(arrayList), position_(position) {
	}

	template<typename T>
	inline ArrayList<T>::ArrayListIterator::~ArrayListIterator() {
		this->position_ = 0;
	}

	template<typename T>
	inline Iterator<T> &ArrayList<T>::ArrayListIterator::operator=(const Iterator<T>& other) {
		if (this != &other) {
			const ArrayList<T>::ArrayListIterator temp = dynamic_cast<const ArrayList<T>::ArrayListIterator &>(other);
			this->arrayList_ = temp.arrayList_;
			this->position_ = temp.position_;
		}
		return *this;
	}

	template<typename T>
	inline bool ArrayList<T>::ArrayListIterator::operator!=(const Iterator<T> &other) {
		const ArrayList<T>::ArrayListIterator temp = dynamic_cast<const ArrayList<T>::ArrayListIterator &>(other);
		return this->position_ != temp.position_;
	}

	template<typename T>
	inline const T ArrayList<T>::ArrayListIterator::operator*() {
		return (*this->arrayList_)[this->position_];
	}

	template<typename T>
	inline Iterator<T>& ArrayList<T>::ArrayListIterator::operator++() {
		++this->position_;
		return *this;
	}

}
