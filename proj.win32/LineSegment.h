
#ifndef LINESEGMENT_H
#define LINESEGMENT_H
#include "Box2D.h"
#include "GameObject.h"
#include <stdlib.h>
#define PTM_RATIO 32
class LineSegment : public GameObject{
private:
protected:
	float _width;
	float _height;
	b2Vec2 _lastVerts[2];
	b2Vec2 _startWorldPosition;
	b2World *world;
	b2Vec2 _GameWorldVerticies[4];
	void GetVertsSquare(b2Vec2 vertices[],float width,float height);
	void GetVertsInclineSquare(b2Vec2 vertices[],float width,float height,float incline);
	
public:
	virtual void GenerateBody(b2Body* retBody);
	virtual void InitilizeData();
	virtual bool GenerateNextBody(b2Body* retBody);
	LineSegment(b2World *world,b2Vec2 startPosition);
	virtual b2Vec2 getLinearVelocity();
	virtual b2Vec2 getLastVerticies();
	virtual float getIncline();
	virtual b2Vec2 GetGameWorldVerticies(int verticie);
	virtual bool isOffScreen(float scale);
	void SetPosition(b2Vec2 _startWorldPosition);
	b2Vec2 GetPosition();
	float GetWidth();
	float GetHeight();
};
#endif