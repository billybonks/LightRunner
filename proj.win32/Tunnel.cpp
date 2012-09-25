#include "LineSegment.h"

Tunnel::Tunnel(b2World *world,b2Vec2 startPosition,float width,float height,bool leftEntrance,bool rightExit)
	:ContinuousLineSegment(world,startPosition,width,height)
		{
			left = new EdgeLineSegment(world,0,height);
			right = new EdgeLineSegment(world,0,height);
		}

Tunnel::Tunnel(b2World *world,float width,float height,bool leftEntrance,bool rightExit)	
	:ContinuousLineSegment(world,width,height)
		{
			left = new EdgeLineSegment(world,0,height);
			right = new EdgeLineSegment(world,0,height);
		}


void  Tunnel::OffsetStartPosition( int targetAttachementVerticie, int sourceAttachementVerticie,LineSegment* target ){

}
void Tunnel::GenerateBody()
{

}

bool Tunnel::GenerateNextBody()
{
	return true;
}

void Tunnel::InitilizeData()
{

}

float Tunnel::CalculateDistance()
{
	return 0.0f;
}

float Tunnel::GetYForX(float x)
{
	return 0.0f;
}