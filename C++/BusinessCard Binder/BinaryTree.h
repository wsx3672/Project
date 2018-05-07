//BinaryTree.h

#ifndef _BINARYTREE_H
#define _BINARYTREE_H

typedef signed long int Long;
template <typename T>

class BinaryTree {
public:
	//nested Class
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
			if (this != 0) {
				delete this;
				this = 0;
			}
			new Node(source.key);
			if (this->left != 0) {
				*this->left = source.left;
			}
			if (this->right != 0) {
				*this->right = source.right;
			}
			return *this;
		}
		void CopyToBuffer(T(*keys), Long *length, Long *i) {
			if (this != 0) {
				this->left->CopyToBuffer(keys, length, i);
				keys[*i] = this->key;
				(*length)++;
				(*i)++;
				this->right->CopyToBuffer(keys, length, i);
			}
		}
		void DeleteAllItems() {
			if (this != 0) {
				this->left->DeleteAllItems();
				this->right->DeleteAllItems();
				this->left = 0;
				this->right = 0;
				delete this;
			}
		}
		static Node* MakeTree(T(*keys), Long min, Long max) {
			Long mid;
			Node *node = 0;
			if (min <= max) {
				mid = (min + max) / 2;
				node = new Node(keys[mid]);
				node->left = node->MakeTree(keys, min, mid - 1);
				node->right = node->MakeTree(keys, mid + 1, max);
			}
			return node;
		}
		T& GetKey() const {
			return const_cast<T&>(this->key);
		}
		Node* GetLeft()const {
			return this->left;
		}
		Node* GetRight()const {
			return this->right;
		}
	private:
		Node *left;
		T key;
		Node *right;
	};//Nested Class

public:
	BinaryTree();
	BinaryTree(const BinaryTree& source);
	BinaryTree& operator=(const BinaryTree& source);
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
	Node* GetRoot()const;

private:
	Node *root;
	Long length;
	Long balance;
};

template <typename T>
inline Long BinaryTree<T>::GetLength() const {
	return this->length;
}

template <typename T>
inline Long BinaryTree<T>::GetBalance() const {
	return this->balance;
}

template <typename T>      //칠판에 template <typename T> 추가해야함
inline typename BinaryTree<T>::Node* BinaryTree<T>::GetRoot()const {
	return const_cast<Node*>(this->root);
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
BinaryTree<T>& BinaryTree<T>::operator=(const BinaryTree& source) {
	if (this->root != 0) {
		delete this->root;
		this->root = 0;
	}
	this->root = new Node(*source.root);
	this->length = source.length;
	this->balance = source.balance;
	return *this;
}

template <typename T>
BinaryTree<T>::~BinaryTree() {
	if (this->root != 0) {
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
		if (compare(&it->key, &key) > 0) {
			it = it->left;
		}
		else {
			it = it->right;
		}
	}
	Node *node = new Node(key);
	if (parent != 0) {
		if (compare(&parent->key, &node->key) > 0) {
			parent->left = node;
		}
		else {
			parent->right = node;
		}
		if (compare(&this->root->key, &node->key) > 0) {
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

template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::Search(T key, int(*compare)(void*, void*)) {
	Node *index = this->root;
	while (index != 0 && compare(&index->key, &key) != 0) {
		if (compare(&index->key, &key) < 0) {
			index = index->right;
		}
		else {
			index = index->left;
		}
	}
	return index;
}

template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::Delete(T key, int(*compare)(void*, void*)) {
	Node *index;
	Node *parent = 0;
	Node *otherIndex = 0;
	Node *parentIndex = 0;

	index = this->root;
	while (compare(&index->key, &key) != 0) {
		parent = index;
		if (compare(&index->key, &key) > 0) {
			index = index->left;
		}
		else {
			index = index->right;
		}
	}
	if (index->right != 0) {
		otherIndex = index->right;
		while (otherIndex->left != 0) {
			parentIndex = otherIndex;
			otherIndex = otherIndex->left;
		}
		if (parentIndex != 0) {
			parentIndex->left = otherIndex->right;
			otherIndex->left = index->left;
			otherIndex->right = index->right;
		}
		else {
			otherIndex->left = index->left;
		}
	}
	else if (index->left != 0) {
		otherIndex = index->left;
		while (otherIndex -> right != 0) {
			parentIndex = otherIndex;
			otherIndex = otherIndex->right;
		}
		if (parentIndex != 0) {
			parentIndex->right = otherIndex->left;
			otherIndex->left = index->left;
			otherIndex->right = index->right;
		}
		else {
			otherIndex->right = index->right;
		}
	}
	if (compare(&this->root->key, &key) != 0) {
		if (compare(&this->root->key, &key) < 0) {
			this->balance--;
		}
		else {
			this->balance++;
		}
	}
	else {
		this->root = otherIndex;
		if (index->right != 0) {
			this->balance--;
		}
		else if (index->left != 0) {
			this->balance++;
		}
	}
	if (parent != 0) {
		if (compare(&parent->key, &key) > 0) {
			parent->left = otherIndex;
		}
		else {
			parent->right = otherIndex;
		}
	}
	if (index != 0) {
		index->left = 0;
		index->right = 0;
		delete index;
		index = 0;
	}
	return index;
}

template <typename T>
void BinaryTree<T>::MakeBalance() {
	T(*keys);
	Long length;
	this->CopyToBuffer(&keys, &length);
	this->DeleteAllItems();
	this->MakeTree(keys, length);
	if (keys != 0) {
		delete[] keys;
		keys = 0;
	}
}

template <typename T>
void BinaryTree<T>::CopyToBuffer(T*(*keys), Long *length) {
	Long i = 0;
	*length = 0;
	*keys = new T[this->length];
	this->root->CopyToBuffer(*keys, length, &i);
}

template <typename T>
void BinaryTree<T>::DeleteAllItems() {
	this->root->DeleteAllItems();
	this->root = 0;
	this->length = 0;
	this->balance = 0;
}

template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::MakeTree(T(*keys), Long length) {
	BinaryTree<T>::Node *node = 0;
	Long min = 0;
	Long max;
	Long remainder;

	max = length - 1;
	this->root = node->MakeTree(keys, min, max);
	this->length = length;
	remainder = length % 2;

	if (remainder == 0) {
		this->balance = 1;
	}
	else {
		this->balance = 0;
	}
	return node;
}

template <typename T>
T& BinaryTree<T>::GetAt(Node *index) {
	return index->key;
}

#endif // _BINARYTREE_H





