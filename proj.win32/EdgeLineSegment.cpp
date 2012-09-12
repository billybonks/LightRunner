#include "LineSegment.h"

EdgeLineSegment::EdgeLineSegment(b2World *world,b2Vec2 startPosition,float width,float height)
	:ContinuousLineSegment(world,startPosition,width,height)
{

}

void EdgeLineSegment::GenerateBody()
{

}

//hello
///JOOOOOOOOOOOOOOOO
bool EdgeLineSegment::GenerateNextBody()
{
	_startWorldPosition;
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(_startWorldPosition.x,_startWorldPosition.y);
	body =world->CreateBody(&bodyDef);
	b2FixtureDef* fixture = new b2FixtureDef();
	b2EdgeShape edge;
	edge.Set(*_verts[0],*_verts[1]);
	fixture->shape = &edge;
	fixture->density = 1.0f;
	fixture->friction = 0;
	body->CreateFixture(fixture);
	if(child != NULL){
		if(child->GenerateNextBody()){
			return true;
		}else{
			return false;
		}
		return false;
	}
	return false;
	return true;
}


void EdgeLineSegment::InitilizeData()
{
	float w = _width/2;
	float h = _height/2;
	_verts[0] = new b2Vec2(-w,-h);
	_verts[1] = new b2Vec2(w,h);
	float x,y;
	x = _startWorldPosition.x;
	y = _startWorldPosition.y;
	LineSegment::_GameWorldVerticies[0] = new b2Vec2((x-w)*PTM_RATIO,(y-h)*PTM_RATIO);
	LineSegment::_GameWorldVerticies[1] = new b2Vec2((x+w)*PTM_RATIO,(y+h)*PTM_RATIO);
	LineSegment::_GameWorldVerticies[2] =  _GameWorldVerticies[1];
	LineSegment::_GameWorldVerticies[3] =  _GameWorldVerticies[0];
}

void EdgeLineSegment::OffsetStartPosition( int attachementVerticie,LineSegment* target)
{
	float rentWidth = target->GetWidth()/PTM_RATIO;
	this->_startWorldPosition.x = _startWorldPosition.x + _width/2;
	this->_startWorldPosition.y = _startWorldPosition.y +( _height/2);
}