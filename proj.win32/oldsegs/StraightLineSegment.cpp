#include "Segment.h"
#include "PlatformSprite.h"

StraightSegment::StraightSegment(b2World *world,b2Vec2 startPosition,float width,float height)
	:ContinuousSegment(world,startPosition,width,height)
{
	_polygonVerticies = (b2Vec2*)malloc(sizeof(b2Vec2)*4);
	ContinuousSegment::GetVertsSquare(_polygonVerticies,_width,_height);
	this->SetCanBeOffScreen(true);

}

StraightSegment::StraightSegment(b2World *world,float width,float height):ContinuousSegment(world,width,height){
	_polygonVerticies = (b2Vec2*)malloc(sizeof(b2Vec2)*4);
	ContinuousSegment::GetVertsSquare(_polygonVerticies,_width,_height);
	this->SetCanBeOffScreen(true);

}

void StraightSegment::GenerateBody()
{

}


bool StraightSegment::GenerateNextBody()
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
	this->sprite=PlatformSprite::retainedPlatformSprite(_polygonVerticies);
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

b2Vec2* StraightSegment::GetGameWorldVerticies(int verticie)
{ 
	return _GameWorldVerticies[verticie];
}

void StraightSegment::InitilizeData(){
	float y,x;
	y = Segment::_startWorldPosition.y+_polygonVerticies[0].y;
	x = Segment::_startWorldPosition.x+_polygonVerticies[0].x;
	Segment::_GameWorldVerticies[0] =new b2Vec2((x)*PTM_RATIO,(y)*PTM_RATIO);
	y = Segment::_startWorldPosition.y+_polygonVerticies[3].y;
	x = Segment::_startWorldPosition.x+_polygonVerticies[3].x;
	Segment::_GameWorldVerticies[3] =new b2Vec2((x)*PTM_RATIO,(y)*PTM_RATIO);
	y = Segment::_startWorldPosition.y+_polygonVerticies[1].y;
	x = Segment::_startWorldPosition.x+_polygonVerticies[1].x;
	Segment::_GameWorldVerticies[1] =new b2Vec2((x)*PTM_RATIO,(y)*PTM_RATIO);
	y = Segment::_startWorldPosition.y+_polygonVerticies[2].y;
	x = Segment::_startWorldPosition.x+_polygonVerticies[2].x;
	Segment::_GameWorldVerticies[2] =new b2Vec2((x)*PTM_RATIO,(y)*PTM_RATIO);
}


float StraightSegment::CalculateDistance(){
	if(this->_sourceAttachmentVerticie == 0||this->_sourceAttachmentVerticie == 3){
		return this->GetWidth();
	}
	return this->GetWidth()*-1;
}

float StraightSegment::GetYForX(float x){
	return 0;
}

CCPoint StraightSegment::worldToLocalPoint(b2Vec2 point){
	return ccp(0,0);
}

void StraightSegment::removeFromParentAndCleanup(){
			this->body->GetWorld()->DestroyBody( this->body );
			this->sprite->removeFromParentAndCleanup(true);
		}	