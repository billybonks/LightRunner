#include "Player.h"

using namespace cocos2d;

class ContactListener : public b2ContactListener
  {
      void BeginContact(b2Contact* contact) {
          //check if fixture A was the foot sensor
          void* fixtureUserData = contact->GetFixtureA()->GetUserData();
		  if ( (int)fixtureUserData == 3 ){
			  Player* player = (Player*)contact->GetFixtureA()->GetBody()->GetUserData();
			  player->addNumFootContacts();
		  }
          //check if fixture B was the foot sensor
          fixtureUserData = contact->GetFixtureB()->GetUserData();
		  if ( (int)fixtureUserData == 3 ){
			Player* player = (Player*)contact->GetFixtureB()->GetBody()->GetUserData();
			  player->addNumFootContacts();		  }
      }
  
      void EndContact(b2Contact* contact) {
          //check if fixture A was the foot sensor
          void* fixtureUserData = contact->GetFixtureA()->GetUserData();
          if ( (int)fixtureUserData == 3 ){
			  Player* player = (Player*)contact->GetFixtureA()->GetBody()->GetUserData();
			  player->subNumFootContacts();		  
		  }
          //check if fixture B was the foot sensor
          fixtureUserData = contact->GetFixtureB()->GetUserData();
          if ( (int)fixtureUserData == 3 ){
			  Player* player = (Player*)contact->GetFixtureB()->GetBody()->GetUserData();
			  player->subNumFootContacts();		  
		  }
      }
  };