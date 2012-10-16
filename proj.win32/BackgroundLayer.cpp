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
	_fillColour= colour;
	colourmode=0;
	time=0;
	sprite->setFillColour(&this->_fillColour);
	this->addChild(sprite);
	this->scheduleUpdate();
	return true;
}

 void BackgroundLayer::draw(){

 }

void BackgroundLayer::update(float dt){
	time+=dt;
	if(time>0.1){
		nextFillColour();
	time=0;
	}
}

void BackgroundLayer::nextFillColour(){
	 _fillColour.r = _fillColour.r*2.5-1.5 ;
        _fillColour.g =  _fillColour.g*2.5-1.5;
        _fillColour.b = _fillColour.b*2.5-1.5;

	if(colourmode==0){
		_fillColour.b+=0.025f;
		if(_fillColour.b>=1){
			_fillColour.b=1;
			colourmode=1;
		}
	}
	if(colourmode==1){
		_fillColour.r-=0.025f;
		if(_fillColour.r<=0){
			_fillColour.r=0;
			colourmode=2;
		}
	}
	if(colourmode==2){
		_fillColour.g+=0.025f;
		if(_fillColour.g>=1){
			_fillColour.g=1;
			colourmode=3;
		}
	}
	if(colourmode==3){
		_fillColour.b-=0.025f;
		if(_fillColour.b<=0){
			_fillColour.b=0;
			colourmode=4;
		}
	}
	if(colourmode==4){
		_fillColour.r+=0.025f;
		if(_fillColour.r>=1){
			_fillColour.r=1;
			colourmode=5;
		}
	}	
	if(colourmode==5){
		_fillColour.g-=0.025f;
		if(_fillColour.g<=0){
			_fillColour.g=0;
			colourmode=0;
		}
	}	

	 _fillColour.r = (_fillColour.r + 1.5) / 2.5;
        _fillColour.g = ( _fillColour.g + 1.5) / 2.5;
        _fillColour.b = (_fillColour.b +1.5) / 2.5;

}


