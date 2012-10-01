// Player.h

#ifndef PLAYER
#define PLAYER

#include "cocos2d.h"
#include "Box2D.h"
#include "GameObject.h"
 
class Player : public GameObject {
public:
	Player();
	void jump();
	void createFootFixture(b2World* world);
	void setNumFootContacts(int i);
	void addNumFootContacts();
	void subNumFootContacts();
	//	void setCanJump();
	void subCanJump();
private:
	int numFootContacts;
	int canjump;
};
  

#endif