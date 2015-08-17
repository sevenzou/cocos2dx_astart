#include "CollisionBlood.h"

USING_NS_CC;


CollisionBlood::CollisionBlood(cocos2d::Layer *thislayer, Vector<Actor*> target):_layer(thislayer),_vecTarget(target)
{
}

void CollisionBlood::addTarget(Vec2 vec, std::string& str)
{
	Sprite* spr = Sprite::create(str);
	spr->setPosition(vec);
	spr->setTag(2);
	_layer->addChild(spr);
	Actor* actor = Actor::create();
	auto bld = new ActorBlood(100);
	actor->setActorSprite(spr);
	actor->setActorTag(1);
	actor->setActorBlood(bld);
	_vecTarget.pushBack(actor);
}

Actor* CollisionBlood::getCollisionSprite(Actor* target)
{
	for (Actor* actor : _vecTarget)
		if ( actor->getActorSprite()->getBoundingBox().intersectsRect(target->getActorSprite()->getBoundingBox()) ) {
			return actor;
		}
	return nullptr;
}

Actor* CollisionBlood::getCollisionSprite(Vector<Actor*> actorTarget)
{
	for (Actor* target : actorTarget) {
		for (Actor* actor : _vecTarget)
			if ( actor->getActorSprite()->getBoundingBox().intersectsRect(target->getActorSprite()->getBoundingBox()) ) {
				return actor;
			}
	}
	return nullptr;
}



