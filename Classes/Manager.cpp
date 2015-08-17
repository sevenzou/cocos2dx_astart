#include "StartScene.h"
#include "Manager.h"

bool Manager::init()
{
	return true;
}

void Manager::insertTag(std::string str, int tag)
{
//	std::vector<std::string> mapKeyVec;
//	Vector<T> k;
//	__Array a;
//	_mapTag.insert(str, tag);
}

void Manager::insertSprite(std::string, Sprite*)
{
//	_mapSpr.insert(str, tag);
}

int Manager::getTag(std::string str)
{
//	return _mapTag.at(str);
}

Sprite* Manager::getSprite(std::string str)
{
	return _mapSpr.at(str);
}

Map<std::string, int> Manager::getTagMap()
{
//	return _mapTag;
}

Map<std::string, Sprite*> Manager::getSpriteMap()
{
//	return _mapSpr;
}




