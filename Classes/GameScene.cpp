#include "GameScene.h"
#include "Light.h"
#include "cocos2d.h"
#include "b2debugDraw.h"
#include "SimpleAudioEngine.h"    

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
	tracking = false;
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
	listener = new ContactListener();
	world->SetContactListener(listener);

	//prep stats
	_scale = 0.7f;
	this->setScale(_scale);
	this->setAnchorPoint(ccp(0.0f,0.0f));
	winSize = CCDirector::sharedDirector()->getWinSize();
	GameObject::SetScreen(&screenBounds);

	_player = (Player*) GameObject::retainedObjectWithSpriteFrameName("0.png");
	_player->getSprite()->setPosition(ccp(winSize.width * 0.1, winSize.height * 0.5));
	_batchNode->addChild(_player->getSprite(), 1);
	_player->getSprite()->setScale(0.8f);
	_player->createBox2dObject(B2DLayer::world);
	_player->createFootFixture(B2DLayer::world);
	_player->init();

	//animation
	CCArray* frames = CCArray::create(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("1.png"),CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("2.png"),CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("3.png"),NULL);
	CCAnimation *animation = CCAnimation::create(frames,0.2f);
	_player->getSprite()->runAction(CCRepeatForever::create(CCAnimate::create(animation)));   
	_lastPos = _player->getSprite()->getPosition();

	//boss
	_boss = GameObject::retainedObjectWithSpriteFrameName("boss2.png");
	_boss->getSprite()->setPosition(ccp(400.0f, winSize.height * 0.5));
	_batchNode->addChild(_boss->getSprite(), 1);
	_boss->createBox2dObject(B2DLayer::world);
	_boss->SetCanBeOffScreen(true);

		Light::setBoss(_boss);


	//Register for touches and gameloop
	this->setTouchEnabled(true) ;
	this->scheduleUpdate();
	move=true;
	//Debug(false);
	//get the existing filter
	b2Filter filter = _boss->getBody()->GetFixtureList()->GetFilterData();
	//make no collisions
	filter.maskBits = 0;
	//and set it back
	_boss->getBody()->GetFixtureList()->SetFilterData(filter);

	//Spawner
	b2Vec2 start = b2Vec2(_boss->getSprite()->getPositionX()+50,_boss->getSprite()->getPositionY());
	this->_spawner = new Spawner(this, &_stats,world,start,_boss);

	_stats =  Statistics();

	//MUsicccccc
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("ghosts.mp3", true);    

	return true;
}

GameObject* Game::getBoss(){
	return _boss;
}

Spawner* Game::getSpawner(){
	return this->_spawner;
}

void Game::update(float dt) {
	if(tracking)
	{
		steps += dt;
	}
	_player->updateTrail(dt);

	this->_spawner->update();

	//move boss according to platforms
	Segment* temp = _spawner->GetCurrentPlatform();
	//float newY = _spawner->GetCurrentPlatform()->GetYForX(_boss->getBody()->GetPosition().x);
	_boss->getBody()->SetLinearVelocity(b2Vec2(15,0));
	//_boss->getBody()->SetTransform(b2Vec2(_boss->getBody()->GetPosition().x,newY),_boss->getBody()->GetAngle());

	temp = listener->GetLastPlatform();
	//if(temp != NULL){
	//	newY =  temp->GetYForX(playerPos.x);
	//	if(newY-200 > playerPos.y){
	//		playerPos = _player->getBody()->GetPosition();
	//	}
	//}

	//player acceleration
	if(_stats.GetVelocity()<_stats.GetMaximumVelocity()){
		_player->getBody()->ApplyForce(_player->getBody()->GetMass()*b2Vec2(5.0f, 0.0f),_player->getBody()->GetWorldCenter());
	}

	//Box2D tick
	B2DLayer::update(dt);

	//Update Stats
	_stats.IncrementDistance(_player->getSprite()->getPosition().x - _lastPos.x);
	_lastPos = _player->getSprite()->getPosition();
	_stats.SetVelocity(_player->getBody()->GetLinearVelocity().x);

	CleanWorld();
}

void Game::CleanWorld(){
	vector<GameObject*> objectsToClean(0);
	//Iterate over the bodies in the physics world
	for (b2Body* b = world->GetBodyList(); b; b = b->GetNext()) {
		if (b->GetUserData() != NULL&&b->GetType()!=0) {
			GameObject *myActor = (GameObject*)b->GetUserData();
			bool aa = myActor->isOffScreen(_scale);
			bool bb = !myActor->canBeOffScreen();
		//	if(aa&myActor!=_player&&myActor!=_boss)
		//			CCLog("Other Off");
		//	if(aa&myActor==_player)
		//			CCLog("Player Off");
		//	if(aa&myActor==_boss)
		//			CCLog("Boss Off");
			if(aa&&bb){
				objectsToClean.push_back(myActor);	
				}
			else {
				//Synchronize the Sprites position and rotation with the corresponding body
				myActor->getSprite()->setPosition(ccp( b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO));
				myActor->setPosition(ccp( b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO));
				myActor->getSprite()->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
				myActor->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
			}
		}	
	}
	for(int i =0;i<objectsToClean.size();i++){
		objectsToClean.at(i)->removeFromParentAndCleanup(); //err:not 100% sure this frees memory - test!
	//	delete objectsToClean.at(i);
	}
	//move screen
	this->setPosition(ccp((-_player->getBody()->GetPosition().x*PTM_RATIO*_scale+(winSize.width*0.1f)),(-_player->getBody()->GetPosition().y*PTM_RATIO*_scale+(winSize.height*0.5f))));
	screenBounds= CCRect(-this->getPositionX() ,-this->getPositionY(),this->getContentSize().width/_scale,this->getContentSize().height/_scale);

}
void Game::ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event)
{
	tracking = true;
	steps = 0;
}

void Game::ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event)
{
	if(steps > 2.0f){
		steps = 2.0f;
	}
	_player->jump(steps);
	tracking = false;
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
