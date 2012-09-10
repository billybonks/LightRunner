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

}

b2Vec2 EdgeLineSegment::GetGameWorldVerticies(int verticie)
{

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