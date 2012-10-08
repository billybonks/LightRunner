#include "Light.h"

using namespace cocos2d;

Light::Light()
{
	//CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	//CCSprite::CCSprite();
	//_origin = ccp(-50,0);
	//_destination = ccp(MIN(winSize.width*0.9-getPositionX(),50),0);
}

Light::Light(CCPoint position,float width,float height)
{;
	CCSprite::CCSprite();
}

	Light* Light::retainedLight(CCRect* scr){
	Light* l = new Light();
	l->setContentSize(CCSize(100,5));
		l->screen=scr;

	return l;
}
	Light* Light::retainedLight(b2Vec2* polygonVerticies){
	Light* l = new Light();

	//l->_polygonVerticies = (b2Vec2*)malloc(sizeof(b2Vec2)*2);
	//l->_polygonVerticies[0].Set(polygonVerticies[0].x, polygonVerticies[0].y);
	//l->_polygonVerticies[1].Set(polygonVerticies[1].x, polygonVerticies[1].y);
	//l->_polygonVerticies[0].x*=PTM_RATIO;
	//l->_polygonVerticies[1].x*=PTM_RATIO;
	//l->_polygonVerticies[0].y*=PTM_RATIO;
	//l->_polygonVerticies[1].y*=PTM_RATIO;
	
	//l->setContentSize(CCSize(abs(l->_polygonVerticies[1].x-l->_polygonVerticies[0].x),abs(l->_polygonVerticies[1].y-l->_polygonVerticies[0].y)));
	polygonVerticies[0]*=PTM_RATIO;
	polygonVerticies[1]*=PTM_RATIO;
	l->_polygonVerticies=polygonVerticies;
	l->setContentSize(CCSize(abs(polygonVerticies[1].x-polygonVerticies[0].x),abs(polygonVerticies[1].y-polygonVerticies[0].y)));

	//TEST
	//TEST

		CCGLProgram* shaderProgram_ = new CCGLProgram();
        shaderProgram_->initWithVertexShaderFilename("PositionColor.vsh", "PositionColor.fsh");
		l->setShaderProgram(shaderProgram_);
        l->getShaderProgram()->addAttribute(kCCAttributeNamePosition,kCCVertexAttrib_Position);
        l->getShaderProgram()->addAttribute(kCCAttributeNameTexCoord,kCCVertexAttrib_TexCoords);
        l->getShaderProgram()->link();
        l->getShaderProgram()->updateUniforms();
		
        // 3
        int colorRampUniformLocation = glGetUniformLocation(l->getShaderProgram()->getProgram(), "u_colorRampTexture");
        glUniform1i(colorRampUniformLocation, 1);

        // 4
        CCTexture2D *colorRampTexture = CCTextureCache::sharedTextureCache()->addImage("colorRamp.png");
        colorRampTexture->setAliasTexParameters();

        // 5
        l->getShaderProgram()->use();
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, colorRampTexture->getName());
        glActiveTexture(GL_TEXTURE0);

	//ENDTEST
	//ENDTEST
	
	return l;
}
 
 void Light::draw(){
	glLineWidth( 3.0f );
	//ccDrawLine( ccp(-50,0), ccp(MIN(screen->origin.x+screen->size.width*0.9-getPositionX(),50),0));
	ccDrawLine( ccp(_polygonVerticies[0].x,_polygonVerticies[0].y), ccp(_polygonVerticies[1].x,_polygonVerticies[1].y));
	glLineWidth(1);
 }

void Light::removeFromParentAndCleanup(){
	CCSprite::removeFromParentAndCleanup(true);
}

bool Light::IsTouched(){
	return _touched;
}

void Light::IsTouched(bool touched){
	 _touched = touched;
}