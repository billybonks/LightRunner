#pragma once
#ifndef STRAIGHTLINESEGMENT_H
#define STRAIGHTLINESEGMENT_H
#include "ContinuousLineSegment.h"

class StraightLineSegment : public ContinuousLineSegment{
private:
protected:
		float _width;
		float _height;
		float _steps;
		float _stepWidth;
		b2Vec2 *_polygonStartPos;
		b2Vec2 _polygonVerticies[4];
		///Only use if you are going to init steps and polugonStartPos yourself
		StraightLineSegment(b2World *world,b2Vec2 startPosition,float width,float height);
public:
	StraightLineSegment(b2World *world,b2Vec2 startPosition,float width,float height,float steps);
	virtual void GenerateBody(b2Body* retBody);
	virtual bool GenerateNextBody(b2Body* retBody);
	virtual b2Vec2 GetGameWorldVerticies(int verticie);
	virtual void InitilizeData();
	virtual void OffsetStartPosition();
};

#endif