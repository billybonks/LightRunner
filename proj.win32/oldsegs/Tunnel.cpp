#include "Segment.h"
#include "Light.h"

Tunnel::Tunnel(b2World *world,b2Vec2 startPosition,float width,float height,bool leftEntrance,bool rightExit)
	:ContinuousSegment(world,startPosition,width,height)
		{
			_polygonVerticies = (b2Vec2*)malloc(sizeof(b2Vec2)*4);
			ContinuousSegment::GetVertsSquare(_polygonVerticies,_width,_height);
			left = new LineSegment(world,0,height);
			right = new LineSegment(world,0,height);
			bool _leftEntrance=leftEntrance;
			bool _rightExit=rightExit;
			this->SetCanBeOffScreen(true);
		}

Tunnel::Tunnel(b2World *world,float width,float height,bool leftEntrance,bool rightExit)	
	:ContinuousSegment(world,width,height)
		{
			_polygonVerticies = (b2Vec2*)malloc(sizeof(b2Vec2)*4);
			ContinuousSegment::GetVertsSquare(_polygonVerticies,_width,_height);
			left = new LineSegment(world,0,height);
			right = new LineSegment(world,0,height);
			bool _leftEntrance=leftEntrance;
			bool _rightExit=rightExit;
			this->SetCanBeOffScreen(true);
		}

float Tunnel::getEndVertice(){
	return 2;
}

float Tunnel::getStartVertice(){
	return 0;
}

void Tunnel::GenerateBody()
{

}

bool Tunnel::GenerateNextBody()
{
	left->GenerateBody();
	right->GenerateBody();
	return ContinuousSegment::GenerateNextBody();
}

void Tunnel::InitilizeData()
{
	left->InitilizeData();
	right->InitilizeData();

	float y,x;
	y = Segment::_startWorldPosition.y+_polygonVerticies[0].y;
	x = Segment::_startWorldPosition.x+_polygonVerticies[0].x;
	Segment::_GameWorldVerticies[0] =new b2Vec2((x)*PTM_RATIO,(y)*PTM_RATIO);
	y = Segment::_startWorldPosition.y+_polygonVerticies[3].y;
	x = Segment::_startWorldPosition.x+_polygonVerticies[3].x;
	Segment::_GameWorldVerticies[3] =new b2Vec2((x)*PTM_RATIO,(y)*PTM_RATIO);
	y = Segment::_startWorldPosition.y+_polygonVerticies[1].y;
	x = Segment::_startWorldPosition.x+_polygonVerticies[1].x;
	Segment::_GameWorldVerticies[1] =new b2Vec2((x)*PTM_RATIO,(y)*PTM_RATIO);
	y = Segment::_startWorldPosition.y+_polygonVerticies[2].y;
	x = Segment::_startWorldPosition.x+_polygonVerticies[2].x;
	Segment::_GameWorldVerticies[2] =new b2Vec2((x)*PTM_RATIO,(y)*PTM_RATIO);
}

float Tunnel::CalculateDistance()
{
	return 0.0f;
}

float Tunnel::GetYForX(float x)
{
	return 0.0f;
}

CCPoint Tunnel::worldToLocalPoint(b2Vec2 point){
	return ccp(0,0);
}