#ifndef __MANAGER_H__
#define __MANAGER_H__

#include "cocos2d.h"
USING_NS_CC;

class Manager
{
public:
	bool init();
	void insertTag(std::string, int);
	void insertSprite(std::string, Sprite*);

	int getTag(std::string);
	Sprite* getSprite(std::string);

	Map<std::string, int> getTagMap();
	Map<std::string, Sprite*> getSpriteMap();
private:
    Size _visibleSize;
    Vec2 _origin;
    Map<std::string, int> _mapTag;
    Map<std::string, Sprite*> _mapSpr;

};

#endif // __MANAGER_H__
