		#include "GameObject.h"

		using namespace cocos2d;
		CCRect* GameObject::screen;
		GameObject::GameObject()
		{
			this->newtrail=0.05f;
			_ccColor3B c =  {255,0,0};
				this->colour =c;
				this->colourmode=0;
							this->CanBeOffScreen=false;

		CCNode::CCNode();
		}

		void GameObject::SetScreen(CCRect* screen){
			GameObject::screen = screen;
		}

		bool GameObject::canBeOffScreen(){
			return CanBeOffScreen;
		}

		void GameObject::SetCanBeOffScreen(bool can)
		{
			this->CanBeOffScreen=can;
		}
		
		void GameObject::init()
		{
			this->newtrail=0.05f;
			_ccColor3B c =  {255,0,0};
			this->colour =c;
			this->colourmode=0;
			this->CanBeOffScreen=false;
		}

		bool GameObject::isOffScreen(float scale){
			float left = screen->origin.x;
			float bottom = screen->origin.y;
			float winwidth = screen->size.width*scale;
			float winheight = screen->size.height*scale;
			b2Vec2 screenlower=b2Vec2(bounds.lowerBound.x*scale -left,bounds.lowerBound.y*scale -bottom);
			b2Vec2 screenupper=b2Vec2(bounds.upperBound.x*scale -left,bounds.upperBound.y*scale -bottom);
			if (screenupper.x < 0) return true; // is left of screen
			if (screenlower.x > winwidth) return true; // is right of screen
			if (screenupper.y < 0) return true; // is above screen
			if (screenlower.y > winheight) return true; // is below screen
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

		GameObject* GameObject::retainedObjectWithSpriteFrameName(const char *pszSpriteFrameName)
		{
		GameObject *obj = new GameObject();
		if (obj->sprite=CCSprite::createWithSpriteFrameName(pszSpriteFrameName))
		{
			obj->init();
			return obj;
		}
		CC_SAFE_DELETE(obj);
		return NULL;
		}

		GameObject* GameObject::retainedObjectWithSpriteFrame(CCSpriteFrame *pSpriteFrame)
		{
		GameObject *obj = new GameObject();
		if (obj->sprite=CCSprite::create(pSpriteFrame))
		{
						obj->init();


				return obj;
		}
		CC_SAFE_DELETE(obj);
		return NULL;
		}

		GameObject* GameObject::retainedObjectWithSprite(CCSprite *pSprite)
		{
		GameObject *obj = new GameObject();
		obj->sprite=pSprite;
		obj->init();
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
			playerBodyDef.position.Set(this->sprite->getPosition().x/PTM_RATIO, this->sprite->getPosition().y/PTM_RATIO);
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
			this->body->CreateFixture(&fixtureDef);
			setBoundingBox();
		}

		void GameObject::updateTrail(float dt){
			this->newtrail-=dt;
			if(this->newtrail<=0){
				this->newtrail=0.05f;
			}
			GameObject* trail = GameObject::retainedObjectWithSpriteFrame(this->sprite->displayFrame()); 
			trail->sprite->setPosition(ccp(this->sprite->getPositionX(), this->sprite->getPositionY()));
			this->sprite->getParent()->addChild(trail->getSprite());
			trail->sprite->setColor(nextColour());
			trail->getSprite()->setScale(this->getSprite()->getScale());

			trail->createBox2dObject(this->body->GetWorld());
			trail->body->SetType(b2_staticBody);
			//get the existing filter
			b2Filter filter = trail->body->GetFixtureList()->GetFilterData();
			//make no collisions
			filter.maskBits = 0;
			//and set it back
			trail->body->GetFixtureList()->SetFilterData(filter);
		}
				

		void GameObject::update(float dt){

		}


		void GameObject::SetTarget(CCPoint position){
		}

		void GameObject::removeFromParentAndCleanup(){

			this->body->GetWorld()->DestroyBody( this->body );
			this->sprite->removeFromParentAndCleanup(true);
		}	