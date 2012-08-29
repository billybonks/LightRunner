		#include "GameObject.h"

		using namespace cocos2d;

		GameObject::GameObject()
		{
			this->newtrail=0.05f;
			_ccColor3B c =  {255,0,0};
				this->colour =c;
				this->colourmode=0;

		CCNode::CCNode();
		}

		bool GameObject::canBeOffScreen(){
			return CanBeOffScreen;
		}

		void GameObject::SetCanBeOffScreen(bool can)
		{
			this->CanBeOffScreen=can;
		}
		
		void GameObject::init(CCRect* scr)
		{
			this->newtrail=0.05f;
			_ccColor3B c =  {255,0,0};
			this->colour =c;
			this->colourmode=0;
			this->screen=scr;
			this->CanBeOffScreen=false;
		}

		bool GameObject::isOffScreen(){//err: need to implement properly for y axis maybe
			//CCLog("May bug here in offscreen when screen moves up/down");
			if(this->body->GetPosition().x* PTM_RATIO<screen->origin.x-50||this->body->GetPosition().x* PTM_RATIO>screen->origin.x+screen->size.width+50||this->body->GetPosition().y* PTM_RATIO<screen->origin.y-50||this->body->GetPosition().y* PTM_RATIO>screen->origin.y+screen->size.height+50){
				return true;
			}
			return false;
		}

		GameObject* GameObject::retainedObjectWithSpriteFrameName(const char *pszSpriteFrameName, CCRect* scr )
		{
		GameObject *obj = new GameObject();
		if (obj->sprite=CCSprite::createWithSpriteFrameName(pszSpriteFrameName))
		{
			obj->init(scr);
			return obj;
		}
		CC_SAFE_DELETE(obj);
		return NULL;
		}

		GameObject* GameObject::retainedObjectWithSpriteFrame(CCSpriteFrame *pSpriteFrame, CCRect* scr )
		{
		GameObject *obj = new GameObject();
		if (obj->sprite=CCSprite::create(pSpriteFrame))
		{
						obj->init(scr);


				return obj;
		}
		CC_SAFE_DELETE(obj);
		return NULL;
		}

		GameObject* GameObject::retainedObjectWithSprite(CCSprite *pSprite, CCRect* scr )
		{
		GameObject *obj = new GameObject();
		obj->sprite=pSprite;
		obj->init(scr);
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
			dynamicBox.SetAsBox((this->sprite->getContentSize().width/PTM_RATIO)/2, (this->sprite->getContentSize().height/PTM_RATIO)/2);//These are mid points for our 1m box err:if object is scaled/rotated this will bug out
			b2FixtureDef fixtureDef;
			fixtureDef.shape = &dynamicBox;
			fixtureDef.density = 1.0f;
			fixtureDef.friction = 0.0f;
			fixtureDef.restitution =  0.0f;
			this->body->CreateFixture(&fixtureDef);
		}

		void GameObject::updateTrail(float dt){
			this->newtrail-=dt;
			if(this->newtrail<=0){
				this->newtrail=0.05f;
			}
			GameObject* trail = GameObject::retainedObjectWithSpriteFrame(this->sprite->displayFrame(),screen); 
			trail->sprite->setPosition(ccp(this->sprite->getPositionX(), this->sprite->getPositionY()));
			this->sprite->getParent()->addChild(trail->getSprite());
			trail->sprite->setColor(nextColour());

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

		void GameObject::SetPosition(CCPoint position){
			this->getSprite()->setPosition(position); 
		}

		void GameObject::SetTarget(CCPoint position){
		}

		void GameObject::removeFromParentAndCleanup(){
			this->body->GetWorld()->DestroyBody( this->body );
			this->sprite->removeFromParentAndCleanup(true);
		}	