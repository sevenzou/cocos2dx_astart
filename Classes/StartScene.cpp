#include "StartScene.h"
#include "GameScene.h"
#include "SpriteScene.h"
#include "SimpleAudioEngine.h"
#include "JumpScene.h"
#include "BarLoading.h"
#include "PaoTai.h"
#include "JumpMan.h"

int StartScene::_sceneCount = 0;

Scene* StartScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = StartScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool StartScene::init()
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
    auto startOneItem = MenuItemFont::create("1.Hoodle",
										   CC_CALLBACK_1(StartScene::menuStartOneCallback, this));
    startOneItem->ignoreAnchorPointForPosition(false);
    startOneItem->setAnchorPoint(Point(0.5, 0.5));
    startOneItem->setPosition(Vec2(_origin.x + _visibleSize.width*(1.0/6.0),_origin.y + _visibleSize.height*3/5));
    // create menu, it's an autorelease object
	auto menuOne = Menu::create(startOneItem, NULL);
	menuOne->setPosition(Vec2::ZERO);
	this->addChild(menuOne, 1);
	log("startOneItem->getFontSize()=%d",startOneItem->getFontSize());
//	startOneItem->setFontSize(12);

	auto startTwoItem = MenuItemFont::create("2.Sprites",
										   CC_CALLBACK_1(StartScene::menuStartTwoCallback, this));
	startTwoItem->setPosition(Vec2(_origin.x + _visibleSize.width*(1.0/6.0+(5.0/6.0)*(1.0/3.0)),_origin.y + _visibleSize.height*3/5));
	auto menuTwo = Menu::create(startTwoItem, NULL);
	menuTwo->setPosition(Vec2::ZERO);
	this->addChild(menuTwo, 1);

	auto startThreeItem = MenuItemFont::create("3.Jump",
											   CC_CALLBACK_1(StartScene::menuStartThreeCallback, this));
	startThreeItem->setPosition(Vec2(_origin.x + _visibleSize.width*(1.0/6.0+(5.0/6.0)*(2.0/3.0)),_origin.y + _visibleSize.height*3/5));
	auto menuThree = Menu::create(startThreeItem, NULL);
	menuThree->setPosition(Vec2::ZERO);
	this->addChild(menuThree, 1);

	auto startFourItem = MenuItemFont::create("4.PaoTai",
											   CC_CALLBACK_1(StartScene::menuStartFourCallback, this));
	startFourItem->setPosition(Vec2(_origin.x + _visibleSize.width*(1.0/6.0),_origin.y + _visibleSize.height*2.0/5.0));
	menuThree = Menu::create(startFourItem, NULL);
	menuThree->setPosition(Vec2::ZERO);
	this->addChild(menuThree, 1);

	startFourItem = MenuItemFont::create("5.JumpMan",
												   CC_CALLBACK_1(StartScene::menuStartFiveCallback, this));
	startFourItem->setPosition(Vec2(_origin.x + _visibleSize.width*(1.0/6.0+(5.0/6.0)*(1.0/3.0)),_origin.y + _visibleSize.height*2.0/5.0));
	menuThree = Menu::create(startFourItem, NULL);
	menuThree->setPosition(Vec2::ZERO);
	this->addChild(menuThree, 1);

	auto closeItem = MenuItemFont::create(
										   "StopGame",
										   CC_CALLBACK_1(StartScene::menuStopCallback, this));
	closeItem->setPosition(Vec2(_origin.x + _visibleSize.width-closeItem->getContentSize().width,
								_origin.y + _visibleSize.height-closeItem->getContentSize().height));
	auto stopMenu = Menu::create(closeItem, NULL);
	stopMenu->setPosition(Vec2::ZERO);
	this->addChild(stopMenu, 1);

    SimpleAudioEngine::getInstance()->preloadBackgroundMusic("kiss the rain.mp3");

//    auto dispatcher = Director::getInstance()->getEventDispatcher();
//    auto listener = EventListenerTouchOneByOne::create();
//    listener->onTouchBegan = CC_CALLBACK_2(StartScene::onTouchBegan,this);
//    listener->onTouchMoved = CC_CALLBACK_2(StartScene::onTouchMoved,this);
//    listener->onTouchEnded = CC_CALLBACK_2(StartScene::onTouchEnded,this);
//    listener->setSwallowTouches(true);//²»ÏòÏÂ´«µİ´¥Ãş
//    dispatcher->addEventListenerWithSceneGraphPriority(listener,this);

//    SimpleAudioEngine::getInstance()->stopBackgroundMusic(); //Í£Ö¹±³¾°ÒôÀÖ
//    SimpleAudioEngine::getInstance()->stopEffect(_soundId); //Í£Ö¹ÒôĞ§
    
    return true;
}

bool StartScene::onTouchBegan(Touch* touch, Event* event)
{
	return true;
}

void StartScene::onTouchMoved(Touch* touch, Event* event)
{
	log("onTouchMoved");
}

void StartScene::onTouchEnded(Touch* touch, Event* event)
{
	log("StartScene::onTouchEnded");
	log("StartScene::onTouchEnded _sceneCount=%d",StartScene::_sceneCount);
	if (StartScene::_sceneCount == 0) {
		auto scene = GameScene::createScene();
		auto transitions = TransitionRotoZoom::create(1.2f, scene);
		Director::getInstance()->replaceScene(transitions);
	}
}

void StartScene::menuStartOneCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

//    Director::getInstance()->end();
    auto scene = GameScene::createScene();
	auto transitions = TransitionRotoZoom::create(1.2f, scene);
	Director::getInstance()->replaceScene(transitions);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void StartScene::menuStartTwoCallback(Ref* pSender)
{
//    Director::getInstance()->end();
    auto scene = AddSprites::createScene();
	auto transitions = TransitionJumpZoom::create(1.2f, scene);
	Director::getInstance()->replaceScene(transitions);

}

void StartScene::menuStartThreeCallback(Ref* pSender)
{
//	auto scene = JumpScene::createScene();
	auto scene = BarLoading::createScene();

//	auto transitions = TransitionZoomFlipX::create(1.2f, scene);
//	Director::getInstance()->replaceScene(transitions);

	Director::getInstance()->replaceScene(scene);
}

void StartScene::menuStartFourCallback(Ref* pSender)
{
	auto scene = PaoTai::createScene();
	auto transitions = TransitionSlideInL::create(1.2f, scene);
	Director::getInstance()->replaceScene(transitions);
}

void StartScene::menuStartFiveCallback(Ref* pSender)
{
	auto scene = JumpMan::createScene();
	auto transitions = TransitionSlideInL::create(1.2f, scene);
	Director::getInstance()->replaceScene(transitions);
}

void StartScene::menuStopCallback(Ref* pSender)
{
	Director::getInstance()->end();
}

