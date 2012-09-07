

#include "cocos2d.h"
#include "GameObject.h"
#include "Statistics.h"
#include "Light.h"
#include "LineSegment.h"
#include "StraightLineSegment.h"
#include "InclineLineSegment.h"
#include "ContinuousLineSegment.h"
#include <vector>
using namespace cocos2d;

class Spawner 
{
private:
	LineSegment* segmentQueue;
	b2World* _world;
	Statistics* _stats;
	b2Vec2 _initialSpawnLocation;
	float currentStructureDistance;
	void SpawnLine();
	int _counter;
public:
	Spawner(Statistics* stats,b2World* world,b2Vec2 initialSpawnLocation);
	void Spawn(CCLayer layer);
	int Random(int lowest, int highest);
	LineSegment GenerateCompoundSegment(float distance,int segments);
	void update();
};

