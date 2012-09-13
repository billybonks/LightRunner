
#ifndef LINESEGMENT_H
#define LINESEGMENT_H
#include "Box2D.h"
#include "GameObject.h"
#include <stdlib.h>
#define PTM_RATIO 32

class LineSegment : public GameObject{
private:
protected:
	b2Vec2* _polygonVerticies;
	float _width;
	float _height;
	//b2Vec2 _lastVerts[2];
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
	LineSegment(b2World *world,float _width, float _height);
	virtual b2Vec2 getLinearVelocity();
	virtual b2Vec2 getLastVerticies();
	virtual float getIncline();
	virtual b2Vec2* GetGameWorldVerticies(int verticie);
	virtual bool isOffScreen(float scale);
	void SetPosition(b2Vec2 _startWorldPosition);
	b2Vec2 GetPosition();
	float GetWidth();
	float GetHeight();
	virtual void  OffsetStartPosition( int targetAttachementVerticie, int sourceAttachementVerticie,LineSegment* target );
};

class ContinuousLineSegment :public  LineSegment{
private:
	int _targetAttachmentVerticie;
	int _sourceAttachmentVerticie;
protected:
	LineSegment *child;
	LineSegment *parent;
	void GetVertsSquare(b2Vec2 vertices[],float width,float height);
	void GetVertsInclineSquare(b2Vec2 vertices[],float width,float height,float incline);
public:
	ContinuousLineSegment(b2World *world,b2Vec2 startPosition);
	ContinuousLineSegment(b2World *world,b2Vec2 startPosition,float _width, float _height);
	ContinuousLineSegment(b2World *world,float _width, float _height);
	void SetChild(ContinuousLineSegment *child,int sourceAttachementVerticie,int targetAttachementVerticie);
	void SetParent(ContinuousLineSegment *segment);
	virtual ContinuousLineSegment* GetChild();
	virtual ContinuousLineSegment* GetParent();
	virtual void InitilizeData();
};

class StraightLineSegment : public ContinuousLineSegment{
private:
protected:

		b2Vec2 _polygonStartPos;
		///Only use if you are going to init steps and polugonStartPos yourself
public:
	StraightLineSegment(b2World *world,b2Vec2 startPosition,float width,float height);
	StraightLineSegment(b2World *world,float width,float height);
	virtual void GenerateBody();
	virtual bool GenerateNextBody();
	virtual b2Vec2* GetGameWorldVerticies(int verticie);
	virtual void InitilizeData();
	virtual void  OffsetStartPosition(int targetAttachementVerticie,int sourceAttachementVerticie,LineSegment* target);
};

class EdgeLineSegment : public ContinuousLineSegment{
private:
protected:
	b2Vec2* _verts[2];
public:
	EdgeLineSegment(b2World *world,b2Vec2 startPosition,float width,float height);
	EdgeLineSegment(b2World *world,float width,float height);
	virtual void GenerateBody();
	virtual bool GenerateNextBody();
	virtual void InitilizeData();
};

class InclineLineSegment : public StraightLineSegment{
private:
protected:
	float _thickness;
public:
	InclineLineSegment(b2World *world,b2Vec2 startPosition,float width,float maxHieght,float thickness);
	InclineLineSegment(b2World *world,float width,float maxHeight,float thickness);
	virtual b2Vec2 getLinearVelocity();
	virtual void InitilizeData();
};

class GapSegment : public EdgeLineSegment{
private:
protected:
	float _thickness;
public:
	GapSegment(b2World *world,b2Vec2 startPosition,float width,float height);
	GapSegment(b2World *world,float width,float height);
	virtual void GenerateBody();
	virtual bool GenerateNextBody();
	
};


#endif