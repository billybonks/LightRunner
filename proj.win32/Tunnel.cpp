#include "LineSegment.h"
#include "Light.h"

Tunnel::Tunnel(b2World *world,b2Vec2 startPosition,float width,float height,bool leftEntrance,bool rightExit)
	:ContinuousLineSegment(world,startPosition,width,height)
		{
			_polygonVerticies = (b2Vec2*)malloc(sizeof(b2Vec2)*4);
			ContinuousLineSegment::GetVertsSquare(_polygonVerticies,_width,_height);
			left = new EdgeLineSegment(world,0,height);
			right = new EdgeLineSegment(world,0,height);
			bool _leftEntrance=leftEntrance;
			bool _rightExit=rightExit;
			this->SetCanBeOffScreen(true);
		}

Tunnel::Tunnel(b2World *world,float width,float height,bool leftEntrance,bool rightExit)	
	:ContinuousLineSegment(world,width,height)
		{
			_polygonVerticies = (b2Vec2*)malloc(sizeof(b2Vec2)*4);
			ContinuousLineSegment::GetVertsSquare(_polygonVerticies,_width,_height);
			left = new EdgeLineSegment(world,0,height);
			right = new EdgeLineSegment(world,0,height);
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
	return ContinuousLineSegment::GenerateNextBody();
}

void Tunnel::InitilizeData()
{
	left->InitilizeData();
	right->InitilizeData();

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