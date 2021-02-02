#pragma once

#include "BinarySearchTree.h"
#include <random>

namespace Structures {

	template <typename K, typename T>
	class TreapItem : public TableItem<K, T> {
	public:
		TreapItem(K key, T data, int priority);

		int getPriority();
		void minimizePriority();
	private:
		int priority;
	};

	template <typename K, typename T>
	class Treap : public BinarySearchTree<K, T> {
	public:
		Treap();
		Treap(const Treap<K, T>& other);
		~Treap();

		Structure* clone() const override;

		BinarySearchTree<K, T>& operator=(const BinarySearchTree<K, T>& other) override;
		virtual Treap<K, T>& operator=(const Treap<K, T>& other);

		void insert(const K& key, const T& data) override;
		T remove(const K& key) override;

	private:
		std::default_random_engine* generator;

		bool isHeapOK(typename BinarySearchTree<K, T>::BSTTreeNode* node);

		int extractPriority(typename BinarySearchTree<K, T>::BSTTreeNode* node);
		void rotateLeftOverParent(typename BinarySearchTree<K, T>::BSTTreeNode* node);
		void rotateRightOverParent(typename BinarySearchTree<K, T>::BSTTreeNode* node);
	};

	template<typename K, typename T>
	inline TreapItem<K, T>::TreapItem(K key, T data, int priority): TableItem<K, T>(key, data), priority(priority) {
	}

	template<typename K, typename T>
	inline int TreapItem<K, T>::getPriority() {
		return priority;
	}

	template<typename K, typename T>
	inline void TreapItem<K, T>::minimizePriority() {
		priority = INT_MAX;
	}

	template<typename K, typename T>
	inline Treap<K, T>::Treap() : BinarySearchTree<K, T>(), generator(new std::default_random_engine()) {
	}

	template<typename K, typename T>
	inline Treap<K, T>::Treap(const Treap<K, T>& other) : Treap() {
		*this = other;
	}

	template<typename K, typename T>
	inline Treap<K, T>::~Treap() {
		delete this->generator;
		this->generator = nullptr;
	}

	template<typename K, typename T>
	inline Structure * Treap<K, T>::clone() const {
		return new Treap<K, T>(*this);
	}

	template<typename K, typename T>
	inline BinarySearchTree<K, T>& Treap<K, T>::operator=(const BinarySearchTree<K, T>& other) {
		return *this = dynamic_cast<const Treap<K, T>&>(other);
	}

	template<typename K, typename T>
	inline Treap<K, T>& Treap<K, T>::operator=(const Treap<K, T>& other) {
		if (this != &other) {
			BinarySearchTree<K, T>::operator=(other);
			*this->generator = (*other.generator);
		}
		return *this;
	}

	template<typename K, typename T>
	inline void Treap<K, T>::insert(const K& key, const T& data) {
		TableItem<K, T>* newItem = new TreapItem<K, T>(key, data, (*generator)());
		BinaryTreeNode<TableItem<K, T>*>* newNode = new BinaryTreeNode<TableItem<K, T>*>(newItem);

		if (!this->tryToInsertNode(newNode)) {
			delete newItem;
			delete newNode;
			throw std::logic_error("Unable to insert");
		} else {
			while (!this->isHeapOK(newNode)) {
				if (newNode->isLeftSon()) {
					this->rotateRightOverParent(newNode);
				} else {
					this->rotateLeftOverParent(newNode);
				}
			}
		}
	}

	template<typename K, typename T>
	inline T Treap<K, T>::remove(const K& key) {

	}

	template<typename K, typename T>
	inline bool Treap<K, T>::isHeapOK(typename BinarySearchTree<K, T>::BSTTreeNode* node) {
		if (node != nullptr) {
		int myPriority = this->extractPriority(node);
		int parentPriority = this->extractPriority(node->getParent());
		int leftSonPriority = this->extractPriority(node->getLeftSon());
		int rightSonPriority = this->extractPriority(node->getRightSon());

		return (parentPriority == INT_MIN || myPriority >= parentPriority) &&
			   (leftSonPriority == INT_MIN || myPriority <= leftSonPriority) &&
			   (rightSonPriority == INT_MIN || myPriority <= rightSonPriority);
		}
		return true;
	}

	template<typename K, typename T>
	inline int Treap<K, T>::extractPriority(typename BinarySearchTree<K, T>::BSTTreeNode* node) {
		return node == nullptr ? INT_MIN : dynamic_cast<TreapItem<K, T>*>(node->accessData())->getPriority();
	}

	template<typename K, typename T>
	inline void Treap<K, T>::rotateLeftOverParent(typename BinarySearchTree<K, T>::BSTTreeNode* node) {
		if (node->isRightSon()) {
			BinaryTreeNode<TableItem<K, T>*>* left = node->getLeftSon();
			node->setLeftSon(nullptr);
			BinaryTreeNode<TableItem<K, T>*>* parent = node->getParent();
			BinaryTreeNode<TableItem<K, T>*>* grandParent = parent->getParent();
			parent->setRightSon(nullptr);

			if (grandParent != nullptr) {
				if (parent->isLeftSon()) {
					grandParent->setLeftSon(node);
				} else {
					grandParent->setRightSon(node);
				}
			} else {
				this->binaryTree->replaceRoot(node);
			}

			parent->setRightSon(left);
			node->setLeftSon(parent);
		}
	}

	template<typename K, typename T>
	inline void Treap<K, T>::rotateRightOverParent(typename BinarySearchTree<K, T>::BSTTreeNode* node) {
		if (node->isLeftSon()) {
			BinaryTreeNode<TableItem<K, T>*>* right = node->getRightSon();
			node->setRightSon(nullptr);
			BinaryTreeNode<TableItem<K, T>*>* parent = node->getParent();
			BinaryTreeNode<TableItem<K, T>*>* grandParent = parent->getParent();
			parent->setLeftSon(nullptr);

			if (grandParent != nullptr) {
				if (parent->isLeftSon()) {
					grandParent->setLeftSon(node);
				} else {
					grandParent->setRightSon(node);
				}
			} else {
				this->binaryTree->replaceRoot(node);
			}

			parent->setLeftSon(right);
			node->setRightSon(parent);
		}

	}
}
