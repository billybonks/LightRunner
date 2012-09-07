#include "InclineLineSegment.h"

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
		
	}

	b2Vec2 InclineLineSegment::getLinearVelocity(){
		return b2Vec2();
	}

	void InclineLineSegment::InitilizeData(){
		ContinuousLineSegment::GetVertsInclineSquare(_polygonVerticies,_width,_height,_thickness);
		float x,y;
		y = LineSegment::_startWorldPosition.y+_polygonVerticies[0].y;
		x = LineSegment::_startWorldPosition.x+_polygonVerticies[0].x;
		LineSegment::_GameWorldVerticies[0] =b2Vec2((x)*PTM_RATIO,(y)*PTM_RATIO);
		y = LineSegment::_startWorldPosition.y+_polygonVerticies[3].y;
		x = LineSegment::_startWorldPosition.x+_polygonVerticies[3].x;
		LineSegment::_GameWorldVerticies[3] =b2Vec2((x)*PTM_RATIO,(y)*PTM_RATIO);
		y = LineSegment::_startWorldPosition.y+_polygonVerticies[1].y;
		x = LineSegment::_startWorldPosition.x+_polygonVerticies[1].x;
		LineSegment::_GameWorldVerticies[1] =b2Vec2((x)*PTM_RATIO,(y)*PTM_RATIO);
		y = LineSegment::_startWorldPosition.y+_polygonVerticies[2].y;
		x = LineSegment::_startWorldPosition.x+_polygonVerticies[2].x;
		LineSegment::_GameWorldVerticies[2] =b2Vec2((x)*PTM_RATIO,(y)*PTM_RATIO);
		_GameWorldVerticies;
	}

	void InclineLineSegment::OffsetStartPosition(){
		this->_startWorldPosition.x = _startWorldPosition.x + _width/2;
		this->_startWorldPosition.y = _startWorldPosition.y + (_height)/2;
		this->_startWorldPosition.y = _startWorldPosition.y -_thickness/2;
}