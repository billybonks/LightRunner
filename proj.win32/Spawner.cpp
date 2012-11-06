#include "Spawner.h"
#include "GameScene.h"

Spawner::Spawner(Game* game,Statistics* stats,b2World* world,GameObject* player){
	_verticalGapChance = 3;
	_horizontalGapChance = 3;
	
	_game = game;
	_stats = stats;
	_world = world;
	_player = player;
	endVertex=1;
	structType=0;

	CCPoint* startPos = new CCPoint(200,100);
	Segment* segment = dynamic_cast<Segment*>(new LineSegment (_world,*startPos,800,0));
	_currentSegment= segment;

}

int Spawner::Random(int lowest, int highest){
	int range=(highest-lowest)+1;		    	
	return lowest+int(range*rand()/(RAND_MAX + 1.0)); 
}

void Spawner::generateNextSegment(){
	CCPoint* endofLast=_currentSegment->getGameWorldVertice(endVertex);
	
	Segment* segment = chooseSegment();
	
	CCPoint* relStartofCurrent=segment->getPolygonVertice(startVertex);
	CCPoint absStartofCurrent=segment->offsetStartPosition(relStartofCurrent,endofLast,_currentSegment);

	segment->setPosition(absStartofCurrent);
	segment->addSprites(_game);

	_currentSegment = segment;

}

	Segment* Spawner::chooseSegment(){
		
	if(structType==4)//if last was drop
	{
		do //dont lift
			structType = Random(1,5);
		while(structType==5);
	}
	else if(structType==5)//if last was lift
	{
		do //dont lift
			structType = Random(1,5);
		while(structType==4);
	}
	else{
		structType = Random(1,5);
	}

	int height;
	Segment* segment;

	switch ( structType )
	{
	case 1:
		segment = new LineSegment(_world,segmentDistance,0);
		startVertex = 0;
		endVertex = 1;
		break;
	case 2:
		height = Random(segmentDistance/3,segmentDistance/2);
		segment = new LineSegment(_world,segmentDistance,height);
		startVertex = 0;
		endVertex = 1;
		break;	
	case 3:
		height = Random(segmentDistance/3,segmentDistance/2);
		segment = new LineSegment(_world,segmentDistance,-height);
		startVertex = 0;
		endVertex = 1;
		break;
	case 4:
		//drop
		height = Random(segmentDistance/3,segmentDistance/2);
		segment = new LineSegment(_world,0,500);
		startVertex = 1;
		endVertex = 0;
		break;
	case 5:
		//lift
		height = Random(segmentDistance/3,segmentDistance/2);
		segment = new LineSegment(_world,0,500);
		startVertex = 0;
		endVertex = 1;
		break;
	case 6:
		height = 400;
		segment = new  Tunnel(_world,300,height,true,false);
		startVertex = 1;
		endVertex = 3;
		break;
	case 7:
		//Upward jump tunnel
		break;
	case 8:
		break;
	}
	return segment;

	/*
	//Drop and reverse
	int trydrop = Random(1,12);
	if((trydrop > spawnDropAndReverseChance)){
		int dist = segmentDistance;
		if(dist>1){
			int floatH = 20;

			b2Vec2 floaterPos = *(new b2Vec2(pos.x+(segmentDistance/4),pos.y+100));
			QuadSegment *floater = new QuadSegment(_world,floaterPos,floatDist,floatH);
			floater->generateNextBody();
			_game->addChild(floater->getSprite());	
		}
	}
	*/

	//Floaters
	//int spawnFloatingPLatformChance = 10;
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


	}

void Spawner::update(){
	updateStats();
	generateNextSegment();

}

	void Spawner::updateStats(){
		int runtime = Random(1,6)/2;
		float minRunTime = Random(1,6)/2;
		float speed = _stats->GetVelocity()*32;
		float minDistance = speed*minRunTime;
		float maxDistance = speed*runtime;
		segmentDistance =  Random(minDistance,maxDistance);
	}

Segment* Spawner::getCurrentPlatform(){
	return _currentSegment;
}



