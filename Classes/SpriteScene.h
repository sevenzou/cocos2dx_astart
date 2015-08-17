#ifndef __SPRITE_SCENE_H__
#define __SPRITE_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class AddSprites : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    void menuStartCallback(cocos2d::Ref* pSender);
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void update(float dt);
    // implement the "static create()" method manually
    CREATE_FUNC(AddSprites);

private:
    Size _visibleSize;
    Vec2 _origin;
    Sprite *_sprite1;
    Sprite *_sprite2;
    Sprite *_sprite3;
    Sprite *_sprite4;
    Sprite *_sprite5;
};

#endif // __SPRITE_SCENE_H__
