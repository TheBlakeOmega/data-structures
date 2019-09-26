#ifndef PRIORITYQUEUE_H_
#define PRIORITYQUEUE_H_

#include <iostream>
using namespace std;

template <typename T>
struct node{
	T element;
	int priority;
};

template <typename T>
class priorityQueue{
public:
	priorityQueue();
	priorityQueue(int);
	~priorityQueue();
	void changeSize(int);

	node<T>& operator=(const node<T>&);

	bool empty() const;
	bool contains(T) const;
	T getMin() const;
	int getSize() const;
	void push(T,int);
	void pop();
	void print() const;
private:
	int size;
	int maxSize;
	node<T>* heap;
};

template <typename T>
priorityQueue<T>::priorityQueue(){
	size=0;
	maxSize=10;
	heap= new node<T>[maxSize];
}

template <typename T>
priorityQueue<T>::priorityQueue(int mS){
	size=0;
	maxSize=mS;
	heap= new node<T>[maxSize];
}

template <typename T>
priorityQueue<T>::~priorityQueue(){
	delete [] heap;
}

template <typename T>
void priorityQueue<T>::changeSize(int newSize){
	node<T>* newHeap= new node<T>[newSize];
	node<T>* tmp=heap;
	int i;
	for (i=0;i<size;i++){
		newHeap[i]=heap[i];
	}
	heap=newHeap;
	maxSize=newSize;
	delete [] tmp;
}

template <typename T>
node<T>& priorityQueue<T>::operator=(const node<T>& n){
	node<T> tmp;
	tmp.element=n.element;
	tmp.priority=n.priority;
	return tmp;
}

template <typename T>
bool priorityQueue<T>::empty() const{
	return size==0;
}

template <typename T>
bool priorityQueue<T>::contains(T element) const{
	int i;
	for (i=0;i<size;i++){
		if (heap[i].element==element){
			return true;
		}
	}
	return false;
}

template <typename T>
T priorityQueue<T>::getMin() const{
	return heap[0].element;
}

template <typename T>
int priorityQueue<T>::getSize() const{
	return size;
}

template <typename T>
void priorityQueue<T>::push(T element, int priority){
	if(size==maxSize){
		changeSize(maxSize*1.5);
	}
	heap[size].element=element;
	heap[size].priority=priority;
	size++;
	// aggiustamento coda
	node<T> tmp;
	int i=size-1;
	while (i!=0 && heap[i].priority<heap[i/2].priority){
		tmp=heap[i];
		heap[i]=heap[i/2];
		heap[i/2]=tmp;
		i=i/2;
	}

}

template <typename T>
void priorityQueue<T>::pop(){
	if(empty()){
		throw "Queue is empty";
	}
	heap[0]=heap[size];
	size--;
	// aggiustamento coda
	node<T> tmp;
	int i=0;
	int j;
	while (i<size/2){
		j=2*i;
		if(j<size && heap[j+1].priority<heap[j].priority){
			j++;
		}
		if(heap[j].priority<heap[i].priority){
			tmp=heap[i];
			heap[i]=heap[j];
			heap[j]=tmp;
			i=j;
		}else{
			break;
		}
	}
}

template <typename T>
void priorityQueue<T>::print() const{
	int i;
	cout << "Priority:";
	for(i=0;i<size;i++){
		cout << " [" << heap[i].priority << "]";
	}
	cout << endl << "Element: ";
	for(i=0;i<size;i++){
		cout << " [" << heap[i].element << "]";
	}
}














#endif /* PRIORITYQUEUE_H_ */
