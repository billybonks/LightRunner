#include "Spawner.h"

Spawner::Spawner(Statistics stats){
	i = 0;
}

int Spawner::Random(int lowest, int highest){					  
	int range=(highest-lowest)+1;		    	
	return lowest+int(range*rand()/(RAND_MAX + 1.0)); 
}

void Spawner::Spawn(CCLayer layer){
	int lowest=1, highest=3;
	int range=(highest-lowest)+1;
	i = Random(1,4);
	lowest = 100;highest = 300;
	range=(highest-lowest)+1;
	int distance = Random(100,300);
	CCPoint newOrigin = this->_lastLight->_destination;
	CCPoint newDestination;
	int x,y;
	//Gap
	if(i == 1){
		y= newOrigin.y;
		x= newOrigin.x+ distance;
	}
	//incline
	if(i == 2){
		y= newOrigin.y+Random(50,100);
		x= newOrigin.x+ distance;
	}
	//decline
	if(i == 3){
		y= newOrigin.y+(Random(50,100)*-1);
		x= newOrigin.x+ distance;
	}
	//sameplane
	if(i == 4){
		y= newOrigin.y;
		x= newOrigin.x+ distance;
	}
	newDestination =  ccp(x,y);
	//_stats->GetVelocity();
	this->_boss->SetTarget(newDestination);
	//case gap decline incline same plane
	//distance = min 5s run d= v/t
	//spawn line origin = last destination
	//set boss = _destination point 
}

	void SpawnLine();