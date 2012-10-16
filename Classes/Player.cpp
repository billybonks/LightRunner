#include "Player.h"

Player::Player(void)
{
	GameObject::GameObject();
	
}

void Player::init(){
	numFootContacts=0;
	jumpTimeout=0;
	SetCanBeOffScreen(true);
}

void Player::jump(float multiplier){
	if ( this->numFootContacts>= 1 &&jumpTimeout==0) {
    float vertImpulse =  10.0f*multiplier;
	b2Vec2 impulse = b2Vec2(0.0f, vertImpulse*this->getBody()->GetMass());
    this->body->ApplyLinearImpulse(impulse, this->body->GetWorldCenter());	
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
}

void Player::timeOutJump(){
		jumpTimeout=0;
}
void Player::createFootFixture(b2World* world) {
	  //add foot sensor fixture

	b2PolygonShape polygonShape;
     polygonShape.SetAsBox((this->sprite->getContentSize().width/PTM_RATIO*this->getSprite()->getScale())/2, (this->sprite->getContentSize().height/PTM_RATIO)/8, b2Vec2(0,(-this->sprite->getContentSize().height/PTM_RATIO*this->getSprite()->getScale())/1.9), 0);

     b2FixtureDef myFixtureDef;
      myFixtureDef.shape = &polygonShape;
      myFixtureDef.density = 1;
	  	 
      myFixtureDef.isSensor = true;
	  b2Fixture* footSensorFixture = this->getBody()->CreateFixture(&myFixtureDef);
      footSensorFixture->SetUserData( (void*)3 );

}

void Player::setNumFootContacts(int i){
	this->numFootContacts=i;
}
void Player::addNumFootContacts(){
	numFootContacts++;
}
void Player::subNumFootContacts(){
	numFootContacts--;
}
