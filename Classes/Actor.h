#ifndef __ACTOR_H__
#define __ACTOR_H__

#include "cocos2d.h"
#include "CollisionBlood.h"
USING_NS_CC;

class ActorBlood;

class Actor: public Ref
{
public:
	Actor():_actorSpr(NULL),_Tag(-1),_actorBlood(NULL),_weapon(0),_speed(0),_actionType(0) {}
	static Actor* create();

    inline Sprite* getActorSprite() { return _actorSpr; }
    inline int getActorTag() { return _Tag; }
    inline ActorBlood* getActorBlood() { return _actorBlood; }
    inline int getActorWeapon() { return _weapon; }
    inline float getActorSpeed() { return _speed; }
    inline int getActorActionType() { return _actionType; }

    inline void setActorSprite(Sprite* sp) { _actorSpr = sp; }
    inline void setActorTag(int tag) { _Tag = tag; }
    inline void setActorBlood(ActorBlood* bld) { _actorBlood = bld; }
    inline void setActorWeapon(int wp) { _weapon = wp; }
    inline void setActorSpeed(float sp) { _speed = sp; }
    inline void setActorActionType(int type) { _actionType = type; }

private:
    Sprite* _actorSpr;
	int _Tag;
	ActorBlood* _actorBlood;
	int _weapon;
	float _speed;
	int _actionType;
};

#endif // __ACTOR_H__
