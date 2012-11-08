#include "Spawner.h"
#include "GameScene.h"

Spawner::Spawner(Game* game, Chooser* chooser){
	
	_game=game;
	_chooser=chooser;

	_currentSegment=_chooser->init();
	_currentSegment->addSprites(_game);

}

void Spawner::generateNextSegment(){
	CCPoint* endofLast=_currentSegment->getGameWorldVertice(_chooser->getEndVertex());
	
	Segment* segment = _chooser->getNextSegment();
	if(segment==0){
		return;
	}
	CCPoint* relStartofCurrent=segment->getPolygonVertice(_chooser->getStartVertex());
	CCPoint absStartofCurrent=segment->offsetStartPosition(relStartofCurrent,endofLast,_currentSegment);
	CCPoint offSet = _chooser->getOffset();
	CCPoint position =ccp(absStartofCurrent.x+offSet.x,absStartofCurrent.y+offSet.y);
	segment->setPosition(position);

	segment->addSprites(_game);

	_currentSegment = segment;

}


void Spawner::update(){
	generateNextSegment();

}

	

Segment* Spawner::getCurrentSegment(){
	return _currentSegment;
}



