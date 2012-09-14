#include "LineSegment.h"

EdgeLineSegment::EdgeLineSegment(b2World *world,b2Vec2 startPosition,float width,float height)
	:ContinuousLineSegment(world,startPosition,width,height)
{
	_polygonVerticies = (b2Vec2*)malloc(sizeof(EdgeLineSegment)*2);
	float w = _width/2;
	float h = _height/2;
	_polygonVerticies[0].Set(-w, -h);
	_polygonVerticies[1].Set(w, h);
	
}

EdgeLineSegment::EdgeLineSegment(b2World *world,float width,float height):ContinuousLineSegment(world,width,height)
{
	_polygonVerticies = (b2Vec2*)malloc(sizeof(EdgeLineSegment)*2);
	float w = _width/2;
	float h = _height/2;
	_polygonVerticies[0].Set(-w, -h);
	_polygonVerticies[1].Set(w, h);
	
}

void EdgeLineSegment::GenerateBody()
{

}

//hello
///JOOOOOOOOOOOOOOOO
bool EdgeLineSegment::GenerateNextBody()
{
	_startWorldPosition;
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(_startWorldPosition.x,_startWorldPosition.y);
	body =world->CreateBody(&bodyDef);
	b2FixtureDef* fixture = new b2FixtureDef();
	b2EdgeShape edge;
	edge.Set(_polygonVerticies[0],_polygonVerticies[1]);
	fixture->shape = &edge;
	fixture->density = 1.0f;
	fixture->friction = 0;
	body->CreateFixture(fixture);
	return ContinuousLineSegment::GenerateNextBody();
}


void EdgeLineSegment::InitilizeData()
{
	float w = _width;
	float h = _height;
	float x,y;
	x = _startWorldPosition.x;
	y = _startWorldPosition.y;
	LineSegment::_GameWorldVerticies[0] = new b2Vec2((x-w/2)*PTM_RATIO,(y-h/2)*PTM_RATIO);
	LineSegment::_GameWorldVerticies[1] = new b2Vec2((x+w/2)*PTM_RATIO,(y+h/2)*PTM_RATIO);
	LineSegment::_GameWorldVerticies[2] =  _GameWorldVerticies[1];
	LineSegment::_GameWorldVerticies[3] =  _GameWorldVerticies[0];
}

float EdgeLineSegment::CalculateDistance(){
	if(this->_sourceAttachmentVerticie == 0||this->_sourceAttachmentVerticie == 3){
		return this->GetWidth();
	}
	return this->GetWidth()*-1;
}

float EdgeLineSegment::GetYForX(float x){
	b2Vec2 *startVert =   GetGameWorldVerticies(_sourceAttachmentVerticie);
	startVert->x;
	if(x>(startVert->x+_width)){
		return 0;
	}
	float difference = startVert->x -x;
	float rate = _height/_width;
	return GetGameWorldVerticies(_sourceAttachmentVerticie)->y+(difference*rate);
}