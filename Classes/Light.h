#ifndef LIGHT
#define LIGHT

#include "GameObject.h"
using namespace cocos2d;

class Light : public CCSprite
{
public:
	Light();
	Light(CCPoint position,float width,float height);
	float _width;
	float _height;
	static Light* retainedLight();
	virtual void draw();
	virtual void removeFromParentAndCleanup();
	bool IsTouched();
	void IsTouched(bool touched);
	CCPoint _position;
	CCPoint _destination;
protected:
	bool _touched;
};
#endif