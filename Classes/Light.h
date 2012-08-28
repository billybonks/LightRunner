#ifndef LIGHT
#define LIGHT

#include "GameObject.h"
using namespace cocos2d;

class Light : public CCSprite
{
public:
	Light();
	Light(CCPoint position,float width,float height);
	static Light* retainedLight(CCRect* scr);
	virtual void draw();
	virtual void removeFromParentAndCleanup();
	bool IsTouched();
	void IsTouched(bool touched);
			CCRect *screen;

protected:
	bool _touched;
};
#endif