
#ifndef LINESEGMENT_H
#define LINESEGMENT_H
#include "Box2D.h"
#include <stdlib.h>
#define PTM_RATIO 32
class LineSegment{
private:
protected:
	int _steps;
	int _currentStep;
	b2Vec2 _lastVerts[2];
	b2Vec2 _startWorldPosition;
	b2Vec2 _currentStepStartPosition;
	b2World *world;
	b2Vec2 _GameWorldVerticies[4];
	void GetVertsSquare(b2Vec2 vertices[],float width,float height);
	void GetVertsInclineSquare(b2Vec2 vertices[],float width,float height,float incline);
	
public:
	virtual void LineSegment::GenerateBody(b2Body* retBody)= 0;
	virtual void InitilizeData()= 0;;
	LineSegment(b2World *world,b2Vec2 startPosition);
	virtual b2Vec2 getLinearVelocity();
	virtual b2Vec2 getLastVerticies();
	virtual float getIncline();
	virtual bool GenerateNextBody(b2Body* retBody)= 0;
	virtual b2Vec2 GetGameWorldVerticies(int verticie);
	void SetPosition(b2Vec2 _startWorldPosition);
};
#endif