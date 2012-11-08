// Player.h

#ifndef PLAYER
#define PLAYER

#include "cocos2d.h"
#include "Box2D.h"
#include "GameObject.h"
//#include "Timer.h"

class Player : public GameObject {
public:
	void createFootFixture(b2World* world);
	void addNumFootContacts(int i);
	void subNumFootContacts(int i);
	Player();
	void jump();
	void init();
	void timeOutJump();
	void setDirection(int i);
	int getDirection();

	private:
	int numFootContacts[3];
	int jumpTimeout;
	int direction;
};
  
#endif