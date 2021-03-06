

#include "cocos2d.h"
#include "GameObject.h"
#include "Statistics.h"
#define PTM_RATIO 32



using namespace cocos2d;

class ScoreLayer : public cocos2d::CCLayer
{
private:
	CCLabelTTF* _score;
	CCLabelTTF* _velocity;
	CCLabelTTF* _multiplier;
	CCLabelTTF* _distanceTraveled;
		Statistics* _stats;
	void update(float dt);
	CCSize winSize;
public:
	virtual void draw();
	LAYER_CREATE_FUNC(ScoreLayer);
	void SetStatistics(Statistics* _stats);
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();
	
	string floatToStr(float f);
	// a selector callback

	// implement the "static node()" method manually
	LAYER_NODE_FUNC(ScoreLayer);
};

