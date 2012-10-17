#include "TrajectorySprite.h"

TrajectorySprite::TrajectorySprite(b2World* world,b2Body *body){
	this->world = world;
	this->body = body;
}

/*
Impulse = m (v- u)
i/m = v-u
i/m+u = v;*/
void TrajectorySprite::update(b2Vec2* startingPosition, b2Vec2* startingVelocity,b2Vec2* startingImpulse){
	float vY=0,vX=0;
	float impulse =startingImpulse->y;
	float mass = body->GetMass();
	float initV = startingVelocity->y;
	 vY = (impulse/mass) +initV;
	impulse =startingImpulse->x;
	initV = startingVelocity->x;
	 vX = (impulse/mass) +initV;
	 b2Vec2 *temp =
	 this->startingVelocity  = new b2Vec2(vX,vY);
	 this->startingPosition = startingPosition;
	//this->s
	//return (impulse/mass)+initV;
}

void TrajectorySprite::draw(){
	glColor3f(1,1,0);
	glBegin(GL_LINES);
	for (int i = 0; i < 180; i++) { // three seconds at 60fps
		b2Vec2 trajectoryPosition = getTrajectoryPoint( *this->startingPosition,*this->startingVelocity, i );
		glVertex2f(trajectoryPosition.x, trajectoryPosition.y );
	}
	glEnd();
}
b2Vec2 TrajectorySprite::getTrajectoryPoint( b2Vec2 startingPosition, b2Vec2& startingVelocity, float n )
{
	//velocity and gravity are given per second but we want time step values here
	float t = 1 / 60.0f; // seconds per time step (at 60fps)
	b2Vec2 stepVelocity = t * startingVelocity; // m/s
	b2Vec2 stepGravity = t * t * world->GetGravity(); // m/s/s

	return startingPosition + n * stepVelocity + 0.5f * (n*n+n) * stepGravity;
	
}