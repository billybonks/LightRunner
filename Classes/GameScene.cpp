#include "GameScene.h"
#include "Light.h"
#include "cocos2d.h"
#include "b2debugDraw.h"
#include "ContactListener.h"
using namespace cocos2d;

CCScene* Game::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		Game *layer = Game::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}
void Game::draw(){
	B2DLayer::draw();
}
// on "init" you need to initialize your instance
bool Game::init()
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
 //END
	//setting ContactListner
	//ContactListener listener = new ContactListener();
	//world->SetContactListener(listener);
	//Preping Vector
	platforms.reserve(10);
	//prep stats
	_scale = 0.01f;
	this->setScale(_scale);
	 winSize = CCDirector::sharedDirector()->getWinSize();

	_player = (Player*) GameObject::retainedObjectWithSpriteFrameName("stander.png",&screenBounds);
	_player->getSprite()->setPosition(ccp(winSize.width * 0.1, winSize.height * 0.5));
	_batchNode->addChild(_player->getSprite(), 1);
	_player->createBox2dObject(B2DLayer::world);
	_player->SetCanBeOffScreen(true);

	//animation
	CCArray* frames = CCArray::create(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("runner1.png"),CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("runner2.png"),CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("runner3.png"),NULL);
	CCAnimation *animation = CCAnimation::create(frames,0.2f);
	_player->getSprite()->runAction(CCRepeatForever::create(CCAnimate::create(animation)));   
	_lastPos = _player->getSprite()->getPosition();
	
	//boss
	_boss = GameObject::retainedObjectWithSpriteFrameName("boss2.png",&screenBounds);
	_boss->getSprite()->setPosition(ccp(winSize.width * 0.9, winSize.height * 0.5));
	_batchNode->addChild(_boss->getSprite(), 1);
	_boss->createBox2dObject(B2DLayer::world);
	_boss->SetCanBeOffScreen(true);

	//Register for touches and gameloop
	this->setTouchEnabled(true) ;
	this->scheduleUpdate();
	move=true;
	spawnrate=3;
	//Debug(false);
	//get the existing filter
  b2Filter filter = _boss->getBody()->GetFixtureList()->GetFilterData();
  //make no collisions
  filter.maskBits = 0;
  //and set it back
  //this->setScale(0.5);
  _boss->getBody()->GetFixtureList()->SetFilterData(filter);
	//floor
	_floor = GameObject::retainedObjectWithSpriteFrameName("floor.png",&screenBounds);
	_floor->getSprite()->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.1));
	_batchNode->addChild(_floor->getSprite(), 1);
	_floor->createBox2dObject(world);
	_floor->getBody()->SetType(b2_kinematicBody);
	_floor->SetCanBeOffScreen(true);
				b2Vec2 start = b2Vec2::b2Vec2();
			start.Set(_boss->getSprite()->getPositionX()+50,_boss->getSprite()->getPositionY());
	_stats =  Statistics();
	this->_spawner = new Spawner(&_stats,world,start);
	return true;
}
void Game::update(float dt) {
	_player->updateTrail(dt);
	this->_spawner->update();
	
	//CCLog("%f",dt);

	//boss antigravity:
	_boss->getBody()->ApplyForce(_boss->getBody()->GetMass()*b2Vec2(0.0f, 10.0f),_boss->getBody()->GetWorldCenter());
	
	_boss->getBody()->SetLinearVelocity(b2Vec2(_player->getBody()->GetLinearVelocity().x,_boss->getBody()->GetLinearVelocity().y));
	//_floor->getBody()->SetLinearVelocity(b2Vec2(_player->getBody()->GetLinearVelocity().x,0.0f));

	//acceleration
	if(_stats.GetVelocity()<_stats.GetMaximumVelocity()){
		_player->getBody()->ApplyForce(_player->getBody()->GetMass()*b2Vec2(5.0f, 0.0f),_player->getBody()->GetWorldCenter());
	}


	B2DLayer::update(dt);
	_stats.IncrementDistance(_player->getSprite()->getPosition().x - _lastPos.x);
	_lastPos = _player->getSprite()->getPosition();
	_stats.SetVelocity(_player->getBody()->GetLinearVelocity().x);

	CleanWorld();
	if(move==false){
		spawnrate+=dt;
		if(spawnrate>=10){
			spawnrate=10;
			//_boss->getBody()->ApplyLinearImpulse(b2Vec2(0.0f, 0.5f),_boss->getBody()->GetWorldCenter());
			move=true;
		}
	}
	else{
		spawnrate-=dt;
		if(spawnrate<=0){//err:doesn't account for change in players height on new platform
			GameObject* test = GameObject::retainedObjectWithSprite(Light::retainedLight(&screenBounds),&screenBounds);

			//StraightLineSegment segment(B2DLayer::world,start,50.0f,10.0f,1);
			b2Body* body = NULL;
			//segment.InitilizeData();
			//segment.GenerateBody(body);
			/*test->getSprite()->setPosition(ccp(_boss->getSprite()->getPositionX()+50, _boss->getSprite()->getPositionY()));
			this->addChild(test->getSprite());	
			test->createBox2dObject(world);

			b2Body* body = test->getBody();
			body->SetType(b2_staticBody);
			spawnrate=0;
			platforms.push_back((GameObject*)test);
			move=false;*/
		}
	}
}

void Game::CleanWorld(){
		vector<GameObject*> objectsToClean(0);
	//Iterate over the bodies in the physics world
	for (b2Body* b = world->GetBodyList(); b; b = b->GetNext()) {
		if (b->GetUserData() != NULL) {
			GameObject *myActor = (GameObject*)b->GetUserData();
			if(myActor->isOffScreen(_scale)&&!myActor->canBeOffScreen()){
					objectsToClean.push_back(myActor);	
			}
			else {
			//Synchronize the AtlasSprites position and rotation with the corresponding body
				myActor->getSprite()->setPosition(CCPointMake( b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO));
				myActor->getSprite()->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
			}
		}	
	}
	for(int i =0;i<objectsToClean.size();i++){
		objectsToClean.at(i)->removeFromParentAndCleanup(); //err:not 100% sure this frees memory - test!
	}
	//move screen
	this->setPosition(ccp((-_player->getBody()->GetPosition().x*PTM_RATIO+winSize.width * 0.1)*_scale,(-_player->getBody()->GetPosition().y*PTM_RATIO+winSize.height * 0.3)*_scale));
	screenBounds= CCRect(-this->getPositionX() ,-this->getPositionY(),this->getContentSize().width,this->getContentSize().height);
}
void Game::ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event)
{
		_player->jump();
}

Statistics* Game::GetStats(){
	return &_stats;
}

void Game::menuCloseCallback(CCObject* pSender)
{
	B2DLayer::menuCloseCallback(pSender);
	CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
