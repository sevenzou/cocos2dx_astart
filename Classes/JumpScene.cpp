#include "JumpScene.h"
#include "StartScene.h"
//#include "ui/UIWidget.h"

//USING_NS_CC;

Scene* JumpScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = JumpScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool JumpScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    _visibleSize = visibleSize;
    _origin = origin;
    _jumpUpItem = MenuItemFont::create("JumpUp",
										CC_CALLBACK_1(JumpScene::menuJumpUpCallback, this));
    _jumpUpItem->ignoreAnchorPointForPosition(false);
    _jumpUpItem->setAnchorPoint(Point(0.5, 0.5));
    _jumpUpItem->setPosition(Vec2(origin.x + visibleSize.width*(2.0/10.0),
								origin.y + visibleSize.height*(7.0/9.0)));
	auto jumpUpMenu = Menu::create(_jumpUpItem, NULL);
	jumpUpMenu->setPosition(Vec2::ZERO);
	this->addChild(jumpUpMenu, 1);

	_jumpByItem = MenuItemFont::create("JumpBy",
										CC_CALLBACK_1(JumpScene::menuJumpByCallback, this));
	_jumpByItem->ignoreAnchorPointForPosition(false);
	_jumpByItem->setAnchorPoint(Point(0.5, 0.5));
	_jumpByItem->setPosition(Vec2(origin.x + visibleSize.width*(4.0/10.0),
								origin.y + visibleSize.height*(7.0/9.0)));
	jumpUpMenu = Menu::create(_jumpByItem, NULL);
	jumpUpMenu->setPosition(Vec2::ZERO);
	this->addChild(jumpUpMenu, 1);

	_jumpToItem = MenuItemFont::create("JumpTo",
										CC_CALLBACK_1(JumpScene::menuJumpToCallback, this));
	_jumpToItem->ignoreAnchorPointForPosition(false);
	_jumpToItem->setAnchorPoint(Point(0.5, 0.5));
	_jumpToItem->setPosition(Vec2(origin.x + visibleSize.width*(6.0/10.0),
								origin.y + visibleSize.height*(7.0/9.0)));
	jumpUpMenu = Menu::create(_jumpToItem, NULL);
	jumpUpMenu->setPosition(Vec2::ZERO);
	this->addChild(jumpUpMenu, 1);

	_jumpMoveItem = MenuItemFont::create("JumpMove",
										CC_CALLBACK_1(JumpScene::menuMoveCallback, this));
	_jumpMoveItem->ignoreAnchorPointForPosition(false);
	_jumpMoveItem->setAnchorPoint(Point(0.5, 0.5));
	_jumpMoveItem->setPosition(Vec2(origin.x + visibleSize.width*(8.0/10.0),
								origin.y + visibleSize.height*(7.0/9.0)));
	jumpUpMenu = Menu::create(_jumpMoveItem, NULL);
	jumpUpMenu->setPosition(Vec2::ZERO);
	this->addChild(jumpUpMenu, 1);

	_jumpSequenceItem = MenuItemFont::create("SequenceAction",
											CC_CALLBACK_1(JumpScene::menuSequenceCallback, this));
	_jumpSequenceItem->ignoreAnchorPointForPosition(false);
	_jumpSequenceItem->setAnchorPoint(Point(0.5, 0.5));
	_jumpSequenceItem->setPosition(Vec2(origin.x + visibleSize.width*(8.0/10.0),
								origin.y + visibleSize.height*(6.0/9.0)));
	jumpUpMenu = Menu::create(_jumpSequenceItem, NULL);
	jumpUpMenu->setPosition(Vec2::ZERO);
	this->addChild(jumpUpMenu, 1);

    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(JumpScene::menuCloseCallback, this));
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + visibleSize.height -closeItem->getContentSize().height/2));
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

//    LabelAtlas
//    Label
//    LabelBMFont
    _labelTTF = LabelTTF::create("游戏", "Arial", 24);
    _labelTTF->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - _labelTTF->getContentSize().height));
    this->addChild(_labelTTF, 1);
//    TTFConfig config2("fonts/simsunb.ttf", 24);
//    _label = Label::createWithTTF(config2,"中文字库",TextHAlignment::LEFT);
//    _label->setPosition(Vec2(origin.x + visibleSize.width/2,300));
//    this->addChild(_label, 2);

    _huaBanSprite_1 = Sprite::create("bkg1.png");
//    _huaBanSprite_1->setScale(0.3);
    _huaBanSprite_1->setPosition(Vec2(visibleSize.width/5 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(_huaBanSprite_1, 0);
    
    _huaBanSprite_2 = Sprite::create("huaban.png");
	_huaBanSprite_2->setScale(0.3);
	_huaBanSprite_2->setPosition(Vec2(visibleSize.width/5 + origin.x, visibleSize.height/4 + origin.y));
//	_huaBanSprite_2->setVisible(false);
	this->addChild(_huaBanSprite_2, 0);


//	Button* pButton = Button::create();
	_plusItem = MenuItemImage::create(
	        "CloseNormal.png",
	        "CloseSelected.png");
	_minusItem = MenuItemImage::create(
			"bkg1.png",
			"bkg2.png");
	_plusItem->setScale(1.5);
	_minusItem->setScale(1.5);
	MenuItemToggle *toggleItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(JumpScene::plusMinusButtonCallback, this), _plusItem, _minusItem, NULL);
	auto toggleMenu = Menu::create(toggleItem, NULL);
//	toggleMenu->setScale(2);
	toggleMenu->setPosition(Vec2(_minusItem->boundingBox().size.width/2, visibleSize.height-_minusItem->boundingBox().size.height/2));
	this->addChild(toggleMenu, 1);
    return true;
}

void JumpScene::plusMinusButtonCallback(Ref* pSender)
{
	 MenuItemToggle *toggleItem = (MenuItemToggle *)pSender;
	if (toggleItem->getSelectedItem() == _plusItem) {
		_labelTTF->setString("Visible button: +游戏");
	} else if (toggleItem->getSelectedItem() == _minusItem) {
		_labelTTF->setString("Visible button: -游戏");
	}
}

void JumpScene::menuJumpUpCallback(Ref* pSender)
{
//	CallFunc* callFunc_1 = CallFunc::create(CC_CALLBACK_0(JumpScene::disableTouchCallFunc1,this,_jumpUpItem));
//	CallFunc* callFunc_2 = CallFunc::create(CC_CALLBACK_0(JumpScene::enableTouchCallFunc1,this,_jumpUpItem));
	CallFuncN* callFuncN_1 = CallFuncN::create(CC_CALLBACK_1(JumpScene::disableTouchCallFuncN,this,_jumpUpItem));
	CallFuncN* callFuncN_2 = CallFuncN::create(CC_CALLBACK_1(JumpScene::enableTouchCallFuncN,this,_jumpUpItem));
//	CallFunc* callFuncN_1 = CallFuncN::create(std::bind(&JumpScene::disableTouchCallFunc1,this, _jumpUpItem));
//	CallFunc* callFuncN_2 = CallFuncN::create(std::bind(&JumpScene::enableTouchCallFunc1,this,_jumpUpItem));

//	JumpScene::callFunction(callFuncN_1, callFuncN_2, _jumpUpItem);

	JumpScene::allSpritePositionInit(Vec2(_visibleSize.width/5 + _origin.x, _visibleSize.height/2 + _origin.y),
										Vec2(_visibleSize.width/5 + _origin.x, _visibleSize.height/4 + _origin.y));
	auto jumpUp = JumpBy::create(2,Vec2(0, 0),80,1);
	_huaBanSprite_1->runAction(Sequence::create(callFuncN_1,jumpUp,callFuncN_2,NULL));
//	_huaBanSprite_1->runAction(RepeatForever::create(jumpUp));

}

void JumpScene::menuJumpByCallback(Ref* pSender)
{
	JumpScene::allSpritePositionInit(Vec2(_visibleSize.width/5 + _origin.x, _visibleSize.height/2 + _origin.y),
										Vec2(_visibleSize.width/5 + _origin.x, _visibleSize.height/4 + _origin.y));
	CallFunc* callFunc_1 = CallFunc::create(CC_CALLBACK_0(JumpScene::disableTouchCallFunc1,this,_jumpByItem));
	CallFunc* callFunc_2 = CallFunc::create(CC_CALLBACK_0(JumpScene::enableTouchCallFunc1,this,_jumpByItem));

	auto jumpBy = JumpBy::create(1.5,Vec2(150, 0),80,3);
	auto jumpReverse = jumpBy->reverse();
//	_huaBanSprite_1->runAction(Sequence::create(jumpBy,NULL));
	_huaBanSprite_2->runAction(Sequence::create(callFunc_1,jumpBy,jumpReverse,jumpBy,jumpReverse,callFunc_2,NULL));
}

void JumpScene::menuJumpToCallback(Ref* pSender)
{
	JumpScene::allSpritePositionInit(Vec2(_visibleSize.width/5 + _origin.x, _visibleSize.height/2 + _origin.y),
										Vec2(_visibleSize.width/5 + _origin.x, _visibleSize.height/4 + _origin.y));
	CallFunc* callFunc_1 = CallFunc::create(CC_CALLBACK_0(JumpScene::disableTouchCallFunc1,this,_jumpToItem));
	CallFunc* callFunc_2 = CallFunc::create(CC_CALLBACK_0(JumpScene::enableTouchCallFunc1,this,_jumpToItem));

	auto jumpTo = JumpTo::create(2,Vec2(700, 200),50,5);
	_huaBanSprite_2->runAction(Sequence::create(callFunc_1,jumpTo,callFunc_2,NULL));
}

void JumpScene::menuMoveCallback(Ref* pSender)
{
	JumpScene::allSpritePositionInit(Vec2(_visibleSize.width/5 + _origin.x, _visibleSize.height/2 + _origin.y),
										Vec2(_visibleSize.width/5 + _origin.x, _visibleSize.height/4 + _origin.y));
	auto pArrayTo = PointArray::create(7);
	pArrayTo->addControlPoint(Vec2(100,100));
	pArrayTo->addControlPoint(Vec2(200,100));
	pArrayTo->addControlPoint(Vec2(200,200));
	pArrayTo->addControlPoint(Vec2(300,200));
	pArrayTo->addControlPoint(Vec2(300,100));
	auto pArrayBy = PointArray::create(7);
	pArrayBy->addControlPoint(Vec2(0,0));
	pArrayBy->addControlPoint(Vec2(100,0));
	pArrayBy->addControlPoint(Vec2(100,-100));
	pArrayBy->addControlPoint(Vec2(200,-100));
	pArrayBy->addControlPoint(Vec2(200,0));
	pArrayBy->addControlPoint(Vec2(300,0));
	pArrayBy->addControlPoint(Vec2(300,-100));
	pArrayBy->addControlPoint(Vec2(400,-100));

	CallFunc* callFunc_1 = CallFunc::create(CC_CALLBACK_0(JumpScene::disableTouchCallFunc1,this,_jumpMoveItem));
	CallFunc* callFunc_2 = CallFunc::create(CC_CALLBACK_0(JumpScene::enableTouchCallFunc1,this,_jumpMoveItem));

	auto cardinalSplineTo = CardinalSplineTo::create(1,pArrayTo,1);
	auto cardinalSplineBy = CardinalSplineBy::create(3,pArrayBy,0.5);

//	_huaBanSprite_1->runAction(Sequence::create(callFunc_1, cardinalSplineTo, NULL));
	_huaBanSprite_2->runAction(Sequence::create(callFunc_1, cardinalSplineBy, callFunc_2, NULL));
}

void JumpScene::menuSequenceCallback(cocos2d::Ref* pSender)
{
	JumpScene::allSpritePositionInit(Vec2(_visibleSize.width/5 + _origin.x, _visibleSize.height/2 + _origin.y),
											Vec2(_visibleSize.width/5 + _origin.x, _visibleSize.height/4 + _origin.y));
	Vec2 vec2_1 = _huaBanSprite_1->getPosition();
	Vec2 vec2_2 = _huaBanSprite_2->getPosition();

	CallFunc* callFunc_1 = CallFunc::create(CC_CALLBACK_0(JumpScene::disableTouchCallFunc1,this,_jumpSequenceItem));
	CallFunc* callFunc_2 = CallFunc::create(CC_CALLBACK_0(JumpScene::enableTouchCallFunc1,this,_jumpSequenceItem));

	ccBezierConfig bezier_1;
	bezier_1.controlPoint_1 = Point(vec2_1.x+100, vec2_1.y+50);
	bezier_1.controlPoint_2 = Point(vec2_1.x+200, vec2_1.y-200);
	bezier_1.endPosition = Point(vec2_1.x+450, vec2_1.y);
	auto bezierAction_1 = BezierTo::create(0.5f, bezier_1);
	ccBezierConfig bezier_2;
	bezier_2.controlPoint_1 = Point(vec2_2.x+100, vec2_2.y+50);
	bezier_2.controlPoint_2 = Point(vec2_2.x+200, vec2_2.y-200);
	bezier_2.endPosition = Point(vec2_2.x+450, vec2_2.y);
	auto bezierAction_2 = BezierTo::create(0.5f, bezier_2);

	auto scaleTo = ScaleTo::create(0.5f,2.0f);
	auto scaleBy = ScaleBy::create(0.5f,2.0f);
	auto blink_1 = Blink::create(3.0f,5);
	auto blink_2 = Blink::create(3.0f,5);
	auto rotateBy = RotateBy::create(2.0f,720);
	auto rotateTo = RotateTo::create(3.0f,180);
//	EaseSineIn
//	_huaBanSprite_1->runAction(bezierAction_1);
//	_huaBanSprite_2->runAction(bezierAction_2);
	int count = ceil(CCRANDOM_0_1()*1000);

//	_huaBanSprite_1->runAction(Sequence::create(bezierAction_1,scaleTo,blink_1,NULL));
//	_huaBanSprite_2->runAction(Sequence::create(bezierAction_2,scaleBy,blink_2,NULL));
//	_huaBanSprite_1->runAction(EaseSineIn::create((Spawn::create(bezierAction_1,scaleTo,NULL))));
//	_huaBanSprite_2->runAction(Spawn::create(bezierAction_2,scaleBy,NULL));
//	_huaBanSprite_1->runAction(Sequence::create(bezierAction_1,scaleTo,Spawn::create(blink_1,rotateBy,NULL),NULL));
//	_huaBanSprite_2->runAction(Sequence::create(bezierAction_2,scaleBy,Spawn::create(blink_2,rotateTo,NULL),NULL));
	_huaBanSprite_1->runAction(Sequence::create(callFunc_1,bezierAction_1,scaleTo,Spawn::create(blink_1,Repeat::create(rotateBy,2),NULL),callFunc_2,NULL));
	_huaBanSprite_2->runAction(Sequence::create(callFunc_1,bezierAction_2,scaleBy,Spawn::create(blink_2,rotateTo,NULL),callFunc_2,NULL));

}

void JumpScene::callFunction(CallFunc* callFuncN_1, CallFunc* callFuncN_2, Node* pSender)
{
	callFuncN_1 = CallFunc::create(CC_CALLBACK_0(JumpScene::disableTouchCallFunc1,this,pSender));
	callFuncN_2 = CallFunc::create(CC_CALLBACK_0(JumpScene::enableTouchCallFunc1,this,pSender));

}

void JumpScene::disableTouchCallFunc(void)
{
}

void JumpScene::enableTouchCallFunc(void)
{
}

void JumpScene::disableTouchCallFunc1(Node* pSender)
{
	log("JumpScene::disableTouchCallFunc1");
	MenuItemFont* menuItem = (MenuItemFont *)pSender;
	menuItem->setEnabled(false);

}

void JumpScene::enableTouchCallFunc1(Node* pSender)
{
	log("JumpScene::enableTouchCallFunc1");
	MenuItemFont* menuItem = (MenuItemFont *)pSender;
	menuItem->setEnabled(true);

}
void JumpScene::disableTouchCallFuncN(Node* pSender1, Node* pSender)
{
	log("JumpScene::disableTouchCallFuncN");
	MenuItemFont* menuItem = (MenuItemFont *)pSender;
	menuItem->setEnabled(false);

}

void JumpScene::enableTouchCallFuncN(Node* pSender1, Node* pSender)
{
	log("JumpScene::enableTouchCallFuncN");
	MenuItemFont* menuItem = (MenuItemFont *)pSender;
	menuItem->setEnabled(true);

}

void JumpScene::allSpritePositionInit(Vec2 vec2_1, Vec2 vec2_2)
{
	_huaBanSprite_1->setPosition(vec2_1);
	_huaBanSprite_2->setPosition(vec2_2);
//	_huaBanSprite_1->setScale(0.3);
	_huaBanSprite_2->setScale(0.3);
}

void JumpScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

//    Director::getInstance()->end();
    SimpleAudioEngine::getInstance()->stopBackgroundMusic(); //ֹͣ��������
	auto scene = StartScene::createScene();
	auto transitions = TransitionRotoZoom::create(1.2f, scene);
	Director::getInstance()->replaceScene(transitions);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
