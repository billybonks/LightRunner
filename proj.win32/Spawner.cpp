#include "Spawner.h"

Spawner::Spawner(Statistics* stats,b2World* world,b2Vec2 initialSpawnLocation){
	_stats = stats;
	_world = world;
	float minDistance = (_stats->GetMaximumVelocity()*32)*5.0f;
	float maxDistance = (_stats->GetMaximumVelocity()*32)*10.0f;
	float distance = Random(minDistance,maxDistance);
	int maxSegments =distance/100;
	int segments = Random(1,maxSegments);
	LineSegment segment = GenerateCompoundSegment(distance,segments);
	segmentQueue.push_back(segment);
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
	LineSegment segment*;
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
		}
		switch ( structType )
		{
		case 1:
			currentSegment = new StraightLineSegment(_world,_initialSpawnLocation,distance,50,1);
			break;
		case 2:
			currentSegment = new InclineLineSegment(_world,_initialSpawnLocation,distance,100,10);
			break;	
		case 3:
			currentSegment = new InclineLineSegment(_world,_initialSpawnLocation,distance,100,-10);
			break;	
		}
		if(i != 1){
			lastSegment->SetChild(currentSegment,lastSegment);
		}else{
			segment =currentSegment;
		}
		lastSegment = currentSegment;
	}
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
	if(done){
		segmentQueue.clear();
	}
}

