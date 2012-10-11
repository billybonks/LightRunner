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
	//ccDrawLine( ccp(-50,0), ccp(MIN(screen->origin.x+screen->size.width*0.9-getPositionX(),50),0));
	ccDrawLine( ccp(this->getPositionX()/PTM_RATIO,-50), ccp(this->getPositionX()/PTM_RATIO,50));
	CCPoint bosspos = worldToLocalPoint(gameDelegate->getBoss()->getBody()->GetPosition());
	//ccDrawLine( ccp(_polygonVerticies[0].x,_polygonVerticies[0].y), ccp(MIN(bosspos.x,_polygonVerticies[1].x),MIN(bosspos.y,_polygonVerticies[0].y)));
	//CCLog("%f,%f, %f,%f", gameDelegate->getBoss()->getBody()->GetPosition().x,gameDelegate->getBoss()->getBody()->GetPosition().y,bosspos.y,_polygonVerticies[1].y);
	//drawLine( ccp(_polygonVerticies[0].x,_polygonVerticies[0].y), ccp(MIN(_polygonVerticies[1].x,gameDelegate->getBoss()->getSprite()->getPositionX()),_polygonVerticies[1].y));
	glLineWidth(1);
 }

 CCPoint Light::worldToLocalPoint(b2Vec2 point){
		float startX = this->getPositionX();
		float startY = this->getPositionY()/PTM_RATIO;
		float relX =  point.x -startX ;
		float relY =  point.y -startY ;
		//CCLog("%f,%f", startX, );
		return ccp(relX,relY);
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