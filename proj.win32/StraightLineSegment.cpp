#include "LineSegment.h"

StraightLineSegment::StraightLineSegment(b2World *world,b2Vec2 startPosition,float width,float height)
	:ContinuousLineSegment(world,startPosition,width,height)
{
	_polygonVerticies = (b2Vec2*)malloc(sizeof(StraightLineSegment)*4);
	ContinuousLineSegment::GetVertsSquare(_polygonVerticies,_width,_height);

}

StraightLineSegment::StraightLineSegment(b2World *world,float width,float height):ContinuousLineSegment(world,width,height){
	_polygonVerticies = (b2Vec2*)malloc(sizeof(StraightLineSegment)*4);
	ContinuousLineSegment::GetVertsSquare(_polygonVerticies,_width,_height);

}

void StraightLineSegment::GenerateBody()
{
	while(this->GenerateNextBody()){
		//Do Something
	}
}


bool StraightLineSegment::GenerateNextBody()
{ 
	_startWorldPosition;
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(_startWorldPosition.x,_startWorldPosition.y);
	body =world->CreateBody(&bodyDef);
	b2FixtureDef* fixture = new b2FixtureDef();
	b2PolygonShape polygon;
	polygon.Set(_polygonVerticies, 4);
	fixture->shape = &polygon;
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
}

b2Vec2* StraightLineSegment::GetGameWorldVerticies(int verticie)
{ 
	return _GameWorldVerticies[verticie];
}

void StraightLineSegment::InitilizeData(){
	float y,x;
	y = LineSegment::_startWorldPosition.y+_polygonVerticies[0].y;
	x = LineSegment::_startWorldPosition.x+_polygonVerticies[0].x;
	LineSegment::_GameWorldVerticies[0] =new b2Vec2((x)*PTM_RATIO,(y)*PTM_RATIO);
	y = LineSegment::_startWorldPosition.y+_polygonVerticies[3].y;
	x = LineSegment::_startWorldPosition.x+_polygonVerticies[3].x;
	LineSegment::_GameWorldVerticies[3] =new b2Vec2((x)*PTM_RATIO,(y)*PTM_RATIO);
	y = LineSegment::_startWorldPosition.y+_polygonVerticies[1].y;
	x = LineSegment::_startWorldPosition.x+_polygonVerticies[1].x;
	LineSegment::_GameWorldVerticies[1] =new b2Vec2((x)*PTM_RATIO,(y)*PTM_RATIO);
	y = LineSegment::_startWorldPosition.y+_polygonVerticies[2].y;
	x = LineSegment::_startWorldPosition.x+_polygonVerticies[2].x;
	LineSegment::_GameWorldVerticies[2] =new b2Vec2((x)*PTM_RATIO,(y)*PTM_RATIO);
}

void StraightLineSegment::OffsetStartPosition( int targetAttachementVerticie, int sourceAttachementVerticie,LineSegment* target ){
	b2Vec2 sourceVert = this->_polygonVerticies[sourceAttachementVerticie];
	b2Vec2* targetVert = target->GetGameWorldVerticies(targetAttachementVerticie);
	this->_startWorldPosition.x = targetVert->x/PTM_RATIO;
	this->_startWorldPosition.y = targetVert->y/PTM_RATIO;
	this->_startWorldPosition.x -= sourceVert.x;
	this->_startWorldPosition.y -= sourceVert.y;
}
