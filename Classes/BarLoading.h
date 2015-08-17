#ifndef __BAR_LOADING_H__
#define __BAR_LOADING_H__

#include "cocos2d.h"
USING_NS_CC;

class BarLoading : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    void update(float dt);
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(BarLoading);

private:
    Size _visibleSize;
    Vec2 _origin;
    Sprite* _spriteRed;
    Sprite* _spriteYellow;
};

#endif // __BAR_LOADING_H__
