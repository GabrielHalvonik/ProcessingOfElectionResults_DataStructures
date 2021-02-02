#pragma once

#include "Tree.h"
#include "Array/Array.h"

namespace Structures {

	template <typename T, int K>
	class KWayTreeNode : public TreeNode<T> {
	public:
		KWayTreeNode(T data);
		KWayTreeNode(const KWayTreeNode<T, K>& other);
		~KWayTreeNode();

		TreeNode<T>* shallowCopy() override;
		bool isLeaf() override;

		TreeNode<T>* getSon(int order) const override;
		void insertSon(TreeNode<T>* son, int order) override;
		TreeNode<T>* replaceSon(TreeNode<T>* son, int order) override;
		TreeNode<T>* removeSon(int order) override;

		int degree() override;
		int numberOfSons();
	protected:
		Array<KWayTreeNode<T, K>*>* children;
	};

	template <typename T, int K> 
	class KWayTree : public Tree<T> {
	public:
		KWayTree();
		KWayTree(const KWayTree<T, K>& other);
		Structure* clone() const override;

		TreeNode<T>* createTreeNodeInstance() override;
	};


	template<typename T, int K>
	inline KWayTreeNode<T, K>::KWayTreeNode(T data): TreeNode<T>(data), children(new Array<KWayTreeNode<T, K>*>(K)) {
	}

	template<typename T, int K>
	inline KWayTreeNode<T, K>::KWayTreeNode(const KWayTreeNode<T, K>& other) : TreeNode<T>(other),
		children(dynamic_cast<Array<KWayTreeNode<T, K>*>*>(other.children->clone())) {
	}

	template<typename T, int K>
	inline KWayTreeNode<T, K>::~KWayTreeNode() {
		for (int i = 0; i < this->children->size(); ++i) {
			if ((*this->children)[i] != nullptr) {
				delete (*this->children)[i];
				(*this->children)[i] = nullptr;
			}
		}
		delete this->children;
		this->children = nullptr;
	}

	template<typename T, int K>
	inline TreeNode<T>* KWayTreeNode<T, K>::shallowCopy() {
		return new KWayTreeNode<T, K>(*this);
	}

	template<typename T, int K>
	inline bool KWayTreeNode<T, K>::isLeaf() {
		for (int i = 0; i < K; ++i) {
			if ((*this->children)[i] != nullptr) {
				return false;
			}
		}
		return true;
	}

	template<typename T, int K>
	inline TreeNode<T>* KWayTreeNode<T, K>::getSon(int order) const {
		return (*this->children)[order];
	}

	template<typename T, int K>
	inline void KWayTreeNode<T, K>::insertSon(TreeNode<T>* son, int order) {
		this->replaceSon(son, order);
	}

	template<typename T, int K>
	inline TreeNode<T>* KWayTreeNode<T, K>::replaceSon(TreeNode<T>* son, int order) {
		KWayTreeNode<T, K>* result = (*children)[order];
		(*children)[order] = dynamic_cast<KWayTreeNode<T, K>*>(son);

		if (son != nullptr) {
			son->setParent(this);
		}
		if (result != nullptr) {
			result->setParent(nullptr);
		}

		return result;
	}

	template<typename T, int K>
	inline TreeNode<T>* KWayTreeNode<T, K>::removeSon(int order) {
		this->replaceSon(nullptr, order);
	}

	template<typename T, int K>
	inline int KWayTreeNode<T, K>::degree() {
		return K;
	}

	template<typename T, int K>
	inline int KWayTreeNode<T, K>::numberOfSons() {
		int result = 0;

		for (int i = 0; i < K; ++i) {
			if ((*this->children)[i] != nullptr) {
				++result;
			}
		}
		return result;
	}

	template<typename T, int K>
	inline KWayTree<T, K>::KWayTree(): Tree<T>() {
	}

	template<typename T, int K>
	inline KWayTree<T, K>::KWayTree(const KWayTree<T, K>& other) : Tree<T>(other) {
	}

	template<typename T, int K>
	inline Structure * KWayTree<T, K>::clone() const {
		return new KWayTree<T, K>(*this);
	}

	template<typename T, int K>
	inline TreeNode<T>* KWayTree<T, K>::createTreeNodeInstance() {
		T data = T();
		return new KWayTreeNode<T, K>(data);
	}
}

