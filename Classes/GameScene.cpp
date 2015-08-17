#include "GameScene.h"
#include "StartScene.h"
#include "SimpleAudioEngine.h"
#include <math.h>


Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    _visibleSize = visibleSize;
    _origin = origin;
    _statusX = true;
    _statusY = true;
    StartScene::_sceneCount++;
	SimpleAudioEngine::getInstance()->playBackgroundMusic("kiss the rain.mp3", true); //²¥·Å±³¾°ÒôÀÖ

	auto closeItem = MenuItemImage::create(
										   "CloseNormal.png",
										   "CloseSelected.png",
										   CC_CALLBACK_1(GameScene::menuCloseCallback, this));

	closeItem->setPosition(Vec2(_origin.x + _visibleSize.width - closeItem->getContentSize().width/2 ,
								_origin.y + _visibleSize.height - closeItem->getContentSize().height/2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	auto label = LabelTTF::create("Hoodle", "Arial", 24);

	// position the label on the center of the screen
	label->setPosition(Vec2(_origin.x + _visibleSize.width/2,
							_origin.y + _visibleSize.height - label->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(label, 1);

	// add "GameScene" splash screen"
	_sprite = Sprite::create("airplane.png");
	_scale = 0.1;
	_sprite->setScale(_scale);
	// position the sprite on the center of the screen
	_sprite->setPosition(Vec2(_visibleSize.width/2 + _origin.x, _visibleSize.height/2 + _origin.y));

	// add the sprite as a child to this layer
	this->addChild(_sprite, 0);

	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan,this);
	listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved,this);
	listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded,this);
	listener->setSwallowTouches(true);//²»ÏòÏÂ´«µÝ´¥Ãþ
	dispatcher->addEventListenerWithSceneGraphPriority(listener,this);
    //SimpleAudioEngine::getInstance()->stopBackgroundMusic(); //Í£Ö¹±³¾°ÒôÀÖ
    //SimpleAudioEngine::getInstance()->stopEffect(_soundId); //Í£Ö¹ÒôÐ§
	scheduleUpdate();
	schedule(schedule_selector(GameScene::gameUpdate), 1.0f, kRepeatForever, 0);

    return true;
}

void GameScene::gameSceneInit()
{
	log("GameScene::gameSceneInit");
//	GameScene::_scene0 = Scene::create();
//	auto transitions = TransitionRotoZoom::create(1.2f, GameScene::_scene0);
//	Director::getInstance()->replaceScene(transitions);
	StartScene::_sceneCount++;
	log("GameScene::gameSceneInit StartScene::_sceneCount=%d",StartScene::_sceneCount);
}
void GameScene::update(float dt)
{
	Vec2 vec2 = _sprite->getPosition();

	log("GameScene::update vec2.x=%f",vec2.x);
	log("GameScene::update vec2.y=%f",vec2.y);
	log("GameScene::update _statusX=%d",_statusX);
	log("GameScene::update _statusY=%d",_statusY);
	log("GameScene::update _origin.x+_visibleSize.width=%f",_origin.x+_visibleSize.width);
	log("GameScene::update _origin.y+_visibleSize.height=%f",_origin.y+_visibleSize.height);

	log("GameScene::update _sprite->boundingBox().width/2=%f",ceil(_sprite->boundingBox().size.width/2));
	log("GameScene::update _sprite->boundingBox().size.width/2=%f",ceil(_sprite->boundingBox().size.width/2));

//	float topX = ceil(_origin.x+_visibleSize.width-_sprite->boundingBox().size.width/2);
//	float topY = ceil(_origin.y+_visibleSize.height-_sprite->boundingBox().size.height/2);
//	float bottomX = ceil(_origin.x+0+_sprite->boundingBox().size.width/2);
//	float bottomY = ceil(_origin.y+0+_sprite->boundingBox().size.height/2);
	float topX = ceil(_origin.x+_visibleSize.width);
	float topY = ceil(_origin.y+_visibleSize.height);
	float bottomX = ceil(_origin.x+0);
	float bottomY = ceil(_origin.y+0);

	if (_sprite->boundingBox().size.width >= _origin.x+_visibleSize.width
		|| _sprite->boundingBox().size.height >= _origin.y+_visibleSize.height) {
		log("GameScene::update menuCloseCallback");
		unscheduleUpdate();
		SimpleAudioEngine::getInstance()->stopBackgroundMusic(); //Í£Ö¹±³¾°ÒôÀÖ
		auto scene = StartScene::createScene();
		auto transitions = TransitionSlideInL::create(1.2f, scene);
		Director::getInstance()->replaceScene(transitions);
	}

	if ((vec2.x <= topX && vec2.x >= bottomX)
		|| (vec2.y <= topY && vec2.y >= bottomY)) {
		if (_statusX == true)
			vec2.x++;
		else if (_statusX == false)
			vec2.x--;

		if (_statusY == true)
			vec2.y++;
		else if (_statusY == false)
			vec2.y--;
	}

	if (vec2.x == topX || vec2.x == bottomX) {
		if (_statusX == true)
			_statusX = false;
		else if (_statusX == false)
			_statusX = true;
		_scale += 0.1;
		_sprite->setScale(_scale);
//		topX = ceil(_origin.x+_visibleSize.width-_sprite->boundingBox().size.width/2);
//		bottomX = ceil(_origin.x+0+_sprite->boundingBox().size.width/2);
//		if (vec2.x > topX)
//			topX = vec2.x;
//		else if (vec2.x < bottomX)
//			bottomX = vec2.x;
	}
	if (vec2.y == topY || vec2.y == bottomY) {
		log(" _statusY=%d",_statusY);
		if (_statusY == true)
			_statusY = false;
		else if (_statusY == false)
			_statusY = true;
		_scale += 0.1;
		_sprite->setScale(_scale);
//		topY = ceil(_origin.y+_visibleSize.height-_sprite->boundingBox().size.height/2);
//		bottomY = ceil(_origin.y+0+_sprite->boundingBox().size.height/2);
//		if (vec2.y <= topY)
//			topY = vec2.y;
//		else if (vec2.y < bottomY)
//			bottomY = vec2.y;
	}

	_sprite->setPosition(vec2);

}

void GameScene::gameUpdate(float dt)
{

}

bool GameScene::onTouchBegan(Touch* touch, Event* event)
{
	return true;
}

void GameScene::onTouchMoved(Touch* touch, Event* event)
{
	log("onTouchMoved");
}

void GameScene::onTouchEnded(Touch* touch, Event* event)
{
	log("GameScene::onTouchEnded");
	log("GameScene::onTouchEnded StartScene::_sceneCount=%d",StartScene::_sceneCount);
	if (StartScene::_sceneCount != 0) {
		GameScene::gameSceneInit();
	}
}

void GameScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

//    Director::getInstance()->end();
    SimpleAudioEngine::getInstance()->stopBackgroundMusic(); //Í£Ö¹±³¾°ÒôÀÖ
    auto scene = StartScene::createScene();
	auto transitions = TransitionRotoZoom::create(1.2f, scene);
	Director::getInstance()->replaceScene(transitions);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
