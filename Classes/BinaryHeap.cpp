#include "BinaryHeap.h"
//USING_NS_CC;

/*
 * begin Heap
 *
 */
//template <class T>
//Heap<T>::Heap()
//{
//	new (this)Heap(20,true); //true min; false max
//}

template <class T>
BinaryHeap<T>::BinaryHeap(int capacity, bool maxOrmin)
{
	this->_data = new T[capacity];
	this->_size = 0;
	this->_capacity = capacity;
	this->_maxOrmin = maxOrmin;
}

template <class T>
BinaryHeap<T>::~BinaryHeap()
{
	delete[] this->_data;
	this->_size = 0;
	this->_capacity = 0;
	this->_maxOrmin = true;
}

template <class T>
void BinaryHeap<T>::heapify(int index, cmp cmpare)	//same of filterdown()
{
	int last = index;
	int childL = 2*last+1;
	int childR = 2*last+2;

	if (childL<_size && cmpare(_data[childL],_data[last]))	//cmpare() return true is min
		last = childL;
	if (childR<_size && cmpare(_data[childR],_data[last]))
		last = childR;

	if (last != index) {
		T data = _data[last];
		_data[last] = _data[index];
		_data[index] = data;
		heapify(last, cmpare);
	}
}

template <class T>
int BinaryHeap<T>::filterup(int start, cmp cmpare)
{
	int child = start;
	int parent = floor((child-1)/2);
	T data = _data[child];
	if (_size <= 1)
		return 0;
	do {
		if (cmpare(data, _data[parent])) {	//cmpare() return true is min
			_data[child] = _data[parent];
			child = parent;
			parent = floor((child-1)/2);
		} else {
			break;
		}
	}while (child>0);
	_data[child] = data;

	return 0;
}

template <class T>
int BinaryHeap<T>::filterdown(int start, int end, cmp cmpare)
{
	int empty = start;
	int childL = 2*empty+1;
	int childR = 2*empty+2;
	T data = _data[empty];

	do {
		if (cmpare(_data[childL], data) || cmpare(_data[childR], data)) {	//cmpare() return true is min
			_data[empty] = cmpare(_data[childL], _data[childR]) ? _data[childL] : _data[childR];
			empty =_data[childL] < _data[childR] ? childL : childR;
			childL = 2*empty+1;
			childR = 2*empty+2;
		} else {
			break;
		}
	} while(empty <= end);
	_data[empty] = data;
	return 0;
}

template <class T>
int BinaryHeap<T>::getIndex(T data)
{
	int i = 0;
	for(i=0; i<_size; i++) {
		if (_data[i] == data)
			return i;
	}
	if (_size >= i)
		return -1;
}

template <class T>
T BinaryHeap<T>::getData(int index)
{
	return (_data[index]);
}

template <class T>
int BinaryHeap<T>::insert(T data, int index, cmp cmpare)
{
	if (_maxOrmin) {	//_maxOrmin==true min;else max
		if (_data[index] < data) {
			BinaryHeap<T>::filterup(_size, cmpare);
		} else if (_data[index] > data){
			BinaryHeap<T>::filterdown(index, _size, cmpare);
		}
	} else {
		if (_data[index] > data) {
			BinaryHeap<T>::filterup(_size, cmpare);
		} else if (_data[index] < data){
			BinaryHeap<T>::filterdown(index, _size, cmpare);
		}
	}
	return 0;
}

template <class T>
int BinaryHeap<T>::insertToLast(T data, cmp cmpare)
{
	if (_size == _capacity)
		return -1;
	_data[_size] = data;
	_size++;
	BinaryHeap<T>::filterup(_size, cmpare);

	return 0;
}

template <class T>
int BinaryHeap<T>::remove(T data, int index, cmp cmpare)
{
	if (-1 ==index)
		index =  BinaryHeap<T>::getIndex(data);
	if (_size == 0)
		return -1;
	_data[index] = _data[--_size];
	BinaryHeap<T>::filterdown(index, _size-1, cmpare);

	return 0;
}

template <class T>
void BinaryHeap<T>::clear()
{
	this->_size = 0;
	T data;
	for (int i=0; i<this->_capacity; i++) {
		this->_data[i] = data;
	}
}

template <class T>
int BinaryHeap<T>::buildHeap(cmp cmpare)
{
	for (int i=_size/2; i>0; i--)
		BinaryHeap<T>::heapify(i, cmpare);
//		Heap<T>::filterup(_size);

	return 0;
}



