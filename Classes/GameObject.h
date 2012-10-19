// GameObject.h
#ifndef GAMEOBJECT
#define GAMEOBJECT

#include "cocos2d.h"
#include "Box2D.h" 

 using namespace cocos2d;
 #define PTM_RATIO 32


class GameObject : public CCNode {
public:
	static CCRect *screen;

	CCPoint _target;
	string id;
	float velocity;
	bool CanBeOffScreen;

	CCSprite* getSprite();
	b2Body* getBody();
	virtual void createBox2dObject(b2World* world);
	GameObject();
	static GameObject* retainedObjectWithSpriteFrameName(const char *pszSpriteFrameName);
	static GameObject* retainedObjectWithSpriteFrame(CCSpriteFrame *pSpriteFrame);
	static GameObject* retainedObjectWithSprite(CCSprite *pSprite);
	void updateTrail(float dt);
	bool canBeOffScreen();
	virtual bool isOffScreen(float scale);
	virtual void removeFromParentAndCleanup();
	void update(float dt);
	void SetCanBeOffScreen(bool can);
	void SetTarget(CCPoint position);
	
	static void SetScreen(CCRect * screen);
	
	void init();

private:

	int colourmode;
	_ccColor3B colour;
	float newtrail;
	b2AABB bounds;

	_ccColor3B nextColour();

protected:
	b2Body *body;
	CCSprite* sprite;

	void setBoundingBox();

};
#endif