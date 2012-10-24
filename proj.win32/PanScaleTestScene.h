#ifndef AAPanScaleTestScene
#define AAPanScaleTestScene

#include "cocos2d.h"
#include "Box2D.h"
#include "GameObject.h"
#include "Player.h"
#include "SimpleAudioEngine.h"
#include <vector>
#include "B2DLayer.h"
#define PTM_RATIO 32

using namespace cocos2d;

class PanScaleTestScene : public B2DLayer
{
private:
	CCSpriteBatchNode * _batchNode;
	
	void update(float dt);
	
	CCSize winSize;
	CCPoint playerScreenPos;
	CCRect screenBounds;
	
	float _scale;
	GameObject* test;
	GameObject* left;
	GameObject* right;
	GameObject* botright;
	GameObject* topleft;
	GameObject* topright;
	GameObject* botleft;
	b2World* world;
public:
	virtual void draw();
	    LAYER_CREATE_FUNC(PanScaleTestScene);
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();
	
	// a selector callback
	virtual void menuCloseCallback(CCObject* pSender);
	
	virtual void ccTouchesBegan(CCSet* touches, cocos2d::CCEvent* event);
	virtual void ccTouchesEnded(CCSet* touches, cocos2d::CCEvent* event);

	// implement the "static node()" method manually
	LAYER_NODE_FUNC(PanScaleTestScene);
	
};

#endif // PanScaleTestScene
