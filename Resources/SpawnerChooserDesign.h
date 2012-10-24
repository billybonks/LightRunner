#define __SPAWNER__

#include "cocos2d.h"
#include "GameObject.h"
#include "Statistics.h"
#include "Light.h"
#include "Segment.h"
#include <vector>
using namespace cocos2d;
class Game;

class Spawner 
{
private:
	Game* _game;
	vector<Segment*> _segments;
public:
	Spawner(Game* game);
	void update();
	Segment* getCurrentSegment();
};

class Chooser 
{
private:
	
public:
	Segment* getNextSegment();
protected:
};

class ProcChooser 
{
private:
	int _verticalGapChance;
	int _horizontalGapChance;
	int _floatingPlatformChance;
	Statistics* _stats;
public:
	Segment* getNextSegment();
protected:
	
};
#endif