
#ifndef PLATFORMSPRITE
#define PLATFORMSPRITE

#include "GameObject.h"
#include "Light.h"
using namespace cocos2d;
class Game;
class PlatformSprite : public Light
{
public:
	PlatformSprite();
	PlatformSprite(CCPoint position,float width,float height);
	static PlatformSprite* retainedPlatformSprite(b2Vec2* polygonVerticies);

	virtual void draw();
	
private:
	static void lazyInit();
	void drawLine( const CCPoint& origin, const CCPoint& destination );
	CCPoint worldToLocalPoint(CCPoint point);

};
#endif