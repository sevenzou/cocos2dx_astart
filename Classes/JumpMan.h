#ifndef __JUMP_MAN_H__
#define __JUMP_MAN_H__

#include "cocos2d.h"
#include "network/HttpClient.h"
#include "network/HttpRequest.h"
#include "base/CCVector.h"

USING_NS_CC;
using namespace std;
using namespace CocosDenshion;
using namespace cocos2d::network;

class JumpMan : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    bool onTouchBegan(Touch*, Event*);
    void onTouchMoved(Touch*, Event*);
    void onTouchEnded(Touch*, Event*);
    void disableTouchCallFunc(Sprite* sprite);
    void enableTouchCallFunc(Sprite* sprite);
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void storeData(char* pKey, int value);
    int readData(char* pKey);
    void menuStartGameCallback(Ref* pSender);
    void menuGameOver();
    void movingBackground();
    void movingRoadBlockTag();
    void reMovingRoadBlockTag_1(Sprite* sprite);
    void reMovingRoadBlockTag_2(Sprite* sprite);
    void menuBeginItemCallback(Ref* pSender);
    void update(float dt);
    void setAndShowScore();

    void onHttpComplete(HttpClient *sender, HttpResponse *response);
    // implement the "static create()" method manually
    CREATE_FUNC(JumpMan);

private:
    cocos2d::TMXTiledMap *_tileMap;
    cocos2d::TMXLayer *_background;
//    cocos2d::experimental::TMXTiledMap *_tileMap;

    Sprite* _sprite_0;
    Sprite* _sprite_1;
    Sprite* _sprite_2;
    Sprite* _sprite_kill;
    ParticleExplosion* _particle;
    Size _visibleSize;
    Vec2 _origin;
    MenuItemFont* _beginItem;
    MenuItemFont* _startItem;
    JumpBy * _jumpUp;
    EventListenerTouchOneByOne* _listener;
    HttpRequest* _httpReq;
    int _beginAgain;
    int _score;
    int _maxScore;
    Vector<Sprite*>  _spVec;
    Vector<Sequence*> _seqvector;
    Map<std::string, Sprite*> _mapstring;
    Value val;
    std::pair<int, int> p;
    //int i = INT_MAX;

};

#endif // __JUMP_MAN_H__
