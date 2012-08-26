#include "Platform.h"

Platform::Platform(CCPoint position,float width,float height){
	_position = position;
	light = Light(position,width,height);	
	this->sprite = (CCSprite*) &light;
}

void Platform::createBox2dObject(b2World* world){
	b2BodyDef bodyDef;

	bodyDef.type = b2_kinematicBody;
	bodyDef.position.Set(_position.x,_position.y);
	body =world->CreateBody(&bodyDef);
	b2Vec2 vertices[4];
	vertices[0].Set(-light._width/2, -light._height/2);
	vertices[1].Set(light._width/2, -light._height/2);
	vertices[2].Set(light._width/2, light._height/2);
	vertices[3].Set(-light._width/2, light._height/2);
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