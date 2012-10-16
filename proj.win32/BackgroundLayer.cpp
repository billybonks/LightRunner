#include "BackgroundLayer.h"
#include "PlatformSprite.h"

using namespace cocos2d;

bool BackgroundLayer::init(){
	b2Vec2* vertices = (b2Vec2*)malloc(sizeof(b2Vec2)*4);
	float width=CCDirector::sharedDirector()->getWinSize().width;
	float height=CCDirector::sharedDirector()->getWinSize().height;
	vertices[0].Set(-width/2/PTM_RATIO, -height/2/PTM_RATIO);
	vertices[1].Set(width/2/PTM_RATIO, -height/2/PTM_RATIO);
	vertices[2].Set(width/2/PTM_RATIO, height/2/PTM_RATIO);
	vertices[3].Set(-width/2/PTM_RATIO, height/2/PTM_RATIO);
	PlatformSprite* sprite=PlatformSprite::retainedPlatformSprite(vertices);
	sprite->setPosition(ccp(width/2,height/2));
	ccColor4F colour = {1,1,1,1};
	//sprite->setMix(colour);
	this->addChild(sprite);
	return true;
}

 void BackgroundLayer::draw(){

 }

void BackgroundLayer::update(float dt){

}