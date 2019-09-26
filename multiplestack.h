
#ifndef MULTIPLESTACK_H_
#define MULTIPLESTACK_H_
#include <iostream>
#include "pile.h"
using namespace std;

template <typename T>
class multiplestack{
public:
	multiplestack(unsigned int);
	~multiplestack();
	void push(T,unsigned int);
	T pop(unsigned int);
private:
	unsigned int stacksNumber;
	pila<T>* stacks;
};

template <typename T>
multiplestack<T>::multiplestack(unsigned int size){
	stacksNumber=size;
	stacks= new pila<T>[stacksNumber];
}

template <typename T>
multiplestack<T>::~multiplestack(){
	for (int i=0;i<stacksNumber;i++){
		stacks[i].~pila();
	}
	delete[] stacks;
}

template <typename T>
void multiplestack<T>::push(T element,unsigned int n){
	stacks[n].push(element);
}

template <typename T>
T multiplestack<T>::pop(unsigned int n){
	stacks[n].pop();
}

#endif /* MULTIPLESTACK_H_ */
