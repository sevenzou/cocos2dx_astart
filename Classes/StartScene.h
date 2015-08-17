#ifndef __STARTSCENE_SCENE_H__
#define __STARTSCENE_SCENE_H__

#include "cocos2d.h"
using namespace CocosDenshion;
USING_NS_CC;

class StartScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
	static int _sceneCount;
    Size _visibleSize;
    Vec2 _origin;

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    // a selector callback
    void menuStartOneCallback(cocos2d::Ref* pSender);
    void menuStartTwoCallback(cocos2d::Ref* pSender);
    void menuStartThreeCallback(cocos2d::Ref* pSender);
    void menuStartFourCallback(cocos2d::Ref* pSender);
    void menuStartFiveCallback(cocos2d::Ref* pSender);
    void menuStopCallback(cocos2d::Ref* pSender);
    bool onTouchBegan(Touch*, Event*);
    void onTouchMoved(Touch*, Event*);
    void onTouchEnded(Touch*, Event*);
    
    // implement the "static create()" method manually
    CREATE_FUNC(StartScene);
};

#endif // __STARTSCENE_SCENE_H__
