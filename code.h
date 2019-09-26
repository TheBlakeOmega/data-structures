/*
 *code.h
 *Author: Vincenzo Belvedere
 */

#ifndef CODE_H_
#define CODE_H_
#include <iostream>
using namespace std;

template <typename T>
struct nodo{
	T element;
	nodo<T>* succ;
};

template <typename T>
class coda{
public:
	coda();
	~coda();
	bool empty() const;
	T top() const;
	int size() const;
	void push(T);
	void pop();
	void print() const;
private:
	nodo<T>* head;
	nodo<T>* tail;
	int lenght;
};

template <typename T>
coda<T>::coda(){
	head=NULL;
	tail=head;
	lenght=0;
}

template <typename T>
bool coda<T>::empty() const{
	return (head==NULL);
}

template <typename T>
coda<T>::~coda(){
	while(!empty()){
		pop();
	}
}
template <typename T>
int coda<T>::size() const{
	return lenght;
}
template <typename T>
T coda<T>::top() const{
	return head->element;
}
template <typename T>
void coda<T>::push(T element){
	nodo<T>* tmp= new nodo<T>;
	if(empty()){
		head=tmp;
		tail=tmp;
	}else{
		tail->succ=tmp;
	}
	tmp->succ=NULL;
	tmp->element=element;
	tail=tmp;
	lenght++;
}
template <typename T>
void coda<T>::pop(){
	nodo<T>* tmp= head;
	head=head->succ;
	delete(tmp);
	lenght--;
}

template <typename T>
void coda<T>::print() const{
	int i;
	for (i=0;i<lenght;i++){
		push(top());
		cout << top() << " ";
		pop();
	}
}
#endif /* CODE_H_ */