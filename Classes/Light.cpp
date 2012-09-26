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

	Light* Light::retainedLight(b2Vec2* polygonVerticies){
	Light* l = new Light();
	polygonVerticies[0]*=PTM_RATIO;
	polygonVerticies[1]*=PTM_RATIO;
	l->_polygonVerticies=polygonVerticies;
	l->setContentSize(CCSize(abs(polygonVerticies[1].x-polygonVerticies[0].x),abs(polygonVerticies[1].y-polygonVerticies[0].y)));

	return l;
}

void Light::draw(){
	glLineWidth( 3.0f );
	//ccDrawLine( ccp(-50,0), ccp(MIN(screen->origin.x+screen->size.width*0.9-getPositionX(),50),0));
	ccDrawLine( ccp(_polygonVerticies[0].x,_polygonVerticies[0].y), ccp(_polygonVerticies[1].x,_polygonVerticies[1].y));
	glLineWidth(1);
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