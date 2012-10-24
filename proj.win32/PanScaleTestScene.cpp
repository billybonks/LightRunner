#include "PanScaleTestScene.h"
#include "Light.h"
#include "cocos2d.h"
#include "b2debugDraw.h"
#include "SimpleAudioEngine.h"    

using namespace cocos2d;

CCScene* PanScaleTestScene::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		PanScaleTestScene *layer = PanScaleTestScene::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}
void PanScaleTestScene::draw(){
	B2DLayer::draw();
}
// on "init" you need to initialize your instance
bool PanScaleTestScene::init()
{
//////////////////////////////
	// 1. super init first
	if ( !B2DLayer::init() )
	{
		return false;
	}
	//Load Spritesheets
	_batchNode = CCSpriteBatchNode::create("runner.png");
	this->addChild(_batchNode);
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("runner.plist");
	//Register for touches and gameloop
	this->setTouchEnabled(true) ;
	this->scheduleUpdate();
	this->world=B2DLayer::world;

	_scale = 1.0f;
	this->setScale(_scale);
	winSize = CCDirector::sharedDirector()->getWinSize();
	playerScreenPos = ccp(winSize.width*0.1, winSize.height*0.5);
	
	//screentest
	test = GameObject::retainedObjectWithSpriteFrameName("boss2.png",world);
	_batchNode->addChild(test->getSprite(), 1);
	test->setPosition(playerScreenPos);
	test->getBody()->SetType(b2_staticBody);

	//left
	left = GameObject::retainedObjectWithSpriteFrameName("0.png",world);
	_batchNode->addChild(left->getSprite(), 1);
	left->setPosition(ccp(0, winSize.height/2));
	left->getBody()->SetType(b2_staticBody);

	//right
	right = GameObject::retainedObjectWithSpriteFrameName("0.png",world);
	_batchNode->addChild(right->getSprite(), 1);
	right->setPosition(ccp(winSize.width, winSize.height/2));
	right->getBody()->SetType(b2_staticBody);






	//botleft
	botleft = GameObject::retainedObjectWithSpriteFrameName("stander.png",world);
	_batchNode->addChild(botleft->getSprite(), 1);
	botleft->setPosition(ccp(0, 0));
	botleft->getBody()->SetType(b2_staticBody);
	//topleft
	topleft = GameObject::retainedObjectWithSpriteFrameName("stander.png",world);
	_batchNode->addChild(topleft->getSprite(), 1);
	topleft->setPosition(ccp(0, winSize.height));
	topleft->getBody()->SetType(b2_staticBody);
	//topright
	topright = GameObject::retainedObjectWithSpriteFrameName("stander.png",world);
	_batchNode->addChild(topright->getSprite(), 1);
	topright->setPosition(ccp(winSize.width, winSize.height));
	topright->getBody()->SetType(b2_staticBody);
	//botright
	botright = GameObject::retainedObjectWithSpriteFrameName("stander.png",world);
	_batchNode->addChild(botright->getSprite(), 1);
	botright->setPosition(ccp(winSize.width, 0));
	botright->getBody()->SetType(b2_staticBody);



	//this->setScale(_scale);
	
	//this->setPosition(ccp((-_player->getPosition().x),(-_player->getPosition().y)));
//	this->setAnchorPoint(ccp(0,0.0f));
	//this->setPosition(0,0);
	this->setPosition(ccp((-test->getPosition().x+(playerScreenPos.x)),(-test->getPosition().y+(playerScreenPos.y))));
	GameObject::setScreen(&this->screenBounds);
	return true;
}


void PanScaleTestScene::update(float dt) {
	
	//Box2D tick
	B2DLayer::update(dt);
	
}

void PanScaleTestScene::ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event)
{
	//this->setScale(this->getScale()+0.1);
	CCTouch* touch = (CCTouch*)( touches->anyObject() );
    CCPoint location = touch->locationInView();
    location = CCDirector::sharedDirector()->convertToGL(location);
	float x =location.x;
	float y = location.y;
	if (x<240&&y<160)
	{
		//botleft
				test->setPosition(ccp(test->getPositionX()-15,test->getPositionY()));
	this->setPosition(ccp((-test->getPosition().x+playerScreenPos.x),(-test->getPosition().y+playerScreenPos.y)));
	CCPoint wtf = test->getPosition();
	float x = wtf.x/winSize.width;
	float y = wtf.y/winSize.height;
	this->setAnchorPoint(ccp(x,y));

	}
	else if(x<240&&y>160)
	{
		//topleft

		_scale=this->getScale()+0.1;
		this->setScale(_scale);
	}
	else if(x>240&&y<160)
	{
		//botright.
		test->setPosition(ccp(test->getPositionX()+15,test->getPositionY()));
	this->setPosition(ccp((-test->getPosition().x+playerScreenPos.x),(-test->getPosition().y+playerScreenPos.y)));
	CCPoint wtf = test->getPosition();
	float x = wtf.x/winSize.width;
	float y = wtf.y/winSize.height;
	this->setAnchorPoint(ccp(x,y));

	}
	else if(x>240&&y>160)
	{
		//topright
		_scale=this->getScale()-0.1;
		this->setScale(_scale);

	}
	float screenwidth = this->getContentSize().width/_scale;
	float screenheight = this->getContentSize().height/_scale;
	float playershiftx = screenwidth*(playerScreenPos.x/winSize.width);
	float playershifty = screenheight*(playerScreenPos.y/winSize.height);
	screenBounds= CCRect(test->getPosition().x-playershiftx ,test->getPosition().y-playershifty,screenwidth,screenheight);

	botleft->setPosition(ccp(screenBounds.origin.x,screenBounds.origin.y));
	topleft->setPosition(ccp(screenBounds.origin.x,screenBounds.origin.y+screenheight));
	botright->setPosition(ccp(screenBounds.origin.x+screenwidth,screenBounds.origin.y));
	topright->setPosition(ccp(screenBounds.origin.x+screenwidth,screenBounds.origin.y+screenheight));

	//left->isOffScreen();
	//right->isOffScreen();
//	CCLog("%f, %f", this->getPositionX(),this->getPositionY());
	//CCLog("%f, %f,%f, %f", screenBounds.origin.x,screenBounds.origin.y,screenBounds.size.width,screenBounds.size.height);
	
	if(left->isOffScreen()){
		CCLog("Left is offscreen");
	}
	else
	{
		CCLog("Left is onscreen");
	}

	if(right->isOffScreen()){
		CCLog("Right is offscreen");
	}
	else
	{
		CCLog("Right is onscreen");
	}
	
}

void PanScaleTestScene::ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event)
{
	
}

void PanScaleTestScene::menuCloseCallback(CCObject* pSender)
{
	B2DLayer::menuCloseCallback(pSender);
	CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
