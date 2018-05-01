#pragma once
#ifndef _BINARYTREE_H
#define _BINARYTREE_H

typedef signed long int Long;
template <typename T>
class BinaryTree {
public:
	class Node {
		friend class BinaryTree;
	public:
		Node() {
			this->left = 0;
			this->right = 0;
		}
		Node(T key) {
			this->left = 0;
			this->key = key;
			this->right = 0;
		}
		Node(const Node& source) {
			this->key = source.key;
			if (source.left != 0) {
				this->left = new Node(*source.left);
			}
			else {
				this->left = 0;
			}
			if (this->right != 0) {
				this->right = new Node(*source.right);
			}
			else {
				this->right = 0;
			}
		}
		Node& operator =(const Node& source) {
			if (this->0) {
				delete this;
				this = 0;
			}
			this = New Node(*source);
			return *this;
		}
		void CopyToBuffer(T(*keys), Long *length, Long *i) {
			if (this != 0) {
				this->left.CopyToBuffer(keys, length, i);
				keys[*i] = this->key;
				(*length)++;
				(*i)++;
				this->right.CopyToBuffer(keys, length, i);
			}
		}
		void DeleteAllItems() {
			if (this != 0) {
				this->left.DeleteAllItems();
				this->right.DeleteAllItems();
				this->left = 0;
				this->right = 0;
				delete this;
			}
		}
		Node* MakeTree(T(*keys), Long min, Long max) {
			Long mid;
			Node *node = 0;
			if (min <= max) {
				mid = (min + max) / 2;
				node = new Node(keys[mid]);
				this->left = node.MakeTree(keys, min, mid - 1);
				this->right = node->MakeTree(keys, mid + 1, max);
			}
			return node;
		}
		T& GetKey() const {
			return static_cast<T&>(this->key);
		}
	private:
		Node *left;
		T key;
		Node *right;
	};
public:
	BinaryTree();
	BinaryTree(const BinaryTree& source);
	BinaryTree& operator =(const BinaryTree* source);
	~BinaryTree();

	Node* Insert(T key, int(*compare)(void*, void*));
	Node* Search(T key, int(*compare)(void*, void*));
	Node* Delete(T key, int(*compare)(void*, void*));

	void MakeBalance();
	void CopyToBuffer(T *(*keys), Long *length);
	void DeleteAllItems();

	Node* MakeTree(T(*keys), Long length);
	T& GetAt(Node *node);
	Long GetLength()const;
	Long GetBalance()const;
	Node& GetRoot()const;
private:
	Node *root;
	Long length;
	Long balance;
};
template <typename T>
inline Long BinaryTree<T>::GetLength()const {
	return this->length;
}
template <typename T>
inline Long BinaryTree<T>::GetBalance()const {
	return this->balance;
}
template <typename T>		//칠판에 template <typename T> 추가해야함
inline Node& BinaryTree<T>::GetRoot()const {
	return const_cast<Node&>(this->root);
}
template <typename T>
BinaryTree<T>::BinaryTree() {
	this->root = 0;
	this->length = 0;
	this->balance = 0;
}
template <typename T>
BinaryTree<T>::BinaryTree(const BinaryTree& source) {
	this->root = new Node(*source.root);
	this->length = source.length;
	this->balance = source.balance;
}
template <typename T>
BinaryTree<T>::BinaryTree& BinaryTree<T>::operator= (const BinaryTree& source) {
	this->root = source.root;
	this->length = source.length;
	this->balance = source.balance;
	return *this;
}
template <typename T>
BinaryTree<T>::~BinaryTree() {
	if ( this->root!= 0) {
		delete this->root;
		this->root = 0;
	}
}
template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::Insert(T key, int(*compare)(void*, void*)) {
	Node *it = this->root;
	Node *parent = 0;
	while (it != 0) {
		parent = it;
		if (compare(&it->key, key) > 0) {
			it = it->left;
		}
		else {
			it = it->right;
		}
	}
	Node *node = new Node(key);
	if (parent != 0) {
		if (compare(&parent->key, node->key) > 0) {
			parent->left = node;
		}
		else {
			parent->right = node;
		}
		if (compare(&this->root->key, node->key) > 0) {
			this->balance--;
		}
		else {
			this->balance++;
		}
	}
	else {
		this->root = node;
	}
	this->length++;
	return node;
}
#endif // !_BINARYTREE_H
