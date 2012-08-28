#include "Platform.h"

Platform::Platform(){
	this->sprite = Light::retainedLight(this->screen);
}

void Platform::createBox2dObject(b2World* world){
	b2BodyDef bodyDef;

	bodyDef.type = b2_kinematicBody;
	bodyDef.position.Set(this->sprite->getPosition().x/PTM_RATIO, this->sprite->getPosition().y/PTM_RATIO);
		bodyDef.userData = this;
			bodyDef.fixedRotation = true;

	this->body =world->CreateBody(&bodyDef);
	 b2PolygonShape dynamicBox;
	   dynamicBox.SetAsBox((this->sprite->getContentSize().width/PTM_RATIO)/2, (this->sprite->getContentSize().height/PTM_RATIO)/2);//These are mid points for our 1m box err:if object is scaled/rotated this will bug out

	//b2Vec2 vertices[4];
//	vertices[0].Set(-light->_width/2, -light->_height/2);
//	vertices[1].Set(light->_width/2, -light->_height/2);
	//vertices[2].Set(light->_width/2, light->_height/2);
	//vertices[3].Set(-light->_width/2, light->_height/2);
	//int32 count = 4;
	//b2PolygonShape polygon;
	//polygon.Set(vertices, count);
	//polygon.SetAsBox(1.0f, 1.0f);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 0.0f;
	fixtureDef.friction = 0.3f;
	body->CreateFixture(&fixtureDef);

}
