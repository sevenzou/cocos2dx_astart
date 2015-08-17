#include "JumpMan.h"
#include "StartScene.h"
#include "SimpleAudioEngine.h"
#include "Manager.h"
#include <sstream>
#include <iostream>
#include <string>
#include "network/HttpClient.h"
#include "network/HttpRequest.h"

using namespace std;
using namespace cocos2d::network;

Scene* JumpMan::createScene()
{
    auto scene = Scene::create();
    auto layer = JumpMan::create();
    scene->addChild(layer);
    return scene;
}

bool JumpMan::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    _visibleSize = visibleSize;
    _origin = origin;
    _beginAgain = 0;
//    _maxScore = JumpMan::readData("score");
    _score = 0;
    _maxScore = UserDefault::getInstance()->getIntegerForKey("score");
	log("score = %d", _maxScore);
    auto layercolor = LayerColor::create(Color4B::WHITE);
    this->addChild(layercolor);

//    std::string file = "TileMap.tmx";
//	auto str = String::createWithContentsOfFile(FileUtils::getInstance()->fullPathForFilename(file.c_str()).c_str());
//	_tileMap = TMXTiledMap::createWithXML(str->getCString(),"");
    _tileMap = TMXTiledMap::create("TileMap1.tmx");
//	_tileMap->setPosition(Vec2(0,0));
    _tileMap->setScale(_visibleSize.width/_tileMap->getContentSize().width,_visibleSize.height/_tileMap->getContentSize().height);
	_tileMap->setVisible(true);
    _background = _tileMap->layerNamed("Background");
//	_background->getTexture()->setAntiAliasTexParameters();
	Director::getInstance()->setProjection(Director::Projection::_2D);
	this->addChild(_tileMap, 0);
/*
	Sprite* sprbj = Sprite::create("beijing.jpg");
	sprbj->setScale(_visibleSize.width/sprbj->getContentSize().width,_visibleSize.height/sprbj->getContentSize().height);
	sprbj->setTag(99);
	sprbj->setPosition(Vec2(_origin.x+_visibleSize.width/2, _origin.y+_visibleSize.height/2));
	this->addChild(sprbj, 0);

	Sprite* sprbj1 = Sprite::create("beijing.jpg");
	sprbj1->setScale(_visibleSize.width/sprbj1->getContentSize().width,_visibleSize.height/sprbj1->getContentSize().height);
	sprbj1->setTag(100);
	sprbj1->setPosition(Vec2(_origin.x+_visibleSize.width/2, _origin.y+_visibleSize.height/2));
	this->addChild(sprbj1, 0);
*/

    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(JumpMan::menuCloseCallback, this));
	closeItem->setPosition(Vec2(_origin.x + _visibleSize.width - closeItem->getContentSize().width/2 ,
                                _origin.y + _visibleSize.height - closeItem->getContentSize().height/2));
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    _startItem = MenuItemFont::create("StartGame",CC_CALLBACK_1(JumpMan::menuStartGameCallback, this));
    _startItem->setColor(Color3B(0,0,0));
    _startItem->setPosition(Vec2(_origin.x + _visibleSize.width*(2.0/10.0),
							_origin.y + _visibleSize.height*(8.0/9.0)));
    auto startMenu = Menu::create(_startItem, NULL);
    startMenu->setTag(55);
    startMenu->setPosition(Vec2::ZERO);
	this->addChild(startMenu, 1);

	_beginItem = MenuItemFont::create("BeginAgain",CC_CALLBACK_1(JumpMan::menuBeginItemCallback, this));
	_beginItem->setColor(Color3B(0,0,0));
	_beginItem->setPosition(Vec2(_origin.x + _visibleSize.width*(2.0/10.0),_origin.y + _visibleSize.height*(8.0/9.0)));
	_beginItem->setVisible(false);
	auto beginMenu = Menu::create(_beginItem, NULL);
	beginMenu->setTag(56);
	beginMenu->setPosition(Vec2::ZERO);
	this->addChild(beginMenu, 1);

    
	LabelTTF* label = LabelTTF::create("JumpMan", "Arial", 24);
    label->setTag(66);
    label->setColor(Color3B(0,0,0));
    label->setPosition(Vec2(_origin.x + _visibleSize.width/2,
                            _origin.y + _visibleSize.height - label->getContentSize().height));
    this->addChild(label, 1);

    Label* topScorelabel = Label::create("Top Score:", "Arial", 24);
    topScorelabel->setTag(67);
    topScorelabel->setColor(Color3B(0,0,0));
    topScorelabel->setPosition(Vec2(_origin.x + _visibleSize.width*(1.0/5.0),
							_origin.y + _visibleSize.height*(1.0/5.0)));
    topScorelabel->setVisible(false);
	this->addChild(topScorelabel, 1);

	Label* curScorelabel = Label::create("Cur Score:", "Arial", 24);
	curScorelabel->setTag(68);
	curScorelabel->setColor(Color3B(0,0,0));
	curScorelabel->setPosition(Vec2(_origin.x + _visibleSize.width*(1.0/5.0),
							_origin.y + _visibleSize.height*(1.0/5.0)-topScorelabel->getContentSize().height));
	curScorelabel->setVisible(false);
	this->addChild(curScorelabel, 1);

    _sprite_0 = Sprite::create("man1.png");
    _sprite_0->setScale(0.4);
    _sprite_0->setTag(1);
    _sprite_0->setPosition(Vec2(_visibleSize.width*(1.0/4.0) + _origin.x, _visibleSize.height*(2.0/5.0) + _origin.y));
    this->addChild(_sprite_0, 0);
    
    _sprite_1 = Sprite::create("kualan.jpg");
    _sprite_1->setScale(0.1,0.1);
    _sprite_1->setTag(2);
    _sprite_1->setPosition(Vec2(_visibleSize.width*(1.0/1.5) + _origin.x, _visibleSize.height*(2.0/5.0) + _origin.y));
    this->addChild(_sprite_1, 0);

    _sprite_2 = Sprite::create("kualan.jpg");
    _sprite_2->setScale(0.1,0.1);
    _sprite_2->setTag(3);
    _sprite_2->setPosition(Vec2(_visibleSize.width*(2.0/1.5) + _origin.x, _visibleSize.height*(2.0/5.0) + _origin.y));
	this->addChild(_sprite_2, 0);

	_sprite_kill = Sprite::create("kill.png");
	_sprite_kill->setTag(4);
	_sprite_kill->setVisible(false);
	_sprite_kill->setPosition(Vec2(_visibleSize.width*(1.0/2.0) + _origin.x, _visibleSize.height*(1.0/2.0) + _origin.y));
	this->addChild(_sprite_kill, 0);

    _listener = EventListenerTouchOneByOne::create();
    _listener->onTouchBegan = CC_CALLBACK_2(JumpMan::onTouchBegan,this);
    _listener->onTouchMoved = CC_CALLBACK_2(JumpMan::onTouchMoved,this);
    _listener->onTouchEnded = CC_CALLBACK_2(JumpMan::onTouchEnded,this);
    _listener->setSwallowTouches(true);//²»ÏòÏÂ´«µÝ´¥Ãþ
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_listener,_sprite_0);
//	_eventDispatcher->addEventListenerWithSceneGraphPriority(_listener->clone(),startMenu);
	_listener->setEnabled(false);
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("kiss the rain.mp3"); //¼ÓÔØ±³¾°ÒôÀÖ

//	std::string str = "123";
//	str.c_str();
	//HTTP GET
	_httpReq = new HttpRequest();
	_httpReq->setRequestType(HttpRequest::Type::GET);
	_httpReq->setUrl("http://127.0.0.1/index.php");
	_httpReq->setResponseCallback(CC_CALLBACK_2(JumpMan::onHttpComplete,this));
	_httpReq->setTag("Http GET");
	//HttpClient::getInstance()->send(_httpReq);
	_httpReq->release();
	//HTTP POST
	auto httpReqPost = new HttpRequest();
	httpReqPost->setRequestType(HttpRequest::Type::GET);
	httpReqPost->setUrl("http://127.0.0.1");
	httpReqPost->setResponseCallback(CC_CALLBACK_2(JumpMan::onHttpComplete,this));
	const char* buffer = "my data";
	httpReqPost->setRequestData(buffer, strlen(buffer));
	httpReqPost->setTag("Http POST");
	//HttpClient::getInstance()->send(httpReqPost);
	httpReqPost->release();

	this->_seqvector = Vector<Sequence*>(2);

    return true;
}

void JumpMan::onHttpComplete(HttpClient *sender, HttpResponse *response)
{
	if (!response)
	{
		return;
	}

	// You can get original request type from: response->request->reqType
	if (0 != strlen(response->getHttpRequest()->getTag()))
	{
		log("%s completed", response->getHttpRequest()->getTag());
	}

	int statusCode = response->getResponseCode();
	char statusString[64] = {};

	sprintf(statusString, "HTTP Status Code: %d, tag = %s", statusCode, response->getHttpRequest()->getTag());
//	_labelStatusCode->setString(statusString);
	log("response code: %d", statusCode);

	if (!response->isSucceed())
	{
		log("response failed");
		log("error buffer: %s", response->getErrorBuffer());
		return;
	}
	// dump data
	std::vector<char> *buffer = response->getResponseData();
	printf("Http Test, dump data: ");
	for (unsigned int i = 0; i < buffer->size(); i++)
	{
		printf("%c", (*buffer)[i]);
	}
	printf("\n");
}

void JumpMan::menuStartGameCallback(Ref* pSender)
{
	log("JumpMan::menuStartGameCallback");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	_listener->setEnabled(true);

//	auto moveto = MoveTo::create(5,Vec2(-100,visibleSize.height*(1.0/4.0) + origin.y));
//	_sprite_1->runAction(moveto);
	if (_beginAgain == 0) {
		SimpleAudioEngine::getInstance()->playBackgroundMusic("kiss the rain.mp3", true); //²¥·Å±³¾°ÒôÀÖ
		scheduleUpdate();
		movingRoadBlockTag();
	}
}

void JumpMan::menuBeginItemCallback(Ref* pSender)
{
	log("JumpMan::menuBeginItemCallback");
	if (_beginAgain == 1) {
		auto topScorelabel = (Label*)getChildByTag(67);
		auto curScorelabel = (Label*)getChildByTag(68);
		topScorelabel->setVisible(false);
		curScorelabel->setVisible(false);
		_beginAgain = 0;
		_score = 0;
		_maxScore = UserDefault::getInstance()->getIntegerForKey("score");
		_sprite_0->setPosition(Vec2(_visibleSize.width*(1.0/4.0) + _origin.x, _visibleSize.height*(2.0/5.0) + _origin.y));
		_sprite_1->setPosition(Vec2(_visibleSize.width*(1.0/1.5) + _origin.x, _visibleSize.height*(2.0/5.0) + _origin.y));
		_sprite_2->setPosition(Vec2(_visibleSize.width*(2.0/1.5) + _origin.x, _visibleSize.height*(2.0/5.0) + _origin.y));
		_particle->setVisible(false);
		_startItem->setVisible(true);
		_beginItem->setVisible(false);
		_sprite_kill->setVisible(false);

	}
}

void JumpMan::menuGameOver()
{
	log("JumpMan::menuGameOver");
	unscheduleUpdate();

	_listener->setEnabled(false);
	_sprite_0->stopActionByTag(77);
	_sprite_1->stopActionByTag(78);
	_sprite_2->stopActionByTag(79);
	SimpleAudioEngine::getInstance()->pauseBackgroundMusic(); //ÔÝÍ£±³¾°ÒôÀÖ
//	_jumpUp->stop();
//	_sprite_0->stopAllActions();
//	_sprite_1->stopAllActions();
	_beginItem->setVisible(true);
	_startItem->setVisible(false);
	_sprite_kill->setVisible(true);

	_particle = ParticleExplosion::create();
	_particle->setTexture(Director::getInstance()->getTextureCache()->addImage("CloseNormal.png"));
	_particle->setPosition(_sprite_0->getPosition());
	this->addChild(_particle, 2);

	JumpMan::setAndShowScore();
	if (_score > _maxScore)
		UserDefault::getInstance()->setIntegerForKey("score", _score);
	_score = 0;
	_beginAgain = 1;
}

void JumpMan::update(float dt)
{
	if (-(_sprite_1->getBoundingBox().size.width/2) > _sprite_1->getPositionX()) {
		if (_sprite_2->getBoundingBox().origin.x <= _visibleSize.width*(0.5/1.5))
			_sprite_1->setPosition(Vec2(_visibleSize.width+_sprite_1->getBoundingBox().size.width/2 + _origin.x, _visibleSize.height*(2.0/5.0)));
	}

	if (-(_sprite_2->getBoundingBox().size.width/2) > _sprite_2->getPositionX()) {
		if (_sprite_1->getBoundingBox().origin.x <= _visibleSize.width*(0.5/1.5))
			_sprite_2->setPosition(Vec2(_visibleSize.width+_sprite_2->getBoundingBox().size.width/2 + _origin.x, _visibleSize.height*(2.0/5.0)));
	}

	if (_sprite_0->getBoundingBox().intersectsRect(_sprite_1->getBoundingBox())
		|| _sprite_0->getBoundingBox().intersectsRect(_sprite_2->getBoundingBox())) {
		log("haved bone");
		JumpMan::menuGameOver();

	} else {
//		auto moveby1 = MoveBy::create(0.1,Vec2(-3,0));
//		moveby1->setTag(88);
//		auto moveby2 = moveby1->clone();
//		moveby2->setTag(89);
//		_sprite_1->runAction(moveby1);
//		_sprite_2->runAction(moveby2);
	}
}

void JumpMan::movingBackground()
{
//	auto sprbj = (Sprite*)getChildByTag(99);
//	auto sprbj1 = (Sprite*)getChildByTag(100);

//	sprbj->runAction(CCMoveBy::create(3, ccp(0, -48)));
//    m_backSkyHeight -= 48;
//    if (m_backSkyHeight <= winSize.height) {
//        if (!m_isBackSkyReload) {
//            m_backSkyRe = CCSprite::create(s_bg01);
//            m_backSkyRe->setAnchorPoint(ccp(0, 0));
//            addChild(m_backSkyRe, -10);
//            m_backSkyRe->setPosition(ccp(0, winSize.height));
//            m_isBackSkyReload = true;
//        }
//        m_backSkyRe->runAction(CCMoveBy::create(3, ccp(0, -48)));
//    }
//
//    if (m_backSkyHeight <= 0) {
//        m_backSkyHeight = m_backSky->getContentSize().height;
//        this->removeChild(m_backSky, true);
//        m_backSky = m_backSkyRe;
//        m_backSkyRe = NULL;
//        m_isBackSkyReload = false;
//    }
}



void JumpMan::movingRoadBlockTag()
{
	CallFunc* callFunc_1 = CallFunc::create(CC_CALLBACK_0(JumpMan::reMovingRoadBlockTag_1,this,_sprite_1));
	CallFunc* callFunc_2 = CallFunc::create(CC_CALLBACK_0(JumpMan::reMovingRoadBlockTag_2,this,_sprite_2));

	auto moveby1 = MoveBy::create(0.3,Vec2(-50,0));
//	moveby1->setTag(88);
	auto moveby2 = moveby1->clone();
//	moveby2->setTag(89);
	auto sequence_1 = Sequence::create(moveby1,callFunc_1,NULL);
	sequence_1->setTag(78);
	auto sequence_2 = Sequence::create(moveby2,callFunc_2,NULL);
	sequence_2->setTag(79);
	_sprite_1->runAction(sequence_1);
	_sprite_2->runAction(sequence_2);

}

void JumpMan::reMovingRoadBlockTag_1(Sprite* sprite)
{
//	auto sequence = ((Sequence*)getChildByTag(78))->retain();
//	sprite->runAction(_sequence);
	CallFunc* callFunc_1 = CallFunc::create(CC_CALLBACK_0(JumpMan::reMovingRoadBlockTag_1,this,_sprite_1));
	auto sequence = Sequence::create(MoveBy::create(0.3,Vec2(-50,0)),callFunc_1,NULL);
	sequence->setTag(78);
	sprite->runAction(sequence);

}

void JumpMan::reMovingRoadBlockTag_2(Sprite* sprite)
{
	CallFunc* callFunc_2 = CallFunc::create(CC_CALLBACK_0(JumpMan::reMovingRoadBlockTag_2,this,_sprite_2));
	auto sequence = Sequence::create(MoveBy::create(0.3,Vec2(-50,0)),callFunc_2,NULL);
	sequence->setTag(79);
	sprite->runAction(sequence);

}

bool JumpMan::onTouchBegan(Touch* touch, Event* event)
{
	auto sprite = (Sprite *)event->getCurrentTarget();
	CallFunc* callFunc_1 = CallFunc::create(CC_CALLBACK_0(JumpMan::disableTouchCallFunc,this,sprite));
	CallFunc* callFunc_2 = CallFunc::create(CC_CALLBACK_0(JumpMan::enableTouchCallFunc,this,sprite));
	sprite->setPosition(Vec2(_visibleSize.width*(1.0/4.0) + _origin.x, _visibleSize.height*(2.0/5.0) + _origin.y));

	_jumpUp = JumpBy::create(2,Vec2(0, 0),150,1);
	auto sequence = Sequence::create(callFunc_1,_jumpUp,callFunc_2,NULL);
	sequence->setTag(77);
	_sprite_0->runAction(sequence);
//	sprite->runAction(RepeatForever::create(jumpUp));
	return true;
}

void JumpMan::onTouchMoved(Touch* touch, Event* event)
{

}

void JumpMan::onTouchEnded(Touch* touch, Event* event)
{

}

void JumpMan::disableTouchCallFunc(Sprite* sprite)
{
//	_eventDispatcher->setEnabled(false);
	_listener->setEnabled(false);
}

void JumpMan::enableTouchCallFunc(Sprite* sprite)
{
//	_eventDispatcher->setEnabled(true);
	_listener->setEnabled(true);
	if (_sprite_0->getPositionX() -_sprite_1->getPositionX() <= _sprite_1->getBoundingBox().size.width*2.5
		|| _sprite_0->getPositionX() -_sprite_2->getPositionX() <= _sprite_1->getBoundingBox().size.width*2.5)
		_score += 100;
}

void JumpMan::storeData(char* pKey, int value)
{
	UserDefault::getInstance()->setIntegerForKey(pKey, value);
}

int JumpMan::readData(char* pKey)
{
	return UserDefault::getInstance()->getIntegerForKey(pKey);
}

void JumpMan::setAndShowScore()
{
	char buffer[30];
	auto topScorelabel = (Label*)getChildByTag(67);
	auto curScorelabel = (Label*)getChildByTag(68);
	sprintf(buffer, "Top Score:%6lu", (unsigned long)_maxScore);
	topScorelabel->setString(buffer);
	sprintf(buffer, "Cur Score:%6lu", (unsigned long)_score);
	curScorelabel->setString(buffer);
	topScorelabel->setVisible(true);
	curScorelabel->setVisible(true);
/***************************************************/
/*	stringstream sTopScore;
/*	string topScore;
/*	string str = "Cur Score:";
/*	sTopScore << (int) _maxScore;
/*	sTopScore >> topScore;
/*	topScore = str+topScore;
 * curScorelabel->setString(topScore);
 */
/***************************************************/
}

void JumpMan::menuCloseCallback(Ref* pSender)
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
