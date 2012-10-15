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
	void setNumFootContacts(int i);
	void addNumFootContacts();
	void subNumFootContacts();
	Player();
	void jump(float multiplier);
	void init();
	void timeOutJump();

	private:
	int numFootContacts;
	int jumpTimeout;
};
  
#endif