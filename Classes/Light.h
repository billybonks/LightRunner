#ifndef LIGHT
#define LIGHT

#include "GameObject.h"
using namespace cocos2d;
class Game;
class Light : public CCSprite
{
public:
	Light();
	Light(CCPoint position,float width,float height);
	static Light* retainedLight(b2Vec2* polygonVerticies);
	CCPoint* _polygonVerticies;

	virtual void draw();
	virtual void removeFromParentAndCleanup();
	bool IsTouched();
	void IsTouched(bool touched);
	CCRect *screen;
	static void setGame(Game* game);

protected:
	bool _touched;
	static Game* gameDelegate;
	static CCGLProgram* _shaderProgram;
	static void lazyInit();

private:
	//CCTexture2D *colorRampTexture;
	void drawLine( const CCPoint& origin, const CCPoint& destination );
	CCPoint worldToLocalPoint(CCPoint point);

};
#endif