#include "Actor.h"
#include "ActorManager.h"

USING_NS_CC;


Actor* Actor::create()
{
	auto actor = new Actor();
	if (actor)
		return actor;
	return nullptr;
}
