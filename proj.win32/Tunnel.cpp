#include "Segment.h"
#include "Light.h"
#include "GameScene.h"

Tunnel::Tunnel(b2World *world,CCPoint position,float width,float height,bool leftEntrance,bool rightExit) :CompoundSegment(world,position){
	this->init(world,width,height,leftEntrance,rightExit);
	this->setPosition(position);
	generate(world);

}

Tunnel::Tunnel(b2World *world,float width,float height,bool leftEntrance,bool rightExit) :CompoundSegment(world){
	this->init(world,width,height,leftEntrance,rightExit);
	generate(world);
}

void Tunnel::generate(b2World *world){
	this->segments[0].generate(world);
	this->segments[1].generate(world);
}

void Tunnel::setPosition(const CCPoint& newPosition){
	this->segments[0].setPosition( ccp(newPosition.x,newPosition.y+100));
	CCPoint newpos = this->segments[1].offsetStartPosition(this->segments[0].getGameWorldVertice(1),this->segments[1].getGameWorldVertice(0),&this->segments[0]);
	this->segments[1].setPosition(ccp(newpos.x+(200*directionModifier),newpos.y));
	float x = this->getPosition().x;
	float y = this->getPosition().y;
	this->_gameWorldVerticesCCW[0].setPoint((x-this->getContentSize().width/2),(y+this->getContentSize().height/2));
	this->_gameWorldVerticesCCW[1].setPoint((x-this->getContentSize().width/2),(y-this->getContentSize().height/2));
	this->_gameWorldVerticesCCW[2].setPoint((x+this->getContentSize().width/2),(y-this->getContentSize().height/2));
	this->_gameWorldVerticesCCW[3].setPoint((x+this->getContentSize().width/2),(y+this->getContentSize().height/2));
		
}

void Tunnel::init(b2World *world,float width,float height,bool leftEntrance,bool rightExit){
	this->segments = new Segment[2];
	this->_gameWorldVerticesCCW = new CCPoint[4];
	this->_polygonVerticesCCW = new CCPoint[4];
	if(_leftEntrance == true){
		directionModifier = 1;
	}else{
		directionModifier = -1;
	}
	this->segments[0] =  *new LineSegment(world,width,height);
	this->segments[1] =  *new LineSegment(world,width,height);
	this->_polygonVerticesCCW[0] = ccp(this->segments[0].getGameWorldVertice(0)->x+(100*directionModifier),this->segments[0].getGameWorldVertice(1)->y);
	this->_polygonVerticesCCW[1] = ccp(this->segments[0].getGameWorldVertice(0)->x+(100*directionModifier),this->segments[0].getGameWorldVertice(1)->y);
	this->_polygonVerticesCCW[1] = ccp(100.0f,100.0f);
	this->_polygonVerticesCCW[2] = ccp(_gameWorldVerticesCCW[0].x,this->segments[0].getGameWorldVertice(0)->y);
	this->_polygonVerticesCCW[3] = ccp(_gameWorldVerticesCCW[1].x,this->segments[0].getGameWorldVertice(0)->y);
	CCPoint* point = Segment::getPolygonVertice(1);
	this->_leftEntrance = leftEntrance;
	this->_rightExit = rightExit;
	this->setContentSize(*new CCSize(width,height));
}

float Tunnel::getEndVerticeNum(){
	return 3;
}

float Tunnel::getStartVerticeNum(){
	return 0;
}