#include "Player.h"


Player::Player(void)
{
	GameObject::GameObject();
}

void Player::jump(){
	if ( this->numFootContacts>= 1 ) {
    b2Vec2 impulse = b2Vec2(0.0f, 4.5f);
    this->body->ApplyLinearImpulse(impulse, this->body->GetWorldCenter());	
	}
}

void Player::createFootFixture(b2World* world) {
	  //add foot sensor fixture

	b2PolygonShape polygonShape;
     polygonShape.SetAsBox((this->sprite->getContentSize().width/PTM_RATIO)/2, (this->sprite->getContentSize().height/PTM_RATIO)/8, b2Vec2(0,(-this->sprite->getContentSize().height/PTM_RATIO)/1.9), 0);

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
