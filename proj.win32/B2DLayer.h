#ifndef B2DLAYER
#define B2DLAYER

#include "cocos2d.h"
#include "Box2D.h"
#define PTM_RATIO 32
#define DEGTORAD 0.0174532925f


using namespace cocos2d;

class B2DLayer : public CCLayer
{
private :

protected:
	void update(float dt);
	b2World* world;
	bool _debug;
	float _secondCounter;
public:

	virtual void draw();

	//virtual void secondsUpdate();
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  
	
	void Debug(bool debug);
	// a selector callback
	virtual void menuCloseCallback(CCObject* pSender);

};
#endif


