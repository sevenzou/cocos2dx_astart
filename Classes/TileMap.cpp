#include "TileMap.h"
#include "AstartPathFinding.h"

USING_NS_CC;

Scene* TileMap::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = TileMap::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TileMap::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    _visibleSize = visibleSize;
    _origin = origin;

    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(TileMap::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    auto label = LabelTTF::create("TileMap", "Arial", 24);
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
    this->addChild(label, 1);


    _tileMap = TMXTiledMap::create("bg_TileMap.tmx");
	_tileMap->setPosition(Vec2(0,0));
//    _tileMap->setScale(_visibleSize.width/_tileMap->getContentSize().width,_visibleSize.height/_tileMap->getContentSize().height);
	_tileMap->setVisible(true);
    _background = _tileMap->layerNamed("bg");
    _collidable =  _tileMap->layerNamed("Meta");
	_collidable->setVisible(false);
	Director::getInstance()->setProjection(Director::Projection::_2D);
	this->addChild(_tileMap, 0, 50);

	TMXObjectGroup *group = _tileMap->getObjectGroup("Objects");
	ValueMap spawnPoint = group->getObject("SpawnPoint");
	float x = spawnPoint["x"].asFloat();
	float y = spawnPoint["y"].asFloat();

//	ActorManager::getInstance()->_actorTarget = new Vector<Actor*>(50);
//	ActorManager::getInstance()->_monsterTarget = Vector<Actor*>(50);
	_actor = Actor::create();
	_player = Sprite::create("ninja.png");
	_player->setTag(100);
	_player->setPosition(Vec2(x,y));
//	_posInScreen = Vec2(x,y);
	this->addChild(_player, 2);
	auto bld = new ActorBlood(100);
	_actor->setActorSprite(_player);
	_actor->setActorTag(1);
	_actor->setActorBlood(bld);
	ActorManager::getInstance()->_actorTarget.pushBack(_actor);

	_collision = new CollisionBlood(this, ActorManager::getInstance()->_monsterTarget);
	for (int i=1; i<6; i++) {
		ValueMap point = group->getObject("target"+Value(i).asString());
		float x = point["x"].asFloat();
		float y = point["y"].asFloat();
		std::string str = "BasiliskBrown.PNG";
		_collision->addTarget(Vec2(x,y), str);
	}


	/*
	 * screen Touch
	 */
	_listener = EventListenerTouchOneByOne::create();
	_listener->onTouchBegan = CC_CALLBACK_2(TileMap::onTouchBegan,this);
	_listener->onTouchMoved = CC_CALLBACK_2(TileMap::onTouchMoved,this);
	_listener->onTouchEnded = CC_CALLBACK_2(TileMap::onTouchEnded,this);
	_listener->setSwallowTouches(true);//≤ªœÚœ¬¥´µ›¥•√˛
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_listener,this);
	//_listener->setEnabled(false);

	/*
	 * AstartPathFinding
	 */
	AstartPathFinding* astart = new AstartPathFinding(_tileMap->getMapSize().width, _tileMap->getMapSize().height);
	_astart = astart;
	astart->mapInit();
	for (int i=0; i<_tileMap->getMapSize().width; i++)
		for (int j=0; j<_tileMap->getMapSize().height; j++) {
			if (checkNodePassable(Vec2(i,_tileMap->getMapSize().height-j-1)) == false)
				astart->getMap(i,j)->setPassable(false);
		}

//	for (int i=0; i<_tileMap->getMapSize().width; i++)
//		for (int j=0; j<_tileMap->getMapSize().height; j++)  {
//			log("checkNodePassable_[%d][%d] =  %d",i, j,_astart->getMap(i,j)->getPassable());
//		}
//	log("_tileMap->getMapSize().width = %f",_tileMap->getMapSize().width);
//	log("_tileMap->getMapSize().height = %f",_tileMap->getMapSize().height);

	this->scheduleUpdate();

    return true;
}

void TileMap::showClickParticle(Vec2 vec)
{
	_particle = ParticleSystemQuad::create("showClick.plist");
	_particle->setPosition(vec);
	_particle->setScale(0.5);
	_particle->setAutoRemoveOnFinish(true);
	this->addChild(_particle, 2);
}

/*
 * update 1FPS to check player target collision
 **/
void TileMap::update(float dt)
{
//	log("TileMap::update(float %f)",dt);

	Actor* actor = _collision->getCollisionSprite(ActorManager::getInstance()->_actorTarget);
	if (nullptr != actor) {
//		log("TileMap::update() actor != nullptr");
		actor->getActorSprite()->setVisible(false);
	}
}

bool TileMap::onTouchBegan(Touch* touch, Event* event)
{
	log("TileMap onTouchBegan");
	auto touchLocation = touch->getLocation();
	this->setViewPointInScreenByhand(touchLocation);
	return true;
}

void TileMap::onTouchMoved(Touch* touch, Event* event)
{
	log("TileMap onTouchMoved");
}

void TileMap::onTouchEnded(Touch* touch, Event* event)
{
	log("TileMap onTouchEnded");
	this->setViewPointInScreenByhandEnd();
	auto touchLocation = touch->getLocation();
	showClickParticle(touchLocation);

	log("touchLocation.x = %f", touchLocation.x);
	if (touchLocation.x < _tileMap->getTileSize().width
		|| touchLocation.x > _visibleSize.width - _tileMap->getTileSize().width
		|| touchLocation.y < _tileMap->getTileSize().height
		|| touchLocation.y > _visibleSize.height - _tileMap->getTileSize().height)
		return;
	touchLocation = this->convertToNodeSpace(touchLocation);
	log("convertToNodeSpace touchLocation.x = %f", touchLocation.x);

//	walkStepbystep(touchLocation);
	walkToGoalbyAstart(touchLocation);
}

Vec2 TileMap::tileCoordFromPosition(Vec2 pos)
{
	int x = pos.x/_tileMap->getTileSize().width;
	int y = (_tileMap->getMapSize().height*_tileMap->getTileSize().height - pos.y) / _tileMap->getTileSize().height;
	return Vec2(x,y);
}

Vec2 TileMap::mapCoordFromPosition(Vec2 pos)
{
	int x = pos.x/_tileMap->getTileSize().width;
	int y = pos.y/_tileMap->getTileSize().height;
	return Vec2(x,y);
}

bool TileMap::checkNodePassable(Vec2 tileCoord)
{
	int tileGid = _collidable->getTileGIDAt(tileCoord);
	if (tileGid > 0) {
		ValueMap proMap = _tileMap->getPropertiesForGID(tileGid).asValueMap();
		if (!proMap.empty()) {
			auto collision = proMap["Collidable"].asString();
			if ("true" == collision)
				return false;
		}
	}
	return true;
}

void TileMap::setPlayerPosition(Vec2 playerPos)
{
	Vec2 tileCoord = tileCoordFromPosition(playerPos);
	if (checkNodePassable(tileCoord) == false)
		return;
	_player->setPosition(playerPos);
}

void TileMap::setViewPointCenter(Vec2 vec2)
{
	int x = MAX(vec2.x, _visibleSize.width*1/2);
	int y = MAX(vec2.y, _visibleSize.height*1/2);
	Size mapSize = _tileMap->getMapSize();
	Size tileSize = _tileMap->getTileSize();
	x = MIN(x, (mapSize.width*tileSize.width) - _visibleSize.width*1/2);
	y = MIN(y, (mapSize.height*tileSize.height) - _visibleSize.height*1/2);

	Vec2 screenCenter = Vec2(_visibleSize.width*1/2, _visibleSize.height*1/2);
	Vec2 playerPoint = Vec2(x,y);
	Vec2 offset = screenCenter - playerPoint;
	this->setPosition(offset);

}

void TileMap::setViewPointInScreenOneofFour(Vec2 vec2)  //not use
{
	int x = MAX(vec2.x, _visibleSize.width*1/4);
	int y = MAX(vec2.y, _visibleSize.height*1/4);
	Size mapSize = _tileMap->getMapSize();
	Size tileSize = _tileMap->getTileSize();
	x = MIN(x, (mapSize.width*tileSize.width) - _visibleSize.width*3/4);
	y = MIN(y, (mapSize.height*tileSize.height) - _visibleSize.height*3/4);
	Vec2 screenCenter = Vec2(_visibleSize.width*1/2, _visibleSize.height*1/2);
	Vec2 playerPoint = Vec2(x,y);
	Vec2 offset = screenCenter - playerPoint;
	if (abs(offset.x) > _visibleSize.width*1/4 || abs(offset.y) > _visibleSize.height*1/4) {
		this->setPosition(offset);
	}
}

void TileMap::walkStepbystep(Vec2 touchLocation)
{
	auto playerPos = _player->getPosition();
	auto diff = touchLocation - playerPos;

	if (abs(diff.x) > abs(diff.y)) {
		if (diff.x > 0) {
			playerPos.x += _tileMap->getTileSize().width;
			_player->runAction(FlipX::create(false));
		} else {
			playerPos.x -= _tileMap->getTileSize().width;
			_player->runAction(FlipX::create(true));
		}
	} else {
		if (diff.y > 0) {
			playerPos.y += _tileMap->getTileSize().height;
		} else {
			playerPos.y -= _tileMap->getTileSize().height;
		}
	}

	this->setPlayerPosition(playerPos);

	this->setViewPointCenter(_player->getPosition());	//set player in the center of screen
	_posInScreen = Vec2(_visibleSize.width*1/2, _visibleSize.height*1/2);
}

float TileMap::setSpeedFactor(int flag, float speed)
{
	float speedFactor = 0;
	_horizenDistance = _tileMap->getTileSize().width;
	_diagonalDistance = sqrt(pow(_tileMap->getTileSize().width,2) + pow(_tileMap->getTileSize().height,2));

	if (!flag)
		speedFactor = 100;
	else {
		speedFactor = speed;
	}
	return speedFactor;
}

float TileMap::setPlayerSpeed(Vec2 playerPos, Vec2 pos)
{
	float timeFactor = 0;
	if (_walkToLast) {
		float distance =  sqrt(pow(playerPos.x - pos.x,2) + pow(playerPos.y - pos.y,2));
		timeFactor = distance/_speedFactor;
	} else {
		if (playerPos.x != pos.x && playerPos.y != pos.y)
			timeFactor = _diagonalDistance/_speedFactor;
		else
			timeFactor = _horizenDistance/_speedFactor;
	}
	return timeFactor;
}

Vec2 TileMap::positionFromMapCoord(Vec2 touchLocation)
{
	if (_findPath.size() > 1) {
		MyPoint* point = _findPath.back();
//		log("point->getPosition().x=%f  point->getPosition().y=%f",point->getPosition().x,point->getPosition().y);
		_findPath.pop_back();
		return Vec2((point->getPosition().x+0.5)*_tileMap->getTileSize().width, (point->getPosition().y+0.5)*_tileMap->getTileSize().height);
	} else if (_findPath.size() == 1) {
		_walkToLast = true;
		_findPath.pop_back();
		return touchLocation;
	} else {
		return Vec2(0,0);
	}
}

void TileMap::walkSequenceToGoal(Sprite* sprite, Vec2 touchLocation)
{
	if (_findPath.size() >= 1) {
//		this->setViewPointCenter(_player->getPosition());	//set player in the center of screen //no use
//		_posInScreen = Vec2(_visibleSize.width*1/2, _visibleSize.height*1/2);//set player in the of screen //no use
		auto playerPos = _player->getPosition();
		auto pos = positionFromMapCoord(touchLocation);
		_timeFactor = setPlayerSpeed(playerPos, pos);

		CallFunc* callFunc_1 = CallFunc::create(CC_CALLBACK_0(TileMap::walkSequenceToGoal,this,sprite,touchLocation));
		auto moveTo = MoveTo::create(_timeFactor,pos);
		auto sequence = Sequence::create(moveTo,callFunc_1,NULL);
		sequence->setTag(78);
		sprite->runAction(sequence);
	}
}

void TileMap::walkToGoalbyAstart(Vec2 touchLocation)
{
	auto playerPos = _player->getPosition();
	Vec2 playerCoord = mapCoordFromPosition(playerPos);
	Vec2 goalCoord = mapCoordFromPosition(touchLocation);
	log("playerCoord.x = %f, playerCoord.y = %f", playerCoord.x, playerCoord.y);
	log("goalCoord.x = %f, goalCoord.y = %f", goalCoord.x, goalCoord.y);
	if (playerCoord == goalCoord)
		return;
	bool findstatus = _astart->findPath(playerCoord, goalCoord);
	log("find the path status:findstatus = %d", findstatus);

	if (findstatus == true) {
		_findPath =  _astart->getPath();
		_findPath.pop_back();         //remove the start position
		_player->stopActionByTag(78);
		_walkToLast = false;
		_speedFactor = setSpeedFactor(1, 150);
		TileMap::walkSequenceToGoal(_player, touchLocation);
	} else {
		log("the path cannot be finded");
	}
	_astart->mapClear();
}

void TileMap::setViewPointInScreenByhand(Vec2 vec2)
{
	auto nodepos = this->getPosition();
	Size mapSize = _tileMap->getMapSize();
	Size tileSize = _tileMap->getTileSize();
	log("setViewPointInScreenByhand");
	_handPosition = nodepos;

	if (tileSize.width >= vec2.x) {
		_direction = TileMap::Direction::dir_left;
		this->schedule(schedule_selector(TileMap::myscheduleUpdate), 0.1);
	} else if ((_visibleSize.width-tileSize.width) <= vec2.x) {
		_direction = TileMap::Direction::dir_right;
		this->schedule(schedule_selector(TileMap::myscheduleUpdate), 0.1);
	}

	if (tileSize.height >= vec2.y) {
		_direction = TileMap::Direction::dir_down;
		this->schedule(schedule_selector(TileMap::myscheduleUpdate), 0.1);
	} else if ((_visibleSize.height-tileSize.height) <= vec2.y) {
		_direction = TileMap::Direction::dir_up;
		this->schedule(schedule_selector(TileMap::myscheduleUpdate), 0.1);
	}
}

void TileMap::setViewPointInScreenByhandEnd(void)
{
	this->unschedule(schedule_selector(TileMap::myscheduleUpdate));
}

void TileMap::myscheduleUpdate(float ft)
{
	Size mapSize = _tileMap->getMapSize();
	Size tileSize = _tileMap->getTileSize();

	if (TileMap::Direction::dir_left == _direction) {
		_handPosition.x = (_handPosition.x+_tileMap->getTileSize().width <= 0) ? (_handPosition.x+_tileMap->getTileSize().width) : _handPosition.x;
	} else if (TileMap::Direction::dir_right == _direction) {
		_handPosition.x = ((mapSize.width*tileSize.width-_visibleSize.width+_handPosition.x) >= _tileMap->getTileSize().width) ? (_handPosition.x-_tileMap->getTileSize().width) : _handPosition.x;
	} else if (TileMap::Direction::dir_down == _direction) {
		_handPosition.y = (_handPosition.y+_tileMap->getTileSize().height <= 0) ? (_handPosition.y+_tileMap->getTileSize().height) : _handPosition.y;
	} else if (TileMap::Direction::dir_up == _direction) {
		_handPosition.y = ((mapSize.height*tileSize.height-_visibleSize.height+_handPosition.y) >= _tileMap->getTileSize().height) ? (_handPosition.y-_tileMap->getTileSize().height) : _handPosition.y;
	}
	this->setPosition(_handPosition);
}

void TileMap::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();
//    SimpleAudioEngine::getInstance()->stopBackgroundMusic(); //Õ£÷π±≥æ∞“Ù¿÷

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
