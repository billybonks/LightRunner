#ifndef PLATFORM_H
#define PLATFORM_H
#include "GameObject.h"
#include "Light.h"

class Platform :  public GameObject  {
public:
	CCPoint _position;
	Platform(CCPoint position,float width,float height);
	virtual void createBox2dObject(b2World* world);
protected:
	Light light;
private:
};

#endif
