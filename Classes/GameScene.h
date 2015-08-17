#ifndef __GAMESCENE_SCENE_H__
#define __GAMESCENE_SCENE_H__

#include "cocos2d.h"
using namespace CocosDenshion;
USING_NS_CC;

class GameScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    Scene* _gameScene0;
    Layer* _gameLayer0;
    Size _visibleSize;
    Vec2 _origin;
    Sprite *_sprite;
    bool _statusX;
    bool _statusY;
    float _scale;

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    void gameSceneInit();
    void update(float dt) override;
    void gameUpdate(float dt);
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    bool onTouchBegan(Touch*, Event*);
    void onTouchMoved(Touch*, Event*);
    void onTouchEnded(Touch*, Event*);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
};

#endif // __GAMESCENE_SCENE_H__
