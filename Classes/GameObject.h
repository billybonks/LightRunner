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
	//used so i can easily identify a gameObject in the world
	string id;
	GameObject();
	static GameObject* retainedObjectWithSpriteFrameName(const char *pszSpriteFrameName, CCRect* scr);
	static GameObject* retainedObjectWithSpriteFrame(CCSpriteFrame *pSpriteFrame, CCRect* scr );
	static GameObject* retainedObjectWithSprite(CCSprite *pSprite, CCRect* scr );
	void updateTrail(float dt);
	bool canBeOffScreen();
	bool isOffScreen();
	virtual void removeFromParentAndCleanup();
	void update(float dt);
	void SetPosition(CCPoint position);
	void SetTarget(CCPoint position);
	float velocity;
		CCRect *screen;

private:
	int colourmode;
		_ccColor3B colour;
		float newtrail;
		_ccColor3B nextColour();
protected:
	    b2Body *body;
		CCSprite* sprite;
};
#endif