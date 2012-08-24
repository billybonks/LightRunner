
#include "cocos2d.h"
#include "Box2D.h"
#define PTM_RATIO 32



using namespace cocos2d;

class B2DLayer : public cocos2d::CCLayer
{
protected:
	void update(float dt);
	b2World* world;
	bool _debug;
public:
	virtual void draw();
	LAYER_CREATE_FUNC(B2DLayer);

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  
	
	void Debug(bool debug);
	// a selector callback
	virtual void menuCloseCallback(CCObject* pSender);

	// implement the "static node()" method manually
	LAYER_NODE_FUNC(B2DLayer);
};


