#include "LineSegment.h"

EdgeLineSegment::EdgeLineSegment(b2World *world,b2Vec2 startPosition,float width,float height)
	:ContinuousLineSegment(world,startPosition,width,height)
{

}

void EdgeLineSegment::GenerateBody()
{

}

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
	_verts[0] = new b2Vec2(0.0f,0.0f);
	_verts[1] = new b2Vec2(_width,_height);
	float x,y;
	x = _startWorldPosition.x;
	y = _startWorldPosition.y;
	LineSegment::_GameWorldVerticies[0] = new b2Vec2((x)*PTM_RATIO,(y)*PTM_RATIO);
	x = _startWorldPosition.x+_width;
	y = _startWorldPosition.y;
	LineSegment::_GameWorldVerticies[1] = new b2Vec2((x)*PTM_RATIO,(y)*PTM_RATIO);
	x = _startWorldPosition.x+_width;
	y = _startWorldPosition.y+_height;
	LineSegment::_GameWorldVerticies[2] =  new b2Vec2((x)*PTM_RATIO,(y)*PTM_RATIO);
	x = _startWorldPosition.x;
	y = _startWorldPosition.y+_height;
	LineSegment::_GameWorldVerticies[3] =  new b2Vec2((x)*PTM_RATIO,(y)*PTM_RATIO);
}

void EdgeLineSegment::OffsetStartPosition()
{

}