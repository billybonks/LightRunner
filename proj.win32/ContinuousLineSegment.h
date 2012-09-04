
#ifndef CONTINUOUSLINESEGMENT_H
#define CONTINUOUSLINESEGMENT_H
#include "LineSegment.h"

class ContinuousLineSegment :public  LineSegment{
private:

protected:
	LineSegment *child;
	LineSegment *parent;
	void GetVertsSquare(b2Vec2 vertices[],float width,float height);
	void GetVertsInclineSquare(b2Vec2 vertices[],float width,float height,float incline);
public:
	ContinuousLineSegment(b2World *world,b2Vec2 startPosition);
	virtual void SetChild(ContinuousLineSegment *child,ContinuousLineSegment *parent);
	virtual void SetParent(ContinuousLineSegment *segment);
	virtual ContinuousLineSegment* GetChild();
	virtual ContinuousLineSegment* GetParent();
	virtual void OffsetStartPosition() = 0;
	virtual void InitilizeData();
};

#endif