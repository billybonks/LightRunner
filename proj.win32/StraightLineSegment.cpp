#include "StraightLineSegment.h"

StraightLineSegment::StraightLineSegment(b2World *world,b2Vec2 startPosition,float width,float height)
	:ContinuousLineSegment(world,startPosition){
		this->_width = width/PTM_RATIO;
		this->_height = height/PTM_RATIO;
}

StraightLineSegment::StraightLineSegment(b2World *world,b2Vec2 startPosition,float width,float height,float steps)
	:ContinuousLineSegment(world,startPosition)
{
	this->_width = width/PTM_RATIO;
	this->_height = height/PTM_RATIO;
	this->_steps = steps;
	this->_stepWidth = _width/_steps;
	this->_polygonStartPos = (b2Vec2*)malloc(_steps*sizeof(b2Vec2));
	float widthPerStep = _width/_steps;
	ContinuousLineSegment::GetVertsSquare(_polygonVerticies,widthPerStep,_height);
}

void StraightLineSegment::GenerateBody(b2Body* retBody)
{
	while(this->GenerateNextBody(retBody)){
		//Do Something
	}
}


bool StraightLineSegment::GenerateNextBody(b2Body* retBody)
{ 
	if(_currentStep == _steps){
		if(child != NULL){
			if(child->GenerateNextBody(retBody)){
				return true;
			}else{
				return false;
			}
		}
		return false;
	}
	b2Vec2 _currentStepStartPosition = _polygonStartPos[_currentStep];
	_currentStep++;
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(_currentStepStartPosition.x,_currentStepStartPosition.y);
	retBody =world->CreateBody(&bodyDef);
	b2FixtureDef* fixture = new b2FixtureDef();
	bodyDef.position.Set(_currentStepStartPosition.x,_currentStepStartPosition.y);
	retBody =world->CreateBody(&bodyDef);
	int32 count = 4;
	b2PolygonShape polygon;
	polygon.Set(_polygonVerticies, count);
	fixture->shape = &polygon;
	fixture->density = 1.0f;
	fixture->friction = 0.3f;
	retBody->CreateFixture(fixture);
	return true;
}

b2Vec2 StraightLineSegment::GetGameWorldVerticies(int verticie)
{ 
	return _GameWorldVerticies[verticie];
}

void StraightLineSegment::InitilizeData(){
	_startWorldPosition;
	//LineSegment::_startWorldPosition.x = (_polygonVerticies[0].x*-1);
	_currentStepStartPosition.x = LineSegment::_startWorldPosition.x;
	_currentStepStartPosition.y = LineSegment::_startWorldPosition.y;
	//LineSegment::_startWorldPosition.x = LineSegment::_startWorldPosition.x -((_polygonVerticies[0].x*-1)/_steps-1);
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
	}	
	_GameWorldVerticies;
}

void StraightLineSegment::OffsetStartPosition(){
	this->_startWorldPosition.x = _startWorldPosition.x + _stepWidth/2;
	this->_startWorldPosition.y = _startWorldPosition.y - _height/2;
}
