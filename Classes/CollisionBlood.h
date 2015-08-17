#ifndef __COLLISION_BLOOD_H__
#define __COLLISION_BLOOD_H__

#include "cocos2d.h"
#include "ActorManager.h"
USING_NS_CC;

class Actor;

class CollisionBlood
{
public:
	CollisionBlood(cocos2d::Layer*, Vector<Actor*>);
	void addTarget(Vec2, std::string&);
	Actor* getCollisionSprite(Actor*);
	Actor* getCollisionSprite(Vector<Actor*>);
	inline Vector<Actor*> getVecTarget() { return _vecTarget; }

private:
	cocos2d::Layer *_layer;
	Vector<Actor*> _vecTarget;

};

class ActorBlood
{
public:
	friend class CollisionBlood;
	ActorBlood():_blood(0){}
	ActorBlood(int bld):_blood(bld){}
	inline int getBlood() { return _blood; }
	inline void setBlood(int bld) { _blood = bld; }
private:
	int _blood;

};


#endif // __COLLISION_BLOOD_H__
