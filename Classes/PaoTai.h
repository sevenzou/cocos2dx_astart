#ifndef __PAO_TAI_H__
#define __PAO_TAI_H__

#include "cocos2d.h"

USING_NS_CC;

class PaoTai : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    bool onTouchBegan(Touch*, Event*);
	void onTouchMoved(Touch*, Event*);
	void onTouchEnded(Touch*, Event*);
    // implement the "static create()" method manually
    CREATE_FUNC(PaoTai);

private:
    Size _visibleSize;
    Vec2 _origin;
    Sprite* _sprite_1;
    Sprite* _sprite_2;
    int _touchEnable;

};

#endif // __PAO_TAI_H__
