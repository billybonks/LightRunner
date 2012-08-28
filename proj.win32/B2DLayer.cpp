#include "B2DLayer.h"
#include "cocos2d.h"
#include "b2debugDraw.h"

bool B2DLayer::init(){
	if ( !CCLayer::init() )
	{
		return false;
	}
	b2Vec2 gravity;
	_secondCounter=0.0f;
	gravity.Set(0.0f, -10.0f);
	world = new b2World(gravity);
	world->SetContinuousPhysics(true);
	//DEBUG
	b2DebugDraw *debugDraw = new b2DebugDraw(PTM_RATIO);
	world->SetDebugDraw(debugDraw);
	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	flags += b2Draw::e_jointBit;
	flags += b2Draw::e_centerOfMassBit;
	flags += b2Draw::e_aabbBit;
	flags += b2Draw::e_pairBit;
	debugDraw->SetFlags(flags);
return true;
}

void B2DLayer::draw(){
	CCLayer::draw();
	ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
	kmGLPushMatrix();
	if(_debug){
		world->DrawDebugData();
	}
	kmGLPopMatrix();
}

void B2DLayer::Debug(bool debug){
		_debug = debug;
}


void B2DLayer::update(float dt){
	_secondCounter++;
	int32 velocityIterations = 8;
	int32 positionIterations = 1;
	float32 timeStep = 1.0f / 60.0f;
	world->Step(timeStep, velocityIterations, positionIterations);
	if(_secondCounter == 60){
		_secondCounter = 0;
	}
}

void B2DLayer::menuCloseCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}