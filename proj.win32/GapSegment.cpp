#include "LineSegment.h"

GapSegment::GapSegment(b2World *world,b2Vec2 startPosition,float width,float height):EdgeLineSegment(world,startPosition,width,height){

}

GapSegment::GapSegment(b2World *world,float width,float height):EdgeLineSegment(world,width,height){

}
void GapSegment::GenerateBody(){

}

bool GapSegment::GenerateNextBody(){
	return ContinuousLineSegment::GenerateNextBody();
}