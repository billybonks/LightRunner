/*#include "cocos2d.h"
#include "B2DLayer.h"
#include "GameObject.h"
#define PTM_RATIO 32
#define POSITIVESLOPE 1
#define NEGATIVESLOPE 1
#define PI 3.14159265359
#define PIXELTOCENTIMETER 0.026458333

using namespace cocos2d;

class B2dPlay : public B2DLayer
{
private:
	bool move;
	float spawnrate;
	CCSpriteBatchNode * _batchNode;
	void update(float dt);
	CCSize winSize;
	void CleanWorld();
	GameObject* _floor;
	b2Body* body;
	void DrawHill(b2Vec2 start,b2Vec2 end,float stepWidth,int width,int peak);
	b2FixtureDef* B2dPlay::GenSquare(b2Vec2 vertices[],b2World* world,b2Vec2 position);
public:
	LAYER_NODE_FUNC(B2dPlay);
	b2Vec2 B2dPlay::findCentroid(b2Vec2 vs[], int count);
	float B2dPlay::drawHill(int pixelStep,float xOffset,float yOffset,float width,float height,b2World* world) ;
	 void GetVerts(b2Vec2 vertices[],float width,float height);
	 void GetVertsInclineSquare(b2Vec2 vertices[],float width,float height,float incline);
	 b2FixtureDef* GenSquare(float width, float height,b2World* world);
	virtual void draw();
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  
	void SegmentTest();

	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();
	
	// a selector callback
	virtual void menuCloseCallback(CCObject* pSender);
	
	virtual void ccTouchesBegan(CCSet* touches, cocos2d::CCEvent* event);
	LAYER_CREATE_FUNC(B2dPlay);

};

*/