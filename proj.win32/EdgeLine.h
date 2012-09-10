#pragma once
#ifndef STRAIGHTLINESEGMENT_H
#define STRAIGHTLINESEGMENT_H
#include "ContinuousLineSegment.h"

class EdgeLineSegment : public ContinuousLineSegment{
private:
protected:

		b2Vec2 _polygonStartPos;
		b2Vec2 _polygonVerticies[4];
		///Only use if you are going to init steps and polugonStartPos yourself
public:
	EdgeLineSegment(b2World *world,b2Vec2 startPosition,float width,float height);
	virtual void GenerateBody(b2Body* retBody);
	virtual bool GenerateNextBody(b2Body* retBody);
	virtual b2Vec2 GetGameWorldVerticies(int verticie);
	virtual void InitilizeData();
	virtual void OffsetStartPosition();
};

#endif