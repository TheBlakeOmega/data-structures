
#ifndef DEQUEUE_H_
#define DEQUEUE_H_
#include <iostream>
using namespace std;

template <typename T>
struct nodo{
	T element;
	nodo<T>* succ;
};

template <typename T>
class dequeue{
public:
	dequeue();
	~dequeue();
	bool empty() const;
	int size() const;
	T rightTop() const;
	T leftTop() const;
	void rightPush(T);
	void leftPush(T);
	void rightPop();
	void leftPop();
	void print() const;
private:
	nodo<T>* left;
	nodo<T>* right;
	int length;
};

template <typename T>
dequeue<T>::dequeue(){
	left=right=nullptr;
	length=0;
}

template <typename T>
dequeue<T>::~dequeue(){
	if(empty()){
		return;
	}
	int i;
	for (i=0;i<length;i++){
		leftPop();
	}
	delete left,right,length;
}

template <typename T>
bool dequeue<T>::empty() const{
	bool (left=right=nullptr);
}

template <typename T>
int dequeue<T>::size()const{
	return length;
}

template <typename T>
T dequeue<T>::rightTop() const{
	return right->element;
}

template <typename T>
T dequeue<T>::leftTop() const{
	return left->element;
}

template <typename T>
void dequeue<T>::rightPush(T element){
	nodo<T>* tmp= new nodo<T>;
	tmp->element=element;
	tmp->succ=nullptr;
	if(empty()){
		left=right=tmp;
	}else{
	right->succ=tmp;
	right=tmp;
	}
	length++;
}

template <typename T>
void dequeue<T>::leftPush(T element){
	nodo<T>* tmp= new nodo<T>;
	tmp->element=element;
	if(empty()){
		tmp->succ=nullptr;
		left=right=tmp;
	}else{
	tmp->succ=left;
	left=tmp;
	}
	length++;
}

template <typename T>
void dequeue<T>::rightPop(){
	nodo<T>* tmp= new nodo<T>;
	tmp=left;
	while(tmp->succ!=right){
		tmp=tmp->succ;
	}
	right=tmp;
	tmp=tmp->succ;
	delete tmp;
	length--;
}

template <typename T>
void dequeue<T>::leftPop(){
	nodo<T>* tmp= new nodo<T>;
	tmp=left;
	left=left->succ;
	delete tmp;
	length--;
}

template <typename T>
void dequeue<T>::print()const{
	int i;
	nodo<T>* tmp= new nodo<T>;
	tmp=left;
	for(i=0;i<length;i++){
		cout << leftTop() << " ";
		rightPush(leftTop());
		leftPop();
	}
	cout << endl;
}



#endif /* DEQUEUE_H_ */
