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

	CCSprite* getSprite();
	b2Body* getBody();
	virtual void createBox2dObject(b2World* world);
	GameObject(b2World* world);
	GameObject();
	static GameObject* retainedObjectWithSpriteFrameName(const char *pszSpriteFrameName,b2World* world);
	static GameObject *retainedObjectWithSpriteFrame(CCSpriteFrame *pSpriteFrame,b2World* world);
	static GameObject* retainedObjectWithSprite(CCSprite *pSprite,b2World* world);
	void updateTrail(float dt);
	bool getCanBeOffScreen();
	virtual bool isOffScreen();
	virtual void removeFromParentAndCleanup();
	void update(float dt);
	void setCanBeOffScreen(bool can);
	virtual void setPosition(CCPoint pos);
	virtual void setPositionX(float x);
	virtual void setPositionY(float y);

	static void setScreen(CCRect * screen);
	
	void init(b2World* world);

private:

	int colourmode;
	_ccColor3B colour;
	float newtrail;
	b2AABB bounds;
	bool canBeOffScreen;

	_ccColor3B nextColour();

protected:
	b2Body *body;
	CCSprite* sprite;

	void setBoundingBox();

};
#endif