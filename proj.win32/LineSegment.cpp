#include "Segment.h"
#include "Light.h"
#include "GameScene.h"

using namespace cocos2d;

LineSegment::LineSegment()
{
	B2Segment::B2Segment();
}

LineSegment::LineSegment(b2World *world,float width,float height)
{
	B2Segment::B2Segment();
	init(world,width,height);
	generate(world);
}

LineSegment::LineSegment(b2World *world,CCPoint position,float width,float height)
{
	init(world,width,height);
	generate(world);
	this->setPosition(position);
}

void LineSegment::init(b2World *world,float width,float height){
	_gameWorldVerticesCCW = new CCPoint[2];
	this->setContentSize(CCSize( width, height));
	_polygonVerticesCCW =  new CCPoint[2];
	_polygonVerticesCCW[0]=ccp((-this->getContentSize().width/2),(-this->getContentSize().height/2)) ;
	_polygonVerticesCCW[1]= ccp((this->getContentSize().width/2),(this->getContentSize().height/2)) ;
}

void LineSegment::setPosition(const CCPoint& newPosition){
	CCNode::setPosition(newPosition);
	float x = this->getPositionX();
	float y = this->getPositionY();
	this->_gameWorldVerticesCCW[0].setPoint((x-this->getContentSize().width/2),(y-this->getContentSize().height/2));
	this->_gameWorldVerticesCCW[1].setPoint((x+this->getContentSize().width/2),(y+this->getContentSize().height/2));
	this->getBody()->SetTransform(b2Vec2(this->getPositionX()/PTM_RATIO,this->getPositionY()/PTM_RATIO),this->getBody()->GetAngle());
	this->getSprite()->setPosition(this->getPosition());
}

void LineSegment::generate(b2World *world)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	//bodyDef.position.Set(this->getPositionX()/PTM_RATIO,this->getPositionY()/PTM_RATIO);
	this->_body =world->CreateBody(&bodyDef);
	this->_body->SetUserData(NULL);//If this needs to be changed then cleanWorld if conditions identifying only game objects needs to be changed too.
	b2FixtureDef* fixture = new b2FixtureDef();
	b2EdgeShape edge;
	
	b2Vec2 leftvertex=b2Vec2(_polygonVerticesCCW[0].x/PTM_RATIO,_polygonVerticesCCW[0].y/PTM_RATIO) ;
	b2Vec2 rightvertex= b2Vec2(_polygonVerticesCCW[1].x/PTM_RATIO,_polygonVerticesCCW[1].y/PTM_RATIO) ;
	
	edge.Set(leftvertex,rightvertex);
	fixture->shape = &edge;
	fixture->density = 1.0f;
	fixture->friction = 0;
	fixture->userData = (void*) -1;

	this->_body->CreateFixture(fixture);

	this->_sprite=Light::retainedLight(_polygonVerticesCCW);

	genBoundingBox();
}

void LineSegment::addSprites(Game* game){
	game->addChild(this->getSprite());
}

float LineSegment::getStartVerticeNum(){
	return 0;
}

float LineSegment::getEndVerticeNum(){
	return 1;
}
