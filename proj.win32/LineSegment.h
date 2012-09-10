
#ifndef LINESEGMENT_H
#define LINESEGMENT_H
#include "Box2D.h"
#include "GameObject.h"
#include <stdlib.h>
#define PTM_RATIO 32

class LineSegment : public GameObject{
private:
protected:
	float _width;
	float _height;
	b2Vec2 _lastVerts[2];
	b2Vec2 _startWorldPosition;
	b2World *world;
	b2Vec2 *_GameWorldVerticies[4];
	void GetVertsSquare(b2Vec2 vertices[],float width,float height);
	void GetVertsInclineSquare(b2Vec2 vertices[],float width,float height,float incline);
	
public:
	virtual void GenerateBody();
	virtual void InitilizeData();
	virtual bool GenerateNextBody();
	LineSegment(b2World *world,b2Vec2 startPosition);
	LineSegment(b2World *world,b2Vec2 startPosition,float _width, float _height);
	virtual b2Vec2 getLinearVelocity();
	virtual b2Vec2 getLastVerticies();
	virtual float getIncline();
	virtual b2Vec2* GetGameWorldVerticies(int verticie);
	virtual bool isOffScreen(float scale);
	void SetPosition(b2Vec2 _startWorldPosition);
	b2Vec2 GetPosition();
	float GetWidth();
	float GetHeight();
};

class ContinuousLineSegment :public  LineSegment{
private:

protected:
	LineSegment *child;
	LineSegment *parent;
	void GetVertsSquare(b2Vec2 vertices[],float width,float height);
	void GetVertsInclineSquare(b2Vec2 vertices[],float width,float height,float incline);
public:
	ContinuousLineSegment(b2World *world,b2Vec2 startPosition);
	ContinuousLineSegment(b2World *world,b2Vec2 startPosition,float _width, float _height);
	virtual void SetChild(ContinuousLineSegment *child,ContinuousLineSegment *parent);
	virtual void SetParent(ContinuousLineSegment *segment);
	virtual ContinuousLineSegment* GetChild();
	virtual ContinuousLineSegment* GetParent();
	virtual void OffsetStartPosition();
	virtual void InitilizeData();
};

class StraightLineSegment : public ContinuousLineSegment{
private:
protected:

		b2Vec2 _polygonStartPos;
		b2Vec2 _polygonVerticies[4];
		///Only use if you are going to init steps and polugonStartPos yourself
public:
	StraightLineSegment(b2World *world,b2Vec2 startPosition,float width,float height);
	virtual void GenerateBody();
	virtual bool GenerateNextBody();
	virtual b2Vec2* GetGameWorldVerticies(int verticie);
	virtual void InitilizeData();
	virtual void OffsetStartPosition();
};

class EdgeLineSegment : public ContinuousLineSegment{
private:
protected:
	b2Vec2* _verts[2];
public:
	EdgeLineSegment(b2World *world,b2Vec2 startPosition,float width,float height);
	virtual void GenerateBody();
	virtual bool GenerateNextBody();
	virtual void InitilizeData();
	virtual void OffsetStartPosition();
};

class InclineLineSegment : public StraightLineSegment{
private:
protected:
	float _thickness;
public:
	InclineLineSegment(b2World *world,b2Vec2 startPosition,float width,float maxHieght,float thickness);
	virtual b2Vec2 getLinearVelocity();
	virtual void InitilizeData();
	virtual void OffsetStartPosition();
};




#endif