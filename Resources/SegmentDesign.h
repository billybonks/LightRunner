
#ifndef Segment_H
#define Segment_H
#include "Box2D.h"
#include "GameObject.h"
#include <stdlib.h>
#define PTM_RATIO 32

class Segment : CCNode{
private:
protected:
	CCPoint*_gameWorldVerticiesCCW[4];
	Path* _bossPath;
public:
	Segment();	
	virtual void generate();
	virtual CCPoint* getGameWorldVertice(int vertice);
	virtual void  OffsetStartPosition(int sourceAttachementVerticie,int targetAttachementVerticie,Segment* target );
	bool insideBoundingBox();
};

class B2DSegment : public Segment{
private:
	B2Body* _body;
	CCSprite* _sprite;
protected:
public:
	B2DSegment();
	B2Body* getBody();
	CCSprite* getSprite();
};

class CompoundSegment : public Segment{
private:
	Segment* segments;
protected:
public:
	CompoundSegment();
};

/*
needs to look after animation changes , Point for Time 
*/
class Path {
private:
protected:
public:
	virtual float GetYForX(float x);
	virtual CCPoint worldToLocalPoint(b2Vec2 point);
};

/*
If you if two quad segments touch you run the chance of causing Ghost Vertice bug in Box2d
*/
class  QuadSegment : public B2DSegment{
private:
protected:
public:
	StraightSegment();
	virtual void generate();
};

class LineSegment : public B2DSegment{
private:
protected:
	b2Vec2* _verts[2];
public:
	StraightSegment();
	virtual void generate();
};


class Tunnel :public CompoundSegment{
private:
	bool _leftEntrance;
	bool _rightExit;
protected:
	EdgeSegment* left;
	EdgeSegment* right;
public:
	Tunnel(b2World *world,b2Vec2 startPosition,float width,float height,bool leftEntrance,bool rightExit);
	Tunnel(b2World *world,float width,float height,bool leftEntrance,bool rightExit);
	virtual void generate();
};
#endif