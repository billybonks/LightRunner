#ifndef TRAJECTORYSPRITE
#define TRAJECTORYSPRITE

#include "GameObject.h"
using namespace cocos2d;
class TrajectorySprite : public CCSprite{
public :
	TrajectorySprite(b2World* world,b2Body *body);
	virtual void draw();
	b2Vec2 getTrajectoryPoint( b2Vec2 startingPosition, b2Vec2& startingVelocity, float n );
	void update(b2Vec2* startingPosition, b2Vec2* startingVelocity,b2Vec2* startingImpulse);
private:
	b2World* world;
	b2Body *body;
	b2Vec2* startingPosition;
	b2Vec2* startingVelocity;
};
#endif