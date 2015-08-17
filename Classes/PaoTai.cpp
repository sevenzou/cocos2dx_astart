#include "PaoTai.h"
#include "StartScene.h"

Scene* PaoTai::createScene()
{
    auto scene = Scene::create();
    auto layer = PaoTai::create();
    scene->addChild(layer);
    return scene;
}

// on "init" you need to initialize your instance
bool PaoTai::init()
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
                                           CC_CALLBACK_1(PaoTai::menuCloseCallback, this));
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + visibleSize.height -closeItem->getContentSize().height/2));

    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    auto label = LabelTTF::create("Sprite", "Arial", 24);
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
    this->addChild(label, 1);

    _sprite_1 = Sprite::create("one.png");
    _sprite_1->setScale(1.0);
    _sprite_1->setPosition(Vec2(visibleSize.width*(1.0/4.0) + origin.x, visibleSize.height*(2.0/3.0) + origin.y));
    _sprite_1->setVisible(false);
    this->addChild(_sprite_1, 0);
    
    _sprite_2 = Sprite::create("two.jpg");
    _sprite_2->setScale(0.5);
    _sprite_2->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    _sprite_2->setVisible(false);
//    _sprite_2->setTag(10);
	this->addChild(_sprite_2, 0);

//    auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(PaoTai::onTouchBegan,this);
	listener->onTouchMoved = CC_CALLBACK_2(PaoTai::onTouchMoved,this);
	listener->onTouchEnded = CC_CALLBACK_2(PaoTai::onTouchEnded,this);
	listener->setSwallowTouches(true);//不向下传递触摸
//	dispatcher->addEventListenerWithSceneGraphPriority(listener,_sprite_1);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,_sprite_1);
    return true;
}
bool PaoTai::onTouchBegan(Touch* touch, Event* event)
{
	Vec2 vec2_1 = touch->getLocation();
	Sprite* target = (Sprite *)event->getCurrentTarget();
	Vec2 vec2_2 = target->convertTouchToNodeSpace(touch);
	Rect rect = target->getBoundingBox();

	if (rect.containsPoint(vec2_1)) {//判断触摸点是否在目标的范围内
		log("onTouchBegan return true");
		_sprite_1->setPosition(vec2_1);
		_sprite_1->setVisible(true);
		return true;
	} else {
		log("onTouchBegan return false");
	    return false;
	}

//	if (vec2.y >= _visibleSize.height*(2.0/3.0) && vec2.x <= _visibleSize.width*(1.0/4.0)) {
//		_sprite_1->setPosition(vec2);
//		_sprite_1->setVisible(true);
//	}
//	return true;
}

void PaoTai::onTouchMoved(Touch* touch, Event* event)
{
	log("onTouchMoved");
	Vec2 vec2 = touch->getLocation();
	_sprite_1->setPosition(vec2);
}

void PaoTai::onTouchEnded(Touch* touch, Event* event)
{
	log("GameScene::onTouchEnded");
	Vec2 vec2 = touch->getLocation();
//	auto sprite = Sprite::create();
	auto sprite = Sprite::create("two.jpg");
	sprite->setScale(1.0);
	sprite->setVisible(true);
	sprite->setPosition(vec2);
	this->addChild(sprite, 0);
	//手动添加
/**/
	auto animation = Animation::create();
	animation->addSpriteFrameWithFile("bkg1.png");
	animation->addSpriteFrameWithFile("bkg2.png");
	// should last 2.8 seconds. And there are 14 frames.
	animation->setDelayPerUnit(2.8f / 14.0f);
	animation->setRestoreOriginalFrame(true);
//		animation->setLoops(-1);
	animation->setLoops(7);
	auto action = Animate::create(animation);
	sprite->runAction(Sequence::create(action, NULL));
//		sprite->runAction(Sequence::create(action, action->reverse(), NULL));

/*
	//文件添加
	auto cache = AnimationCache::getInstance();
	cache->addAnimationsWithFile("TP/tp.plist");
	auto animation2 = cache->getAnimation("frames");
	animation2->setLoops(-1);
	auto action2 = Animate::create(animation2);
	sprite->runAction(Sequence::create(action2, action2->reverse(), NULL));
*/
	_sprite_1->setPosition(Vec2(_visibleSize.width*(1.0/4.0) + _origin.x, _visibleSize.height*(2.0/3.0) + _origin.y));
	_sprite_1->setVisible(false);

}



void PaoTai::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

//    Director::getInstance()->end();
    SimpleAudioEngine::getInstance()->stopBackgroundMusic(); //停止背景音乐
	auto scene = StartScene::createScene();
	auto transitions = TransitionRotoZoom::create(1.2f, scene);
	Director::getInstance()->replaceScene(transitions);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
