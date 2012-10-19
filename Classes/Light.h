#ifndef LIGHT
#define LIGHT

#include "GameObject.h"
using namespace cocos2d;

class Light : public CCSprite
{
public:
	Light();
	Light(CCPoint position,float width,float height);
	static Light* retainedLight(CCPoint* polygonVerticies);
	CCPoint* _polygonVerticies;

	virtual void draw();
	virtual void removeFromParentAndCleanup();
	bool IsTouched();
	void IsTouched(bool touched);
	CCRect *screen;
	static void setBoss(GameObject* boss);
	void setMix(ccColor4F mix);

protected:
	bool _touched;
	static GameObject* _boss;
	static CCGLProgram* _shaderProgram;
	static void lazyInit();
	void drawLine( const CCPoint& origin, const CCPoint& destination,ccColor4F colour );
	CCPoint worldToLocalPoint(CCPoint point);

	ccColor4F _mix;
	ccColor4F _colour;
	void nextColour();

private:
	//CCTexture2D *colorRampTexture;

};
#endif