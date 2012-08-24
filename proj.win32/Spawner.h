

#include "cocos2d.h"
#include "GameObject.h"
#include "Statistics.h"
#include "Light.h"
using namespace cocos2d;

class Spawner 
{
private:
	int colourer;
	Statistics* _stats;
	Light* _lastLight;
	GameObject* _boss;
	int i;
	void SpawnLine();
public:
	Spawner(Statistics stats);
	void Spawn(CCLayer layer);
	int Random(int lowest, int highest);
};

