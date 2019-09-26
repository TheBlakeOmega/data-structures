#ifndef SET_H_
#define SET_H_

#include <iostream>
#include "list.h"
using namespace std;

template <typename T>
class set{
public:
	set();
	~set();
	bool empty() const;
	bool belong(T) const;
	int getSize() const;
	void insert(T);
	void remove(T);
	void blending(const set<T>&);  //se avessi scritto union mi prendeva la parola chiave, ho dovuto quindi trovare un sinonimo
	void intersection(const set<T>&);
	void difference(const set<T>&);
	void print() const;

private:
	List<T> elements;
	int size;
	List<T> getElements() const;
};

template <typename T>
set<T>::set(){
	size=0;
}

template <typename T>
set<T>::~set(){
	elements.~List();
}

template <typename T>
bool set<T>::empty() const{
	return size==0;
}

template <typename T>
bool set<T>::belong(T element) const{
	Node<T>* tmp=elements.find(element);
	return (tmp!=nullptr);
}

template <typename T>
void set<T>::insert(T element){
	if(!belong(element)){
		elements.pushFront(element);
	}
	size++;
}

template <typename T>
void set<T>::remove(T element){
	Node<T>* tmp=elements.find(element);
	if (tmp!=nullptr){
		elements.remove(tmp);
	}
	size--;
}

template <typename T>
List<T> set<T>::getElements() const{
	return elements;
}

template <typename T>
void set<T>::blending(const set<T>& setB){
	List<T> B=setB.getElements();
	Node<T>* tmp=B.begin();
	while(!B.end(tmp)){
		insert(B.read(tmp));
		tmp=B.next(tmp);
	}
}

template <typename T>
void set<T>::intersection(const set<T>& setB){
	Node<T>* tmp=elements.begin();
	while(!elements.end(tmp)){
		if(!setB.belong(elements.read(tmp))){
			remove(elements.read(tmp));
		}
		tmp=elements.next(tmp);
	}
}

template <typename T>
void set<T>::difference(const set<T>& setB){
	Node<T>* tmp=elements.begin();
	while(!elements.end(tmp)){
		if(setB.belong(elements.read(tmp))){
			remove(elements.read(tmp));
		}
		tmp=elements.next(tmp);
	}
}

template <typename T>
int set<T>::getSize() const{
	return size;
}

template <typename T>
void set<T>::print() const{
	elements.print();
}











#endif /* SET_H_ */
