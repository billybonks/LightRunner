#include "Spawner.h"
#include "GameScene.h"

Spawner::Spawner(Game* game, Chooser* chooser){
	
	_game=game;
	_chooser=chooser;

	_currentSegment=_chooser->init();
}

void Spawner::generateNextSegment(){
	CCPoint* endofLast=_currentSegment->getGameWorldVertice(_chooser->getEndVertex());
	
	Segment* segment = _chooser->getNextSegment();
	
	CCPoint* relStartofCurrent=segment->getPolygonVertice(_chooser->getStartVertex());
	CCPoint absStartofCurrent=segment->offsetStartPosition(relStartofCurrent,endofLast,_currentSegment);

	segment->setPosition(absStartofCurrent);
	segment->addSprites(_game);

	_currentSegment = segment;

}


void Spawner::update(){
	generateNextSegment();

}

	

Segment* Spawner::getCurrentSegment(){
	return _currentSegment;
}



