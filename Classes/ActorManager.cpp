#include "ActorManager.h"

USING_NS_CC;

static ActorManager *s_actorManager = nullptr;

ActorManager* ActorManager::getInstance()
{
	if (!s_actorManager)
		s_actorManager = new ActorManager();

	return s_actorManager;
}

Actor* ActorManager::getActorByTag(int tag)
{
	for (Actor* actor : _actorTarget)
		if ( tag == actor->getActorTag() )
			return actor;
	return nullptr;
}

Actor* ActorManager::getMonsterByTag(int tag)
{
	for (Actor* monster : _monsterTarget)
		if ( tag == monster->getActorTag() )
			return monster;
	return nullptr;
}

