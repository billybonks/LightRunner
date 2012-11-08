		#include "GameObject.h"

		using namespace cocos2d;
		CCRect* GameObject::screen;
		GameObject::GameObject(b2World* world)
		{
			CCNode::CCNode();
			this->init(world);

		}
		GameObject::GameObject()
		{
			CCNode::CCNode();
		}

		void GameObject::setScreen(CCRect* screen){
			GameObject::screen = screen;
		}

		bool GameObject::getCanBeOffScreen(){
			return canBeOffScreen;
		}

		void GameObject::setCanBeOffScreen(bool can)
		{
			this->canBeOffScreen=can;
		}
		
		void GameObject::setPosition(CCPoint pos){
			CCNode::setPosition(pos);
			this->getSprite()->setPosition(pos);
			this->getBody()->SetTransform(b2Vec2(pos.x/ PTM_RATIO,pos.y/PTM_RATIO),this->getBody()->GetAngle());
			setBoundingBox();

		}

		void GameObject::setPositionX(float x){
			CCNode::setPositionX(x);
			this->getSprite()->setPositionX(x);
			this->getBody()->SetTransform(b2Vec2(x/PTM_RATIO,this->getBody()->GetPosition().y),this->getBody()->GetAngle());
			setBoundingBox();
		}

		void GameObject::setPositionY(float y){
			CCNode::setPositionY(y);
			this->getSprite()->setPositionY(y);
			this->getBody()->SetTransform(b2Vec2(this->getBody()->GetPosition().x,y/PTM_RATIO),this->getBody()->GetAngle());
			setBoundingBox();
		}

		void GameObject::init(b2World* world)
		{
			this->newtrail=0.05f;
			_ccColor3B c =  {255,0,0};
			this->colour =c;
			this->colourmode=0;
			this->canBeOffScreen=false;
			this->createBox2dObject(world);
		}

		
		bool GameObject::isOffScreen(){
			float left = screen->origin.x;
			float bottom = screen->origin.y;
			b2Vec2 screenlower=b2Vec2(bounds.lowerBound.x -left,bounds.lowerBound.y -bottom);
			b2Vec2 screenupper=b2Vec2(bounds.upperBound.x -left,bounds.upperBound.y -bottom);
			//CCLog("%f, %f, %f, %f",bounds.lowerBound.x,bounds.lowerBound.y,bounds.upperBound.x,bounds.upperBound.y);
			if (screenupper.x < 0) 
				return true; // is left of screen
			if (screenlower.x > screen->size.width) 
				return true; // is right of screen
			if (screenupper.y < 0) 
				return true; // is above screen
			if (screenlower.y > screen->size.height) 
				return true; // is below screen
			return false; // onscreen		
		}

	void GameObject::setBoundingBox(){
		b2AABB aabb;
		aabb.lowerBound = b2Vec2(FLT_MAX,FLT_MAX);
		aabb.upperBound = b2Vec2(-FLT_MAX,-FLT_MAX); 
		b2Fixture* fixture = this->body->GetFixtureList();
		while (fixture != NULL)
		{
			aabb.Combine(aabb, fixture->GetAABB(0));
			fixture = fixture->GetNext();
		}
		aabb.lowerBound*=PTM_RATIO;
		aabb.upperBound*=PTM_RATIO;
		bounds=aabb;
	}

		GameObject* GameObject::retainedObjectWithSpriteFrameName(const char *pszSpriteFrameName,b2World* world)
		{
		GameObject *obj = new GameObject();
		if (obj->sprite=CCSprite::createWithSpriteFrameName(pszSpriteFrameName))
		{
			obj->init(world);
			return obj;
		}
		CC_SAFE_DELETE(obj);
		return NULL;
		}

		GameObject* GameObject::retainedObjectWithSpriteFrame(CCSpriteFrame *pSpriteFrame,b2World* world)
		{
		GameObject *obj = new GameObject();
		if (obj->sprite=CCSprite::create(pSpriteFrame))
		{
						obj->init(world);


				return obj;
		}
		CC_SAFE_DELETE(obj);
		return NULL;
		}
		
		GameObject* GameObject::retainedObjectWithSprite(CCSprite *pSprite,b2World* world)
		{
		GameObject *obj = new GameObject();
		obj->sprite=pSprite;
		obj->init(world);
		return obj;
	
		}

		CCSprite* GameObject::getSprite(){
			return this->sprite;
		}

		b2Body* GameObject::getBody(){
			return this->body;	
		}

		_ccColor3B GameObject::nextColour(){
			if(colourmode==0){
				colour.b+=51;
				if(colour.b==255){
				colourmode=1;
				}
			}
			if(colourmode==1){
				colour.r-=51;
				if(colour.r==0){
				colourmode=2;
				}
			}
			if(colourmode==2){
				colour.g+=51;
				if(colour.g==255){
				colourmode=3;
				}
			}
			if(colourmode==3){
				colour.b-=51;
				if(colour.b==0){
				colourmode=4;
				}
			}
			if(colourmode==4){
				colour.r+=51;
				if(colour.r==255){
				colourmode=5;
				}
			}	
			if(colourmode==5){
				colour.g-=51;
				if(colour.g==0){
				colourmode=0;
				}
			}	
			return this->colour;
		}

		void GameObject::createBox2dObject(b2World* world) {
			b2BodyDef playerBodyDef;
			playerBodyDef.type = b2_dynamicBody;
			playerBodyDef.userData = this;
			playerBodyDef.fixedRotation = true;
			this->body = world->CreateBody(&playerBodyDef);
			b2PolygonShape dynamicBox;
			dynamicBox.SetAsBox((this->sprite->getContentSize().width/PTM_RATIO*this->sprite->getScale())/2, (this->sprite->getContentSize().height/PTM_RATIO)/2*this->sprite->getScale());//These are mid points for our 1m box err:if object is scaled/rotated this will bug out
			b2FixtureDef fixtureDef;
			fixtureDef.shape = &dynamicBox;
			fixtureDef.density = 1.0f;
			fixtureDef.friction = 0.0f;
			fixtureDef.restitution =  0.0f;
			b2Fixture* fixture = this->body->CreateFixture(&fixtureDef);
			fixture->SetUserData((void*)-1);
		}

		void GameObject::updateTrail(float dt){
			this->newtrail-=dt;
			if(this->newtrail<=0){
			this->newtrail=0.01f;
			GameObject* trail = GameObject::retainedObjectWithSpriteFrame(this->sprite->displayFrame(),this->getBody()->GetWorld()); 
			trail->setPosition(ccp(this->sprite->getPositionX(), this->sprite->getPositionY()));
			this->sprite->getParent()->addChild(trail->getSprite());
			trail->sprite->setColor(nextColour());
			trail->getSprite()->setScale(this->getSprite()->getScale());
			trail->body->SetType(b2_staticBody);
			//get the existing filter
			b2Filter filter = trail->body->GetFixtureList()->GetFilterData();
			//make no collisions
			filter.maskBits = 0;
			//and set it back
			trail->body->GetFixtureList()->SetFilterData(filter);
			}
		}
				

		void GameObject::update(float dt){

		}
		
		void GameObject::removeFromParentAndCleanup(){

			this->body->GetWorld()->DestroyBody( this->body );
			this->sprite->removeFromParentAndCleanup(true);
		}	