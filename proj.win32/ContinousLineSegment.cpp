
#include "LineSegment.h"

ContinuousLineSegment::ContinuousLineSegment(b2World *world,b2Vec2 startPosition)
	:LineSegment(world,startPosition)
{
	parent = NULL;
	child = NULL;
}

ContinuousLineSegment::ContinuousLineSegment(b2World *world,float width, float height):LineSegment(world,width,height){
	parent = NULL;
	child = NULL;
}

ContinuousLineSegment::ContinuousLineSegment(b2World *world,b2Vec2 startPosition,float width, float height):LineSegment(world,startPosition,width,height)
{
	parent = NULL;
	child = NULL;
}

void ContinuousLineSegment::SetChild(ContinuousLineSegment *child,int sourceAttachementVerticie,int targetAttachementVerticie){
	_targetAttachmentVerticie = targetAttachementVerticie;
	_sourceAttachmentVerticie = sourceAttachementVerticie;
	this->child = child;
	child->SetParent(this);
	child->OffsetStartPosition(_targetAttachmentVerticie,_sourceAttachmentVerticie,this);
	//ContinuousLineSegment::InitilizeData();
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
	child->SetPosition(*(new b2Vec2(*this->_GameWorldVerticies[_targetAttachmentVerticie])));
	ContinuousLineSegment* childCast = (ContinuousLineSegment*)child;
//	childCast->OffsetStartPosition(,_attachmentVerticie);
}

void ContinuousLineSegment::OffsetStartPosition( int targetAttachementVerticie, int sourceAttachementVerticie,LineSegment* target )
{


}