#include "Player.h"
#include "Segment.h"

using namespace cocos2d;
class ContactListener : public b2ContactListener
{
	Segment* lastPlatform;
public :ContactListener(){
			lastPlatform = NULL;
		}

		void BeginContact(b2Contact* contact) {
			//check if fixture A was the foot sensor
			void* fixtureUserData = contact->GetFixtureA()->GetUserData();
			if ( (int)fixtureUserData == 0 ){
				Player* player = (Player*)contact->GetFixtureA()->GetBody()->GetUserData();
				player->addNumFootContacts(0);
				lastPlatform=(Segment*) contact->GetFixtureB()->GetBody()->GetUserData();
			}
			else if ( (int)fixtureUserData == 1 ){
				Player* player = (Player*)contact->GetFixtureA()->GetBody()->GetUserData();
				player->addNumFootContacts(1);
				lastPlatform=(Segment*) contact->GetFixtureB()->GetBody()->GetUserData();
			}
			else if ( (int)fixtureUserData == 2 ){
				Player* player = (Player*)contact->GetFixtureA()->GetBody()->GetUserData();
				player->addNumFootContacts(2);
				lastPlatform=(Segment*) contact->GetFixtureB()->GetBody()->GetUserData();
			}


			//check if fixture B was the foot sensor
			fixtureUserData = contact->GetFixtureB()->GetUserData();
			if ( (int)fixtureUserData == 0 ){
				Player* player = (Player*)contact->GetFixtureB()->GetBody()->GetUserData();
				player->addNumFootContacts(0);		 
				lastPlatform=(Segment*) contact->GetFixtureA()->GetBody()->GetUserData();
			}
			else if ( (int)fixtureUserData == 1 ){
				Player* player = (Player*)contact->GetFixtureB()->GetBody()->GetUserData();
				player->addNumFootContacts(1);		 
				lastPlatform=(Segment*) contact->GetFixtureA()->GetBody()->GetUserData();
			}
			else if ( (int)fixtureUserData == 2 ){
				Player* player = (Player*)contact->GetFixtureB()->GetBody()->GetUserData();
				player->addNumFootContacts(2);		 
				lastPlatform=(Segment*) contact->GetFixtureA()->GetBody()->GetUserData();
			}
		}

		void EndContact(b2Contact* contact) {
			//check if fixture A was the foot sensor
			void* fixtureUserData = contact->GetFixtureA()->GetUserData();
			if ( (int)fixtureUserData == 0 ){
				Player* player = (Player*)contact->GetFixtureA()->GetBody()->GetUserData();
				player->subNumFootContacts(0);		  
			}
			else if ( (int)fixtureUserData == 1 ){
				Player* player = (Player*)contact->GetFixtureA()->GetBody()->GetUserData();
				player->subNumFootContacts(1);		  
			}
			else if ( (int)fixtureUserData == 2 ){
				Player* player = (Player*)contact->GetFixtureA()->GetBody()->GetUserData();
				player->subNumFootContacts(2);		  
			}

			//check if fixture B was the foot sensor
			fixtureUserData = contact->GetFixtureB()->GetUserData();
			if ( (int)fixtureUserData == 0 ){
				Player* player = (Player*)contact->GetFixtureB()->GetBody()->GetUserData();
				player->subNumFootContacts(0);		  
			}
			else if ( (int)fixtureUserData == 1 ){
				Player* player = (Player*)contact->GetFixtureB()->GetBody()->GetUserData();
				player->subNumFootContacts(1);		  
			}
			else if ( (int)fixtureUserData == 2 ){
				Player* player = (Player*)contact->GetFixtureB()->GetBody()->GetUserData();
				player->subNumFootContacts(2);		  
			}
		}

public: Segment* GetLastPlatform(){
			return lastPlatform;
		}
};