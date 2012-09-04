#include "LineSegment.h"
	
	void LineSegment::GetVertsInclineSquare(b2Vec2 vertices[],float width,float height,float incline){
		vertices[0].Set(-width/2, -height/2);
		vertices[1].Set(width/2, (-height/2)+(incline/2));
		vertices[2].Set(width/2, (height/2)+(incline/2));
		vertices[3].Set(-width/2, height/2);
	}

	void LineSegment::GetVertsSquare(b2Vec2 vertices[],float width,float height){
		vertices[0].Set(-width/2, -height/2);
		vertices[1].Set(width/2, -height/2);
		vertices[2].Set(width/2, height/2);
		vertices[3].Set(-width/2, height/2);
	}
	//INPUT EXAMPLES 
	//Inputs work in pixel values
	//LineSegment segment(B2DLayer::world,start,10.0f,-0.5f,10.0f); NEVative Sloper
	//LineSegment segment(B2DLayer::world,start,10.0f,0.5f,10.0f);	Positive Slope
	//LineSegment segment(B2DLayer::world,start,10.0f,10.0f,10.0f); Square
	//LineSegment segment(B2DLayer::world,start,5.0f,5.0f,10.0f); Rectangle
	LineSegment::LineSegment(b2World *world,b2Vec2 startPosition){
		startPosition.x = startPosition.x/PTM_RATIO;
		startPosition.y = startPosition.y/PTM_RATIO;
		int slopeModifier = 1;
		this->_currentStep = 0;
		this->_startWorldPosition = startPosition;
		this->_currentStepStartPosition  = _startWorldPosition;
		this->world = world;
		//this->_lastVerts = originPoints;
	}

	b2Vec2 LineSegment::getLinearVelocity(){
				return b2Vec2();
	}

	b2Vec2 LineSegment::getLastVerticies(){
		return b2Vec2();
	}

	float LineSegment::getIncline(){
		return 0.0f;
	}

	b2Vec2 LineSegment::GetGameWorldVerticies(int verticie){
		return _GameWorldVerticies[verticie];
	}

	void LineSegment::SetPosition(b2Vec2 startPosition){
		startPosition.x = startPosition.x/PTM_RATIO;
		startPosition.y = startPosition.y/PTM_RATIO;
		this->_startWorldPosition = startPosition;
		this->_currentStepStartPosition  = _startWorldPosition;
	}