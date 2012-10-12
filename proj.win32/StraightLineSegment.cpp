#include "LineSegment.h"
#include "Light.h"

StraightLineSegment::StraightLineSegment(b2World *world,b2Vec2 startPosition,float width,float height)
	:ContinuousLineSegment(world,startPosition,width,height)
{
	_polygonVerticies = (b2Vec2*)malloc(sizeof(b2Vec2)*4);
	ContinuousLineSegment::GetVertsSquare(_polygonVerticies,_width,_height);
	this->SetCanBeOffScreen(true);

}

StraightLineSegment::StraightLineSegment(b2World *world,float width,float height):ContinuousLineSegment(world,width,height){
	_polygonVerticies = (b2Vec2*)malloc(sizeof(b2Vec2)*4);
	ContinuousLineSegment::GetVertsSquare(_polygonVerticies,_width,_height);
	this->SetCanBeOffScreen(true);

}

void StraightLineSegment::GenerateBody()
{

}


bool StraightLineSegment::GenerateNextBody()
{ 
	_startWorldPosition;
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(_startWorldPosition.x,_startWorldPosition.y);
	body =world->CreateBody(&bodyDef);
	b2FixtureDef* fixture = new b2FixtureDef();
	b2PolygonShape polygon;
	polygon.Set(_polygonVerticies, 4);
	fixture->shape = &polygon;
	fixture->density = 1.0f;
	fixture->friction = 0;
	fixture->userData = (void*)1;
	body->SetUserData(this);
	this->sprite=new CCSprite();
	body->CreateFixture(fixture);
	this->sprite=Light::retainedLight(_polygonVerticies);
	this->sprite->setPosition(ccp(_startWorldPosition.x*PTM_RATIO,_startWorldPosition.y*PTM_RATIO));
	GameObject::setBoundingBox();
	if(child != NULL){
		if(child->GenerateNextBody()){
			return true;
		}else{
			return false;
		}
	return false;
	}
	return false;
}

b2Vec2* StraightLineSegment::GetGameWorldVerticies(int verticie)
{ 
	return _GameWorldVerticies[verticie];
}

void StraightLineSegment::InitilizeData(){
	float y,x;
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


float StraightLineSegment::CalculateDistance(){
	if(this->_sourceAttachmentVerticie == 0||this->_sourceAttachmentVerticie == 3){
		return this->GetWidth();
	}
	return this->GetWidth()*-1;
}

float StraightLineSegment::GetYForX(float x){
	return 0;
}

CCPoint StraightLineSegment::worldToLocalPoint(b2Vec2 point){
	return ccp(0,0);
}

void StraightLineSegment::removeFromParentAndCleanup(){
			this->body->GetWorld()->DestroyBody( this->body );
			this->sprite->removeFromParentAndCleanup(true);
		}	