#include "Spawner.h"
#include "GameScene.h"

Spawner::Spawner(Game* game,Statistics* stats,b2World* world,b2Vec2 initialSpawnLocation,GameObject* player){
	_game = game;
	srand(time(0));
	_stats = stats;
	_world = world;
	_player = player;
	_initialSpawnLocation = initialSpawnLocation;
	CCPoint* startPos = new CCPoint(200,100);
	Segment* segment = dynamic_cast<Segment*>(new LineSegment (_world,*startPos,800,0));
	_currentSegment= segment;
	_verticalGapChance = 3;
	_horizontalGapChance = 3;
}

int Spawner::Random(int lowest, int highest){

	int range=(highest-lowest)+1;		    	
	return lowest+int(range*rand()/(RAND_MAX + 1.0)); 
}

void Spawner::GenerateCompoundSegment(){

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
	Segment* segment;
	float distanceRemeinder;
	int structType;
	int height;
	int startVerticie;
	int endVerticie;

	runtime = Random(1,6)/2;
	float minRunTime = Random(1,6)/2;
	float speed = _stats->GetVelocity()*32;
	minDistance = speed*minRunTime;
	maxDistance = speed*runtime;
	segmentDistance =  Random(minDistance,maxDistance);
	distanceRemeinder;
	int spawnFloatingPLatformChance = 10;
	structType = Random(1,5);
	switch ( structType )
	{
	case 1:
		segment = new LineSegment(_world,segmentDistance,0);
		startVerticie = 0;
		endVerticie = 1;
		break;
	case 2:
		height = Random(segmentDistance/3,segmentDistance/2);
		segment = new LineSegment(_world,segmentDistance,height);
		startVerticie = 0;
		endVerticie = 1;
		break;	
	case 3:
		height = Random(segmentDistance/3,segmentDistance/2);
		segment = new LineSegment(_world,segmentDistance,-height);
		startVerticie = 0;
		endVerticie = 1;
		break;
	case 4:
		//drop
		height = Random(segmentDistance/3,segmentDistance/2);
		segment = new LineSegment(_world,0,-500);
		startVerticie = 0;
		endVerticie = 1;
		break;
	case 5:
		//lift
		startVerticie = 1;
		endVerticie = 0;
		height = Random(segmentDistance/3,segmentDistance/2);
		segment = new LineSegment(_world,0,500);
		break;
	case 6:
		height = 400;
		segment = new  Tunnel(_world,300,height,true,false);
		startVerticie = 1;
		endVerticie = 3;
		break;
	case 7:
		//Upward jump tunnel
		break;
	case 8:
		break;
	}
	CCPoint* endofLast=_currentSegment->getGameWorldVertice(_currentSegment->getEndVerticeNum());
	CCPoint* relStartofCurrent=segment->getPolygonVertice(_currentSegment->getStartVerticeNum());
	CCPoint absStartofCurrent=segment->offsetStartPosition(relStartofCurrent,endofLast,_currentSegment);

	segment->setPosition(absStartofCurrent);
	segment->addSprites(_game);
	//b2Vec2 pos = segment->GetPosition();

	//Floaters
	//int spawnFloatingPLatform = Random(1,10);
	//if((spawnFloatingPLatformChance > spawnFloatingPLatform)&&(structType ==1)){
	//	int floatDist = segmentDistance/2;
	//	if(floatDist>1){
	//		int floatH = 20;
	//		b2Vec2 floaterPos = *(new b2Vec2(pos.x+(segmentDistance/4),pos.y+100));
	//		QuadSegment *floater = new QuadSegment(_world,floaterPos,floatDist,floatH);
	//		floater->GenerateNextBody();
	//			_game->addChild(floater->getSprite());	

	//	}

	//}

	//Gaps
	//structType = Random(1,10);
	//	if((structType < _verticalGapChance)&&(!spawnFloatingPLatformChance > spawnFloatingPLatform)){
	//	pos.y = pos.y+100;
	//}
	//structType = Random(1,10);
	//if(structType < _horizontalGapChance){
	//	pos.x = pos.x+100;
	//}


	//segment->SetPosition(pos);
	//segment->InitilizeData();
	//Segment* ret =  dynamic_cast<Segment*>(segment);
	_nextSegment = segment;
	//_nextSegment->generate();

	//b2Vec2* vert = _lastSegment->GetGameWorldVerticies(0);
	//return *ret;
}

void Spawner::update(){

	float x;
	float spawnX;
	//float distanace = _currentSegment->CalculateDistance();
	float playerX = _player->getBody()->GetPosition().x*PTM_RATIO;
	//if(distanace>0){
	//	x =_currentSegment->GetGameWorldVerticies(0)->x;
	//}else{
	//	x =_currentSegment->GetGameWorldVerticies(1)->x;
	//}
	//if(playerX >x+distanace){
	GenerateCompoundSegment();
	_currentSegment = _nextSegment;
	//}

}

Segment* Spawner::GetCurrentPlatform(){
	return _currentSegment;
}



