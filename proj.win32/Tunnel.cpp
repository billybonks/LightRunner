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
	CompoundSegment::segments[0].generate(world);
	this->CompoundSegment::segments[1].generate(world);
}

void Tunnel::setPosition(const CCPoint& newPosition){
	CompoundSegment::segments[0].setPosition( ccp(newPosition.x,newPosition.y+100));
	CCPoint newpos = CompoundSegment::segments[1].offsetStartPosition(CompoundSegment::segments[0].getGameWorldVertice(1),CompoundSegment::segments[1].getGameWorldVertice(0),&CompoundSegment::segments[0]);
	CompoundSegment::segments[1].setPosition(ccp(newpos.x+(200*directionModifier),newpos.y));
	float x = this->getPosition().x;
	float y = this->getPosition().y;
	this->_gameWorldVerticesCCW[0].setPoint((x-this->getContentSize().width/2),(y+this->getContentSize().height/2));
	this->_gameWorldVerticesCCW[1].setPoint((x-this->getContentSize().width/2),(y-this->getContentSize().height/2));
	this->_gameWorldVerticesCCW[2].setPoint((x+this->getContentSize().width/2),(y-this->getContentSize().height/2));
	this->_gameWorldVerticesCCW[3].setPoint((x+this->getContentSize().width/2),(y+this->getContentSize().height/2));
		
}

void Tunnel::init(b2World *world,float width,float height,bool leftEntrance,bool rightExit){
	CompoundSegment::segments = new Segment[2];
	Segment::_gameWorldVerticesCCW = new CCPoint[4];
	Segment::_polygonVerticesCCW = new CCPoint[4];
	if(_leftEntrance == true){
		directionModifier = 1;
	}else{
		directionModifier = -1;
	}
	CompoundSegment::segments[0] =  *new LineSegment(world,width,height);
	CompoundSegment::segments[1] =  *new LineSegment(world,width,height);
	Segment::_polygonVerticesCCW[0] = ccp(CompoundSegment::segments[0].getGameWorldVertice(0)->x+(100*directionModifier),CompoundSegment::segments[0].getGameWorldVertice(1)->y);
	Segment::_polygonVerticesCCW[1] = ccp(CompoundSegment::segments[0].getGameWorldVertice(0)->x+(100*directionModifier),CompoundSegment::segments[0].getGameWorldVertice(1)->y);
	Segment::_polygonVerticesCCW[1] = ccp(100.0f,100.0f);
	Segment::_polygonVerticesCCW[2] = ccp(_gameWorldVerticesCCW[0].x,CompoundSegment::segments[0].getGameWorldVertice(0)->y);
	Segment::_polygonVerticesCCW[3] = ccp(_gameWorldVerticesCCW[1].x,CompoundSegment::segments[0].getGameWorldVertice(0)->y);
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