

#include "cocos2d.h"
#include "GameObject.h"
#include "Statistics.h"
#include "Light.h"
#include "LineSegment.h"
#include <vector>
using namespace cocos2d;

class Spawner 
{
private:
	vector<LineSegment*> segmentQueue;
	b2World* _world;
	Statistics* _stats;
	b2Vec2 _initialSpawnLocation;
	LineSegment* _lastSegment;
	int _counter;
public:
	Spawner(Statistics* stats,b2World* world,b2Vec2 initialSpawnLocation);
	int Random(int lowest, int highest);
	LineSegment GenerateCompoundSegment();
	void update();
};

