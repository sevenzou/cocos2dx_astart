#include "SpriteScene.h"
#include "StartScene.h"
//#include "2d/CCSpriteBatchNode.h"
//USING_NS_CC;

Scene* AddSprites::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = AddSprites::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool AddSprites::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    _visibleSize =visibleSize;
    _origin = origin;
    /////////////////////////////
    auto startOneItem = MenuItemFont::create("StartGame",
    										   CC_CALLBACK_1(AddSprites::menuStartCallback, this));
	startOneItem->ignoreAnchorPointForPosition(false);
	startOneItem->setAnchorPoint(Point(0.5, 0.5));
	startOneItem->setPosition(Vec2(origin.x + visibleSize.width*3/8,
								origin.y + visibleSize.height*7/9));
	auto menuStart = Menu::create(startOneItem, NULL);
	menuStart->setPosition(Vec2::ZERO);
	this->addChild(menuStart, 1);

    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(AddSprites::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + visibleSize.height - closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    auto label = LabelTTF::create("Sprite", "Arial", 24);
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
    this->addChild(label, 1);

    auto sprite = Sprite::create("background.png");
    sprite->setScale(visibleSize.width/sprite->getContentSize().width,visibleSize.height/sprite->getContentSize().height);
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(sprite, 0);
    
//    _sprite1 = Sprite::createWithTexture(TextureCache::getInstance()->addImage("one.jpg"));
    _sprite1 = Sprite::create("one.png");
    _sprite1->setScale(0.5);
    _sprite1->setPosition(Vec2(visibleSize.width*2/6 + origin.x, visibleSize.height/4 + origin.y));
    this->addChild(_sprite1, 0);

//    _sprite2 = Sprite::createWithSpriteFrameName("two.jpg");
    _sprite2 = Sprite::create("two.jpg");
    _sprite2->setScale(0.25);
    _sprite2->setPosition(Vec2(visibleSize.width*2/6 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(_sprite2, 0);

//    _sprite3 = Sprite::createWithTexture(TextureCache::getInstance()->addImage("showahone.png"));
    _sprite3 = Sprite::create("showahtwo.jpg");
    _sprite3->setScale(0.05);
    _sprite3->setPosition(Vec2(visibleSize.width*4/5 + origin.x, visibleSize.height/4 + origin.y));
	this->addChild(_sprite3, 0);

//	_sprite4 = Sprite::createWithSpriteFrameName("showahtwo.jpg");
	_sprite4 = Sprite::create("showahtwo.jpg");
	_sprite4->setScale(0.05);
	_sprite4->setPosition(Vec2(visibleSize.width*4/5 + origin.x, visibleSize.height/2 + origin.y));
	this->addChild(_sprite4, 0);

	_sprite5 = Sprite::create("kill.png");
//	_sprite5->setScale(1.0);
	_sprite5->setPosition(Vec2(visibleSize.width*2/4 + origin.x, visibleSize.height/2 + origin.y));
	_sprite5->setVisible(false);
	this->addChild(_sprite5, 0);

	auto cache = SpriteFrameCache::getInstance();
//	cache->addSpriteFramesWithFile("TP/tp.plist"); //first way of addSpriteFramesWithFile
	cache->addSpriteFramesWithFile("TP/tp.plist","TP/tp.png"); //second way of addSpriteFramesWithFile
//	auto spriteFrame = cache->getSpriteFrameByName("airplane.png");//first way of createWithSpriteFrame
//	auto sprite6 = Sprite::createWithSpriteFrame(spriteFrame);	   //first way of createWithSpriteFrame
	auto sprite6 = Sprite::createWithSpriteFrameName("airplane.png"); //second way of createWithSpriteFrame
	sprite6->setPosition(Vec2(visibleSize.width*3/4 + origin.x, visibleSize.height*3/4 + origin.y));
	this->addChild(sprite6, 0);

	auto spriteFrame1 = cache->getSpriteFrameByName("kill.png");
	auto sprite7 = Sprite::createWithSpriteFrame(spriteFrame1);
	sprite7->setPosition(Vec2(visibleSize.width*2/4 + origin.x, visibleSize.height*2/4 + origin.y));
	this->addChild(sprite7, 0);

	for (int i=0; i<=2; i++) {
		auto sprite8 = Sprite::createWithSpriteFrame(spriteFrame1);
		sprite8->setPosition(Vec2(visibleSize.width*2/4+i*50 + origin.x, visibleSize.height*2/4 + origin.y));
		this->addChild(sprite8, 0);
	}

//	auto spBatchNode = SpriteBatchNode::create("eat.png", 17);
//	auto spBatchNode = SpriteBatchNode::createWithTexture(sprite7->getTexture(), 17);
//	spBatchNode->setPosition(Point::ZERO);
//	this->addChild(spBatchNode);
//	for (int i=0; i<=16; i++) {
//		auto sprite9 = Sprite::createWithTexture(spBatchNode->getTexture());
//		sprite9->setPosition(Vec2(visibleSize.width*CCRANDOM_0_1() + origin.x, visibleSize.height*CCRANDOM_0_1() + origin.y));
//		sprite9->setScale(0.3);
//		spBatchNode->addChild(sprite9, 0);
//	}

    return true;
}

void AddSprites::update(float dt)
{
	log("AddSprites::update");
	auto temp1 = abs(_sprite1->getPositionX()-_sprite3->getPositionX());
	auto temp2 = abs(_sprite2->getPositionX()-_sprite4->getPositionX());
	if (temp1 <= _sprite1->boundingBox().size.width/2) {
		_sprite3->setVisible(false);
	}

	if (temp2 <= _sprite2->boundingBox().size.width/2) {
		_sprite2->setVisible(false);
	}

	if (_sprite4->getPositionX() <= 0) {
		unscheduleUpdate();
		_sprite5->setVisible(true);
	}
}

void AddSprites::menuStartCallback(Ref* pSender)
{
	log("AddSprites::menuStartCallback");
	SimpleAudioEngine::getInstance()->playBackgroundMusic("kiss the rain.mp3", true); //²¥·Å±³¾°ÒôÀÖ
	scheduleUpdate();
	auto moveby3 = MoveBy::create(10, Point(-(_sprite3->getPositionX()),0));
	auto moveby4 = MoveBy::create(15, Point(-(_sprite4->getPositionX()),0));
	_sprite3->runAction(moveby3);
	_sprite4->runAction(moveby4);

}

void AddSprites::menuCloseCallback(Ref* pSender)
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
