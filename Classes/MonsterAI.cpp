#include "MonsterAI.h"

USING_NS_CC;

/*
 * Monster action class
 *
 **/
void Move::Execute(MonsterAI* monster)
{
	monster->ifFaraway();

	monster->move();
}

void Stop::Execute(MonsterAI* monster)
{
	monster->stop();
}

void Hunter::Execute(MonsterAI* monster)
{
	monster->hunter();
}

void Attack::Execute(MonsterAI* monster)
{
	monster->attack();
}

void AfterAttack::Execute(MonsterAI* monster)
{
	monster->afterAttack();
}

/*
 *MonsterAI class
 *
 */
int MonsterAI::update()
{
	int ret = -1;
	//add check function

	_currentState->Execute(this);

	return ret;
}

int MonsterAI::changeState(State* newState)
{
	int ret = -1;
	delete _currentState;
	_currentState = newState;
	return ret;
}

int MonsterAI::move()
{
	int ret = -1;

	return ret;
}

int MonsterAI::stop()
{
	int ret = -1;

	return ret;
}

int MonsterAI::hunter()
{
	int ret = -1;

	return ret;
}

int MonsterAI::attack()
{
	int ret = -1;

	return ret;
}

int MonsterAI::afterAttack()
{
	int ret = -1;

	return ret;
}

int MonsterAI::ifClose()
{
	int ret = -1;

	return ret;
}

int MonsterAI::ifFaraway()
{
	int ret = -1;

	return ret;
}




