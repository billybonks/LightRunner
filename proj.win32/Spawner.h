

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
	LineSegment* _currentSegment;
	float indexMarker;
	int _counter;
	GameObject* _player;
public:
	Spawner(Statistics* stats,b2World* world,b2Vec2 initialSpawnLocation,GameObject* _player);
	int Random(int lowest, int highest);
	LineSegment GenerateCompoundSegment();
	void update();
	LineSegment* GetCurrentPlatform();
};

