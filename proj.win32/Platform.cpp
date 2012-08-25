#include "Platform.h"

Platform::Platform(CCPoint origin,CCPoint destination,float lineWidth){
	light = Light(origin,destination,lineWidth);	
	this->sprite = (CCSprite*) &light;
}

void Platform::createBox2dObject(b2World* world){
	b2BodyDef bodyDef;
	bodyDef.type = b2_kinematicBody;
	bodyDef.position.Set(2.0f, 4.0f);
	b2Body* body =world->CreateBody(&bodyDef);
	b2Vec2 vertices[4];
	vertices[0].Set(0.0f, 0.0f);
	vertices[1].Set(0.0f, vertices[0].y+light._width);
	vertices[2].Set(light._destination.x,light._destination.y);
	vertices[3].Set(light._destination.x,light._destination.y-light._width);
	int32 count = 4;
	b2PolygonShape polygon;
	polygon.Set(vertices, count);
	//polygon.SetAsBox(1.0f, 1.0f);
	b2FixtureDef fixtureDef2;
	fixtureDef2.shape = &polygon;
	fixtureDef2.density = 1.0f;
	fixtureDef2.friction = 0.3f;
	body->CreateFixture(&fixtureDef2);
}