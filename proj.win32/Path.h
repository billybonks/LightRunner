#ifndef PATH_H
#define PATH_H
#include "Box2D.h"
#include "cocos2d.h"
#include <stdlib.h>
#define PTM_RATIO 32
using namespace cocos2d;

/*
needs to look after animation changes , Point for Time 
*/
class Path {
private:
protected:
public:
	Path();
	virtual float GetYForX(float x);
	virtual CCPoint worldToLocalPoint(b2Vec2 point);
};
#endif