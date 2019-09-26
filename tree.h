#ifndef TREE_H_
#define TREE_H_

#include <iostream>
#include "list.h"
using namespace std;

template <typename T>
struct node{
	T element;
	bool free=true;
	node<T>* father=nullptr;
	List<node<T>*> sons;
};

template <typename T>
class tree{
public:
	tree();
	tree(int);
	~tree();

	bool empty() const;
	void insRoot(T);
	node<T>* getRoot() const;
	node<T>* getFather(node<T>*) const;
	node<T>* getFirstSon(node<T>*) const;
	node<T>* getLastSon(node<T>*) const;
	node<T>* getNextBrother(node<T>*) const;
	List<node<T>*> getSons(node<T>*) const;
	bool leaf(node<T>*) const;
	bool lastBrother(node<T>*) const;
	void insSon(node<T>*,T);
	void cancSubtree(node<T>*);
	void switchNodes(node<T>*,node<T>*);
	void printSubTree(node<T>*) const;

	void preVisit(node<T>*) const;
	void postVisit(node<T>*) const;

private:
	node<T>* Tree;
	int MaxLength;
	int nNode;
	node<T>* getFree() const;
};

template <typename T>
tree<T>::tree(){
	nNode=0;
	Tree= new node<T>[100];
	MaxLength=100;
}

template <typename T>
tree<T>::tree(int nodes){
	nNode=0;
	Tree=new node<T>[nodes];
	MaxLength=nodes;
}

template <typename T>
tree<T>::~tree(){
	int i;
	for(i=0;i<MaxLength;i++){
		Tree[i].sons.~List();
	}
	delete[] Tree;
}

template <typename T>
bool tree<T>::empty() const{
	return (Tree[0].free);
}

template <typename T>
void tree<T>::insRoot(T el){
	Tree[0].element=el;
	Tree[0].free=false;
	nNode=1;
}

template <typename T>
node<T>* tree<T>::getRoot() const{
	return Tree;
}

template <typename T>
node<T>* tree<T>::getFather(node<T>* p) const{
	return p->father;
}

template <typename T>
node<T>* tree<T>::getFirstSon(node<T>* p) const{
	return p->sons.read(p->sons.begin());
}

template <typename T>
node<T>* tree<T>::getLastSon(node<T>* p) const{
	return p->sons.read(p->sons.last());
}

template <typename T>
node<T>* tree<T>::getNextBrother(node<T>* p) const{
	node<T>* tmp=getFather(p);
	return tmp->sons.read(tmp->sons.next(tmp->sons.find(p)));
}

template <typename T>
List<node<T>*> tree<T>::getSons(node<T>* p) const{
	return p->sons;
}

template <typename T>
node<T>* tree<T>::getFree() const{
	node<T>* free;
	int i=0;
	while (i<MaxLength){
		if (Tree[i].free==true){
			free=&Tree[i];
			return free;
		}
		i++;
	}
	cout << "Error: full memory" << endl;
	return nullptr;
}

template <typename T>
bool tree<T>::leaf(node<T>* p) const{
	return p->sons.empty();
}

template <typename T>
bool tree<T>::lastBrother(node<T>* p) const{
	node<T>* tmp=getFather(p);
	return p==getLastSon(tmp);
}

template <typename T>
void tree<T>::insSon(node<T>* p, T el){
	node<T>* tmp=getFree();
	tmp->element=el;
	tmp->father=p;
	tmp->free=false;
	p->sons.pushBack(tmp);
	nNode+=1;
}

template <typename T>
void tree<T>::cancSubtree(node<T>* p){
	if(!leaf(p)){
		while (!p->sons.empty()){
			cancSubTree(getFirstSon(p));
		}
	}
	node<T>* tmp=getNextBrother(p);
	Node<T>* son=tmp->sons.begin();
	while(tmp->sons.read(son)!=p){
		son=tmp->sons.next(son);
	}
	tmp->sons.remove(son);
	p->free=true;
}

template <typename T>
void tree<T>::switchNodes(node<T>* t,node<T>* s){
	T hold=t->element;
	t->element=s->element;
	s->element=hold;
}

template <typename T>
void tree<T>::printSubTree(node<T>* p) const{
	if(!leaf(p)){
		cout << "[ " << p->element;
		node<T>* tmp=getFirstSon(p);
		while(!p->sons.end(tmp)){
			printSubTree(tmp);
			tmp=p->sons.next(tmp);
		}
		cout << "] ";
	}else{
		cout <<"[/] ";
	}
}

template <typename T>
void tree<T>::preVisit(node<T>* p) const{

	// Do something with p

	node<T>* tmp=getFirstSon(p);
	while(!p->sons.end(tmp)){
		preVisit(tmp);
		tmp=p->sons.next(tmp);
	}
}

template <typename T>
void tree<T>::postVisit(node<T>* p) const{
	node<T>* tmp=getFirstSon(p);
	while(!p->sons.end(tmp)){
		print(tmp);
		tmp=p->sons.next(tmp);
	}

	// Do something with p
}






#endif /* TREE_H_ */
