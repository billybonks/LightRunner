#include "InclineLineSegment.h"

	InclineLineSegment::InclineLineSegment(b2World *world,b2Vec2 startPosition,float width,float maxHeight,float thickness)
		:StraightLineSegment(world,startPosition,width,maxHeight)
	{
		int slopeModifier = 1;
		thickness= thickness/PTM_RATIO;
		width = width/PTM_RATIO;
		maxHeight = maxHeight/PTM_RATIO;
		if(thickness < 0){
			slopeModifier = -1;
		}
		this->_thickness = slopeModifier*thickness;
		this->_steps =maxHeight/_thickness;
		this->_inclinePerStep = slopeModifier*(maxHeight/_steps)*2;
		this->_stepWidth = _width/_steps;
		this->_polygonStartPos = (b2Vec2*)malloc(_steps*sizeof(b2Vec2));
	}

	b2Vec2 InclineLineSegment::getLinearVelocity(){
		return b2Vec2();
	}

	void InclineLineSegment::InitilizeData(){
		LineSegment::_currentStepStartPosition = this->_startWorldPosition; 
		float widthPerStep = _width/_steps;
		ContinuousLineSegment::GetVertsInclineSquare(_polygonVerticies,widthPerStep,_thickness,_inclinePerStep);
		for(int i = 0;i<_steps; i++){
			_polygonStartPos[i] =  LineSegment::_currentStepStartPosition;
			if(i == 0){
					float y = LineSegment::_currentStepStartPosition.y+_polygonVerticies[0].y;
					float x = LineSegment::_currentStepStartPosition.x+_polygonVerticies[0].x;
					LineSegment::_GameWorldVerticies[0] =b2Vec2((x)*PTM_RATIO,(y)*PTM_RATIO);
					 y = LineSegment::_currentStepStartPosition.y+_polygonVerticies[3].y;
					 x = LineSegment::_currentStepStartPosition.x+_polygonVerticies[3].x;
					LineSegment::_GameWorldVerticies[3] =b2Vec2((x)*PTM_RATIO,(y)*PTM_RATIO);
			}
			if(_steps-1 == i){
					float y = LineSegment::_currentStepStartPosition.y+_polygonVerticies[1].y;
					float x = LineSegment::_currentStepStartPosition.x+_polygonVerticies[1].x;
					LineSegment::_GameWorldVerticies[1] =b2Vec2((x)*PTM_RATIO,(y)*PTM_RATIO);
					 y = LineSegment::_currentStepStartPosition.y+_polygonVerticies[2].y;
					 x = LineSegment::_currentStepStartPosition.x+_polygonVerticies[2].x;
					LineSegment::_GameWorldVerticies[2] =b2Vec2((x)*PTM_RATIO,(y)*PTM_RATIO);
			}
			LineSegment::_currentStepStartPosition.x += _polygonVerticies[2].x+(_polygonVerticies[2].x);
			LineSegment::_currentStepStartPosition.y +=(_inclinePerStep/2);
		}
	}

	void InclineLineSegment::OffsetStartPosition(){
		this->_startWorldPosition.x = _startWorldPosition.x + _stepWidth/2;
		this->_startWorldPosition.y = _startWorldPosition.y - _inclinePerStep/4;
}