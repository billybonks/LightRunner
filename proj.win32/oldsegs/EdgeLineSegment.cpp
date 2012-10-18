#include "Segment.h"
#include "Light.h"

EdgeSegment::EdgeSegment(b2World *world,b2Vec2 startPosition,float width,float height)
	:ContinuousSegment(world,startPosition,width,height)
{
	_polygonVerticies = (b2Vec2*)malloc(sizeof(b2Vec2)*2);
	float w = _width/2;
	float h = _height/2;
	_polygonVerticies[0].Set(-w, -h);
	_polygonVerticies[1].Set(w, h);
	this->SetCanBeOffScreen(true);

}

EdgeSegment::EdgeSegment(b2World *world,float width,float height):ContinuousSegment(world,width,height)
{
	_polygonVerticies = (b2Vec2*)malloc(sizeof(b2Vec2)*2);
	float w = _width/2;
	float h = _height/2;
	_polygonVerticies[0].Set(-w, -h);
	_polygonVerticies[1].Set(w, h);
	this->SetCanBeOffScreen(true);

}

void EdgeSegment::GenerateBody()
{

}

//hello
///JOOOOOOOOOOOOOOOO
//whats up??
bool EdgeSegment::GenerateNextBody()
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(_startWorldPosition.x,_startWorldPosition.y);
	body =world->CreateBody(&bodyDef);
	body->SetUserData(this);
	b2FixtureDef* fixture = new b2FixtureDef();
	b2EdgeShape edge;
	edge.Set(_polygonVerticies[0],_polygonVerticies[1]);
	fixture->shape = &edge;
	fixture->density = 1.0f;
	fixture->friction = 0;
	body->CreateFixture(fixture);
	this->sprite=Light::retainedLight(_polygonVerticies);
	this->sprite->setPosition(ccp(_startWorldPosition.x*PTM_RATIO,_startWorldPosition.y*PTM_RATIO));
	fixture->userData = (void*) 1;
	GameObject::setBoundingBox();
	return ContinuousSegment::GenerateNextBody();
}


void EdgeSegment::InitilizeData()
{
	float w = _width;
	float h = _height;
	float x,y;
	x = _startWorldPosition.x;
	y = _startWorldPosition.y;
	this->_GameWorldVerticies[0] = new b2Vec2((x-w/2)*PTM_RATIO,(y-h/2)*PTM_RATIO);
	this->_GameWorldVerticies[1] = new b2Vec2((x+w/2)*PTM_RATIO,(y+h/2)*PTM_RATIO);
	this->_GameWorldVerticies[2] =  _GameWorldVerticies[1];
	this->_GameWorldVerticies[3] =  _GameWorldVerticies[0];
}

float EdgeSegment::CalculateDistance(){
	if(this->_sourceAttachmentVerticie == 0||this->_sourceAttachmentVerticie == 3){
		return this->GetWidth();
	}
	return this->GetWidth()*-1;
}


//y = mx+c
//m = (x2-x1)/(y2-y1)
//c = 0
// x = param
float EdgeSegment::GetYForX(float x){
	float startX = _GameWorldVerticies[0]->x/PTM_RATIO;
	float relX =  x -startX ;
	b2Vec2* v1 = _GameWorldVerticies[0];
	b2Vec2* v2 = _GameWorldVerticies[1];
	float cY = (v2->y-v1->y);
	float cX = (v2->x-v1->x);
	float m;
	if(cY!=0){
		m = cY/cX;
	}else{

		float  y = v1->y;

		return y/PTM_RATIO;
	}
					return _startWorldPosition.y-(v2->y/PTM_RATIO-v1->y/PTM_RATIO)/2 +(m*relX);
}

CCPoint EdgeSegment::worldToLocalPoint(b2Vec2 point){
		float startX = _GameWorldVerticies[0]->x/PTM_RATIO;
		float startY = _GameWorldVerticies[0]->y/PTM_RATIO;
		float relX =  point.x -startX ;
		float relY =  point.y -startY ;
		return ccp(relX,relY);
}

	void EdgeSegment::removeFromParentAndCleanup(){
			this->body->GetWorld()->DestroyBody( this->body );
			this->sprite->removeFromParentAndCleanup(true);
		}	