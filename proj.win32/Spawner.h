#ifndef __SPAWNER__
#define __SPAWNER__

#include "cocos2d.h"
#include "GameObject.h"
#include "Statistics.h"
#include "Light.h"
#include "LineSegment.h"
#include <vector>
using namespace cocos2d;
class Game;

class Spawner 
{
private:
	Game* _game;
	vector<LineSegment*> segmentQueue;
	b2World* _world;
	Statistics* _stats;
	b2Vec2 _initialSpawnLocation;
	LineSegment* _currentSegment;
	LineSegment* _nextSegment;
	bool _generate;
	float indexMarker;
	int _counter;
	GameObject* _player;
	int _verticalGapChance;
	int _horizontalGapChance;
	int _floatingPlatformChance;
public:
	Spawner(Game* game,Statistics* stats,b2World* world,b2Vec2 initialSpawnLocation,GameObject* _player);
	int Random(int lowest, int highest);
	LineSegment GenerateCompoundSegment();
	void update();
	LineSegment* GetCurrentPlatform();
};

#endif