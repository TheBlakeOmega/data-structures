
#ifndef LIST_H_
#define LIST_H_
#include <iostream>
using namespace std;

template<class T>
class List;

template<class T>
class Node{
friend class List<T>;
private:
	T value;
	Node *next;
	Node *prev;
};

template<class T>
class List{
public:
	List();
	List(const List &l);
	~List();

	T read(Node<T> *p) const;
	void write(Node<T> *p, T v);
	Node<T> *next(Node<T> *p) const;
	Node<T> *prev(Node<T> *p) const;
	bool empty() const;
	Node<T> *begin() const;
	Node<T> *last() const;
	bool end(Node<T> *p) const;
	void insert(Node<T> *p, T v);
	void remove(Node<T> *p);
	Node<T> *find(T v) const;
	void pushBack(T v);
	void pushFront(T v);
	void popBack();
	void popFront();
	int size() const;
	void reverse();
	void print() const;

private:
	Node<T> *head;
	Node<T> *tail;
};


template<typename T>
List<T>::List(){
	head = tail = nullptr;
}

template<typename T>
List<T>::List(const List<T> &l){
	head = tail = nullptr;
	Node<T> *tmp = l.begin();
	while(!l.end(tmp)){
		pushBack(tmp->value);
		tmp = tmp->next;
	}
}

template<typename T>
List<T>::~List(){
	Node<T> *tmp;
	while(head != nullptr){
		tmp = head;
		head = head->next;
		delete tmp;
	}
}

template<typename T>
T List<T>::read(Node<T> *pos) const{
	return pos->value;
}

template<typename T>
void List<T>::write(Node<T> *pos, T element){
	pos->value = element;
}

template<typename T>
Node<T> *List<T>::next(Node<T> *pos) const{
	return pos->next;
}

template<typename T>
Node<T> *List<T>::prev(Node<T> *pos) const{
	return pos->prev;
}

template<typename T>
bool List<T>::empty() const{
	return head == nullptr;
}

template<typename T>
Node<T> *List<T>::begin() const{
	return head;
}

template<typename T>
Node<T> *List<T>::last() const{
	return tail;
}

template<typename T>
bool List<T>::end(Node<T> *pos) const{
	return pos == nullptr;
}

template<typename T>
void List<T>::insert(Node<T> *pos, T element){
	Node<T> *node = new Node<T>;
	node->value = element;
	node->next = pos->next;
	node->prev = pos;
	if(pos->next == nullptr)
		tail = node;
	else
		pos->next->prev = node;
	pos->next = node;
}

template<typename T>
void List<T>::remove(Node<T> *pos){
	Node<T> *tmp = pos;
	if(pos->prev == nullptr){
		head = pos->next;
	}
	else{
		pos->prev->next = pos->next;
	}
	if(pos->next == nullptr)	{
		tail = pos->prev;
	}
	else{
		pos->next->prev = pos->prev;
	}

	delete tmp;
}

template<typename T>
Node<T> *List<T>::find(T element) const{
	Node<T> *tmp = begin();
	while(!end(tmp)){
		if(tmp->value == element)
			return tmp;
		tmp = tmp->next;
	}
	return nullptr;
}

template<typename T>
void List<T>::pushBack(T element){
	Node<T> *node = new Node<T>;
	node->value = element;
	node->next = nullptr;
	if(empty())	{
		head = node;
		node->prev = nullptr;
	}
	else{
		tail->next = node;
		node->prev = tail;
	}
	tail = node;
}

template<typename T>
void List<T>::pushFront(T element){
	Node<T> *node = new Node<T>;
	node->value = element;
	node->prev = nullptr;
	if(empty()){
		tail = node;
		node->next = nullptr;
	}
	else{
		head->prev = node;
		node->next = head;
	}
	head = node;
}

template<typename T>
void List<T>::popBack(){
	if(empty())
		return;
	if(head == tail)
	{
		delete head;
		head = nullptr;
	}
	else{
		Node<T> *tmp = tail;
		tail->prev->next = nullptr;
		tail = tail->prev;
		delete tmp;
	}
}

template<typename T>
void List<T>::popFront(){
	if(empty()){
		return;
	}
	Node<T>* tmp;
	tmp=head;
	head=head->next;
	delete tmp;
}

template<typename T>
int List<T>::size()const{
	int i=0;
	if(empty())
		return i;
	Node<T>* tmp;
	tmp=head;
	while(!end(tmp)){
		i++;
		tmp=tmp->next;
	}
	return i;
}

template<typename T>
void List<T>::reverse(){
	Node<T> tmp;
	Node<T> hold;
	tmp=tail;
	tail=head;
	head=tmp;
	while(!end(tmp)){
	hold=tmp->next;
	tmp->next=tmp->prev;
	tmp->prev=hold;
	tmp=tmp->next;
	}
}

template <typename T>
void List<T>::print() const{
	Node<T>* tmp=begin();
	while(!end(tmp)){
		cout << "[" << read(tmp) << "] ";
		tmp=next(tmp);
	}
	cout << endl;
}

#endif /* LISTE_H_ */
