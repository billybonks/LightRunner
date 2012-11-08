#include "Player.h"

Player::Player(void)
{
	GameObject::GameObject();
	
}

void Player::init(){
	numFootContacts[0]= 0;
	numFootContacts[1]= 0;
	numFootContacts[2]= 0;
	jumpTimeout=0;
	setCanBeOffScreen(true);
}

void Player::jump(){
	if ( this->numFootContacts[0]>= 1 &&jumpTimeout==0) {
	this->body->SetLinearVelocity(b2Vec2(this->body->GetLinearVelocity().x,0));
	b2Vec2 impulse = b2Vec2(0.0f, 10.0f*this->getBody()->GetMass());
    this->body->ApplyLinearImpulse(impulse, this->body->GetWorldCenter());	
	CCArray* jumpframes = CCArray::create(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("4.png"),CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("5.png"),CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("6.png"),CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("7.png"),CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("8.png"),CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("7.png"),CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("6.png"),CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("5.png"),CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("4.png"),NULL);
	CCArray* runframes = CCArray::create(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("1.png"),CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("2.png"),CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("3.png"),NULL);
	CCAction *jump = CCAnimate::create(CCAnimation::create(jumpframes,0.2f));
	CCAction *run =  CCRepeat::create(CCAnimate::create(CCAnimation::create(runframes,0.2f)),INT_MAX);
	CCSequence* wtf = CCSequence::create((CCFiniteTimeAction*)jump, (CCFiniteTimeAction*)run);
	this->getSprite()->stopAllActions();
	this->getSprite()->runAction(wtf);   
	
	//jumpTimeout=1;
	// t = new Timer();

	// set up the time delay
	//CCDelayTime *delayAction = CCDelayTime::create(0.2f);
	// perform the selector call
	//t->forJumpTimeout=*CCCallFunc::create(this, callfunc_selector(Player::timeOutJump));
	// run the action
	//t->runAction(CCSequence::create(delayAction, t->forJumpTimeout, NULL));
	//CCTimer* test = CCTimer::timerWithTarget(this,schedule_selector(Player::timeOutJump),0.2f);
	//test->update(2.3f);
	}
	else if (this->numFootContacts[1]== 1&&this->numFootContacts[2]==0){
		this->body->SetLinearVelocity(b2Vec2(this->body->GetLinearVelocity().x,0));
		b2Vec2 impulse = b2Vec2(0.0f, 10.0f*this->getBody()->GetMass());
		this->body->ApplyLinearImpulse(impulse, this->body->GetWorldCenter());	
		this->setDirection(1);
		}
	else if (this->numFootContacts[2]== 1&&this->numFootContacts[1]==0){
		this->body->SetLinearVelocity(b2Vec2(this->body->GetLinearVelocity().x,0));
		b2Vec2 impulse = b2Vec2(0.0f, 10.0f*this->getBody()->GetMass());
		this->body->ApplyLinearImpulse(impulse, this->body->GetWorldCenter());	
		this->setDirection(-1);
		}
}

void Player::timeOutJump(){
		jumpTimeout=0;
}
void Player::createFootFixture(b2World* world) {
	  //add foot sensor fixture

	b2PolygonShape bottomFootShape;
     bottomFootShape.SetAsBox((0.85*this->sprite->getContentSize().width/PTM_RATIO*this->getSprite()->getScale())/2, (this->sprite->getContentSize().height/PTM_RATIO)/8, b2Vec2(0,(-this->sprite->getContentSize().height/PTM_RATIO*this->getSprite()->getScale())/1.9), 0);

     b2FixtureDef bottomFootFixtureDef;
      bottomFootFixtureDef.shape = &bottomFootShape;
      bottomFootFixtureDef.density = 1;
	  	 
      bottomFootFixtureDef.isSensor = true;
	  b2Fixture* bottomfootSensorFixture = this->getBody()->CreateFixture(&bottomFootFixtureDef);
      bottomfootSensorFixture->SetUserData( (void*)0 );

	  b2PolygonShape leftFootShape;
     leftFootShape.SetAsBox(this->sprite->getContentSize().width/PTM_RATIO/32, (0.45*(this->sprite->getContentSize().height/PTM_RATIO)*this->getSprite()->getScale())/2,b2Vec2((-this->sprite->getContentSize().width/PTM_RATIO*this->getSprite()->getScale())/2,(-0.55*(this->sprite->getContentSize().height/PTM_RATIO)*this->getSprite()->getScale())/2), 0);

	  b2FixtureDef leftFootFixtureDef;
      leftFootFixtureDef.shape = &leftFootShape;
      leftFootFixtureDef.density = 1;
	  	 
      leftFootFixtureDef.isSensor = true;
	  b2Fixture* leftfootSensorFixture = this->getBody()->CreateFixture(&leftFootFixtureDef);
      leftfootSensorFixture->SetUserData( (void*)1 );

	  b2PolygonShape rightFootShape;
      rightFootShape.SetAsBox(this->sprite->getContentSize().width/PTM_RATIO/32, (0.45*(this->sprite->getContentSize().height/PTM_RATIO)*this->getSprite()->getScale())/2,b2Vec2((this->sprite->getContentSize().width/PTM_RATIO*this->getSprite()->getScale())/2,(-0.55*(this->sprite->getContentSize().height/PTM_RATIO)*this->getSprite()->getScale())/2), 0);

	  b2FixtureDef rightFootFixtureDef;
      rightFootFixtureDef.shape = &rightFootShape;
      rightFootFixtureDef.density = 1;
	  	 
      rightFootFixtureDef.isSensor = true;
	  b2Fixture* rightfootSensorFixture = this->getBody()->CreateFixture(&rightFootFixtureDef);
      rightfootSensorFixture->SetUserData( (void*)2 );
}

void Player::addNumFootContacts(int i){
	CCLog("%i",i);

	numFootContacts[i]++;
}
void Player::subNumFootContacts(int i){
	numFootContacts[i]--;
}

void Player::setDirection(int i){
	direction=i;
}

int Player::getDirection(){
	return direction;
}
