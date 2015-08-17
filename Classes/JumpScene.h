#ifndef __JUMP_SCENE_H__
#define __JUMP_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;
USING_NS_CC_MATH;
class JumpScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuJumpUpCallback(cocos2d::Ref* pSender);
    void menuJumpByCallback(cocos2d::Ref* pSender);
    void menuJumpToCallback(cocos2d::Ref* pSender);
    void menuMoveCallback(cocos2d::Ref* pSender);
    void menuSequenceCallback(cocos2d::Ref* pSender);
    void menuCloseCallback(cocos2d::Ref* pSender);
    void allSpritePositionInit(Vec2 vec2_1, Vec2 vec2_2);
    void plusMinusButtonCallback(cocos2d::Ref* pSender);
    void callFunction(CallFunc* callFuncN_1, CallFunc* callFuncN_2, Node* pSender);
    void disableTouchCallFunc(void);
    void enableTouchCallFunc(void);
    void disableTouchCallFunc1(cocos2d::Node* pSender);
    void enableTouchCallFunc1(cocos2d::Node* pSender);
    void disableTouchCallFuncN(Node* pSender1, cocos2d::Node* pSender);
    void enableTouchCallFuncN(Node* pSender1, cocos2d::Node* pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(JumpScene);

private:
    Size _visibleSize;
    Vec2 _origin;
    Sprite* _huaBanSprite_1;
    Sprite* _huaBanSprite_2;
    Label* _label;
    LabelTTF* _labelTTF;
    MenuItemImage* _plusItem;
    MenuItemImage* _minusItem;
    MenuItemFont* _jumpUpItem;
    MenuItemFont* _jumpByItem;
    MenuItemFont* _jumpToItem;
    MenuItemFont* _jumpMoveItem;
    MenuItemFont* _jumpSequenceItem;
};

#endif // __JUMP_SCENE_H__
