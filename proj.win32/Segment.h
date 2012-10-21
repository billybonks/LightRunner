
#ifndef Segment_H
#define Segment_H

#include "Box2D.h"
#include "cocos2d.h"
#include <stdlib.h>
#include "Path.h"

#define PTM_RATIO 32
using namespace cocos2d;
class Game;

class Segment : public CCNode{
private:
protected:
	CCPoint* _gameWorldVerticesCCW;
	CCPoint* _polygonVerticesCCW;
	Path* _bossPath;
	b2AABB* _pixelBounds;
public:
	Segment();	
	Segment(b2World *world, CCPoint position);	
	virtual void generate(b2World *world);
	CCPoint* getGameWorldVertice(int vertice);
	CCPoint* getPolygonVertice(int vertice);
	virtual CCPoint offsetStartPosition(CCPoint* sourceVert,CCPoint* targetVert,Segment* target );
	virtual bool insideBoundingBox();
	void setBounds(b2AABB* bounds);
	virtual float getEndVerticeNum();
	virtual float getStartVerticeNum();
	virtual void addSprites(Game* game);
	CCPoint bossPositionAtDistance(float bossD);
	b2AABB* getBounds();
	virtual void setPosition(const CCPoint& newPosition);
};

class B2Segment : public Segment{
private:
protected:
		b2Body* _body;
		CCSprite* _sprite;
		void genBoundingBox();
public:
	B2Segment();
	B2Segment(b2World *world,CCPoint position);	
	virtual b2Body* getBody();
	virtual CCSprite* getSprite();
};

class CompoundSegment : public Segment{
private:
	
protected:
	Segment* segments;
public:
	virtual void setPosition(const CCPoint& newPosition);
	CompoundSegment(b2World *world,CCPoint position);
	CompoundSegment(b2World *world);
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
	virtual void setPosition(const CCPoint& newPosition);
};

class LineSegment : public B2Segment{
private:
	void init(b2World *world,float width,float height);

protected:
public:
	LineSegment();
	LineSegment(b2World* world, CCPoint position,float width,float height);
	LineSegment(b2World* world, float width,float height);
	virtual void generate(b2World *world);
	virtual float getEndVerticeNum();
	virtual float getStartVerticeNum();
	virtual void setPosition(const CCPoint& newPosition);
	virtual void addSprites(Game* game);
};


class Tunnel :public CompoundSegment{
private:
	bool _leftEntrance;
	bool _rightExit;
protected:
//	LineSegment* entrance;0
//	LineSegment *exit;1
	int directionModifier;
public:
	Tunnel(b2World *world,CCPoint startPosition,float width,float height,bool leftEntrance,bool rightExit);
	Tunnel(b2World *world,float width,float height,bool leftEntrance,bool rightExit);
	virtual void generate(b2World *world);
	virtual void setPosition(const CCPoint& newPosition);
	void init(b2World *world,float width,float height,bool leftEntrance,bool rightExit);
		virtual float getEndVerticeNum();
	virtual float getStartVerticeNum();
};
#endif