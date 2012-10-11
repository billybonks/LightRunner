// GameObject.h
#ifndef GAMEOBJECT
#define GAMEOBJECT

#include "cocos2d.h"
#include "box2d.h"
 using namespace cocos2d;
 #define PTM_RATIO 32


class GameObject : public CCNode {
public:
	CCSprite* getSprite();
	b2Body* getBody();
	virtual void createBox2dObject(b2World* world);
	CCPoint _target;
	string id;
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
	float velocity;
	static CCRect *screen;
	static void SetScreen(CCRect * screen);
	bool CanBeOffScreen;
	void init();

private:

	int colourmode;
	_ccColor3B colour;
	float newtrail;
	_ccColor3B nextColour();
	b2AABB bounds;

protected:
	b2Body *body;
	CCSprite* sprite;
	void setBoundingBox();

};
#endif