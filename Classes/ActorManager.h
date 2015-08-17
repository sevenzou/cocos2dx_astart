#ifndef __ACTOR_MANAGER_H__
#define __ACTOR_MANAGER_H__

#include "cocos2d.h"
#include "CollisionBlood.h"
#include "Actor.h"
USING_NS_CC;
class Actor;

class ActorManager
{
public:
//	ActorManager():_actorTarget(NULL) {}
	Vector<Actor*> _actorTarget;
	Vector<Actor*> _monsterTarget;
//	std::vector<Actor*> dmonsterTarget();
//	std::shared_ptr<Vector<Sprite*>> _actorTarget;
//	std::shared_ptr<Vector<Sprite*>> _monsterTarget;


	static ActorManager* getInstance();

	Vector<Actor*>* creatActorTarget(int);
	Actor* getActorByTag(int tag);
	Actor* getMonsterByTag(int tag);

private:

};

#endif // __ACTOR_MANAGER_H__
