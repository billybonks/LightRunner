#ifndef BRAZIERCURVE
#define BRAZIERCURVE

#include "GameObject.h"

using namespace cocos2d;

class BrazierCurve : public CCSprite
{
public:
	BrazierCurve();
	BrazierCurve(CCPoint p1,CCPoint p2, CCPoint p3,CCPoint p4);
	static BrazierCurve* retainedLight(CCRect* scr);
	CCPoint PointForT(float t);
	virtual void draw();
	virtual void removeFromParentAndCleanup();
	CCPoint p1;
	CCPoint p2;
	CCPoint p3;
	CCPoint p4;
protected:
};
#endif