#pragma once
#ifndef INCLINESEGMENT_H
#define INCLINESEGMENT_H
#include "StraightLineSegment.h"
class InclineLineSegment : public StraightLineSegment{
private:
protected:
	
	float _thickness;
	float _inclinePerStep;

public:
	InclineLineSegment(b2World *world,b2Vec2 startPosition,float width,float maxHieght,float thickness);
	virtual b2Vec2 getLinearVelocity();
	virtual void InitilizeData();
	virtual void OffsetStartPosition();
};
#endif
