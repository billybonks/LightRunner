#include "Light.h"
#include "GameScene.h"

using namespace cocos2d;
CCGLProgram* Light::_shaderProgram;
Game* Light::gameDelegate;

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
void Light::lazyInit(){
		_shaderProgram = new CCGLProgram();
        _shaderProgram->initWithVertexShaderFilename("PositionColor.vsh", "PositionColor.fsh");
        _shaderProgram->addAttribute(kCCAttributeNamePosition,kCCVertexAttrib_Position);
        _shaderProgram->addAttribute(kCCAttributeNameTexCoord,kCCVertexAttrib_TexCoords);
        _shaderProgram->link();
        _shaderProgram->updateUniforms();
}

void Light::setGame(Game* game){
		Light::gameDelegate=game;
	}

Light* Light::retainedLight(b2Vec2* polygonVerticies){
		if(_shaderProgram==NULL){
			Light::lazyInit();
		}
		Light* l = new Light();
		polygonVerticies[0]*=PTM_RATIO;
		polygonVerticies[1]*=PTM_RATIO;
		l->_polygonVerticies=polygonVerticies;
		l->setContentSize(CCSize(abs(polygonVerticies[1].x-polygonVerticies[0].x),abs(polygonVerticies[1].y-polygonVerticies[0].y)));
		l->setShaderProgram(_shaderProgram);
        //TEST
	  // 3
		//  int colorRampUniformLocation = glGetUniformLocation(l->getShaderProgram()->getProgram(), "u_colorRampTexture");
		//  glUniform1i(colorRampUniformLocation, 1);
		  // 4
		//  l->colorRampTexture = CCTextureCache::sharedTextureCache()->addImage("colorRamp.png");
		//  l->colorRampTexture->setAliasTexParameters();

        // 5

	return l;
}
 
 void Light::draw(){
	//  glActiveTexture(GL_TEXTURE1);
    //    glBindTexture(GL_TEXTURE_2D, colorRampTexture->getName());
     //   glActiveTexture(GL_TEXTURE0);
	glLineWidth( 3.0f );
	CCPoint bosspos = worldToLocalPoint(gameDelegate->getBoss()->getPosition());
	drawLine( ccp(_polygonVerticies[0].x,_polygonVerticies[0].y), bosspos);
	glLineWidth(1);
 }

 CCPoint Light::worldToLocalPoint(CCPoint point){
	float thisx=this->getPositionX();
	float distancex=point.x-thisx-_polygonVerticies[0].x;
	float lengthx=_polygonVerticies[1].x-_polygonVerticies[0].x;
	float drawtox=0;
	if (distancex<0)
		drawtox=_polygonVerticies[0].x;
	else if (distancex<lengthx)
		drawtox=distancex-_polygonVerticies[1].x;
	else 
		drawtox=_polygonVerticies[1].x;

	float thisy=this->getPositionY();
	float distancey=point.y-thisy;
	float drawtoy=0;
	if (distancex<0)
		drawtoy=_polygonVerticies[0].y;
	else if (distancex<lengthx)
		drawtoy=distancey;
	else 
		drawtoy=_polygonVerticies[1].y;
	return ccp(drawtox,drawtoy);
}

 void Light::drawLine( const CCPoint& origin, const CCPoint& destination )
{

    ccVertex2F vertices[2] = {
        {origin.x, origin.y},
        {destination.x, destination.y}
    };

	_shaderProgram->use();
    CHECK_GL_ERROR_DEBUG();
    _shaderProgram->setUniformForModelViewProjectionMatrix();
    CHECK_GL_ERROR_DEBUG();
	float wat= rand()/(RAND_MAX + 1.0); 
	float the= rand()/(RAND_MAX + 1.0); 
	float fuck= rand()/(RAND_MAX + 1.0); 
	
	const GLuint program = _shaderProgram->getProgram();
	_shaderProgram->setUniformLocationWith1f(glGetUniformLocation( program, "wat"), wat);
	_shaderProgram->setUniformLocationWith1f(glGetUniformLocation( program, "the"), the);
	_shaderProgram->setUniformLocationWith1f(glGetUniformLocation( program, "fuck"), fuck);
 ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
    CHECK_GL_ERROR_DEBUG();
    glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    CHECK_GL_ERROR_DEBUG();
    glDrawArrays(GL_LINES, 0, 2);

    CC_INCREMENT_GL_DRAWS(1);
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