#ifndef __CHOOSER__
#define __CHOOSER__

#include "Statistics.h"
#include "Segment.h"

class Chooser
{
private:

public:
	Chooser();
	virtual Segment* getNextSegment();
	int getEndVertex();
	int	getStartVertex();
	virtual Segment* init();
	virtual CCPoint getOffset();
protected:
	int endVertex;
	int startVertex;
	CCPoint offset;
};


class ProcChooser : public Chooser
{
private:
	int _verticalGapChance;
	int _horizontalGapChance;
	int _floatingPlatformChance;
	int reverse;
	int structType;


	Statistics* _stats;
	b2World* _world;
	float segmentDistance;
	
	int Random(int lowest, int highest);
	
	void updateStats();

public:
	ProcChooser(Statistics* stats,b2World* world);
	ProcChooser();
	virtual Segment* getNextSegment();
	virtual Segment* init();

protected:
	
};


class FileChooser : public Chooser
{
private:
	b2World* _world;
	Segment* makePlatform(int type,int w,int h);
	CCDictionary* level;
	CCDictionary* platforms;
	int numplatforms;
	int currplatform;
public:
	FileChooser(b2World* world);
	FileChooser();
	virtual Segment* getNextSegment();
	virtual Segment* init();

protected:
	
};
#endif