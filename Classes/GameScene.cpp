#include "GameScene.h"
#include "Light.h"
#include "cocos2d.h"
#include "b2debugDraw.h"
#include "ContactListener.h"
#include "Platform.h"

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
_stats =  Statistics();
	 winSize = CCDirector::sharedDirector()->getWinSize();
	_player = (Player*) GameObject::retainedObjectWithSpriteFrameName("stander.png",&screenBounds);
	_player->getSprite()->setPosition(ccp(winSize.width * 0.1, winSize.height * 0.5));
	_batchNode->addChild(_player->getSprite(), 1);
	_player->createBox2dObject(B2DLayer::world);
	//_player->getBody()->SetLinearVelocity(b2Vec2(1.0f, 0.0f));
	//_player->getBody()->SetType(b2_kinematicBody);
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

	//Register for touches and gameloop
	this->setTouchEnabled(true) ;
	this->scheduleUpdate();
	move=true;
	spawnrate=3;
	//get the existing filter
  b2Filter filter = _boss->getBody()->GetFixtureList()->GetFilterData();
  //make no collisions
  filter.maskBits = 0;
  //and set it back
  _boss->getBody()->GetFixtureList()->SetFilterData(filter);
	//floor
	_floor = GameObject::retainedObjectWithSpriteFrameName("floor.png",&screenBounds);
	_floor->getSprite()->setPosition(ccp(winSize.width * 0.5, winSize.height * 0.1));
	_batchNode->addChild(_floor->getSprite(), 1);
	_floor->createBox2dObject(world);
	_floor->getBody()->SetType(b2_kinematicBody);
	return true;
}
void Game::update(float dt) {
	//clean out out of bounds platforms (is this all legit plz check - why is removefromparent commented and l is unused all this actually does is erase begin
	int platCount = platforms.size();
	if(platCount > 0){
		GameObject *obj =  platforms.front();
		b2Vec2  pos = obj->getBody()->GetPosition();
		if(obj->isOffScreen()){
			Light* l = (Light*)obj;

			//obj->removeFromParentAndCleanup();
			platforms.erase(platforms.begin());
		}
	}
	_player->updateTrail(dt);
	//It is recommended that a fixed time step is used with Box2D for stability
	//of the simulation, however, we are using a variable time step here.
	//You need to make an informed choice, the following URL is useful
	//http://gafferongames.com/game-physics/fix-your-timestep/
 

	this->setPosition(ccp(-_player->getBody()->GetPosition().x*PTM_RATIO+winSize.width * 0.1,0));
 	screenBounds= CCRect(this->getPositionX() ,this->getPositionY(),this->getContentSize().width,this->getContentSize().height);

	//boss antigravity:
	_boss->getBody()->ApplyForce(_boss->getBody()->GetMass()*b2Vec2(0.0f, 10.0f),_boss->getBody()->GetWorldCenter());

	//acceleration
	if(_stats.GetVelocity()<_stats.GetMaximumVelocity()){
		_player->getBody()->ApplyForce(_player->getBody()->GetMass()*b2Vec2(5.0f, 0.0f),_player->getBody()->GetWorldCenter());
		_boss->getBody()->SetLinearVelocity(b2Vec2(_player->getBody()->GetLinearVelocity().x,_boss->getBody()->GetLinearVelocity().y));
		_floor->getBody()->SetLinearVelocity(b2Vec2(_player->getBody()->GetLinearVelocity().x,0.0f));
	}
	_boss->getBody()->SetLinearVelocity(b2Vec2(_player->getBody()->GetLinearVelocity().x,_boss->getBody()->GetLinearVelocity().y));
		_floor->getBody()->SetLinearVelocity(b2Vec2(_player->getBody()->GetLinearVelocity().x,0.0f));
	//	CCLog("%f + %f",_boss->getBody()->GetPosition().y * PTM_RATIO, -this->getScreenBounds().origin.y+this->getScreenBounds().size.height+50);

	// Instruct the world to perform a single step of simulation. It is
	// generally best to keep the time step and iterations fixed.
		B2DLayer::update(dt);
		CCPoint newPoint = _player->getSprite()->getPosition();
		float distance = newPoint.x - _lastPos.x;
		_lastPos = newPoint;
		_stats.IncrementDistance(distance);
	CleanWorld();
	if(move==false){
		spawnrate+=dt;
		if(spawnrate>=1){
			spawnrate=0.5;
			//_boss->getBody()->ApplyLinearImpulse(b2Vec2(0.0f, 0.5f),_boss->getBody()->GetWorldCenter());
			move=true;
		}
	}
	else{
		spawnrate-=dt;
		if((spawnrate<=0)&&(_boss->getSprite()->getPositionY()<winSize.height*0.1+0.5*winSize.height)){//err:doesn't account for change in players height on new platform
			GameObject* test = GameObject::retainedObjectWithSprite(Light::retainedLight(&screenBounds),&screenBounds);
			//CCSize winSize = CCDirector::sharedDirector()->getWinSize();
			//CCPoint origin = ccp(40,0);
			//CCPoint destination = ccp(MIN(winSize.width*0.9-getPositionX(),50),0);
			//Platform  *test = new Platform(,&screenBounds);
			test->getSprite()->setPosition(ccp(_boss->getSprite()->getPositionX()+50, _boss->getSprite()->getPositionY()));
			this->addChild(test->getSprite());	
			test->createBox2dObject(world);

			b2Body* body = test->getBody();
			body->SetType(b2_staticBody);
			//test->getSprite()->runAction(CCMoveBy::create( 4 ,ccp(-winSize.width*1.5, 0)));
			spawnrate=0;
			platforms.push_back((GameObject*)test);
			move=false;
			CCLog("%i", _batchNode->getChildrenCount());//err:gameobjects arent autoreleased(coz it doesnt work dunno wtf- cocos releases them too early maybe?) so makesure to release when done - check/confirm memusage with this print
		}
	}
	_stats.SetVelocity(_player->getBody()->GetLinearVelocity().x);
}

void Game::CleanWorld(){
		vector<GameObject*> objectsToClean(0);
	//Iterate over the bodies in the physics world
	for (b2Body* b = world->GetBodyList(); b; b = b->GetNext()) {
		if (b->GetUserData() != NULL) {
			GameObject *myActor = (GameObject*)b->GetUserData();
			if(myActor->isOffScreen()&&!myActor->canBeOffScreen()){
				//if not player sprite dont add to clean arr
				if(_player != myActor){
					objectsToClean.push_back(myActor);	
				}else{
					//place in screen again
					myActor->getSprite()->setPosition(CCPointMake( b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO));
				myActor->getSprite()->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
				}
			}
			else {
			//Synchronize the AtlasSprites position and rotation with the corresponding body
				myActor->getSprite()->setPosition(CCPointMake( b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO));
				myActor->getSprite()->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
			}
		}	
	}
	for(int i =0;i<objectsToClean.size();i++){
		objectsToClean.at(i)->removeFromParentAndCleanup();
	}
}
void Game::ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event)
{
	//if(_player->getSprite()->getPositionY()==0.1*winSize.height){//err:doesn't account for change in players height on new platform
		_player->jump();
	//}
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
