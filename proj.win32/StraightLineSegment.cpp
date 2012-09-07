#include "StraightLineSegment.h"

StraightLineSegment::StraightLineSegment(b2World *world,b2Vec2 startPosition,float width,float height)
	:ContinuousLineSegment(world,startPosition)
{
	this->_width = width/PTM_RATIO;
	this->_height = height/PTM_RATIO;
	this->_startWorldPosition.x = startPosition.x/32;
	this->_startWorldPosition.y = startPosition.y/32;
}

void StraightLineSegment::GenerateBody(b2Body* retBody)
{
	while(this->GenerateNextBody(retBody)){
		//Do Something
	}
}


bool StraightLineSegment::GenerateNextBody(b2Body* retBody)
{ 
	_startWorldPosition;
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(_startWorldPosition.x,_startWorldPosition.y);
	retBody =world->CreateBody(&bodyDef);
	b2FixtureDef* fixture = new b2FixtureDef();
	b2PolygonShape polygon;
	polygon.Set(_polygonVerticies, 4);
	fixture->shape = &polygon;
	fixture->density = 1.0f;
	fixture->friction = 0;
	retBody->CreateFixture(fixture);
	if(child != NULL){
		if(child->GenerateNextBody(retBody)){
			return true;
		}else{
			return false;
		}
	return false;
	}
	return false;
}

b2Vec2 StraightLineSegment::GetGameWorldVerticies(int verticie)
{ 
	return _GameWorldVerticies[verticie];
}

void StraightLineSegment::InitilizeData(){
	_startWorldPosition;
	float y,x;
	ContinuousLineSegment::GetVertsSquare(_polygonVerticies,_width,_height);
	_startWorldPosition.x;
	_startWorldPosition.y;
	y = LineSegment::_startWorldPosition.y+_polygonVerticies[0].y;
	x = LineSegment::_startWorldPosition.x+_polygonVerticies[0].x;
	LineSegment::_GameWorldVerticies[0] =b2Vec2((x)*PTM_RATIO,(y)*PTM_RATIO);
	y = LineSegment::_startWorldPosition.y+_polygonVerticies[3].y;
	x = LineSegment::_startWorldPosition.x+_polygonVerticies[3].x;
	LineSegment::_GameWorldVerticies[3] =b2Vec2((x)*PTM_RATIO,(y)*PTM_RATIO);
	y = LineSegment::_startWorldPosition.y+_polygonVerticies[1].y;
	x = LineSegment::_startWorldPosition.x+_polygonVerticies[1].x;
	LineSegment::_GameWorldVerticies[1] =b2Vec2((x)*PTM_RATIO,(y)*PTM_RATIO);
	y = LineSegment::_startWorldPosition.y+_polygonVerticies[2].y;
	x = LineSegment::_startWorldPosition.x+_polygonVerticies[2].x;
	LineSegment::_GameWorldVerticies[2] =b2Vec2((x)*PTM_RATIO,(y)*PTM_RATIO);
	_GameWorldVerticies;
}

void StraightLineSegment::OffsetStartPosition(){
	this->_startWorldPosition.x = _startWorldPosition.x + _width/2;
	this->_startWorldPosition.y = _startWorldPosition.y - _height/2;
}
