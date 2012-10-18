
#ifndef Segment_H
#define Segment_H
#include "Box2D.h"
#include "cocos2d.h"
#include <stdlib.h>
#include "Path.h"

#define PTM_RATIO 32
using namespace cocos2d;

class Segment : public CCNode{
private:
protected:
	CCPoint* _gameWorldVerticesCCW;
	CCPoint* _polygonVerticesCCW;
	Path* _bossPath;
	b2AABB* _pixelBounds;
public:
	Segment();	
	Segment(CCPoint position);	
	virtual void generate();
	CCPoint* getGameWorldVertice(int vertice);
	CCPoint* getPolygonVertice(int vertice);
	virtual void offsetStartPosition(CCPoint* sourceVert,CCPoint* targetVert,Segment* target );
	virtual bool insideBoundingBox();
	void setBounds(b2AABB* bounds);
	virtual CCPoint* getEndVertice();
	virtual CCPoint* getStartVertice();
	b2AABB* getBounds();
};

class B2Segment : public Segment{
private:
protected:
		b2Body* _body;
		CCSprite* _sprite;
		void genBoundingBox();
public:
	B2Segment();
	B2Segment(CCPoint position);	
	virtual b2Body* getBody();
	virtual CCSprite* getSprite();
};

class CompoundSegment : public Segment{
private:
	Segment* segments;
protected:
public:
	CompoundSegment();
};



/*
If you if two quad segments touch you run the chance of causing Ghost Vertice bug in Box2d
*/
class  QuadSegment : public B2Segment{
private:

protected:

public:
	QuadSegment();
	virtual void generate();
};

class LineSegment : public B2Segment{
private:

protected:
public:
	LineSegment();
	LineSegment(b2World* world, CCPoint position,float width,float height);
	LineSegment(b2World* world, float width,float height);
	virtual void generate(b2World *world);
	virtual CCPoint* getEndVertice();
	virtual CCPoint* getStartVertice();
};


class Tunnel :public CompoundSegment{
private:
	bool _leftEntrance;
	bool _rightExit;
protected:
	LineSegment* left;
	LineSegment* right;
public:
	Tunnel(b2World *world,b2Vec2 startPosition,float width,float height,bool leftEntrance,bool rightExit);
	Tunnel(b2World *world,float width,float height,bool leftEntrance,bool rightExit);
	virtual void generate();
};
#endif