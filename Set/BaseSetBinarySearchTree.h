#pragma once

#include <cstddef>
#include <initializer_list>

template <typename T>
class Node {
public:
	Node(T value) : right(nullptr), left(nullptr), value(value), index(indexCount++) {}

	inline void setRightNode(Node<T> *node) { this->right = node; }
	inline void setLeftNode(Node<T> *node) { this->left = node; }

	inline Node<T> *getRightNode() const { return this->right; }
	inline Node<T> *getLeftNode() const { return this->left; }
	inline T getValue() const { return this->value; }
	inline size_t getIndex() const { return this->index; }

	inline int siblingCount() const { return (!right && !left) ? 0 : ((!right || !left) ? 1 : 2); }
private:
	Node *right;
	Node *left;
	T value;
	size_t index;

	static size_t indexCount;
};

template <typename T>
size_t Node<T>::indexCount = 0;

////////////////////////

template <typename T>
class BinarySearchTree {
public:
	BinarySearchTree();
	~BinarySearchTree();

	Node<T>* insertValue(T);
	Node<T>* find(T);
	void deleteTree();

private:
	Node<T>* insertValue(T, Node<T>*);
	Node<T>* find(T, Node<T>*);
	void deleteTree(Node<T>*);

private:
	Node<T>* root;
};

template<typename T>
BinarySearchTree<T>::BinarySearchTree() : root(nullptr) {

}

template<typename T>
BinarySearchTree<T>::~BinarySearchTree() {
	this->deleteTree();
}

template<typename T>
Node<T> *BinarySearchTree<T>::insertValue(T value) {
	this->root = this->insertValue(value, this->root);
	return this->root;
}

template<typename T>
Node<T> *BinarySearchTree<T>::find(T value) {
	return this->find(value, this->root);
}

template<typename T>
void BinarySearchTree<T>::deleteTree() {
	this->deleteTree(this->root);
	this->root = nullptr;
}

template<typename T>
Node<T> *BinarySearchTree<T>::insertValue(T value, Node<T> *node) {
	if (node == nullptr) {
		node = new Node<T>(value);
	} else if (value < node->getValue()) {
		node->setLeftNode(this->insertValue(value, node->getLeftNode()));
	} else if (value > node->getValue()) {
		node->setRightNode(this->insertValue(value, node->getRightNode()));
	}
	return node;
}

template<typename T>
Node<T> *BinarySearchTree<T>::find(T value, Node<T> *node) {
	if (node == nullptr) {
		return nullptr;
	} else if (value < node->getValue()) {
		return this->find(value, node->getLeftNode());
	} else if (value > node->getValue()) {
		return this->find(value, node->getRightNode());
	} else {
		return node;
	}
}

template<typename T>
void BinarySearchTree<T>::deleteTree(Node<T> *node) {
	if (node != nullptr) {
		this->deleteTree(node->getLeftNode());
		this->deleteTree(node->getRightNode());
		delete node;
		node = nullptr;
	}
}

//////////

namespace Structures {

	template <typename T>
	class BaseSetBinarySearchTree {
	public:
		BaseSetBinarySearchTree(const size_t);
		BaseSetBinarySearchTree(const std::initializer_list<T>&);
		BaseSetBinarySearchTree(const BaseSetBinarySearchTree&);
		~BaseSetBinarySearchTree();

		void add(const T&);

		BaseSetBinarySearchTree& operator=(const BaseSetBinarySearchTree&);
//		T& operator[](const size_t);
//		const T& operator[](const size_t) const;

		int getIndexOf(const T&);

		size_t size() const;

	private:
		BinarySearchTree<T>* base;
		size_t size_;
	};

	template<typename T>
	BaseSetBinarySearchTree<T>::BaseSetBinarySearchTree(const size_t size) : size_(size), base(new BinarySearchTree<T>) {
	}

	template<typename T>
	BaseSetBinarySearchTree<T>::BaseSetBinarySearchTree(const std::initializer_list<T>& baseList) : base(new BinarySearchTree<T>), size_(baseList.size()) {
		for (const T& temp : baseList) {
			this->base->insertValue(temp);
		}
	}

	template<typename T>
	BaseSetBinarySearchTree<T>::BaseSetBinarySearchTree(const BaseSetBinarySearchTree& other) : size_(other.size_), base(new BinarySearchTree<T>) {
//		memcpy(this->base, other.base, this->size_ * sizeof(T));
	}

	template<typename T>
	BaseSetBinarySearchTree<T>::~BaseSetBinarySearchTree() {
		delete this->base;
		this->base = nullptr;
		this->size_ = 0;
	}

	template<typename T>
	void BaseSetBinarySearchTree<T>::add(const T& data) {
		this->base->insertValue(data);
	}

	template<typename T>
	BaseSetBinarySearchTree<T>& BaseSetBinarySearchTree<T>::operator=(const BaseSetBinarySearchTree& other) {
//		if (this != &other) {
//			if (this->size_ != other.size_) {
//				this->size_ = other.size_;
//				delete[] this->base;
//				this->base = new T[this->size_];
//			}
//			std::memcpy(this->base, other.base, this->size_ * sizeof(T));
//		}
		return *this;
	}

//	template<typename T>
//	T& BaseSetBinarySearchTree<T>::operator[](const size_t index) {
//		if (index > this->size_) {
//			throw std::out_of_range("BaseSet<T>::operator[]...Out of Bounds!");
//		}
//		return this->base[index];
//	}

//	template<typename T>
//	const T& BaseSetBinarySearchTree<T>::operator[](const size_t index) const {
//		if (index >= this->size_) {
//			throw std::out_of_range("BaseSet<T>::operator[]...Out of Bounds!");
//		}
//		return this->base[index];
//	}

	template<typename T>
	int BaseSetBinarySearchTree<T>::getIndexOf(const T& data) {
		return this->base->find(data)->getIndex();
	}

	template<typename T>
	size_t BaseSetBinarySearchTree<T>::size() const {
		return this->size_;
	}

}
