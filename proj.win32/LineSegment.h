
#ifndef LINESEGMENT_H
#define LINESEGMENT_H
#include "Box2D.h"

class LineSegment{
private:
	 void GetVertsSquare(b2Vec2 vertices[],float width,float height);
	 void GetVertsInclineSquare(b2Vec2 vertices[],float width,float height,float incline);
protected:
	float _maxHieght;
	float _thickness;
	float _width;
	int _steps;
	int _currentStep;
	float _stepWidth;
	float _inclinePerStep;
	b2Vec2 _lastVerts[2];
public:
	LineSegment(b2Vec2 originPoints[],float maxHieght,float thickness,float width);
	b2Vec2 getLinearVelocity();
	b2Vec2 getLastVerticies();
	float getIncline();
	bool GenerateNextBody(b2Body* retBody);
};
#endif