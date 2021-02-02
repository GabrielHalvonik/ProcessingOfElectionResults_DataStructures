#pragma once

#include "KWayTree.h"
#include "Tree.h"

namespace Structures {

	template <typename T>
	class BinaryTreeNode : public KWayTreeNode<T, 2> {
	public:
		BinaryTreeNode(T data);
		BinaryTreeNode(const BinaryTreeNode<T>& other);

		TreeNode<T>* shallowCopy() override;
		BinaryTreeNode<T>* getLeftSon() const;
		BinaryTreeNode<T>* getRightSon() const;
		BinaryTreeNode<T>* getParent() const;

		void setLeftSon(BinaryTreeNode<T>* leftSon);
		void setRightSon(BinaryTreeNode<T>* rightSon);

		BinaryTreeNode<T>* changeLeftSon(BinaryTreeNode<T>* leftSon);
		BinaryTreeNode<T>* changeRightSon(BinaryTreeNode<T>* rightSon);

		bool isLeftSon() const;
		bool isRightSon() const;
		bool hasLeftSon() const;
		bool hasRightSon() const;

	private:
		static const int LEFT_SON = 0;
		static const int RIGHT_SON = 1;
	};

	template <typename T>
	class BinaryTree : public KWayTree<T,2> {
	public:
		BinaryTree();
		BinaryTree(const BinaryTree<T>& other);

		Structure* clone() const override;
		TreeNode<T>* createTreeNodeInstance() override;

		Iterator<T>* getBeginIterator() const override;
		Iterator<T>* getEndIterator() const override;
	public:
		class InOrderTreeIterator : public Tree<T>::TreeIterator {
		public:
			InOrderTreeIterator(TreeNode<T>* const startNode);
		private:
			void populatePath(TreeNode<T>* const current);
		};
	};

	template<typename T>
	inline BinaryTreeNode<T>::BinaryTreeNode(T data): KWayTreeNode<T, 2>(data) {
	}

	template<typename T>
	inline BinaryTreeNode<T>::BinaryTreeNode(const BinaryTreeNode<T>& other): KWayTreeNode<T, 2>(other) {
	}

	template<typename T>
	inline TreeNode<T>* BinaryTreeNode<T>::shallowCopy() {
		return KWayTreeNode<T, 2>::shallowCopy();
	}

	template<typename T>
	inline BinaryTreeNode<T>* BinaryTreeNode<T>::getParent() const {
		return dynamic_cast<BinaryTreeNode<T>*>(TreeNode<T>::getParent());
	}

	template<typename T>
	inline BinaryTreeNode<T>* BinaryTreeNode<T>::getLeftSon() const {
		return dynamic_cast<BinaryTreeNode<T>*>(KWayTreeNode<T,2>::getSon(BinaryTreeNode::LEFT_SON));
	}

	template<typename T>
	inline BinaryTreeNode<T>* BinaryTreeNode<T>::getRightSon() const {
		return dynamic_cast<BinaryTreeNode<T>*>(KWayTreeNode<T,2>::getSon(BinaryTreeNode::RIGHT_SON));
	}

	template<typename T>
	inline void BinaryTreeNode<T>::setLeftSon(BinaryTreeNode<T>* leftSon) {
		this->changeLeftSon(leftSon);
	}

	template<typename T>
	inline void BinaryTreeNode<T>::setRightSon(BinaryTreeNode<T>* rightSon) {
		this->changeLeftSon(rightSon);
	}

	template<typename T>
	inline BinaryTreeNode<T>* BinaryTreeNode<T>::changeLeftSon(BinaryTreeNode<T>* leftSon) {
		return dynamic_cast<BinaryTreeNode<T>*>(KWayTreeNode<T, 2>::replaceSon(leftSon, BinaryTreeNode::LEFT_SON));
	}

	template<typename T>
	inline BinaryTreeNode<T>* BinaryTreeNode<T>::changeRightSon(BinaryTreeNode<T>* rightSon) {
		return dynamic_cast<BinaryTreeNode<T>*>(KWayTreeNode<T, 2>::replaceSon(rightSon, BinaryTreeNode::RIGHT_SON));
	}

	template<typename T>
	inline bool BinaryTreeNode<T>::isLeftSon() const {
		BinaryTreeNode<T>* parent = this->getParent();
		return (parent != nullptr) ? parent->getLeftSon() == this : false;
	}

	template<typename T>
	inline bool BinaryTreeNode<T>::isRightSon() const {
		BinaryTreeNode<T>* parent = this->getParent();
		return (parent != nullptr) ? parent->getRightSon() == this : false;
	}

	template<typename T>
	inline bool BinaryTreeNode<T>::hasLeftSon() const {
		return KWayTreeNode<T, 2>::getSon(BinaryTreeNode<T>::LEFT_SON) != nullptr;
	}

	template<typename T>
	inline bool BinaryTreeNode<T>::hasRightSon() const {
		return KWayTreeNode<T, 2>::getSon(BinaryTreeNode<T>::RIGHT_SON) != nullptr;
	}

	template<typename T>
	inline BinaryTree<T>::BinaryTree(): KWayTree<T, 2>() {
	}

	template<typename T>
	inline BinaryTree<T>::BinaryTree(const BinaryTree<T>& other): KWayTree<T, 2>(other) {
	}

	template<typename T>
	inline Structure * BinaryTree<T>::clone() const {
		return new BinaryTree<T>(*this);
	}

	template<typename T>
	inline TreeNode<T>* BinaryTree<T>::createTreeNodeInstance() {
		T data = T();
		return new BinaryTreeNode<T>(data);
	}

	template<typename T>
	inline Iterator<T>* BinaryTree<T>::getBeginIterator() const {
		return new InOrderTreeIterator(this->root);
	}

	template<typename T>
	inline Iterator<T>* BinaryTree<T>::getEndIterator() const {
		return new InOrderTreeIterator(nullptr);
	}

	template<typename T>
	inline BinaryTree<T>::InOrderTreeIterator::InOrderTreeIterator(TreeNode<T>* const startNode) : Tree<T>::TreeIterator() {
		this->populatePath(startNode);
	}

	template<typename T>
	inline void BinaryTree<T>::InOrderTreeIterator::populatePath(TreeNode<T>* const current) {
		if (current != nullptr) {

			BinaryTreeNode<T>* node = dynamic_cast<BinaryTreeNode<T>*>(current);

			this->populatePath(node->getLeftSon());
			this->path->push(node);
			this->populatePath(node->getRightSon());
		}
	}

}

