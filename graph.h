#ifndef GRAPH_H_
#define GRAPH_H_

#include <iostream>
#include "list.h"
using namespace std;

template <typename L>
struct node{
	L label;
	bool empty=true;
	int inArc=0;
	int outArc=0;
	int Arc=inArc+outArc;
};


template <typename W>
struct arc{
	W weight;
	bool empty=true;

	arc<W> operator=(const arc<W>);
};

template <typename W>
arc<W> arc<W>::operator=(const arc<W> s){
	arc<W> tmp;
	tmp.weight=s.weight;
	tmp.empty=s.empty;
	return tmp;
}


template <typename L, typename W>
class graph{
public:
	graph(int);
	~graph();

	bool empty() const;
	bool existNode(node<L>*) const;
	bool existArc(node<L>*,node<L>*) const;
	List<node<L>> adjacent(node<L>*) const;
	void insNode(node<L>*);
	void insArc(node<L>*,node<L>*);
	void insArc(node<L>*,node<L>*,W);
	void cancNode(node<L>*);
	void cancArc(node<L>*,node<L>*);
	void writeNode(node<L>*,L);
	void writeArc(node<L>*,node<L>*,W);
	L readNode(node<L>*) const;
	W readArc(node<L>*,node<L>*) const;
	int getSizeNode() const;
	int getSizeArc() const;
	int getNodePosition(L) const; //utilizzabile solo se si è sicuri che tutti gli elementi nei nodi sono diversi
	int* getArcPosition(W) const;  //stessa cosa della precedente

	int inDegree(node<L>*) const;
	int outDegree(node<L>*) const;
	double meanOutDegree() const;
	double meanInDegree() const;
private:
	node<L>* nodes;
	arc<L>** arcs;
	int dimension;
	int sizeNode;
	int sizeArc;

	int search(node<L>*) const;
	int getFree() const;
};

template <typename L, typename W>
graph<L,W>::graph(int dim){
	dimension=dim;
	sizeNode=0;
	sizeArc=0;
	nodes= new node<L>[dimension];
	arcs= new arc<W>*[dimension];
	for (int i=0;i<dimension;i++){
		arcs[i]=new arc<W>[dimension];
	}
}

template <typename L, typename W>
graph<L,W>::~graph(){
	for (int i=0;i<dimension;i++){
		delete[] arcs[i];
	}
	delete[] arcs;
	delete nodes;
}

template <typename L, typename W>
int graph<L,W>::search(node<L>* p) const{
	int i=0;
	node<L>* tmp=nodes;
	while(tmp!=p){
		i++;
		tmp++;
	}
	return i;
}

template <typename L, typename W>
int graph<L,W>::getFree() const{
	int i=0;
	node<L>* tmp=nodes;
	while(!tmp->empty){
		i++;
	}
	return i;
}

template <typename L, typename W>
bool graph<L,W>::empty() const{
	return sizeNode==0;
}

template <typename L, typename W>
bool graph<L,W>::existNode(node<L>* p) const{
	return !(p->empty);
}

template <typename L, typename W>
bool graph<L,W>::existArc(node<L>* p,node<L>* h) const{
	int i=search(p);
	int j=search(h);
	return !(arcs[i][j].empty);
}

template <typename L, typename W>
List<node<L>> graph<L,W>::adjacent(node<L>* p) const{
	List<node<L>> A;
	int k=search(p);
	for(int i=0;i<dimension;i++){
		if(!(arcs[k][i].empty)){
			A.pushBack(nodes[i]);
		}
	}
	return A;
}

template <typename L, typename W>
void graph<L,W>::insNode(node<L>* el){
	if (sizeNode==dimension){
		throw "Full graph";
	}else{
		int i=getFree();
		nodes[i].label=el->label;
		nodes[i].empty=false;
		sizeNode++;
	}
}

template <typename L, typename W>
void graph<L,W>::insArc(node<L>* p,node<L>* s){
	int i= search(p);
	int j= search(s);
	arcs[i][j].empty=false;
	p->outArc++;
	p->inArc++;
	sizeArc++;
}

template <typename L, typename W>
void graph<L,W>::insArc(node<L>* p,node<L>* s,W el){
	int i= search(p);
	int j= search(s);
	arcs[i][j].empty=false;
	arcs[i][j].weight=el;
	p->outArc++;
	p->inArc++;
	sizeArc++;
}

template <typename L, typename W>
void graph<L,W>::cancNode(node<L>* p){
	p->empty=true;
	int k=search(p);
	for(int i=0;i<dimension;i++){
		arcs[i][k].empty=true;
		arcs[k][i].empty=true;
	}
	sizeNode--;
}

template <typename L, typename W>
void graph<L,W>::cancArc(node<L>* p, node<L>* s){
	int i=search(p);
	int j=search(s);
	arcs[i][j].empty=true;
	p->outArc--;
	p->inArc--;
	sizeArc--;
}

template <typename L, typename W>
void graph<L,W>::writeNode(node<L>* p,L el){
	p->label=el;
}

template <typename L, typename W>
void graph<L,W>::writeArc(node<L>* p, node<L>* s, W el){
	int i=search(p);
	int j=search(s);
	arcs[i][j].weight=el;
}

template <typename L, typename W>
L graph<L,W>::readNode(node<L>* p) const{
	return p->label;
}

template <typename L, typename W>
W graph<L,W>::readArc(node<L>* p,node<L>* s) const{
	int i=search(p);
	int j=search(s);
	return arcs[i][j].weight;
}

template <typename L, typename W>
int graph<L,W>::getSizeNode() const{
	return sizeNode;
}

template <typename L, typename W>
int graph<L,W>::getSizeArc() const{
	return sizeArc;
}

template <typename L, typename W>
int graph<L,W>::getNodePosition(L el) const{
	int i=0;
	while(nodes[i].label!=el && i<dimension){
		i++;
	}
	if (i!=dimension){
		return i;
	}else{
		throw "Node doesn't exists";
	}
}

template <typename L,typename W>
int* graph<L,W>::getArcPosition(W el) const{
	int* pos= new int[2];
	int j;
	int i=0;
	while(arcs[i][j]!=el && i<dimension){
		j=0;
		while(arcs[i][j]!=el && j<dimension){
			j++;
		}
		i++;
	}
	*pos=i;
	*(pos+1)=j;
	if(i!=dimension){
		return pos;
	}else{
		throw "Arc doesn't exists";
	}
}

template <typename L,typename W>
int graph<L,W>::inDegree(node<L>* p) const{
	return p->inArc;
}

template <typename L,typename W>
int graph<L,W>::outDegree(node<L>* p) const{
	return p->outArc;
}

template <typename L, typename W>
double graph<L,W>::meanOutDegree() const{
	int sum=0;
	int j=0;
	for (int i=0;i<dimension;i++){
		if(existNode(nodes[i])){
			j++;
			sum=sum+nodes[i].outArc;
		}
	}
	double mean=sum/j;
	return mean;
}

template <typename L, typename W>
double graph<L,W>::meanInDegree() const{
	int sum=0;
	int j=0;
	for (int i=0;i<dimension;i++){
		if(existNode(nodes[i])){
			j++;
			sum=sum+nodes[i].inArc;
		}
	}
	double mean=sum/j;
	return mean;
}

#endif /* GRAPH_H_ */
