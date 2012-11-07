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
	this->world=B2DLayer::world;
	world->SetContactListener(listener);

	//prep stats
	_scale =0.2f;
	this->setScale(_scale);
	winSize = CCDirector::sharedDirector()->getWinSize();
	playerScreenPos = ccp(winSize.width*0.2, winSize.height*0.4);
	direction=1;
	
	GameObject::setScreen(&screenBounds);

	_player = (Player*) GameObject::retainedObjectWithSpriteFrameName("0.png",world);
	_batchNode->addChild(_player->getSprite(), 1);
	//_player->getSprite()->setScale(0.8f);
	_player->createFootFixture(world);
	_player->setPosition(playerScreenPos);
	_player->init();
	_lastPos = _player->getSprite()->getPosition();

	//animation
	CCArray* frames = CCArray::create(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("1.png"),CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("2.png"),CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("3.png"),NULL);
	CCAnimation *animation = CCAnimation::create(frames,0.2f);
	_player->getSprite()->runAction(CCRepeatForever::create(CCAnimate::create(animation)));   

	//boss
	_boss = GameObject::retainedObjectWithSpriteFrameName("boss2.png",world);
	_boss->getSprite()->setPosition(ccp(winSize.width*0.5, winSize.height * 0.5));
	_batchNode->addChild(_boss->getSprite(), 1);
	_boss->setCanBeOffScreen(true);
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
	this->_spawner = new Spawner(this,new ProcChooser(&_stats,world));

	_stats =  Statistics();

	//MUsicccccc
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("ghosts.mp3", true);    

	syncScreenToPlayer();
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
	Segment* temp = _spawner->getCurrentSegment();
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
	if(abs(_stats.GetVelocity())<_stats.GetMaximumVelocity()){
		_player->getBody()->SetLinearVelocity(b2Vec2(direction*10.0f, _player->getBody()->GetLinearVelocity().y));
		//_player->getBody()->ApplyForce(direction*_player->getBody()->GetMass()*b2Vec2(5.0f, 0.0f),_player->getBody()->GetWorldCenter());
	}

	//Box2D tick
	B2DLayer::update(dt);

	//Update Stats
	_stats.IncrementDistance(_player->getSprite()->getPosition().x - _lastPos.x);
	_lastPos = _player->getSprite()->getPosition();
	_stats.SetVelocity(_player->getBody()->GetLinearVelocity().x);

	cleanWorld();
}
void Game::syncScreenToPlayer(){
	this->setPosition(ccp((-_player->getPosition().x+playerScreenPos.x),(-_player->getPosition().y+playerScreenPos.y)));
	CCPoint absanchor = _player->getPosition();
	float relx = absanchor.x/winSize.width;
	float rely = absanchor.y/winSize.height;
	this->setAnchorPoint(ccp(relx,rely));

	float screenwidth = this->getContentSize().width/_scale;
	float screenheight = this->getContentSize().height/_scale;
	float playershiftx = screenwidth*(playerScreenPos.x/winSize.width);
	float playershifty = screenheight*(playerScreenPos.y/winSize.height);
	screenBounds= CCRect(_player->getPosition().x-playershiftx ,_player->getPosition().y-playershifty,screenwidth,screenheight);
}

void Game::cleanWorld(){
	//Sync Player to body
	_player->setPosition(ccp( _player->getBody()->GetPosition().x * PTM_RATIO, _player->getBody()->GetPosition().y * PTM_RATIO));
	
	syncScreenToPlayer();

	//Sync other objects to body and remove offscreen ones that should be removed
	//For performance here, should maybe keep list of only removable bodies and iterate over just them but whatever YOLO :D
	vector<GameObject*> objectsToClean(0);
	for (b2Body* b = world->GetBodyList(); b; b = b->GetNext()) {
		if (b->GetUserData() != NULL) {

			GameObject *object = (GameObject*)b->GetUserData();
			//Synchronize the Sprites position and rotation with the corresponding body
			object->setPosition(ccp( b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO));
			if(object->isOffScreen()&&!object->getCanBeOffScreen()){
				objectsToClean.push_back(object);
			}
		}	
	}
	for(int i=0;i<objectsToClean.size();i++)
	{
			objectsToClean.at(i)->removeFromParentAndCleanup(); //err:not 100% sure this frees memory - test!
			//delete objectsToClean.at(i);
	}
	
	

}

void Game::ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event)
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
		direction=-1;
	}
	else if(x>240&&y<160)
	{
		//botright.
		direction=1;
	}
	else if(y>160)
	{
		//top
		_player->jump();
	}
	
}

void Game::ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event)
{

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
