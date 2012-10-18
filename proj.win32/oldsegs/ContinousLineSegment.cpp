
#include "Segment.h"

ContinuousSegment::ContinuousSegment(b2World *world,b2Vec2 startPosition)
	:Segment(world,startPosition)
{
	 _sourceAttachmentVerticie = 0;
	parent = NULL;
	child = NULL;
}

ContinuousSegment::ContinuousSegment(b2World *world,float width, float height):Segment(world,width,height){
	parent = NULL;
	child = NULL;
	 _sourceAttachmentVerticie = 0;
}

ContinuousSegment::ContinuousSegment(b2World *world,b2Vec2 startPosition,float width, float height):Segment(world,startPosition,width,height)
{
	 _sourceAttachmentVerticie = 0;
	parent = NULL;
	child = NULL;
}

void ContinuousSegment::SetChild(ContinuousSegment *child,int sourceAttachementVerticie,int targetAttachementVerticie){
	_targetAttachmentVerticie = targetAttachementVerticie;
	_sourceAttachmentVerticie = sourceAttachementVerticie;

	this->child = child;
	child->SetParent(this);
	child->OffsetStartPosition(_targetAttachmentVerticie,_sourceAttachmentVerticie,this);
	//ContinuousSegment::InitilizeData();
	child->InitilizeData();
}

void ContinuousSegment::SetParent(ContinuousSegment *segment){
	this->parent = segment;
}

ContinuousSegment* ContinuousSegment::GetChild()
{
	return (ContinuousSegment*)child;
}

ContinuousSegment* ContinuousSegment::GetParent()
{
	return (ContinuousSegment*)parent;
}


void ContinuousSegment::GetVertsInclineSquare(b2Vec2 vertices[],float width,float height,float incline){
	Segment::GetVertsInclineSquare(vertices,width,height,incline);
}

void ContinuousSegment::GetVertsSquare(b2Vec2 vertices[],float width,float height){
	Segment::GetVertsSquare(vertices,width,height);
}

void ContinuousSegment::InitilizeData()
{
	child->SetPosition(*(new b2Vec2(*this->_GameWorldVerticies[_targetAttachmentVerticie])));
	ContinuousSegment* childCast = (ContinuousSegment*)child;
	//	childCast->OffsetStartPosition(,_attachmentVerticie);
}

bool ContinuousSegment::GenerateNextBody(){
	if(child != NULL){
		if(child->GenerateNextBody()){
			return true;
		}else{
			return false;
		}
		return false;
	}
}
