#ifndef __TILE_MAP_H__
#define __TILE_MAP_H__

#include "cocos2d.h"
#include "AstartPathFinding.h"
#include "CollisionBlood.h"
#include "ActorManager.h"
USING_NS_CC;

class TileMap : public cocos2d::Layer
{
public:
	typedef enum Direction_ {
		dir_up    = 0,
		dir_down  = 1,
		dir_left  = 2,
		dir_right = 3
	} Direction;
	Direction _direction;

	Size _visibleSize;
	Vec2 _origin;
	Vec2 _posInScreen;
	Vec2 _handPosition;
	cocos2d::TMXTiledMap *_tileMap;
	cocos2d::TMXLayer *_background;
	cocos2d::TMXLayer *_collidable;
	Sprite *_player;
	EventListenerTouchOneByOne* _listener;
	AstartPathFinding* _astart;
	std::vector<MyPoint*> _findPath;
	float _speedFactor;
	float _timeFactor;
	float _horizenDistance;
	float _diagonalDistance;
	bool _walkToLast;
//	Vector<Sprite*> *_vecTarget;
	CollisionBlood *_collision;
//	ActorManager * _actorManager;
	Actor *_actor;
	ParticleSystemQuad* _particle;
	void showClickParticle(Vec2);
	float setSpeedFactor(int, float);
	float setPlayerSpeed(Vec2, Vec2);
	bool onTouchBegan(Touch*, Event*);
	void onTouchMoved(Touch*, Event*);
	void onTouchEnded(Touch*, Event*);
	Vec2 tileCoordFromPosition(Vec2);
	Vec2 mapCoordFromPosition(Vec2);
	Vec2 positionFromMapCoord(Vec2);
	bool checkNodePassable(Vec2);
	void setPlayerPosition(Vec2);
	void setViewPointCenter(Vec2);
	void setViewPointInScreenOneofFour(Vec2);
	void walkStepbystep(Vec2);
	void walkSequenceToGoal(Sprite*, Vec2);
	void walkToGoalbyAstart(Vec2);
	void setViewPointInScreenByhand(Vec2);
	void setViewPointInScreenByhandEnd(void);
	void myscheduleUpdate(float);

	void update(float);
//	void addTarget(Vec2);

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(TileMap);
};

#endif // __TILE_MAP_H__
