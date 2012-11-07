#ifndef __SPAWNER__
#define __SPAWNER__

#include "cocos2d.h"
#include "GameObject.h"
#include "Statistics.h"
#include "Light.h"
#include "Segment.h"
#include "Chooser.h"
#include <vector>
using namespace cocos2d;
class  Game;

class Spawner 
{
private:
	Game* _game;
	Segment* _currentSegment;
	int _counter;
	
	Chooser* _chooser;

public:
	Spawner(Game* game, Chooser* chooser);
	void generateNextSegment();
	void update();
	Segment* getCurrentSegment();
};

#endif