#ifndef __MONSTER_AI_H__
#define __MONSTER_AI_H__

#include "cocos2d.h"
USING_NS_CC;
class MonsterAI;

class State
{
public:
	virtual ~State() {}
	virtual void Execute(MonsterAI*) = 0;
};

class MonsterAI
{

public:

    enum class _Status {
    	MOVE,
		STOP,
		HUNTER,
		ATTACK,
		AFTER_ATTACK
    };

    enum class Type {
    	LIVE,
		DEATH
    };
    MonsterAI();
    MonsterAI(const MonsterAI &);
    MonsterAI(MonsterAI &&);
    int update();
    int changeState(State*);
    int move();
    int stop();
    int hunter();
    int attack();
    int afterAttack();
    int ifClose();
    int ifFaraway();
    int moveEnableCheck();
    virtual ~MonsterAI();
private:
	State* _currentState;
	_Status _monsterStatus;
	Vec2 _pos;
	int _blood;
};



class Move : public State
{
public:
	virtual void Execute(MonsterAI*);
};

class Stop : public State
{
public:
	virtual void Execute(MonsterAI*);
};

class Hunter : public State
{
public:
	virtual void Execute(MonsterAI*);
};

class Attack : public State
{
public:
	virtual void Execute(MonsterAI*);
};

class AfterAttack : public State
{
public:
	virtual void Execute(MonsterAI*);
};


#endif // __MONSTER_AI_H__
