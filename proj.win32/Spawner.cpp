#include "Spawner.h"

Spawner::Spawner(Statistics* stats,b2World* world,b2Vec2 initialSpawnLocation){
	srand(time(0));
	_stats = stats;
	_world = world;
	_initialSpawnLocation = initialSpawnLocation;
	float minDistance = (_stats->GetMaximumVelocity()*32)*10.0f;
	float maxDistance = (_stats->GetMaximumVelocity()*32)*20.0f;
	float distance = Random(minDistance,maxDistance);
	int maxSegments =distance/200;
	int segments = Random(1,maxSegments);
	LineSegment segment = GenerateCompoundSegment(distance,segments);
}

int Spawner::Random(int lowest, int highest){
	 
	int range=(highest-lowest)+1;		    	
	return lowest+int(range*rand()/(RAND_MAX + 1.0)); 
}

LineSegment Spawner::GenerateCompoundSegment(float distance,int segments){
	/*
	Currently only spawning with 3 test OBJects
	str8 line	1
	Incline line positive	2
	Incline Line Negative	3
	*/
	ContinuousLineSegment* segment;
	float segmentDistance = 0;
	float distanceRemeinder;
	float maxDistancePerSegment = distance/segments;
	float minDistancePerSegment = maxDistancePerSegment/2;
	ContinuousLineSegment* currentSegment;
	ContinuousLineSegment* lastSegment;
	distanceRemeinder = maxDistancePerSegment;
	for(int i = 1;i<=segments;i++){
		int structType = Random(1,3);
		if(i == segments){
			segmentDistance = distanceRemeinder;
		}else{
			segmentDistance = Random(minDistancePerSegment,maxDistancePerSegment);
			//distanceRemeinder = segmentDistance - maxDistancePerSegment;
		}
		switch ( structType )
		{
		case 1:
			currentSegment = dynamic_cast<ContinuousLineSegment*>( new StraightLineSegment(_world,_initialSpawnLocation,segmentDistance,50));
			break;
		case 2:
			currentSegment = dynamic_cast<ContinuousLineSegment*>(new InclineLineSegment(_world,_initialSpawnLocation,segmentDistance,100,10));
			break;	
		case 3:
			currentSegment = dynamic_cast<ContinuousLineSegment*>(new InclineLineSegment(_world,_initialSpawnLocation,segmentDistance,100,-10));
			break;
		case 4:
			//stright line gap
			break;
		case 5:
			//Positive Incline Gap
			break;
		case 6:
			//negative Incline Gap
			break;
		case 7:
			//Upward jump tunnel
			break;
		case 8:
			//LongDrop jump tunnel
			break;
		}
		if(i != 1){
			lastSegment->SetChild(currentSegment,lastSegment);
		}else{
			segment = currentSegment;
			segment->InitilizeData();
		}
		lastSegment = currentSegment;
	}
	
	LineSegment* retSegment = dynamic_cast<LineSegment*>(segment);
	segmentQueue.push_back(retSegment);
	
	return *retSegment;
}


void Spawner::Spawn(CCLayer layer){

	//_stats->GetVelocity();
	//case gap decline incline same plane
	//distance = min 5s run d= v/t
	//spawn line origin = last destination
	//set boss = _destination point 
}

void SpawnLine();

void Spawner::update(){
	LineSegment* segment = segmentQueue.front();
	b2Body* body = NULL;
	bool done = segment->GenerateNextBody(body);
	//if(done){
	//	segmentQueue.clear();
	//}
}

