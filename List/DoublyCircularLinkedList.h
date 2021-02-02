#pragma once

#include "DoublyLinkedList.h"
#include "StructureIterator.h"
#include "DSRoutines.h"

namespace Structures {

	template <typename T>
	class DoublyCircularLinkedList : public DoublyLinkedList<T> {
	public:
		DoublyCircularLinkedList();
		DoublyCircularLinkedList(const DoublyCircularLinkedList&);
		~DoublyCircularLinkedList();

		Structure* clone() const override;
		size_t size() const override;

		List<T>& operator=(const List<T>& other) override;
		DoublyCircularLinkedList& operator=(const DoublyCircularLinkedList&);

		void add(const T& data) override;
		void insert(const T& data, const int index) override;
		T removeAt(const int index) override;
		void clear() override;

		Iterator<T>* getBeginIterator() const override;
		Iterator<T>* getEndIterator() const override;

	private:
		class DoublyCircularLinkedListIterator : virtual public DoublyLinkedList<T>::DoublyLinkedListIterator {
		public:
			DoublyCircularLinkedListIterator(DoublyLinkedListItem<T>*, const DoublyCircularLinkedList<T>*);
			Iterator<T>& operator++() override;
		private:
			const DoublyCircularLinkedList<T>* list;
		};
	};

	template<typename T>
	DoublyCircularLinkedList<T>::DoublyCircularLinkedList() : DoublyLinkedList<T>() {
	}

	template<typename T>
	DoublyCircularLinkedList<T>::DoublyCircularLinkedList(const DoublyCircularLinkedList& other) : DoublyCircularLinkedList() {
		*this = other;
	}

	template<typename T>
	DoublyCircularLinkedList<T>::~DoublyCircularLinkedList() {
		this->clear();
	}

	template<typename T>
	Structure* DoublyCircularLinkedList<T>::clone() const {
		return new DoublyCircularLinkedList<T>(*this);
	}

	template<typename T>
	size_t DoublyCircularLinkedList<T>::size() const {
		return this->size_;
	}

	template<typename T>
	List<T>& DoublyCircularLinkedList<T>::operator=(const List<T>& other) {
		if (this != &other) {
			*this = dynamic_cast<const DoublyCircularLinkedList<T>&>(other);
		}
		return *this;
	}

	template<typename T>
	DoublyCircularLinkedList<T>& DoublyCircularLinkedList<T>::operator=(const DoublyCircularLinkedList& other) {
		DoublyLinkedList<T>::operator=(other);

		return *this;
	}

	template<typename T>
	void DoublyCircularLinkedList<T>::add(const T& data) {
		DoublyLinkedList<T>::add(data);

		this->last_->setNext(this->first_);
		this->first_->setPrevious(this->last_);
	}

	template<typename T>
	void DoublyCircularLinkedList<T>::insert(const T& data, const int index) {
		DoublyLinkedList<T>::insert(data, index);

		if (!this->isEmpty() && (index == 0 || index == this->size_)) {
			this->first_->setPrevious(this->last_);
			this->last_->setNext(this->first_);
		}
	}

	template<typename T>
	T DoublyCircularLinkedList<T>::removeAt(const int index) {
		T removedData = DoublyLinkedList<T>::removeAt(index);

		if (!this->isEmpty() && (index == 0 || index == this->size_)) {
			this->first_->setPrevious(this->last_);
			this->last_->setNext(this->first_);
		}

		return removedData;
	}

	template<typename T>
	void DoublyCircularLinkedList<T>::clear() {
		if (this->isEmpty()) {
			return;
		}

		DoublyLinkedListItem<T>* itemToRemove = this->first_;

		while (itemToRemove != this->last_) {
			this->first_ = this->first_->getNext();
			delete itemToRemove;
			itemToRemove = this->first_;
		}
		delete this->last_;
		this->size_ = 0;
		this->first_ = this->last_ = nullptr;
	}

	template<typename T>
	Iterator<T>* DoublyCircularLinkedList<T>::getBeginIterator() const {
		return new DoublyCircularLinkedListIterator(this->first_, this);
	}

	template<typename T>
	Iterator<T>* DoublyCircularLinkedList<T>::getEndIterator() const {
		return new DoublyCircularLinkedListIterator(nullptr, this);
	}

	template<typename T>
	DoublyCircularLinkedList<T>::DoublyCircularLinkedListIterator::DoublyCircularLinkedListIterator(DoublyLinkedListItem<T>* position,
		const DoublyCircularLinkedList<T>* list) : DoublyLinkedList<T>::DoublyLinkedListIterator(position), list(list) { }

	template<typename T>
	Iterator<T>& DoublyCircularLinkedList<T>::DoublyCircularLinkedListIterator::operator++() {
		if (this->position_->getNext() == this->list->first_) {
			this->position_ = nullptr;
		} else {
			this->position_ = this->position_->getNext();
		}
		return *this;
	}

}

