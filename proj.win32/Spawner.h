#ifndef __SPAWNER__
#define __SPAWNER__

#include "cocos2d.h"
#include "GameObject.h"
#include "Statistics.h"
#include "Light.h"
#include "Segment.h"
#include <vector>
using namespace cocos2d;
class  Game;

class Spawner 
{
private:
	Game* _game;
	b2World* _world;
	Statistics* _stats;
	b2Vec2 _initialSpawnLocation;
	Segment* _currentSegment;
	int _counter;
	GameObject* _player;
	int _verticalGapChance;
	int _horizontalGapChance;
	int _floatingPlatformChance;
	int endVertex;
	int startVertex;
	int structType;
	float segmentDistance;
public:
	Spawner(Game* game,Statistics* stats,b2World* world,GameObject* _player);
	int Random(int lowest, int highest);
	void generateNextSegment();
	Segment* chooseSegment();
	void update();
	void updateStats();
	Segment* getCurrentPlatform();
};

#endif