#ifndef LIGHT
#define LIGHT

#include "GameObject.h"
using namespace cocos2d;

class Light : public CCSprite
{
public:
	Light();
	Light(CCPoint origin,CCPoint destination,float lineWidth);
	float _width;
	static Light* retainedLight();
	virtual void draw();
	virtual void removeFromParentAndCleanup();
	bool IsTouched();
	void IsTouched(bool touched);
	CCPoint _origin;
	CCPoint _destination;
protected:
	bool _touched;
};
#endif