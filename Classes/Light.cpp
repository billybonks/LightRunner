#include "Light.h"

using namespace cocos2d;

Light::Light()
{
	//CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	//CCSprite::CCSprite();
	//_origin = ccp(-50,0);
	//_destination = ccp(MIN(winSize.width*0.9-getPositionX(),50),0);
}

Light::Light(CCPoint position,float width,float height)
{;
	CCSprite::CCSprite();
}

	Light* Light::retainedLight(CCRect* scr){
	Light* l = new Light();
	l->setContentSize(CCSize(100,5));
		l->screen=scr;

	return l;
}

void Light::draw(){
	glLineWidth( 5.0f );
	glColor4ub(255.0f,0.0f,0.0f,255.0f);
	ccDrawLine( ccp(-50,0), ccp(MIN(screen->origin.x+screen->size.width*0.9-getPositionX(),50),0));
	glLineWidth(1);
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