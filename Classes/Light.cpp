#include "Light.h"

using namespace cocos2d;

Light::Light()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSprite::CCSprite();
	_origin = ccp(-50,0);
	_destination = ccp(MIN(winSize.width*0.9-getPositionX(),50),0);
}

Light::Light(CCPoint origin,CCPoint destination,float lineWidth)
{;
	CCSprite::CCSprite();
	_origin = origin;
	_destination = destination;
	_width = lineWidth;
}

	Light* Light::retainedLight(){
	Light* l = new Light();
	l->setContentSize(CCSize(100,5));
	return l;
}

void Light::draw(){
	glLineWidth(_width);
	glColor4ub(255.0f,0.0f,0.0f,255.0f);
	ccDrawLine(_origin,_destination );
	glColor4ub(255,255,255,255);

}

void Light::removeFromParentAndCleanup(){
	CCSprite::removeFromParentAndCleanup(true);
}

bool Light::IsTouched(){
	return _touched;
}

void Light::IsTouched(bool touched){
	 _touched = touched;
}