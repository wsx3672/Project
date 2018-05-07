//LinkedList.h
#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H

typedef signed long int Long; // 필요해서 씀
template <typename T> // template 자료형을 T 라고 씀

class LinkedList { // LinkedList 클래스 선언 시작
public: 
	//nested Class
	class Node { // LinkedList 클래스 안에 Node Class를 nested Class 로 선언 시작
		friend class LinkedList; // LinkedList를 friend class 로 지정함, 오픈
	public:
		Node() {
			this->previous = this;
			this->next = this;
		}
		Node(T object) {
			this->previous = this;
			this->object = object;
			this->next = this;
		}
		Node(Node *previous, T object) {
			this->previous = previous;
			this->object = object;
			this->next = this;
		}
		Node(T object, Node *next) {
			this->previous = this;
			this->object = object;
			this->next = next;
		}
		Node(Node *previous, T object, Node *next) {
			this->previous = previous;
			this->object = object;
			this->next = next;
		}
		Node(const Node& source) {
			this->previous = source.previous;
			this->object = source.object;
			this->next = source.next;
		}
		Node &operator = (const Node& source) {
			this->previous = source.previous;
			this->object = source.object;
			this->next = source.next;
			return *this;
		}
		T& GetObject() const {
			return const_cast<T&>(this->object);
		}
	private:
		Node *previous;
		T object;
		Node *next;
	};  //Nested Class

public:
	LinkedList();
	LinkedList(const LinkedList& source); //복사생성자
	LinkedList<T>& LinkedList<T>::operator = (const LinkedList& source); //치환연산자
	~LinkedList();

	Node* InsertBefore(Node* index, T object);
	Node* InsertAfter(Node* index, T object);
	Node* AppendFromHead(T object);
	Node* AppendFromTail(T object);
	Node* Delete(Node* index);
	Node* DeleteFromHead();
	Node* DeleteFromTail();
	void DeleteAllItems();
	Node* LinearSearchUnique(void *key, int(*compare)(void *, void *));
	void LinearSearchDuplicate(void *key, Node**(*indexes), Long *count, int(*compare)(void*, void*));
	Node* First();
	Node* Previous();
	Node* Next();
	Node* Last();

	T& GetAt(Long index);
	Node* Move(Node *index);
	T& operator[](Long index); //첨자 연산자
	Long GetLength() const;
	Node* GetCurrent() const;

private:
	Node* head;
	Node* tail;
	Long length;
	Node* current;
};
template<typename T>
inline Long LinkedList<T>::GetLength() const {
	return this->length;
}
template<typename T>
inline typename LinkedList<T>::Node* LinkedList<T>::GetCurrent() const {
	return const_cast<Node*>(this->current);
}

template<typename T>
LinkedList<T>::LinkedList() {
	this->head = 0;
	this->tail = 0;
	this->length = 0;
	this->current = 0;
}


template<typename T>
LinkedList<T>::LinkedList(const LinkedList& source) { //복사생성자
	Node *sourcePrevious = source.head;
	Node *sourceIt = sourcePrevious->next;
	Node *newCurrent;
	Node *newPrevious;

	newCurrent = new Node(sourcePrevious->object);
	this->current = newCurrent;
	this->head = this->current;
	this->tail = this->current;
	newPrevious = this->head;

	while (sourcePrevious != source.current && sourceIt != sourcePrevious) {
		newCurrent = new Node(newPrevious, sourceIt->object);
		newPrevious->next = newCurrent;
		newPrevious = newPrevious->next;
		this->current = newCurrent;

		sourcePrevious = sourceIt;
		sourceIt = sourceIt->next;
	}

	while (sourceIt != sourcePrevious) {
		newCurrent = new Node(newPrevious, sourceIt->object);
		newPrevious->next = newCurrent;
		newPrevious = newPrevious->next;

		sourcePrevious = sourceIt;
		sourceIt = sourceIt->next;
	}

	this->tail = newCurrent;
	this->length = source.length;
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator = (const LinkedList& source) { //치환연산자
	
	delete[] this->head;

	Node *sourcePrevious = source.head;
	Node *sourceIt = sourcePrevious->next;
	Node *newCurrent;
	Node *newPrevious;

	newCurrent = new Node(sourcePrevious->object);
	this->current = newCurrent;
	this->head = this->current;
	this->tail = this->current;
	newPrevious = this->head;

	while (sourcePrevious != source.current && sourceIt != sourcePrevious) {
		newCurrent = new Node(newPrevious, sourceIt->object);
		newPrevious->next = newCurrent;
		newPrevious = newPrevious->next;
		this->current = newCurrent;

		sourcePrevious = sourceIt;
		sourceIt = sourceIt->next;
	}

	while (sourceIt != sourcePrevious) {
		newCurrent = new Node(newPrevious, sourceIt->object);
		newPrevious->next = newCurrent;
		newPrevious = newPrevious->next;

		sourcePrevious = sourceIt;
		sourceIt = sourceIt->next;
	}

	this->tail = newCurrent;
	this->length = source.length;

	return *this;
}
// */

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::InsertBefore(Node* index, T object) {
	if (this->head != index) {
		this->current = new Node(index->previous, object, index);
	}
	else {
		this->current = new Node(object, index);
	}

	if (this->head != index) {
		index->previous->next = this->current;
	}
	else {
		this->head = this->current;
	}
	index->previous = this->current;
	this->length++;

	return this->current;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::InsertAfter(Node* index, T object) {
	if (this->tail != index) {
		this->current = new Node(index, object, index->next);
	}
	else {
		this->current = new Node(index, object);
	}
	if (this->tail != index) {
		index->next->previous = this->current;
	}
	else {
		this->tail = this->current;
	}
	index->next = this->current;
	this->length++;
	return this->current;
}


template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::AppendFromHead(T object) {
	if (this->head != 0) {
		this->current = new Node(object, this->head);
	}
	else {
		this->current = new Node(object);
	}
	if (this->head != 0) {
		this->head->previous = this->current;
	}
	else {
		this->tail = this->current;
	}
	this->head = this->current;
	this->length++;
	return this->current;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::AppendFromTail(T object) {
	if (this->tail != 0) {
		this->current = new Node(this->tail, object);
	}
	else {
		this->current = new Node(object);
	}
	if (this->tail != 0) {
		this->tail->next = this->current;
	}
	else {
		this->head = this->current;
	}
	this->tail = this->current;
	this->length++;
	return this->current;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::Delete(Node* index) {
	if (this->current == index) {
		if (this->tail != index) {
			this->current = index->next;
		}
		else {
			this->current = index->previous;
		}
	}
	if (this->head != index && this->tail != index) {
		index->previous->next = index->next;
		index->next->previous = index->previous;
	}
	else if (this->head == this->tail) {
		this->head = 0;
		this->current = 0;
		this->tail = 0;
	}
	else if (this->tail == index) {
		index->previous->next = index->previous;
		this->tail = index->previous;
	}
	else {
		index->next->previous = index->next;
		this->head = index->next;
	}
	if (index != 0) {
		delete index;
		index = 0;
	}
	this->length--;
	return index;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::DeleteFromHead() {
	Node* index = this->head;
	if (this->head != this->tail) {
		this->current = this->head->next;
		this->current->previous = this->current;
		this->head = this->current;
	}
	else {
		this->head = 0;
		this->tail = 0;
		this->current = 0;
	}
	if (index != 0) {
		delete index;
		index = 0;
	}
	this->length--;
	return index;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::DeleteFromTail() {
	Node* index = this->tail;
	if (this->tail != this->head) {
		this->current = this->tail->previous;
		this->current->next = this->current;
		this->tail = this->current;
	}
	else {
		this->tail = 0;
		this->head = 0;
		this->current = 0;
	}
	if (index != 0) {
		delete index;
		index = 0;
	}

	this->length--;
	return index;
}


template<typename T>
void LinkedList<T>::DeleteAllItems() {
	Node* previous = 0;
	Node* it = this->head;

	while (it != previous) {
		previous = it;
		this->head = this->head->next;
		if (it != 0) {
			delete it;
			it = 0;
		}
		this->length--;
		it = this->head;
	}
	this->head = 0;
	this->tail = 0;
	this->current = 0;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::LinearSearchUnique(void *key, int(*compare)(void*, void*)) {
	Node* it;
	Node* index = 0;
	Node* previous = 0;
	it = this->head;
	while (it != previous && compare(&it->object, key) != 0) {
		previous = it;
		it = it->next;
	}
	if (it != previous) {
		index = it;
	}
	return index;
}

template<typename T>
void LinkedList<T>::LinearSearchDuplicate(void *key, Node* *(*indexes), Long *count, int(*compare)(void*, void*)) {
	Node *it;
	Node* previous = 0;
	Long i = 0;
	*count = 0;
	*indexes = new Node*[this->length];
	it = this->head;
	while (it != previous) {
		if (compare(&it->object, key) == 0) {
			(*indexes)[i] = it;
			i++;
			(*count)++;
		}
		previous = it;
		it = it->next;
	}
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::First() {
	this->current = this->head;
	return this->current;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::Previous() {
	this->current = this->current->previous;
	return this->current;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::Last() {
	this->current = this->tail;
	return this->current;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::Next() {
	this->current = this->current->next;
	return this->current;
}

template<typename T>
LinkedList<T>::~LinkedList() {
	Node* previous = 0;
	Node* current = this->head;
	while (current != previous) {
		this->head = current->next;
		previous = current;
		if (current != 0) {
			delete current;
		}
	}
	this->length--;
	current = this->head;
}

template<typename T>
T& LinkedList<T>::GetAt(Long index) {
	Long i = 0;
	this->current = this->head;
	while (i < index) {
		this->current = this->current->next;
		i++;
	}
	return this->current->object;
}

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::Move(Node *index) {
	this->current = index;
	return this->current;
}

template<typename T>
T& LinkedList<T>::operator[](Long index) {
	Long i = 0;
	Node *current=this->head;
	//this->current = this->head;
	while (i < index) {
		current = current->next;
		i++;
	}
	return current->object;
}

#endif // _LINKEDLIST_H