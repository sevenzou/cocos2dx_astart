#ifndef __ASTART_PATH_FINDING_H__
#define __ASTART_PATH_FINDING_H__

#include "cocos2d.h"
//#include <vector>
#include <deque>
#include <queue>
//#include <algorithm>
#include "BinaryHeap.h"
USING_NS_CC;

const int _Direction[8][2] = {
	{0,1},   //north
	{1,0},   //east
	{0,-1},  //south
	{-1,0},  //west
	{1,1},   //northeast
	{1,-1},  //eastsouth
	{-1,-1}, //southwest
	{-1,1}   //westnorth
};

const float _DISTANCE[8] = {
	1,
	1,
	1,
	1,
	1.414f,
	1.414f,
	1.414f,
	1.414f
};

//typedef enum _Walkability {
//	Disable = 0,
//	Enable  = 1
//} Walkability;

class MyPoint
{
public:
	MyPoint(){}

	MyPoint(Vec2 vec, float g, float h, bool m,bool c, bool w)
	{
		this->_pos = vec;
		this->_g   = g;
		this->_h   = h;
		this->_marked = m;
		this->_close = c;
		this->_w   = w;
		this->_f   = _g + _h;
		this->_parentPoint = NULL;
	}

	inline void calcf() { this->_f = this->_g + this->_h;}
	inline float getf() { return this->_f;}
	inline void setPosition(Vec2 v) { _pos = v;}
	inline Vec2 getPosition() { return _pos;}
	inline void setPassable(bool w) { _w = w;}
	inline bool getPassable() { return _w;}
	inline void setg(float g) { _g = g;}
	inline float getg() { return _g;}
	inline void seth(float h) { _h = h;}
	inline float geth() { return _h;}
	inline void setMarked(bool m) { _marked = m;}
	inline bool getMarked() { return _marked; }
	inline void setClose(bool c) { _close = c;}
	inline bool getClose() { return _close; }
	inline void setParent(MyPoint *point) {_parentPoint = point;}
	inline MyPoint* getParent() { return _parentPoint;}
	inline bool operator < (MyPoint& a) { return this->_f < a._f;}
	inline bool operator > (MyPoint& a) { return this->_f > a._f;}
	inline bool operator == (MyPoint& a) { return this->_f == a._f;}
private:
	Vec2 _pos;
	bool _w;
	float _f;
	float _g;
	float _h;
	bool _marked;
	bool _close;
	MyPoint *_parentPoint;
};

typedef bool (*compareTwoPoints)(MyPoint *p1, MyPoint *p2);

class AstartPathFinding
{
public:
	std::vector<MyPoint*> _openList;
	std::vector<MyPoint*> _closeList;
    static Vec2 _start;
    static Vec2 _end;
    BinaryHeap<MyPoint*>* _heapList;
//    typename BinaryHeap<MyPoint*>::cmp _cmpare;

    AstartPathFinding(int mapWidth, int mapHeight):_mapArray(mapWidth*mapHeight)
    {
    	this->_mapWidth = mapWidth;
    	this->_mapHeight = mapHeight;
    	this->_heapList = NULL;
    }

    void mapInit();
    void mapClear();
	void setMap(int, int, MyPoint*);
    MyPoint* getMap(int, int);
    static float distanceBetweenTwoCells(float, float, float, float);
    static bool compareByDistanceBetweenStartandGoal(MyPoint*, MyPoint*);
    void makeOpenList(std::vector<MyPoint*>*);
    void pushOpenList(std::vector<MyPoint*>*);
	MyPoint* popOpenList(std::vector<MyPoint*>*);
	bool findPath(Vec2, Vec2);
	std::vector<MyPoint*> getPath();
	inline std::vector<MyPoint*> getMapArray() {return _mapArray;}
    inline int getWidth() {return _mapWidth;}
    inline int getHeight() {return _mapHeight;}
//    std::priority_queue<MyPoint*, std::vector<MyPoint*>, compareByDistanceBetweenStartandGoal> _openqueue; //not use


private:
    std::vector<MyPoint*> _mapArray;
    int _mapWidth;
    int _mapHeight;
};

#endif
