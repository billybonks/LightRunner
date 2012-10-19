
#ifndef Segment_H
#define Segment_H
#include "Box2D.h"
#include "GameObject.h"
#include <stdlib.h>
#define PTM_RATIO 32

class Segment : public GameObject{
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
	Segment(b2World *world,b2Vec2 startPosition);
	Segment(b2World *world,b2Vec2 startPosition,float _width, float _height);
	Segment(b2World *world,float _width, float _height);
	virtual b2Vec2 getLinearVelocity();
	virtual b2Vec2 getLastVerticies();
	virtual float getIncline();
	virtual b2Vec2* GetGameWorldVerticies(int verticie);
	void SetPosition(b2Vec2 _startWorldPosition);
	b2Vec2 GetPosition();
	float GetWidth();
	float GetHeight();
	virtual void  OffsetStartPosition( int targetAttachementVerticie, int sourceAttachementVerticie,Segment* target );
	virtual float CalculateDistance();
	virtual float GetYForX(float x);
	virtual CCPoint worldToLocalPoint(b2Vec2 point);
	float getStartVertice();
	float getEndVertice();

};

class ContinuousSegment :public  Segment{
private:

protected:
	int _targetAttachmentVerticie;
	int _sourceAttachmentVerticie;
	Segment *child;
	Segment *parent;
	void GetVertsSquare(b2Vec2 vertices[],float width,float height);
	void GetVertsInclineSquare(b2Vec2 vertices[],float width,float height,float incline);
public:
	ContinuousSegment(b2World *world,b2Vec2 startPosition);
	ContinuousSegment(b2World *world,b2Vec2 startPosition,float _width, float _height);
	ContinuousSegment(b2World *world,float _width, float _height);
	void SetChild(ContinuousSegment *child,int sourceAttachementVerticie,int targetAttachementVerticie);
	void SetParent(ContinuousSegment *segment);
	virtual ContinuousSegment* GetChild();
	virtual ContinuousSegment* GetParent();
	virtual void InitilizeData();
	virtual bool GenerateNextBody();
};

class QuadSegment : public ContinuousSegment{
private:
protected:

		b2Vec2 _polygonStartPos;
		///Only use if you are going to init steps and polugonStartPos yourself
public:
	QuadSegment(b2World *world,b2Vec2 startPosition,float width,float height);
	QuadSegment(b2World *world,float width,float height);
	virtual void GenerateBody();
	virtual bool GenerateNextBody();
	virtual b2Vec2* GetGameWorldVerticies(int verticie);
	virtual void InitilizeData();
	virtual float CalculateDistance();
	virtual float GetYForX(float x);
	virtual CCPoint worldToLocalPoint(b2Vec2 point);
	virtual void removeFromParentAndCleanup();
};

class LineSegment : public ContinuousSegment{
private:
protected:
	b2Vec2* _verts[2];
public:
	LineSegment(b2World *world,b2Vec2 startPosition,float width,float height);
	LineSegment(b2World *world,float width,float height);
	virtual void GenerateBody();
	virtual bool GenerateNextBody();
	virtual void InitilizeData();
	virtual float CalculateDistance();
	virtual float GetYForX(float x);
	virtual CCPoint worldToLocalPoint(b2Vec2 point);
	virtual void removeFromParentAndCleanup();
};

class InclineSegment : public QuadSegment{
private:
protected:
	float _thickness;
public:
	InclineSegment(b2World *world,b2Vec2 startPosition,float width,float maxHieght,float thickness);
	InclineSegment(b2World *world,float width,float maxHeight,float thickness);
	virtual b2Vec2 getLinearVelocity();
	virtual void InitilizeData();
	virtual float GetYForX(float x);
	virtual CCPoint worldToLocalPoint(b2Vec2 point);

};

class GapSegment : public LineSegment{
private:
protected:
	float _thickness;
public:
	GapSegment(b2World *world,b2Vec2 startPosition,float width,float height);
	GapSegment(b2World *world,float width,float height);
	virtual void GenerateBody();
	virtual bool GenerateNextBody();
};


class Tunnel :public ContinuousSegment{
private:
	bool _leftEntrance;
		bool _rightExit;
protected:
	LineSegment* left;
	LineSegment* right;
public:
	Tunnel(b2World *world,b2Vec2 startPosition,float width,float height,bool leftEntrance,bool rightExit);
	Tunnel(b2World *world,float width,float height,bool leftEntrance,bool rightExit);
	virtual void GenerateBody();
	virtual bool GenerateNextBody();
	virtual void InitilizeData();
	virtual float CalculateDistance();
	virtual float GetYForX(float x);
	virtual CCPoint worldToLocalPoint(b2Vec2 point);
	virtual float getEndVertice();
	virtual float getStartVertice();

};
#endif