#pragma once

#include "Table.h"
#include "List/List.h"
#include "Tree/BinaryTree.h"
#include <stdexcept>

namespace Structures {

	template <typename K, typename T>
	class BinarySearchTree : public Table<K, T> {
	public:
		using BSTTreeNode = BinaryTreeNode<TableItem<K, T>*>;
	public:
		BinarySearchTree();
		BinarySearchTree(const BinarySearchTree<K, T>& other);
		~BinarySearchTree();

		virtual Structure* clone() const;

		size_t size() const override;

		Table<K, T>& operator=(const Table<K, T>& other) override;
		virtual BinarySearchTree<K, T>& operator=(const BinarySearchTree<K, T>& other);

		T& operator[](const K key) override;
		const T operator[](const K key) const override;

		void insert(const K& key, const T& data) override;
		T remove(const K& key) override;
		bool tryFind(const K& key, T& data) override;
		bool containsKey(const K& key) override;
		void clear() override;

		Iterator<TableItem<K, T>*>* getBeginIterator() const override;
		Iterator<TableItem<K, T>*>* getEndIterator() const override;
	protected:
		BSTTreeNode* findBSTNode(const K& key, bool& found) const;
	protected:
		BinaryTree<TableItem<K, T>*>* binaryTree;
		size_t size_;

		bool tryToInsertNode(BSTTreeNode* node);
		void extractNode(BSTTreeNode* node);
	};

	template<typename K, typename T>
	inline BinarySearchTree<K, T>::BinarySearchTree(): Table<K, T>(), binaryTree(new BinaryTree<TableItem<K, T>*>()), size_(0) {
	}

	template<typename K, typename T>
	inline BinarySearchTree<K, T>::BinarySearchTree(const BinarySearchTree<K, T>& other): BinarySearchTree() {
		*this = other;
	}

	template<typename K, typename T>
	inline BinarySearchTree<K, T>::~BinarySearchTree() {
		this->clear();
		delete this->binaryTree;
		this->binaryTree = nullptr;
	}

	template<typename K, typename T>
	inline Structure * BinarySearchTree<K, T>::clone() const {
		return new BinarySearchTree<K, T>(*this);
	}

	template<typename K, typename T>
	inline size_t BinarySearchTree<K, T>::size() const {
		return this->size_;
	}

	template<typename K, typename T>
	inline Table<K, T>& BinarySearchTree<K, T>::operator=(const Table<K, T>& other) {
		if (this != &other) {
			*this = dynamic_cast<const BinarySearchTree<K, T>&>(other);
		}
		return *this;
	}

	template<typename K, typename T>
	inline BinarySearchTree<K, T>& BinarySearchTree<K, T>::operator=(const BinarySearchTree<K, T>& other) {
		if (this != &other) {
			this->clear();

			Iterator<TableItem<K, T>*>* current = new typename Tree<TableItem<K, T>*>::PreOrderTreeIterator(other.binaryTree->getRoot());
			Iterator<TableItem<K, T>*>* end = new typename Tree<TableItem<K, T>*>::PreOrderTreeIterator(nullptr);
			while (*current != *end) {
				TableItem<K, T>* item = *(*current);
				this->insert(item->getKey(), item->accessData());
				++(*current);
			}
			delete current;
			delete end;
		}
		return *this;
	}

	template<typename K, typename T>
	inline T & BinarySearchTree<K, T>::operator[](const K key) {
		bool found = false;
		BSTTreeNode* node = this->findBSTNode(key, found);

		if (found) {
			return node->accessData()->accessData();
		} else {
			throw std::invalid_argument("Data with key not found!");
		}
	}

	template<typename K, typename T>
	inline const T BinarySearchTree<K, T>::operator[](const K key) const {
		bool found = false;
		BSTTreeNode* node = this->findBSTNode(key, found);

		if (found) {
			return node->accessData()->accessData();
		} else {
			throw std::invalid_argument("Data with key not found!");
		}
	}

	template<typename K, typename T>
	inline void BinarySearchTree<K, T>::insert(const K& key, const T& data) {
		TableItem<K, T>* newItem = new TableItem<K, T>(key, data);
		BSTTreeNode* newNode = new BinaryTreeNode<TableItem<K, T>*>(newItem);

		if (!this->tryToInsertNode(newNode)) {
			delete newItem;
			delete newNode;
			throw std::logic_error("Unable to insert");
		}
	}

	template<typename K, typename T>
	inline T BinarySearchTree<K, T>::remove(const K& key) {
		//TODO 10: BinarySearchTree
//		throw std::exception("BinarySearchTree<K, T>::remove: Not implemented yet.");
	}

	template<typename K, typename T>
	inline bool BinarySearchTree<K, T>::tryFind(const K& key, T& data) {
		bool found = false;
		BSTTreeNode* node = this->findBSTNode(key, found);
		if (found) {
			data = node->accessData()->accessData();
		}
		return found;
	}

	template<typename K, typename T>
	inline bool BinarySearchTree<K, T>::containsKey(const K& key) {
		bool found = false;
		this->findBSTNode(key, found);
		return found;
	}

	template<typename K, typename T>
	inline void BinarySearchTree<K, T>::clear() {
		for (TableItem<K, T>* item : *this->binaryTree) {
			delete item;
		}
		this->binaryTree->clear();
		this->size_ = 0;
	}

	template<typename K, typename T>
	inline Iterator<TableItem<K, T>*>* BinarySearchTree<K, T>::getBeginIterator() const {
//		return new typename BinaryTree<TableItem<K, T>*>::InOrderTreeIterator(this->binaryTree->getRoot());
		return this->binaryTree->getBeginIterator();
	}

	template<typename K, typename T>
	inline Iterator<TableItem<K, T>*>* BinarySearchTree<K, T>::getEndIterator() const {
//		return new typename BinaryTree<TableItem<K, T>*>::InOrderTreeIterator(nullptr);
		return this->binaryTree->getEndIterator();
	}

	template<typename K, typename T>
	inline typename BinarySearchTree<K,T>::BSTTreeNode* BinarySearchTree<K, T>::findBSTNode(const K& key, bool& found) const {
		BSTTreeNode* result = dynamic_cast<BSTTreeNode*>(this->binaryTree->getRoot());

		if (result == nullptr) {
			found = false;
			return result;
		}

		while (result->accessData()->getKey() != key) {
			if (key < result->accessData()->getKey()) {
				if (result->hasLeftSon()) {
					result = result->getLeftSon();
				} else {
					break;
				}
			} else {
				if (result->hasRightSon()) {
					result = result->getRightSon();
				} else {
					break;
				}
			}
		}

		found = result->accessData()->getKey() == key;
		return result;
	}

	template<typename K, typename T>
	inline bool BinarySearchTree<K, T>::tryToInsertNode(BSTTreeNode* node) {
		bool found = false;
		BSTTreeNode* parent = this->findBSTNode(node->accessData()->getKey(), found);

		if (!found) {
			if (parent == nullptr) {
				this->binaryTree->replaceRoot(node);
			} else {
				if (parent->accessData()->getKey() < node->accessData()->getKey()) {
					parent->changeRightSon(node);
				} else {
					parent->changeLeftSon(node);
				}
			}
			++this->size_;
		}
		return found == 0;
	}

	template<typename K, typename T>
	inline void BinarySearchTree<K, T>::extractNode(BSTTreeNode* node) {

	}

}

