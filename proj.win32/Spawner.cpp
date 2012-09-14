#include "Spawner.h"

Spawner::Spawner(Statistics* stats,b2World* world,b2Vec2 initialSpawnLocation){
	srand(time(0));
	_stats = stats;
	_world = world;
	_initialSpawnLocation = initialSpawnLocation;
	b2Vec2* startPos = new b2Vec2(400,100);
	LineSegment* segment = dynamic_cast<LineSegment*>(new EdgeLineSegment (_world,*startPos,800,0));
	segment->InitilizeData();
	segmentQueue.push_back(segment);
	segment->GenerateNextBody();
	_lastSegment = segment;
}

int Spawner::Random(int lowest, int highest){
	 
	int range=(highest-lowest)+1;		    	
	return lowest+int(range*rand()/(RAND_MAX + 1.0)); 
}

LineSegment Spawner::GenerateCompoundSegment(){
	/*
	Currently only spawning with 3 test OBJects
	str8 line	1
	Incline line positive	2
	Incline Line Negative	3
	*/
	int runtime;
	float minDistance;
	float maxDistance;
	float segmentDistance;
	ContinuousLineSegment* segment;
	float distanceRemeinder;
	int structType;
	int hieght;

	runtime = Random(1,6)/2;
	float minRunTime = Random(1,6)/2;
	float speed = _stats->GetVelocity()*32;
	minDistance = speed*minRunTime;
	maxDistance = speed*runtime;
	segmentDistance =  Random(minDistance,maxDistance);
	distanceRemeinder;
	structType = Random(1,6);
	switch ( structType )
	{
	case 1:
		segment = dynamic_cast<ContinuousLineSegment*>(new EdgeLineSegment(_world,segmentDistance,0));
		break;
	case 2:
		hieght = Random(segmentDistance/3,segmentDistance/2);
		segment = dynamic_cast<ContinuousLineSegment*>(new EdgeLineSegment(_world,segmentDistance,hieght));
		break;	
	case 3:
		hieght = Random(segmentDistance/3,segmentDistance/2);
		segment = dynamic_cast<ContinuousLineSegment*>(new EdgeLineSegment(_world,segmentDistance,-hieght));
		break;
	case 4:
		segmentDistance = Random(segmentDistance/3,(segmentDistance/2));
		segment = dynamic_cast<ContinuousLineSegment*>(new EdgeLineSegment(_world,segmentDistance,0));
		break;
	case 5:
		segmentDistance = Random(segmentDistance/3,(segmentDistance/2));
		hieght = Random(segmentDistance/3,segmentDistance/2);
		segment = dynamic_cast<ContinuousLineSegment*>(new EdgeLineSegment(_world,segmentDistance,hieght));
		break;
	case 6:
		segmentDistance = Random(segmentDistance/3,(segmentDistance/2));
		hieght = Random(segmentDistance/3,segmentDistance/2);
		segment = dynamic_cast<ContinuousLineSegment*>(new EdgeLineSegment(_world,segmentDistance,-hieght));
		break;
	case 7:
		//Upward jump tunnel
		break;
	case 8:
		//LongDrop jump tunnel
		break;
	}
	b2Vec2* vert = _lastSegment->GetGameWorldVerticies(2);
	segment->OffsetStartPosition(2,0,_lastSegment);
	segment->InitilizeData();
	LineSegment* ret =  dynamic_cast<LineSegment*>(segment);
	segmentQueue.push_back(segment);
	_lastSegment = segment;
	//b2Vec2* vert = _lastSegment->GetGameWorldVerticies(0);
	return *ret;
}

void Spawner::update(){
	float x;
	float spawnX;
	float distanace = _lastSegment->CalculateDistance();
	if(distanace>0){
		 x =_lastSegment->GetGameWorldVerticies(0)->x;
	}else{
		 x =_lastSegment->GetGameWorldVerticies(1)->x;
	}
	spawnX = distanace/4+x;
	if(_stats->GetDistanceTraveled()>spawnX){
		GenerateCompoundSegment();
		segmentQueue.back()->GenerateNextBody();
		
	}
}

