#include "Spawner.h"
#include "GameScene.h"

Spawner::Spawner(Game* game,Statistics* stats,b2World* world,b2Vec2 initialSpawnLocation,GameObject* player){
	_game = game;
	srand(time(0));
	_stats = stats;
	_world = world;
	_player = player;
	_initialSpawnLocation = initialSpawnLocation;
	b2Vec2* startPos = new b2Vec2(200,100);
	LineSegment* segment = dynamic_cast<LineSegment*>(new EdgeLineSegment (_world,*startPos,800,0));
	segment->InitilizeData();
	segmentQueue.push_back(segment);
	segment->GenerateNextBody();
	_currentSegment= segment;
	indexMarker =0;
	_generate = true;
	_verticalGapChance = 0;
	_horizontalGapChance = 0;
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
	int spawnFloatingPLatformChance = 10;
	structType = Random(1,3);
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
		break;
	case 6:
		break;
	case 7:
		//Upward jump tunnel
		break;
	case 8:
		//LongDrop jump tunnel
		break;
	}
	segment->OffsetStartPosition(2,0,_currentSegment);

	b2Vec2 pos = segment->GetPosition();
	int spawnFloatingPLatform = Random(1,10);
	if((spawnFloatingPLatformChance > spawnFloatingPLatform)&&(structType ==1)){
		int floatDist = segmentDistance/2;
		if(floatDist>1){
			int floatH = 20;
			b2Vec2 floaterPos = *(new b2Vec2(pos.x+(segmentDistance/4),pos.y+100));
			StraightLineSegment *floater = new StraightLineSegment(_world,floaterPos,floatDist,floatH);
			floater->GenerateNextBody();
		}

	}

	structType = Random(1,10);
	if((structType < _verticalGapChance)&&(!spawnFloatingPLatformChance > spawnFloatingPLatform)){
		pos.y = pos.y+100;
	}
	structType = Random(1,10);
	if(structType < _horizontalGapChance){
		pos.x = pos.x+100;
	}
	segment->SetPosition(pos);
	segment->InitilizeData();
	LineSegment* ret =  dynamic_cast<LineSegment*>(segment);
	_nextSegment = segment;
	_nextSegment->GenerateNextBody();
	_game->addChild(_nextSegment->getSprite());	
	//b2Vec2* vert = _lastSegment->GetGameWorldVerticies(0);
	return *ret;
}

void Spawner::update(){

	float x;
	float spawnX;
	float distanace = _currentSegment->CalculateDistance();
	float playerX = _player->getBody()->GetPosition().x*PTM_RATIO;
	if(distanace>0){
		x =_currentSegment->GetGameWorldVerticies(0)->x;
	}else{
		x =_currentSegment->GetGameWorldVerticies(1)->x;
	}
	if(_generate == true){
		GenerateCompoundSegment();
		_generate= false;
	}
	if(playerX >x+distanace){
		_currentSegment = _nextSegment;
		_generate = true;
	}

}

LineSegment* Spawner::GetCurrentPlatform(){
	return _currentSegment;
}



