#pragma once

#include "List.h"
#include "StructureIterator.h"
#include "DSRoutines.h"

namespace Structures {

	template<typename T>
	class LinkedListItem : public DataItem<T> {
	public:
		LinkedListItem(T data);
		LinkedListItem(const LinkedListItem<T> &other);
		~LinkedListItem();

		LinkedListItem<T>* getNext();
		void setNext(LinkedListItem<T>* next);
	private:
		LinkedListItem<T>* next_;
	};

	template<typename T>
	class LinkedList : public List<T> {
	public:
		LinkedList();
		LinkedList(const LinkedList<T>& other);
		LinkedList(LinkedList<T>&& other);
		~LinkedList();

		Structure *clone() const override;
		size_t size() const override;

		List<T>& operator=(const List<T> &other) override;
		LinkedList<T>& operator=(const LinkedList<T> &other);
		LinkedList<T>& operator=(LinkedList<T> &&other);
		T& operator[](const int index) override;
		const T operator[](const int index) const override;

		void add(const T& data) override;
//		void add(T&& data);
		void insert(const T& data, const int index) override;
		bool tryRemove(const T& data) override;
		T removeAt(const int index) override;
		int getIndexOf(const T& data) override;
		void clear() override;

		Iterator<T>* getBeginIterator() const override;
		Iterator<T>* getEndIterator() const override;
	private:
		size_t size_;
		LinkedListItem<T>* first_;
		LinkedListItem<T>* last_;
	private:
		LinkedListItem<T>* getItemAtIndex(int index) const;
	private:
		class LinkedListIterator : public Iterator<T> {
		public:
			LinkedListIterator(LinkedListItem<T> *position);
			~LinkedListIterator();

			Iterator<T> &operator=(const Iterator<T> &other) override;
			bool operator!=(const Iterator<T> &other) override;
			const T operator*() override;
			Iterator<T>& operator++() override;
		private:
			LinkedListItem<T> *position_;
		};
	};

	template<typename T>
	inline LinkedListItem<T>::LinkedListItem(T data): DataItem<T>(data), next_(nullptr) {
	}

	template<typename T>
	inline LinkedListItem<T>::LinkedListItem(const LinkedListItem<T>& other): DataItem<T>(other), next_(other.next_) {
	}

	template<typename T>
	inline LinkedListItem<T>::~LinkedListItem() {
		this->next_ = nullptr;
	}

	template<typename T>
	inline LinkedListItem<T> * LinkedListItem<T>::getNext() {
		return next_;
	}

	template<typename T>
	inline void LinkedListItem<T>::setNext(LinkedListItem<T> *next) {
		next_ = next;
	}

	template<typename T>
	inline LinkedList<T>::LinkedList(): List<T>(), size_(0), first_(nullptr), last_(nullptr) {
	}

	template<typename T>
	inline LinkedList<T>::LinkedList(const LinkedList<T>& other) : LinkedList<T>() {
		*this = other;
	}

	template<typename T>
	inline LinkedList<T>::LinkedList(LinkedList<T>&& other) : List<T>(), size_(other.size_), first_(other.first_), last_(other.last_) {
		other.size_ = 0;
		other.first_ = nullptr;
		other.last_ = nullptr;
	}

	template<typename T>
	inline LinkedList<T>::~LinkedList() {
		this->clear();
	}

	template<typename T>
	inline Structure * LinkedList<T>::clone() const {
		return new LinkedList<T>(*this);
	}

	template<typename T>
	inline size_t LinkedList<T>::size() const {
		return size_;
	}

	template<typename T>
	inline List<T>& LinkedList<T>::operator=(const List<T>& other) {
		if (this != &other) {
			*this = dynamic_cast<const LinkedList<T>&>(other);
		}
		return *this;
	}

	template<typename T>
	inline LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other) {
		if (this != &other) {
			this->clear();
			LinkedListItem<T> *item = other.first_;
			while (item != nullptr) {
				this->add(item->accessData());
				item = item->getNext();
			}
		}
		return *this;
	}

	template<typename T>
	inline LinkedList<T>& LinkedList<T>::operator=(LinkedList<T>&& other) {
		this->clear();

		this->first_ = other.first_;
		other.first_ = nullptr;

		this->last_ = other.last_;
		other.last_ = nullptr;

		this->size_ = other.size_;
		other.size_ = 0;

		return *this;
	}

	template<typename T>
	inline T& LinkedList<T>::operator[](const int index) {
		return this->getItemAtIndex(index)->accessData();
	}

	template<typename T>
	inline const T LinkedList<T>::operator[](const int index) const {
		return this->getItemAtIndex(index)->accessData();
	}

	template<typename T>
	inline void LinkedList<T>::add(const T& data) {
		LinkedListItem<T> *newItem = new LinkedListItem<T>(data);
		if (this->size_ == 0) {
			this->first_ = this->last_ = newItem;
		} else {
			this->last_->setNext(newItem);
			this->last_ = newItem;
		}
		++this->size_;
	}

//	template<typename T>
//	inline void LinkedList<T>::add(T&& data) {
//		LinkedListItem<T> *newItem = new LinkedListItem<T>(data);
//		if (this->size_ == 0) {
//			this->first_ = this->last_ = newItem;
//		} else {
//			this->last_->setNext(newItem);
//			this->last_ = newItem;
//		}
//		++this->size_;
//	}

	template<typename T>
	inline void LinkedList<T>::insert(const T& data, const int index) {
//		DSRoutines::rangeCheckExcept(0, this->size_ + 1, "LinkedList<T>::insert...Out of bounds!");
		if (index == this->size_) {
			this->add(data);
		} else {
			LinkedListItem<T> *newItem = new LinkedListItem<T>(data);
			if (index == 0) {
				newItem->setNext(this->first_);
				this->first_ = newItem;
			} else {
				LinkedListItem<T> *previousItem = this->getItemAtIndex(index - 1);								//try/catch
				newItem->setNext(previousItem->getNext());
				previousItem->setNext(newItem);
			}
			++this->size_;
		}
	}

	template<typename T>
	inline bool LinkedList<T>::tryRemove(const T & data) {
		int index = this->getIndexOf(data);			//usetrit...predchodcu...55m
		if (index == -1) {
			return false;
		}
		this->removeAt(index);
		return true;
	}

	template<typename T>
	inline T LinkedList<T>::removeAt(const int index) {
//		DSRoutines::rangeCheckExcept(index, this->size_, "LinkedList<T>::removeAt...out of range");

		LinkedListItem<T> *itemToRemove;
		if (index == 0) {
			itemToRemove = this->first_;
			if (this->size_ == 1) {
				this->first_ = this->last_ = nullptr;
			} else {
				this->first_ = this->first_->getNext();
			}
		} else {
			LinkedListItem<T> *previousItem = this->getItemAtIndex(index - 1);
			itemToRemove = previousItem->getNext();
			previousItem->setNext(itemToRemove->getNext());
			if (this->last_ == itemToRemove) {
				this->last_ = previousItem;
			}
		}
		T removedData = itemToRemove->accessData();
		delete itemToRemove;
		itemToRemove = nullptr;

		--this->size_;
		return removedData;
	}

	template<typename T>
	inline int LinkedList<T>::getIndexOf(const T& data) {
//		LinkedListItem<T> *item = this->first_;
		int index = 0;
		for (T item : *this) {
			if (item == data) {
				return index;
			}
			++index;
		}
		return -1;
	}

	template<typename T>
	inline void LinkedList<T>::clear() {
		LinkedListItem<T> *itemToRemove	 = this->first_;

		while (itemToRemove != nullptr) {
			this->first_ = this->first_->getNext();
			delete itemToRemove;
			itemToRemove = this->first_;
		}
		this->size_ = 0;
		this->first_ = this->last_ = nullptr;
	}

	template<typename T>
	inline Iterator<T>* LinkedList<T>::getBeginIterator() const {
		return new LinkedListIterator(first_);
	}

	template<typename T>
	inline Iterator<T>* LinkedList<T>::getEndIterator() const {
		return new LinkedListIterator(nullptr);
	}

	template<typename T>
	inline LinkedListItem<T>* LinkedList<T>::getItemAtIndex(int index) const {
//	DSRoutines::rangeCheckExcept(index, this->size_, "LinkedList<T>::getItemAtIndex...Out of bounds.");

		LinkedListItem<T> *item = this->first_;
		for (int i = 0; i < index; i++) {
			item = item->getNext();
		}
		return item;
	}

	template<typename T>
	inline LinkedList<T>::LinkedListIterator::LinkedListIterator( LinkedListItem<T> *position): position_(position) {
	}

	template<typename T>
	inline LinkedList<T>::LinkedListIterator::~LinkedListIterator() {
		this->position_ = nullptr;
	}

	template<typename T>
	inline Iterator<T>& LinkedList<T>::LinkedListIterator::operator=(const Iterator<T>& other) {
		if (this != &other) {
			position_ = dynamic_cast<const LinkedList<T>::LinkedListIterator&>(other).position_;
		}
		return *this;
	}

	template<typename T>
	inline bool LinkedList<T>::LinkedListIterator::operator!=(const Iterator<T>& other) {
		return this->position_ != dynamic_cast<const LinkedList<T>::LinkedListIterator &>(other).position_;
	}

	template<typename T>
	inline const T LinkedList<T>::LinkedListIterator::operator*() {
		return this->position_->accessData();
	}

	template<typename T>
	inline Iterator<T>& LinkedList<T>::LinkedListIterator::operator++() {
		this->position_ = this->position_->getNext();
		return *this;
	}
}
