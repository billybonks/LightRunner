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

	LineSegment::LineSegment(b2Vec2 originPoints[],float maxHieght,float thickness,float width){
		this->_maxHieght = maxHieght;
		this->_thickness = thickness;
		this->_width = width;
		this->_steps =maxHieght/thickness;
		this->_currentStep = 0;
		_lastVerts[0] = originPoints[0];
		_lastVerts[1] = originPoints[1];
		_stepWidth = _width/_steps;
		_inclinePerStep = _maxHieght/_steps;
		//this->_lastVerts = originPoints;
	}

	b2Vec2 LineSegment::getLinearVelocity(){
		return b2Vec2(_stepWidth,_inclinePerStep);
	}

	b2Vec2 LineSegment::getLastVerticies(){
		return b2Vec2();
	}

	float LineSegment::getIncline(){
		return 0.0f;
	}

	bool LineSegment::GenerateNextBody(b2Body* retBody){
		_currentStep++;
		b2Vec2 vertices[4];
		GetVertsInclineSquare(vertices,_stepWidth,_thickness,_inclinePerStep);
		//GenSquare(vertices,world,startPos);
		//startPos.x += vertices[2].x+(vertices[2].x);
		//startPos.y +=(inclinePerStep/2);
		return true;
	}