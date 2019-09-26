#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include <iostream>
#include <string>
#include "list.h"
using namespace std;

template <typename K>
class myHash{
public:
	int operator() (const K) const;  //implementare la funzione di hash in base alle specifiche del problema in cui utilizzarla
};

/*   ESEMPIO: SPECIALIZZAZIONE CON TIPO STRINGA
template<>
class myHash<string>{
public:
	int operator() (const string key) const{
		int i;
		int length=key.length();
		int hashValue=0;
		for(i=0;i<length;i++){
			hashValue=(hashValue*5)+key.at(i);
		}
		return hashValue;
	}
};*/


template <typename K,typename T>
struct myPair{
	K key;
	T element;

	myPair(){};
	myPair(myPair<K,T>& el){
		key=el.key;
		element=el.element;
	}
};

template <typename K, typename T>
class hashTable{
public:
	hashTable(int);
	~hashTable();

	bool empty() const;
	bool belong(const K&) const;
	int getSize() const;
	int search(const K&) const;         //ricerca una posizione in tabella utilizzando la funzione di hash utilizzata finchè non viene soddisfatta una delle tre condizioni studiate
	myPair<K,T>* find(const K&) const;
	T getElement(const K&) const;
	void insert(myPair<K,T>&);
	void erase(const K&);
	void modify(const K&, const T&);
	void print() const;

	bool containsValue(const T&) const;
	List<T> values() const;
	List<K> keys() const;
	void resize();                       // raddoppia la dimensione della tabella
private:
	myPair<K,T>** table;
	myHash<K> hash;
	int size;
	int divisor;


};

template <typename K, typename T>
hashTable<K,T>::hashTable(int div){
	size=0;
	divisor=div;
	table=new myPair<K,T>*[divisor];
	int i;
	for(i=0;i<divisor;i++){
		table[i]=nullptr;
	}
}

template <typename K, typename T>
hashTable<K,T>::~hashTable(){
	int i;
	for(i=0;i<divisor;i++){
		delete [] table[i];
	}
	delete[] table;
}

template <typename K, typename T>
bool hashTable<K,T>::empty() const{
	return size==0;
}

template <typename K, typename T>
bool hashTable<K,T>::belong(const K& key) const{
	int b=search(key);
	if(table[b]==nullptr || table[b]!=key){
		return false;
	}else{
		return true;
	}
}

template <typename K, typename T>
int hashTable<K,T>::getSize() const{
	return size;
}

template <typename K, typename T>
int hashTable<K,T>::search(const K& key) const{
	int i=(int) hash(key)%divisor;
	int j=i;
	do{
		if(table[j]==nullptr || table[j]->key==key){
			return j;
		}
		j=(j+1)%divisor;
	}while(j!=i);
	return j;   //tabella piena
}

template <typename K, typename T>
myPair<K,T>* hashTable<K,T>::find(const K& key) const{
	int b=search(key);
	if(table[b]==nullptr || table[b]->key!=key){
		return nullptr;
	}else{
		return table[b];
	}
}

template <typename K, typename T>
T hashTable<K,T>::getElement(const K& key) const{
	int b=search(key);
	if(table[b]==nullptr || table[b]->key!=key){
		throw "This key doesn't exosts";
	}else{
		return table[b]->element;
	}
}

template <typename K, typename T>
void hashTable<K,T>::insert(myPair<K,T>& el){
	int b=search(el.key);
	if(table[b]==nullptr){
		table[b]= new pair<K,T>(el);
		size++;
	}else{
		if(table[b]->key==el.key){
			throw "This key already exists";
		}else{
			throw "Full table";
		}
	}
}

template <typename K, typename T>
void hashTable<K,T>::erase(const K& key){
	int b=search(key);
	if(table[b]==nullptr){
		throw "This key doesn't exists";
	}else{
		table[b]=nullptr;
	}
}

template <typename K, typename T>
void hashTable<K,T>::modify(const K& key,const T& el){
	int b=search(key);
	if(table[b]==nullptr){
		throw "This key doesn't exists";
	}else{
		table[b]->element=el;
	}
}

template <typename K,typename T>
void hashTable<K,T>::print() const{
	if(!empty()){
		cout << "Key: Element:" << endl;
		int i;
		for(i=0;i<divisor;i++){
			if(table[i]!=nullptr){
				cout << table[i]->key << "," << table[i]->element << endl;
			}
		}
	}else{
		cout << "Empty Table" << endl;
	}
}

template <typename K, typename T>
bool hashTable<K,T>::containsValue(const T& value) const{
	int i;
	for(i=0;i<divisor;i++){
		if(value==table[i]->element){
			return true;
		}
	}
	return false;
}

template <typename K, typename T>
List<T> hashTable<K,T>::values() const{
	int i;
	List<T> values;
	for(i=0;i<divisor;i++){
		if(table[i]!=nullptr){
			values.pushBack(table[i]->element);
		}
	}
	return values;
}

template <typename K, typename T>
List<T> hashTable<K,T>::keys() const{
	int i;
	List<K> keys;
	for(i=0;i<divisor;i++){
		if(table[i]!=nullptr){
			values.pushBack(table[i]->key);
		}
	}
	return keys;
}

template <typename K,typename T>
void hashTable<K,T>::resize(){
	int i;
	myPair<K,T>** newTable=new myPair<K,T>*[divisor*2];
	myPair<K,T>** tmp=table;
	int i;
	for(i=0;i<divisor*2;i++){
		newTable[i]=nullptr;
	}
	for(i=0;i<divisor;i++){
		newTable[i]=table[i];
	}
	table=newTable;
	divisor=divisor*2;
	delete[] tmp;
}




#endif /* HASHTABLE_H_ */
