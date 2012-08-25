#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Box2D.h"
#include "TrailedCCSprite.h"
#include "GameObject.h"
#include "Player.h"
#include "SimpleAudioEngine.h"
#include <vector>
#include "Light.h"
#include "Statistics.h"
#include "B2DLayer.h"
#define PTM_RATIO 32



using namespace cocos2d;

class Game : public B2DLayer
{
private:
	bool move;
	float spawnrate;
	CCSpriteBatchNode * _batchNode;
	Player* _player;
	GameObject* _floor;
	GameObject* _boss;
	void update(float dt);
	CCSize winSize;
	std::vector<GameObject*> platforms;
	Statistics _stats;
	void CleanWorld();
public:
	virtual void draw();
	    LAYER_CREATE_FUNC(Game);

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();
	
	// a selector callback
	virtual void menuCloseCallback(CCObject* pSender);
	
	virtual void ccTouchesBegan(CCSet* touches, cocos2d::CCEvent* event);

	// implement the "static node()" method manually
	LAYER_NODE_FUNC(Game);
};

#endif // __GAME_SCENE_H__
