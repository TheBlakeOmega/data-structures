/*
 * pile.h
 * Author: Vincenzo Belvedere
 */

#ifndef PILE_H_
#define PILE_H_
#include <iostream>
using namespace std;

template <typename T>
struct nodo{
	T element;
	nodo<T>* succ;
};

template <typename T>
class pila{
public:
	pila();
	~pila();
	bool empty() const;
	T top() const;
	int size() const;
	void push(T);
	void pop();
	void print() const;
private:
	nodo<T>* head;
	int lenght;
};

template <typename T>
pila<T>::pila(){
	head=NULL;
	lenght=0;
}

template <typename T>
pila<T>::~pila(){
	while(!empty()){
		pop();
	}
}

template <typename T>
bool pila<T>::empty() const{
	return (head==NULL);
}

template <typename T>
T pila<T>::top() const{
	return head->element;
}

template <typename T>
int pila<T>::size() const{
	return lenght;
}


template <typename T>
void pila<T>::push(T element){
	position* tmp=new position;
	tmp->element=element;
	tmp->succ=head;
	head=tmp;
	lenght++;
}

template <typename T>
void pila<T>::pop(){
	if (!(empty())){
		position* tmp;
		tmp=head;
		head=head->succ;
		delete(tmp);
		lenght--;
	}else{
		cout << "Pila gia' vuota\n";
	}
}

template <typename T>
void pila<T>::print() const{
	pila<T> S;
	while(!empty()){
		cout << top() << " ";
		S.push(top());
		pop();
	}
	while(!S.empty()){
		push(S.top());
		S.pop();
	}
	~S;
}









#endif /* PILE_H_ */
