#pragma once

#include "PriorityQueueList.h"
#include "List/ArrayList.h"
#include <exception>

namespace Structures {

	template<typename T>
	class Heap : public PriorityQueueList<T> {
	public:
		Heap();

		Heap(const Heap<T>& other);
		Heap(Heap<T>&& other);

		Structure* clone() const override;

		virtual PriorityQueueList<T>& operator=(const PriorityQueueList<T>& other) override;
		virtual Heap<T>& operator=(const Heap<T>& other);

		void push(const int priority, const T& data) override;
		T pop() override;

	protected:
		int indexOfPeek() const override;

	private:
		int getParentIndex(const int index);
		int getGreaterSonIndex(const int index);
	};

	template<typename T>
	Heap<T>::Heap() : PriorityQueueList<T>(new ArrayList<PriorityQueueItem<T>*>()) {
	}

	template<typename T>
	Heap<T>::Heap(const Heap<T>& other) : Heap<T>() {
		*this = other;
	}

	template <typename T>
	Heap<T>::Heap(Heap<T>&& other) : PriorityQueue<T>(), PriorityQueueList<T>::list(other.list) {
		other.list = nullptr;
	}

	template<typename T>
	Structure* Heap<T>::clone() const {
		return new Heap<T>(*this);
	}

	template<typename T>
	inline PriorityQueueList<T>& Heap<T>::operator=(const PriorityQueueList<T>& other) {
		return *this = dynamic_cast<const Heap<T>&>(other);
	}

	template<typename T>
	inline Heap<T>& Heap<T>::operator=(const Heap<T>& other) {
		if (this != &other) {
			PriorityQueueList<T>::operator=(other);
		}
		return *this;
	}

	template<typename T>
	void Heap<T>::push(const int priority, const T& data) {
		this->list->add(new PriorityQueueItem<T>(priority, data));

		int index = this->list->size() - 1;
		int parentIndex = this->getParentIndex(index);

		while (parentIndex >= 0 && priority < (*this->list)[parentIndex]->getPriority()) {
			DSRoutines::swap((*this->list)[index], (*this->list)[parentIndex]);
			index = parentIndex;
			parentIndex = this->getParentIndex(index);
		}
	}

	template<typename T>
	T Heap<T>::pop() {
		DSRoutines::swap((*this->list)[0], (*this->list)[this->list->size() - 1]);
		PriorityQueueItem<T>* item = this->list->removeAt(this->list->size() - 1);

		size_t oldIndex = 0;
		size_t newIndex = this->getGreaterSonIndex(oldIndex);

		while (newIndex < this->list->size() && (*this->list)[oldIndex]->getPriority() > (*this->list)[newIndex]->getPriority()) {
			DSRoutines::swap((*this->list)[oldIndex], (*this->list)[newIndex]);
			oldIndex = newIndex;
			newIndex = this->getGreaterSonIndex(oldIndex);
		}

		T data = item->accessData();
		delete item;
		return data;
	}

	template<typename T>
	inline int Heap<T>::getParentIndex(const int index) {
		return (index + 1) / 2 - 1;
	}

	template<typename T>
	inline int Heap<T>::getGreaterSonIndex(const int index) {
		int left = 2 * index + 1;
		int right = left + 1;
		if (left >= this->size()) {
			return -1;
		} else {
			if (right >= this->size()) {
				return left;
			} else {
				return (*this->list)[left]->getPriority() <= (*this->list)[right]->getPriority() ? left : right;
			}
		}
	}

	template<typename T>
	inline int Heap<T>::indexOfPeek() const {
//        if (this->list->isEmpty()) {
//            throw std::logic_error("Heap<T>::indexOfPeek()...List is empty...");
//        }
		return 0;
	}
}




//#pragma once

//#include "PriorityQueueList.h"
//#include "List/ArrayList.h"
//#include <exception>

//namespace Structures {

//	template<typename T>
//	class Heap : public PriorityQueueList<T> {
//	public:
//		Heap();

//		Heap(const Heap<T>& other);

//		Structure* clone() const override;

//		virtual PriorityQueueList<T>& operator=(const PriorityQueueList<T>& other) override;
//		virtual Heap<T>& operator=(const Heap<T>& other);

//		void push(const int priority, const T& data) override;
//		T pop() override;

//	protected:
//		int indexOfPeek() const override;

//	private:
//		int getParentIndex(const int index);
//		int getGreaterSonIndex(const int index);
//	};

//	template<typename T>
//	Heap<T>::Heap() : PriorityQueueList<T>(new ArrayList<PriorityQueueItem<T>*>()) {
//	}

//	template<typename T>
//	Heap<T>::Heap(const Heap<T>& other) : Heap<T>() {
//		*this = other;
//	}

//	template<typename T>
//	Structure* Heap<T>::clone() const {
//		return new Heap<T>(*this);
//	}

//	template<typename T>
//	inline PriorityQueueList<T>& Heap<T>::operator=(const PriorityQueueList<T>& other) {
//		return *this = dynamic_cast<const Heap<T>&>(other);
//	}

//	template<typename T>
//	inline Heap<T>& Heap<T>::operator=(const Heap<T>& other) {
//		if (this != &other) {
//			PriorityQueueList<T>::operator=(other);
//		}
//		return *this;
//	}

//	template<typename T>
//	void Heap<T>::push(const int priority, const T& data) {
//		this->list->add(new PriorityQueueItem<T>(priority, data));

//		int index = this->list->size() - 1;
//		int parentIndex = this->getParentIndex(index);

//		while ((index != parentIndex) && (*this->list)[index]->getPriority() < (*this->list)[parentIndex]->getPriority()) {
//			DSRoutines::swap<PriorityQueueItem<T> *>((*this->list)[index], (*this->list)[parentIndex]);
//			index = parentIndex;
//			parentIndex = this->getParentIndex(index);
//		}
//	}

//	template<typename T>
//	T Heap<T>::pop() {
//		if (this->list->isEmpty()) {
//			throw std::logic_error("Heap<T>::indexOfPeek()...List is empty...");
//		}

//		int oldIndex = this->indexOfPeek();
//		int newIndex = this->list->size() - 1;
//		DSRoutines::swap((*this->list)[oldIndex], (*this->list)[newIndex]);
//		T data = this->list->removeAt(newIndex)->accessData();

//		newIndex = this->getGreaterSonIndex(oldIndex);
//		while (newIndex < static_cast<int>(this->list->size()) && (*this->list)[oldIndex]->getPriority() > (*this->list)[newIndex]->getPriority()) {
//			DSRoutines::swap<PriorityQueueItem<T> *>((*this->list)[oldIndex], (*this->list)[newIndex]);
//			oldIndex = newIndex;
//			newIndex = this->getGreaterSonIndex(oldIndex);
//		}
//		return data;
//	}

//	template<typename T>
//	inline int Heap<T>::getParentIndex(const int index) {
//		if (index == 0) {
//			return 0;
//		}
//		return (index - 1) >> 1;
//	}

//	template<typename T>
//	inline int Heap<T>::getGreaterSonIndex(const int index) {
//		int left = index * 2 + 1;
//		int right = left + 1;
//		if (static_cast<int>(this->list->size()) - 1 <= left) {
//			return left;
//		} else {
//			return (*this->list)[left]->getPriority() <= (*this->list)[right]->getPriority() ? left : right;
//		}
//	}

//	template<typename T>
//	inline int Heap<T>::indexOfPeek() const {
//		if (this->list->isEmpty()) {
//			throw std::logic_error("Heap<T>::indexOfPeek()...List is empty...");
//		}
//		return 0;
//	}
//}
