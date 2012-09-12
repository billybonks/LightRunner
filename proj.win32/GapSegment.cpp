#include "LineSegment.h"

GapSegment::GapSegment(b2World *world,b2Vec2 startPosition,float width,float height):EdgeLineSegment(world,startPosition,width,height){

}

void GapSegment::GenerateBody(){

}

bool GapSegment::GenerateNextBody(){

	return false;
}