#include "PlatformSprite.h"
#include "GameScene.h"

PlatformSprite::PlatformSprite()
{
	Light::Light();
	_fillColour=&_colour;
}

PlatformSprite::PlatformSprite(CCPoint position,float width,float height)
{
	PlatformSprite::PlatformSprite();
}

PlatformSprite* PlatformSprite::retainedPlatformSprite(b2Vec2* polygonVerticies){
		if(_shaderProgram==NULL){
			Light::lazyInit();
		}
		PlatformSprite* p = new PlatformSprite();
		p->_polygonVerticies = (CCPoint*)malloc(sizeof(CCPoint)*4);
		p->_polygonVerticies[0]=ccp(polygonVerticies[0].x*PTM_RATIO,polygonVerticies[0].y*PTM_RATIO);
		p->_polygonVerticies[1]=ccp(polygonVerticies[1].x*PTM_RATIO,polygonVerticies[1].y*PTM_RATIO);
		p->_polygonVerticies[2]=ccp(polygonVerticies[2].x*PTM_RATIO,polygonVerticies[2].y*PTM_RATIO);
		p->_polygonVerticies[3]=ccp(polygonVerticies[3].x*PTM_RATIO,polygonVerticies[3].y*PTM_RATIO);
		p->setContentSize(CCSize(abs(polygonVerticies[1].x-polygonVerticies[0].x),abs(polygonVerticies[2].y-polygonVerticies[0].y)));
		p->setShaderProgram(_shaderProgram);
		

		return p;
}
 

void PlatformSprite::setFillColour(ccColor4F* colour){
		this->_fillColour=colour;
	}

 void PlatformSprite::draw(){
	glLineWidth( 1.0f );
	//polygonvertices are:
	//0		1      <maybe wrong and flipped vertically
	//3		2
	CCPoint bosspos = worldToLocalPoint(gameDelegate->getBoss()->getPosition());
	nextColour();
	drawLine( bosspos,ccp(bosspos.x,_polygonVerticies[0].y),_colour);
	CCPoint* vertices = (CCPoint*)malloc(sizeof(CCPoint)*4);
	vertices[0]=ccp(_polygonVerticies[0].x,_polygonVerticies[0].y);
	vertices[1]=ccp(bosspos.x,_polygonVerticies[1].y);
	vertices[2]=ccp(bosspos.x,_polygonVerticies[2].y);
	vertices[3]=ccp(_polygonVerticies[3].x,_polygonVerticies[3].y);
	ccDrawSolidPoly(vertices,4,*_fillColour);
	glLineWidth(1);
 }
