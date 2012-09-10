
#include "LineSegment.h"

ContinuousLineSegment::ContinuousLineSegment(b2World *world,b2Vec2 startPosition)
	:LineSegment(world,startPosition)
{
	parent = NULL;
	child = NULL;
}

ContinuousLineSegment::ContinuousLineSegment(b2World *world,b2Vec2 startPosition,float width, float height):LineSegment(world,startPosition,width,height)
{

}

void ContinuousLineSegment::SetChild(ContinuousLineSegment *child,ContinuousLineSegment *parent){
	this->child = child;
	child->SetParent(parent);
	ContinuousLineSegment::InitilizeData();
	child->InitilizeData();
}

void ContinuousLineSegment::SetParent(ContinuousLineSegment *segment){
	this->parent = segment;
}

ContinuousLineSegment* ContinuousLineSegment::GetChild()
{
	return (ContinuousLineSegment*)child;
}

ContinuousLineSegment* ContinuousLineSegment::GetParent()
{
	return (ContinuousLineSegment*)parent;
}


void ContinuousLineSegment::GetVertsInclineSquare(b2Vec2 vertices[],float width,float height,float incline){
	LineSegment::GetVertsInclineSquare(vertices,width,height,incline);
}

void ContinuousLineSegment::GetVertsSquare(b2Vec2 vertices[],float width,float height){
	LineSegment::GetVertsSquare(vertices,width,height);
}

void ContinuousLineSegment::InitilizeData()
{
	child->SetPosition(LineSegment::_GameWorldVerticies[2]);
	ContinuousLineSegment* childCast = (ContinuousLineSegment*)child;

	childCast->OffsetStartPosition();
}

void ContinuousLineSegment::OffsetStartPosition(){


}