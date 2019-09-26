#ifndef BINTREE_H_
#define BINTREE_H_

#include <iostream>
using namespace std;

template <typename T>
struct node{
	T element;
	node* sonSx=nullptr;
	node* sonDx=nullptr;
	node* father=nullptr;
	bool free=true;
};

template <typename T>
class binTree{
public:
	binTree();
	binTree(int);
	~binTree();
	bool empty() const;
	node<T>* getRoot() const;
	node<T>* getFather(node<T>*) const;
	node<T>* getSonSx(node<T>*) const;
	node<T>* getSonDx(node<T>*) const;
	bool emptySx(node<T>*) const;
	bool emptyDx(node<T>*) const;
	void cancSubTree(node<T>*);
	T read(node<T>*) const;
	void write(node<T>*,T);
	void overwrite(node<T>*,T);
	void insRoot(T);
	void insSonDx(node<T>*,T);
	void insSonSx(node<T>*,T);
	int sizeNode() const;
	void printSubTree(node<T>*) const;

	void visitPreOrder(node<T>* p) const;
	void visitPostOrder(node<T>* p) const;
	void visitInOrder(node<T>* p) const;

private:
	int maxLength;
	node<T>* free;
	node<T>* Tree;
	int nNode;
	node<T>* getFree() const;
};

template <typename T>
binTree<T>::binTree(){
	nNode=0;
	maxLength=64;
	Tree= new node<T>[maxLength];
	free=nullptr;
}

template <typename T>
binTree<T>::binTree(int length){
	nNode=0;
	maxLength=length;
	Tree= new node<T>[maxLength];
	free=nullptr;
}

template <typename T>
binTree<T>::~binTree(){
	delete[] Tree;
	delete free;
}

template <typename T>
bool binTree<T>::empty() const{
	return (Tree[0].free==true);
}

template <typename T>
node<T>* binTree<T>::getRoot() const{
	return Tree;
}

template <typename T>
node<T>* binTree<T>::getSonSx(node<T>* p) const{
	if(p->sonSx!=nullptr)
		return p->sonSx;
	return nullptr;
}

template <typename T>
node<T>* binTree<T>::getSonDx(node<T>* p) const{
	if(p->sonDx!=nullptr)
		return p->sonDx;
	return nullptr;
}

template <typename T>
node<T>* binTree<T>::getFather(node<T>* p) const{
	if (p->father!=nullptr)
		return p->father;
	return nullptr;
}

template <typename T>
bool binTree<T>::emptySx(node<T>* p) const{
	return (p->sonSx==nullptr);
}

template <typename T>
bool binTree<T>::emptyDx(node<T>* p) const{
	return (p->sonDx==nullptr);
}

template <typename T>
void binTree<T>::cancSubTree(node<T>* p){
	if (!emptySx(p))
		cancSubTree(getSx(p));
	if (!emptyDx(p))
		cancSubTree(getDx(p));
	p->free=true;
	p->sonSx=nullptr;
	p->sonDx=nullptr;
	nNode=nNode-1;
}

template <typename T>
T binTree<T>::read(node<T>* p) const{
	return p->element;
}

template <typename T>
node<T>* binTree<T>::getFree() const{
	node<T>* free;
	int i=0;
	while (i<maxLength){
		if (Tree[i].free==true){
			free=Tree+i;
			return free;
		}
		i++;
	}
	cout << "Error: full memory" << endl;
	return nullptr;
}

template <typename T>
void binTree<T>::write(node<T>* p,T el){
	if(p->free==true){
		p->element=el;
		p->free=false;
	}
	nNode=nNode+1;
}

template <typename T>
void binTree<T>::insRoot(T el){
	if(empty()){
		Tree[0].element=el;
		Tree[0].free=false;
		nNode=nNode+1;
	}
}

template <typename T>
void binTree<T>::insSonSx(node<T>* p,T el){
	if(emptySx(p)){
		free=getFree();
		p->sonSx=free;
		free->father=p;
		free->element=el;
		free->free=false;
		nNode=nNode+1;
	}else{
		throw "Error: left son already exists";
	}
}

template <typename T>
void binTree<T>::insSonDx(node<T>* p,T el){
	if(emptyDx(p)){
		free=getFree();
		p->sonDx=free;
		free->father=p;
		free->element=el;
		free->free=false;
		nNode=nNode+1;
	}else{
		throw "Error: right son already exists";
	}
}

template <typename T>
void binTree<T>::overwrite(node<T>* p,T el){
	p->element=el;
}

template <typename T>
int binTree<T>::sizeNode() const{
	return nNode;
}

template <typename T>
void binTree<T>::printSubTree(node<T>* p) const{
	cout << "[ " << read(p);
	if(!emptySx(p)){
		printSubTree(getSonSx(p));
	}else{
		cout << "[/]";
	}
	cout << ", ";
	if(!emptyDx(p)){
		printSubTree(getSonDx(p));
	}else{
		cout << "[/]";
	}
	cout << " ]";
}

template <typename T>
void binTree<T>::visitPreOrder(node<T>* p) const{
	if(!p->free){

		//utilizzare i nodi visitati

		visitPreOrder(getSonSx(p));
		visitPreOrder(getSonDx(p));
	}
}

template <typename T>
void binTree<T>::visitPostOrder(node<T>* p) const{
	if(!p->free){
		visitPostOrder(getSonSx(p));
		visitPostOrder(getSonDx(p));

		//utilizzare i nodi visitati
	}
}

template <typename T>
void binTree<T>::visitInOrder(node<T>* p) const{
	if(!p->free){
		visitInOrder(getSonSx(p));

		//utilizzare i nodi visitati

		visitInOrder(getSonDx(p));
	}
}

/* INSERIMENTO AUTOMATICO                        //VALIDO CON GLI INTERI
#include <time.h>								 //INCLUDERE QUESTA LIBRERIA
template <typename T>
void binTree<T>::randomInsert(node<T>* p){
	if(p!=nullptr){
		srand(time(NULL));
		int i=rand()%2;
		if(i){
			insSonSx(p,rand()%20);
		}
		i=rand()%2;
		if(i){
			insSonDx(p,rand()%20);
		}
		randomInsert(getSonSx(p));
		randomInsert(getSonDx(p));
	}
}
*/








#endif /* BINTREE_H_ */
