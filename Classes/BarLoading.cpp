#include "BarLoading.h"
#include "StartScene.h"
#include "JumpScene.h"

Scene* BarLoading::createScene()
{
    auto scene = Scene::create();
    auto layer = BarLoading::create();
    scene->addChild(layer);

    return scene;
}

// on "init" you need to initialize your instance
bool BarLoading::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size _visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 _origin = Director::getInstance()->getVisibleOrigin();

//    auto closeItem = MenuItemImage::create(
//                                           "CloseNormal.png",
//                                           "CloseSelected.png",
//                                           CC_CALLBACK_1(BarLoading::menuCloseCallback, this));
//
//	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
//                                origin.y + closeItem->getContentSize().height/2));
//
//    auto menu = Menu::create(closeItem, NULL);
//    menu->setPosition(Vec2::ZERO);
//    this->addChild(menu, 1);

//    auto label = LabelTTF::create("Sprite", "Arial", 24);
//    label->setPosition(Vec2(origin.x + visibleSize.width/2,
//                            origin.y + visibleSize.height - label->getContentSize().height));
//    this->addChild(label, 1);

    _spriteYellow = Sprite::create("yellow.jpg");
    _spriteYellow->setScale(_visibleSize.width/_spriteYellow->getContentSize().width*(2.0/3.0),_visibleSize.height/_spriteYellow->getContentSize().height*(1.0/12.0));
    _spriteYellow->setPosition(Vec2(_visibleSize.width/2 + _origin.x, _visibleSize.height/2 + _origin.y));
    this->addChild(_spriteYellow, 0);
    
    _spriteRed = Sprite::create("red.jpg");
//    _spriteRed->setScale(_visibleSize.width/_spriteRed->getContentSize().width*(2.0/3.0),_visibleSize.height/_spriteRed->getContentSize().height*(1.0/12.0));
//    _spriteRed->setPosition(Vec2(_visibleSize.width/2 + _origin.x, _visibleSize.height/2 + _origin.y));
//	this->addChild(_spriteRed, 0);

	auto progresstimer = ProgressTimer::create(_spriteRed);
	progresstimer->setTag(11);
	progresstimer->setScale(_visibleSize.width/_spriteRed->getContentSize().width*(2.0/3.0),_visibleSize.height/_spriteRed->getContentSize().height*(1.0/12.0));
	progresstimer->setPosition(Vec2(_visibleSize.width/2 + _origin.x, _visibleSize.height/2 + _origin.y));
	progresstimer->setType(progresstimer->Type::BAR);//	kCCProgressTimerTypeBar
	progresstimer->setMidpoint(Vec2(0,0));
	progresstimer->setBarChangeRate(Vec2(1,0));
	this->addChild(progresstimer, 0);

	progresstimer->setPercentage(0);
	auto progressTo = ProgressTo::create(1,100);
	progresstimer->runAction(progressTo);

	scheduleUpdate();

    return true;
}

void BarLoading::update(float dt)
{
	ProgressTimer* progresstimer = (ProgressTimer*)this->getChildByTag(11);
	auto count = progresstimer->getPercentage();
	if (count >= 100) {
		unscheduleUpdate();
		auto scene = JumpScene::createScene();
		auto transitions = TransitionZoomFlipY::create(1.2f, scene);
		Director::getInstance()->replaceScene(transitions);
	}
}

void BarLoading::menuCloseCallback(Ref* pSender)
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
