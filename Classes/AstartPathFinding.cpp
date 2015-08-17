#include "AstartPathFinding.h"
#include "BinaryHeap.h"
USING_NS_CC;

/*
 * begin AstartPathFinding
 *
 * */
Vec2 AstartPathFinding::_start = Vec2(0,0);
Vec2 AstartPathFinding::_end = Vec2(0,0);

void AstartPathFinding::mapInit()
{
	//init map
	log("AstartPathFinding::mapInit entry");
	int w = getWidth();
	int h = getHeight();
//	_heapList = new BinaryHeap<MyPoint*>(w*h, true);
	for(int i = 0; i < w; ++i){
		for(int j = 0; j < h; ++j){
			MyPoint *point = new MyPoint(Vec2(i,j), 0, 0, false, false, true);
			setMap(i,j,point);
		}
	}
}

void AstartPathFinding::mapClear()
{
	log("AstartPathFinding::mapClear entry");
	int w = getWidth();
	int h = getHeight();
//	if (0 !=_mapArray.size()) {
		for(int i = 0; i < w; ++i) {
			for(int j = 0; j < h; ++j) {
				MyPoint *point = getMap(i,j);
				point->setClose(false);
				point->setMarked(false);
				point->setParent((MyPoint*)NULL);
				point->setg(0);
				point->seth(0);
				point->calcf();
				setMap(i,j,point);
			}
		}
//	}
	AstartPathFinding::_start = Vec2(0,0);
	AstartPathFinding::_end = Vec2(0,0);
	_openList.clear();
	_closeList.clear();
//	_heapList->clear();
}

void AstartPathFinding::setMap(int x, int y, MyPoint* point)
{
	_mapArray[y*_mapWidth+x] = point;
}

MyPoint* AstartPathFinding::getMap(int x, int y)
{
	return _mapArray[y*_mapWidth+x];
}

float AstartPathFinding::distanceBetweenTwoCells(float p1X,float p1Y, float p2X, float p2Y){

//	return sqrt(pow(p2X - p1X,2) + pow(p2Y - p1Y,2));
	return abs(p2X - p1X) + abs(p2Y - p1Y);
}

bool AstartPathFinding::compareByDistanceBetweenStartandGoal(MyPoint* point1, MyPoint* point2)
{
//	if (point1->getf() <= point2->getf())
//		return false;
//	else
//		return true;							// <= return false max
	return (point1->getf() > point2->getf());	// >  return false min
}

void AstartPathFinding::makeOpenList(std::vector<MyPoint*> *vecPoint)
{
	std::make_heap(vecPoint->begin(),vecPoint->end(), compareByDistanceBetweenStartandGoal);
}

void AstartPathFinding::pushOpenList(std::vector<MyPoint*> *vecPoint)
{
	std::push_heap(vecPoint->begin(),vecPoint->end(), compareByDistanceBetweenStartandGoal);
}
    
MyPoint* AstartPathFinding::popOpenList(std::vector<MyPoint*> *vecPoint)
{
	std::pop_heap(vecPoint->begin(),vecPoint->end(), compareByDistanceBetweenStartandGoal);
	return vecPoint->back();
}

bool AstartPathFinding::findPath(Vec2 start, Vec2 end)
{
	log("AstartPathFinding::findPath entry");
	MyPoint* nowProcessPoint;
	MyPoint* startpoint = this->getMap(start.x, start.y);
	if (this->getMap(end.x, end.y)->getPassable() == false)
		return false;
	AstartPathFinding::_start = start;
	AstartPathFinding::_end = end;
	this->_openList.push_back(startpoint);
	this->makeOpenList(&_openList);
//	BinaryHeap<MyPoint*>::_heapList->insertToLast(startpoint, compareByDistanceBetweenStartandGoal);

	startpoint->setMarked(true);
	startpoint->setClose(true);
	do {
		nowProcessPoint = this->popOpenList(&_openList);
		_openList.pop_back();
//		*nowProcessPoint = _heapList->getData(0);
//		_heapList->remove(*nowProcessPoint, 0);

		_closeList.push_back(nowProcessPoint);
		nowProcessPoint->setClose(true);
//		log("nowProcessPoint->getPosition().x = %f",nowProcessPoint->getPosition().x);
//		log("nowProcessPoint->getPosition().y = %f",nowProcessPoint->getPosition().y);
		log("nowProcessPoint->getg() = %f, getf() = %f",nowProcessPoint->getg(), nowProcessPoint->getf());
		if (nowProcessPoint->getPosition() == end) {
			return true;
		}

		for (int i=0; i<8; ++i) {
			int x = nowProcessPoint->getPosition().x + _Direction[i][0];
			int y = nowProcessPoint->getPosition().y + _Direction[i][1];
//			log("x+_Direction[%d][0] = %d", i, x);
//			log("y+_Direction[%d][1] = %d", i, y);
//			for(MyPoint* vec :_closeList) {
//				if (vec->getPosition().x == x && vec->getPosition().y == y)
//					continue;
//			}
			MyPoint* point = this->getMap(x, y);

			if (x >= 0 && x < this->getWidth() && y >= 0 && y < this->getHeight()
				&& point->getPassable() == true && point->getClose() == false) {

				float beforeDistance = nowProcessPoint->getg() + _DISTANCE[i];//calculate the distance
//				log("beforeDistance = %f", beforeDistance);
				if (point->getMarked() == false) {
//					log("point->getMarked() == false");
					point->setMarked(true);
					point->setParent(nowProcessPoint);
					point->setg(beforeDistance);
					point->seth(distanceBetweenTwoCells(point->getPosition().x,point->getPosition().y,_end.x,_end.y));
					point->calcf();
					_openList.push_back(point);//only push the unmarked cell into the vector
					this->pushOpenList(&_openList);
//					_heapList->insertToLast(*point);
				} else { // if find a lower distance, update it
//					log("point->getMarked() == true");
					if (beforeDistance < point->getg()) {
//						log("find a lower distance");
						point->setParent(nowProcessPoint);
						point->setg(beforeDistance);
						point->calcf();
						this->makeOpenList(&_openList);//distance change,so make heap again
//						_heapList->insert(*point, _heapList->getIndex(*point));
					}

				}
			}
		}

	} while(_openList.size() != 0);
	return false;
}

std::vector<MyPoint*> AstartPathFinding::getPath()
{
	log("AstartPathFinding::getPath entry");
	std::vector<MyPoint*> vec;
	MyPoint* node = this->getMap(_end.x, _end.y)->getParent();
	vec.push_back(this->getMap(_end.x, _end.y));

	while (node) {
		vec.push_back(node);
		node = node->getParent();
	}

	log("vec.size() = %d", vec.size());
//	for (int i=0; i<vec.size(); ++i) {
//		log("getPath:x = %f, y = %f", vec[i]->getPosition().x, vec[i]->getPosition().y);
//	}
	return vec;
}
