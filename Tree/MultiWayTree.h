#pragma once

#include "Tree.h"
#include "List/List.h"
#include "List/ArrayList.h"

namespace Structures {

	template <typename T>
	class MultiWayTreeNode : public TreeNode<T> {
	public:
		MultiWayTreeNode(T data);
		MultiWayTreeNode(const MultiWayTreeNode<T>& other);
		~MultiWayTreeNode();

		TreeNode<T>* shallowCopy() override;
		bool isLeaf() override;

		TreeNode<T>* getSon(int order) const override;

		void insertSon(TreeNode<T>* son, int order) override;
		TreeNode<T>* replaceSon(TreeNode<T>* son, int order) override;
		TreeNode<T>* removeSon(int order) override;

		int degree() override;
	protected:
		List<MultiWayTreeNode<T>*>* children;
	};

	template <typename T>
	class MultiWayTree : public Tree<T> {
	public:
		MultiWayTree();
		MultiWayTree(const MultiWayTree<T>& other);

		Structure* clone() const override;
		TreeNode<T>* createTreeNodeInstance() override;
	};


	template<typename T>
	inline MultiWayTreeNode<T>::MultiWayTreeNode(T data) : TreeNode<T>(data), children(new ArrayList<MultiWayTreeNode<T>*>()) {
	}

	template<typename T>
	inline MultiWayTreeNode<T>::MultiWayTreeNode(const MultiWayTreeNode<T>& other) : TreeNode<T>(other),
		children(dynamic_cast<ArrayList<MultiWayTreeNode<T>*>*>(other.children->clone())) {
	}

	template<typename T>
	inline MultiWayTreeNode<T>::~MultiWayTreeNode() {
		for (MultiWayTreeNode<T>* temp : *this->children) {
			if (temp != nullptr) {
				delete temp;
				temp = nullptr;
			}
		}
		delete this->children;
		this->children = nullptr;
	}

	template<typename T>
	inline TreeNode<T>* MultiWayTreeNode<T>::shallowCopy() {
		return new MultiWayTreeNode<T>(*this);
	}

	template<typename T>
	inline bool MultiWayTreeNode<T>::isLeaf() {
		return this->children->size() == 0;
	}

	template<typename T>
	inline TreeNode<T>* MultiWayTreeNode<T>::getSon(int order) const {
		return (*this->children)[order];
	}

	template<typename T>
	inline void MultiWayTreeNode<T>::insertSon(TreeNode<T>* son, int order) {
		this->children->insert(dynamic_cast<MultiWayTreeNode*>(son), order);
		if (son != nullptr) {
			son->setParent(this);
		}
	}

	template<typename T>
	inline TreeNode<T>* MultiWayTreeNode<T>::replaceSon(TreeNode<T>* son, int order) {
		MultiWayTreeNode<T>* result = (*this->children)[order];
		(*this->children)[order] = dynamic_cast<MultiWayTreeNode<T>*>(son);

		if (son != nullptr) {
			son->setParent(this);
		}
		if (result != nullptr) {
			result->setParent(nullptr);
		}
		return result;
	}

	template<typename T>
	inline TreeNode<T>* MultiWayTreeNode<T>::removeSon(int order) {
		MultiWayTreeNode<T>* result = (*this->children)[order];
		this->children->removeAt(order);

		if (result != nullptr) {
			result->setParent(nullptr);
		}
		return result;
	}

	template<typename T>
	inline int MultiWayTreeNode<T>::degree() {
		return static_cast<int>(this->children->size());
	}

	template<typename T>
	inline MultiWayTree<T>::MultiWayTree() : Tree<T>() {
	}

	template<typename T>
	inline MultiWayTree<T>::MultiWayTree(const MultiWayTree<T>& other) : Tree<T>(other) {
	}

	template<typename T>
	inline Structure * MultiWayTree<T>::clone() const {
		return new MultiWayTree<T>(*this);
	}

	template<typename T>
	inline TreeNode<T>* MultiWayTree<T>::createTreeNodeInstance() {
		T data = T();
		return new MultiWayTreeNode<T>(data);
	}

}

