#include "LineSegment.h"

void LineSegment::GetVertsInclineSquare(b2Vec2 vertices[],float width,float height,float incline){
	vertices[0].Set(-width/2, -height/2);
	vertices[1].Set(width/2, (height/2));
	vertices[2].Set(vertices[1].x, vertices[1].y+(incline/2));
	vertices[3].Set(vertices[0].x, vertices[0].y+(incline/2));
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
	this->_startWorldPosition = *new b2Vec2(startPosition.x/PTM_RATIO,startPosition.y/PTM_RATIO);
	this->world = world;
	//this->_lastVerts = originPoints;
}

LineSegment::LineSegment(b2World *world,float width, float height){
		this->_width = width/PTM_RATIO;
	this->_height = height/PTM_RATIO;
	this->world = world;
}

LineSegment::LineSegment(b2World *world,b2Vec2 startPosition,float width, float height){
	this->_width = width/PTM_RATIO;
	this->_height = height/PTM_RATIO;
	this->_startWorldPosition = *new b2Vec2(startPosition.x/PTM_RATIO,startPosition.y/PTM_RATIO);
	this->world = world;
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

b2Vec2* LineSegment::GetGameWorldVerticies(int verticie){
	return _GameWorldVerticies[verticie];
}

void LineSegment::SetPosition(b2Vec2 startPosition){
	startPosition.x = startPosition.x/PTM_RATIO;
	startPosition.y = startPosition.y/PTM_RATIO;
	this->_startWorldPosition =startPosition;
}

void LineSegment::GenerateBody(){

}

void LineSegment::InitilizeData(){

}

bool LineSegment::GenerateNextBody(){
	return false;
}

b2Vec2 LineSegment::GetPosition(){
	b2Vec2 *ret = new b2Vec2( _startWorldPosition);
	ret->x = ret->x*PTM_RATIO;
	ret->y = ret->y*PTM_RATIO;
	return *ret;
}

float LineSegment::GetWidth(){
	return this->_width*PTM_RATIO;
}

float LineSegment::GetHeight(){
	return _height*PTM_RATIO;
}

bool LineSegment::isOffScreen(float scale){
	float x =  this->body->GetPosition().x* PTM_RATIO;
	float y =  this->body->GetPosition().y* PTM_RATIO;
	float top = screen->origin.y-50;
	float left = screen->origin.x-50;
	float right = screen->origin.x+screen->size.width+50;
	float bottem = screen->origin.y+screen->size.height+50;
	top = top / scale;
	left = left / scale;
	right = right / scale;
	bottem = bottem / scale;
	if(x<left){
		return true;
	}
	return false;
}

void LineSegment::OffsetStartPosition( int targetAttachementVerticie, int sourceAttachementVerticie,LineSegment* target )
{
	b2Vec2 sourceVert = this->_polygonVerticies[sourceAttachementVerticie];
	b2Vec2* targetVert = target->GetGameWorldVerticies(targetAttachementVerticie);
	this->_startWorldPosition.x = targetVert->x/PTM_RATIO;
	this->_startWorldPosition.y = targetVert->y/PTM_RATIO;
	this->_startWorldPosition.x -= sourceVert.x;
	this->_startWorldPosition.y -= sourceVert.y;
}

float LineSegment::CalculateDistance(){
	return 0;
}

float LineSegment::GetYForX(float x){
	return 0;
}