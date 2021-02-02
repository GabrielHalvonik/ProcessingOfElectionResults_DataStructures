#pragma once

#include "List.h"
#include "StructureIterator.h"
#include "DSRoutines.h"

namespace Structures {

	template<typename T>
	class DoublyLinkedListItem : public DataItem<T> {
	public:
		DoublyLinkedListItem(T data);
		DoublyLinkedListItem(const DoublyLinkedListItem<T>& other);
		~DoublyLinkedListItem();

		DoublyLinkedListItem<T>* getNext();
		DoublyLinkedListItem<T>* getPrevious();
		void setNext(DoublyLinkedListItem<T>* next);
		void setPrevious(DoublyLinkedListItem<T>* previous);
	private:
		DoublyLinkedListItem<T>* next_;
		DoublyLinkedListItem<T>* previous_;
	};

	template <typename T>
	class DoublyLinkedList : public List<T> {
	public:
		DoublyLinkedList();
		DoublyLinkedList(const DoublyLinkedList&);
		virtual ~DoublyLinkedList();

		Structure* clone() const override;
		size_t size() const override;

		List<T>& operator=(const List<T>& other) override;
		DoublyLinkedList& operator=(const DoublyLinkedList&);
		T& operator[](const int index) override;
		const T operator[](const int index) const override;

		void add(const T& data) override;
		void insert(const T& data, const int index) override;
		bool tryRemove(const T& data) override;
		T removeAt(const int index) override;
		int getIndexOf(const T& data) override;
		void clear() override;

		Iterator<T>* getBeginIterator() const override;
		Iterator<T>* getEndIterator() const override;

		template <typename E>
		friend class DoublyCircularLinkedList;
	private:
		size_t size_;
		DoublyLinkedListItem<T>* first_;
		DoublyLinkedListItem<T>* last_;

	private:
		DoublyLinkedListItem<T>* getItemAtIndex(int index) const;

	private:
		class DoublyLinkedListIterator : public Iterator<T> {
		public:
			DoublyLinkedListIterator(DoublyLinkedListItem<T>* position);
			~DoublyLinkedListIterator();

			Iterator<T>& operator=(const Iterator<T>& other) override;
			bool operator!=(const Iterator<T>& other) override;
			const T operator*() override;
			virtual Iterator<T>& operator++() override;

		protected:
			DoublyLinkedListItem<T>* position_;
		};
	};

	template<typename T>
	inline DoublyLinkedListItem<T>::DoublyLinkedListItem(T data) : DataItem<T>(data), next_(nullptr), previous_(nullptr) {
	}

	template<typename T>
	inline DoublyLinkedListItem<T>::DoublyLinkedListItem(const DoublyLinkedListItem<T>& other) : DataItem<T>(other.data_),
		previous_(other.previous_), next_(other.next_) {
	}

	template<typename T>
	inline DoublyLinkedListItem<T>::~DoublyLinkedListItem() {
		this->next_ = nullptr;
		this->previous_ = nullptr;
	}

	template<typename T>
	inline DoublyLinkedListItem<T>* DoublyLinkedListItem<T>::getNext() {
		return this->next_;
	}

	template<typename T>
	inline DoublyLinkedListItem<T>* DoublyLinkedListItem<T>::getPrevious() {
		return this->previous_;
	}

	template<typename T>
	inline void DoublyLinkedListItem<T>::setNext(DoublyLinkedListItem<T>* next) {
		this->next_ = next;
	}

	template<typename T>
	inline void DoublyLinkedListItem<T>::setPrevious(DoublyLinkedListItem<T>* previous) {
		this->previous_ = previous;
	}

	template<typename T>
	DoublyLinkedList<T>::DoublyLinkedList() : List<T>(), size_(0), first_(nullptr), last_(nullptr) {
	}

	template<typename T>
	DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList& other) : DoublyLinkedList() {
		*this = other;
	}

	template<typename T>
	DoublyLinkedList<T>::~DoublyLinkedList() {
		this->clear();
	}

	template<typename T>
	Structure* DoublyLinkedList<T>::clone() const {
		return new DoublyLinkedList<T>(*this);
	}

	template<typename T>
	size_t DoublyLinkedList<T>::size() const {
		return this->size_;
	}

	template<typename T>
	List<T>& DoublyLinkedList<T>::operator=(const List<T>& other) {
		if (this != &other) {
			*this = dynamic_cast<const DoublyLinkedList<T>&>(other);
		}
		return *this;
	}

	template<typename T>
	DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList& other) {
		if (this != &other) {
			this->clear();
			for (T item : other) {
				this->add(item);
			}
		}
		return *this;
	}

	template<typename T>
	T& DoublyLinkedList<T>::operator[](const int index) {
		return this->getItemAtIndex(index)->accessData();
	}

	template<typename T>
	const T DoublyLinkedList<T>::operator[](const int index) const {
		return this->getItemAtIndex(index)->accessData();
	}

	template<typename T>
	void DoublyLinkedList<T>::add(const T& data) {
		DoublyLinkedListItem<T>* newItem = new DoublyLinkedListItem<T>(data);
		if (this->size_ == 0) {
			this->first_ = this->last_ = newItem;
		} else {
			this->last_->setNext(newItem);
			newItem->setPrevious(this->last_);
			this->last_ = newItem;
		}
		++this->size_;
	}

	template<typename T>
	void DoublyLinkedList<T>::insert(const T& data, const int index) {
//		DSRoutines::rangeCheckExcept(index, this->size_, "DoublyLinkedList<T>::insert...Out of bouds!");

		if (index == this->size_) {
			this->add(data);
		} else {
			DoublyLinkedListItem<T>* newItem = new DoublyLinkedListItem<T>(data);
			if (index == 0) {
				newItem->setNext(this->first_);
				this->first_->setPrevious(newItem);
				this->first_ = newItem;
			} else {
				DoublyLinkedListItem<T>* previousItem = this->getItemAtIndex(index - 1);
				DoublyLinkedListItem<T>* nextItem = previousItem->getNext();
				newItem->setPrevious(previousItem);
				newItem->setNext(nextItem);
				previousItem->setNext(newItem);
				nextItem->setPrevious(newItem);
			}
			++this->size_;
		}
	}

	template<typename T>
	bool DoublyLinkedList<T>::tryRemove(const T& data) {
		int index = this->getIndexOf(data);
		if (index == -1) {
			return false;
		}
		this->removeAt(index);
		return true;
	}

	template<typename T>
	T DoublyLinkedList<T>::removeAt(const int index) {
//		DSRoutines::rangeCheckExcept(index, this->size_, "DoublyLinkedList<T>::removeAt...Out of bouds!");

		DoublyLinkedListItem<T>* itemToRemove;
		DoublyLinkedListItem<T>* previousItem;
		DoublyLinkedListItem<T>* nextItem;

		if (index == 0) {
			itemToRemove = this->first_;
			if (this->size_ > 1) {
				nextItem = this->first_->getNext();
				nextItem->setPrevious(nullptr);
				this->first_ = nextItem;
			}
		} else if (index == this->size_ - 1) {
			itemToRemove = this->last_;
			if (this->size_ > 1) {
				previousItem = this->last_->getPrevious();
				previousItem->setNext(nullptr);
				this->last_ = previousItem;
			}
		} else {
			itemToRemove = this->getItemAtIndex(index);
			previousItem = itemToRemove->getPrevious();
			nextItem = itemToRemove->getNext();
			previousItem->setNext(nextItem);
			nextItem->setPrevious(previousItem);
		}

		if (this->size_ == 1) {
			this->first_ = this->last_ = nullptr;
		}

		T removedData = itemToRemove->accessData();
		delete itemToRemove;
		itemToRemove = nullptr;

		--this->size_;
		return removedData;
	}

	template<typename T>
	int DoublyLinkedList<T>::getIndexOf(const T& data) {
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
	void DoublyLinkedList<T>::clear() {
		DoublyLinkedListItem<T>* itemToRemove = this->first_;

		while (itemToRemove != nullptr) {
			this->first_ = this->first_->getNext();
			delete itemToRemove;
			itemToRemove = this->first_;
		}
		this->size_ = 0;
		this->first_ = this->last_ = nullptr;
	}

	template<typename T>
	Iterator<T>* DoublyLinkedList<T>::getBeginIterator() const {
		return new DoublyLinkedListIterator(this->first_);
	}

	template<typename T>
	Iterator<T>* DoublyLinkedList<T>::getEndIterator() const {
		return new DoublyLinkedListIterator(nullptr);
	}

	template<typename T>
	DoublyLinkedListItem<T>* DoublyLinkedList<T>::getItemAtIndex(int index) const {
//		DSRoutines::rangeCheckExcept(index, this->size_, "LinkedList<T>::getItemAtIndex...Out of bounds.");

		DoublyLinkedListItem<T>* item;

		if (index < (this->size_ / 2)) {
			item = this->first_;
			for (int i = 0; i < index; ++i) {
				item = item->getNext();
			}
		} else {
			item = this->last_;
			for (int i = this->size_ - 1; i > index ; --i) {
				item = item->getPrevious();
			}
		}
		return item;
	}

	template<typename T>
	DoublyLinkedList<T>::DoublyLinkedListIterator::DoublyLinkedListIterator(DoublyLinkedListItem<T>* position) : position_(position) {
	}

	template<typename T>
	DoublyLinkedList<T>::DoublyLinkedListIterator::~DoublyLinkedListIterator() {
		this->position_ = nullptr;
	}

	template<typename T>
	Iterator<T>& DoublyLinkedList<T>::DoublyLinkedListIterator::operator=(const Iterator<T>& other) {
		if (this != &other) {
			this->position_ = dynamic_cast<const DoublyLinkedList<T>::DoublyLinkedListIterator&>(other).position_;
		}
		return *this;
	}

	template<typename T>
	bool DoublyLinkedList<T>::DoublyLinkedListIterator::operator!=(const Iterator<T>& other) {
		return this->position_ != dynamic_cast<const DoublyLinkedListIterator&>(other).position_;
	}

	template<typename T>
	const T DoublyLinkedList<T>::DoublyLinkedListIterator::operator*() {
		return this->position_->accessData();
	}

	template<typename T>
	Iterator<T>& DoublyLinkedList<T>::DoublyLinkedListIterator::operator++() {
		this->position_ = this->position_->getNext();
		return *this;
	}


}

