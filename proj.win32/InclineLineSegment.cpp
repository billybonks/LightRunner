#include "LineSegment.h"

	InclineLineSegment::InclineLineSegment(b2World *world,b2Vec2 startPosition,float width,float maxHeight,float thickness)
		:StraightLineSegment(world,startPosition,width,maxHeight)
	{
		int slopeModifier = 1;
		thickness= thickness/PTM_RATIO;;
		if(thickness < 0){
			slopeModifier = -1;
		}
		this->_thickness = slopeModifier*thickness;
		this->_height = (slopeModifier*maxHeight)/32;
		_polygonVerticies = (b2Vec2*)malloc(sizeof(InclineLineSegment)*4);
		ContinuousLineSegment::GetVertsInclineSquare(_polygonVerticies,_width,_height,_thickness);

	}

	InclineLineSegment::InclineLineSegment(b2World *world,float width,float maxHeight,float thickness)
		:StraightLineSegment(world,width,maxHeight)
	{
		int slopeModifier = 1;
		thickness= thickness/PTM_RATIO;;
		if(thickness < 0){
			slopeModifier = -1;
		}
		this->_thickness = slopeModifier*thickness;
		this->_height = (slopeModifier*maxHeight)/32;
		_polygonVerticies = (b2Vec2*)malloc(sizeof(InclineLineSegment)*4);
		ContinuousLineSegment::GetVertsInclineSquare(_polygonVerticies,_width,_height,_thickness);
		
	}

	b2Vec2 InclineLineSegment::getLinearVelocity(){
		return b2Vec2();
	}

	void InclineLineSegment::InitilizeData(){
		float x,y;
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

float InclineLineSegment::GetYForX(float x){
	return 0;
}
CCPoint InclineLineSegment::worldToLocalPoint(b2Vec2 point){
	return ccp(0,0);
}
