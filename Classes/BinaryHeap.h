#ifndef __BINARY_HEAP_H__
#define __BINARY_HEAP_H__

#include "cocos2d.h"
//#include <vector>
#include <deque>
#include <queue>
//#include <algorithm>

//USING_NS_CC;

template <class T>
class BinaryHeap {
public:
	typedef bool (*cmp)(T, T);
//	BinaryHeap();
	BinaryHeap(int Capacity, bool maxOrmin);
	~BinaryHeap();
	cmp _cmpare;
	int buildHeap(cmp cmpare);
	int insert(T data, int index, cmp cmpare);
	int insertToLast(T data, cmp cmpare);
	int remove(T data, int index, cmp cmpare);
	int getIndex(T data);
	T  getData(int index);
	void clear();

private:
	void heapify(int index, cmp cmpare);
	int filterup(int start, cmp cmpare);
	int filterdown(int start, int end, cmp cmpare);

	T* _data;
	int _size;
	int _capacity;
	bool _maxOrmin;
};


#endif
