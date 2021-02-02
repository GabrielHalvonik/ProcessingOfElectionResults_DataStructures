#pragma once

#include "Structure.h"
#include "StructureIterator.h"
#include "Queue/ExplicitQueue.h"

namespace Structures {

	template <typename T>
	class TreeNode : public DataItem<T> {
	public:
		virtual TreeNode<T>* shallowCopy() = 0;
		virtual TreeNode<T>* deepCopy();

		bool isRoot();
		virtual bool isLeaf() = 0;
  
		TreeNode<T>* getParent() const;
		void resetParent();
		void setParent(TreeNode<T>* parent);
		virtual TreeNode<T>* getBrother(int brothersOrder);
		virtual TreeNode<T>* getSon(int order) const = 0;
		virtual void insertSon(TreeNode<T>* son, int order) = 0;
		virtual TreeNode<T>* replaceSon(TreeNode<T>* son, int order) = 0;
		virtual TreeNode<T>* removeSon(int order) = 0;
    
		virtual int degree() = 0;   
		virtual size_t sizeOfSubtree();
	protected:
		TreeNode(T data);
		TreeNode(const TreeNode<T>& other);
    
		TreeNode<T>* parent;
	};

	template <typename T> 
	class Tree : public Structure, public Iterable<T> {
	public:
		~Tree();
  
		virtual Structure* clone() const = 0;

		bool isEmpty() const override; 
		virtual size_t size() const;

		Structure& operator=(const Structure& other) override;
		virtual Tree<T>& operator=(const Tree<T>& other);
		
		virtual void clear();
		TreeNode<T>* getRoot();
		virtual TreeNode<T>* replaceRoot(TreeNode<T>* newRoot);
		virtual TreeNode<T>* createTreeNodeInstance() = 0;

		Iterator<T>* getBeginIterator() const override;
		Iterator<T>* getEndIterator() const override;
	protected:
		Tree();
		Tree(const Tree<T>& other);
    
		TreeNode<T>* root;

	protected:

		class TreeIterator : public Iterator<T> {
		public:
			TreeIterator();
			~TreeIterator();

			Iterator<T>& operator=(const Iterator<T>& other) override;
			bool operator!=(const Iterator<T>& other) override;
			const T operator*() override;
			Iterator<T>& operator++() override;

		protected:
			ExplicitQueue<TreeNode<T>*>* path;
		};

	public:
		class PreOrderTreeIterator : public TreeIterator {
		public:
			PreOrderTreeIterator(TreeNode<T>* const startNode);
		private:
			void populatePath(TreeNode<T>* const current);
		};

		class PostOrderTreeIterator: public TreeIterator {
		public:
			PostOrderTreeIterator(TreeNode<T>* const startNode);
		private:
			void populatePath(TreeNode<T>* const current);
		};

		class LevelOrderTreeIterator : public TreeIterator {
		public:
			LevelOrderTreeIterator(TreeNode<T>* const startNode);
		private:
			void populatePath(TreeNode<T>* const current);
		};
	};

	template<typename T>
	inline TreeNode<T>* TreeNode<T>::deepCopy() {
		TreeNode<T>* copy = this->shallowCopy();
		for (int i = 0; i < this->degree(); ++i) {
			TreeNode<T>* son = copy->getSon(i);

			if (son != nullptr) {
				copy->replaceSon(son->deepCopy(), i);
			}
		}
		return copy;
	}

	template<typename T>
	inline bool TreeNode<T>::isRoot() {
		return this->parent == nullptr;
	}

	template<typename T>
	inline TreeNode<T>* TreeNode<T>::getParent() const {
		return parent;
	}

	template<typename T>
	inline void TreeNode<T>::resetParent() {
		parent = nullptr;
	}

	template<typename T>
	inline void TreeNode<T>::setParent(TreeNode<T>* parent) {
		this->parent = parent;
	}

	template<typename T>
	inline TreeNode<T>* TreeNode<T>::getBrother(int brothersOrder) {
		if (this->isRoot()) {
			throw std::logic_error("TreeNode<T>::getBrother...Node is root...");
		}
		return this->parent->getSon(brothersOrder);
	}

	template<typename T>
	inline size_t TreeNode<T>::sizeOfSubtree() {
		size_t size = 1;

		for (int i = 0; i < this->degree(); ++i) {
			TreeNode<T>* son = this->getSon(i);
			if (son != nullptr) {
				size += this->sizeOfSubtree();
			}
		}
		return size;
	}

	template<typename T>
	inline TreeNode<T>::TreeNode(T data): DataItem<T>(data), parent(nullptr) {
	}

	template<typename T>
	inline TreeNode<T>::TreeNode(const TreeNode<T>& other): DataItem<T>(other), parent(other.parent) {
	}
  
	template<typename T>
	inline Tree<T>::~Tree() {
		this->clear();
	}

	template<typename T>
	inline bool Tree<T>::isEmpty() const {
		return this->root == nullptr;
	}

	template<typename T>
	inline size_t Tree<T>::size() const {
		return this->root != nullptr ? this->root->sizeOfSubtree() : 0;
	}

	template<typename T>
	inline Iterator<T>* Tree<T>::getBeginIterator() const {
		return new PreOrderTreeIterator(root);
	}

	template<typename T>
	inline Iterator<T>* Tree<T>::getEndIterator() const {
		return new PreOrderTreeIterator(nullptr);
	}

	template<typename T>
	inline Tree<T>::Tree(): Structure(), Iterable<T>(),	root(nullptr)     {
	}

	template<typename T>
	inline Tree<T>::Tree(const Tree<T>& other): Tree<T>() {
		*this = other;
	}

	template<typename T>
	inline Structure & Tree<T>::operator=(const Structure & other) {
		if (this != &other) {
			*this = dynamic_cast<const Tree<T>&>(other);
		}
		return *this;
	}
  
	template<typename T>
	inline Tree<T>& Tree<T>::operator=(const Tree<T>& other) {
		if (this != &other) {
			this->clear();
			if (other.root != nullptr) {
				this->root = other.root->deepCopy();
			}
		}
		return *this;
	}

	template<typename T>
	inline void Tree<T>::clear() {
		if (this->root != nullptr) {
			delete this->root;
			this->root = nullptr;
		}
	}
  
	template<typename T>
	inline TreeNode<T>* Tree<T>::getRoot() {
		return this->root;
	}
  
	template<typename T>             
	inline TreeNode<T>* Tree<T>::replaceRoot(TreeNode<T>* newRoot) {
		TreeNode<T> *oldRoot = this->root;
		this->root = newRoot;
		return oldRoot;
	}

	template<typename T>
	inline Tree<T>::TreeIterator::TreeIterator(): Iterator<T>(), path(new ExplicitQueue<TreeNode<T>*>()) {

	}

	template<typename T>
	inline Tree<T>::TreeIterator::~TreeIterator() {
		delete this->path;
		this->path = nullptr;
	}

	template<typename T>
	inline Iterator<T>& Tree<T>::TreeIterator::operator=(const Iterator<T>& other) {
		*this->path = *(dynamic_cast<const TreeIterator&>(other)).path;
		return *this;
	}

	template<typename T>
	inline bool Tree<T>::TreeIterator::operator!=(const Iterator<T>& other) {
		const TreeIterator& iterator = dynamic_cast<const TreeIterator&>(other);
		return this->path->size() != iterator.path->size() || (this->path->size() != 0 && this->path->peek() != iterator.path->peek());
	}

	template<typename T>
	inline const T Tree<T>::TreeIterator::operator*() {
		return this->path->peek()->accessData();
	}

	template<typename T>
	inline Iterator<T>& Tree<T>::TreeIterator::operator++() {
		this->path->pop();
		return *this;
	}

	template<typename T>
	inline Tree<T>::PreOrderTreeIterator::PreOrderTreeIterator(TreeNode<T>* const startNode): TreeIterator() {
		this->populatePath(startNode);
	}

	template<typename T>
	inline void Tree<T>::PreOrderTreeIterator::populatePath(TreeNode<T>* const current) {
		if (current != nullptr) {
			this->path->push(current);
			for (int i = 0; i < current->degree(); ++i) {
				this->populatePath(current->getSon(i));
			}
		}
	}

	template<typename T>
	inline Tree<T>::PostOrderTreeIterator::PostOrderTreeIterator(TreeNode<T>* const startNode) : TreeIterator() {
		this->populatePath(startNode);
	}

	template<typename T>
	inline void Tree<T>::PostOrderTreeIterator::populatePath(TreeNode<T>* const current) {
		if (current != nullptr) {
			for (int i = 0; i < current->degree(); ++i) {
				this->populatePath(current->getSon(i));
			}
			this->path->push(current);
		}
	}

	template<typename T>
	inline Tree<T>::LevelOrderTreeIterator::LevelOrderTreeIterator(TreeNode<T>* const startNode) : TreeIterator() {
		this->populatePath(startNode);
	}

	template<typename T>
	inline void Tree<T>::LevelOrderTreeIterator::populatePath(TreeNode<T>* const current) {
		Queue<TreeNode<T>*>* queue = new ExplicitQueue<TreeNode<T>*>();
		queue->push(current);

		while (!queue->isEmpty()) {
			TreeNode<T>* actual = queue->pop();
			if (actual != nullptr) {
				this->path->push(actual);
				for (int i = 0; i < actual->degree(); ++i) {
					queue->push(actual->getSon(i));
				}
			}
		}
		delete queue;
		queue = nullptr;

	}

}

