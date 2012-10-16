#include "Light.h"
#include "GameScene.h"

using namespace cocos2d;
CCGLProgram* Light::_shaderProgram;
Game* Light::gameDelegate;

Light::Light()
{
	CCSprite::CCSprite();
	ccColor4F mix = {0,0,0,0};
	ccColor4F start = {0,0,0,1};
	_mix=mix;
	_colour=start;
}

Light::Light(CCPoint position,float width,float height)
{;
	Light::Light();
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
		
		l->_polygonVerticies = (CCPoint*)malloc(sizeof(CCPoint)*2);
		l->_polygonVerticies[0]=ccp(polygonVerticies[0].x*PTM_RATIO,polygonVerticies[0].y*PTM_RATIO);
		l->_polygonVerticies[1]=ccp(polygonVerticies[1].x*PTM_RATIO,polygonVerticies[1].y*PTM_RATIO);
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
		nextColour();

		drawLine( ccp(_polygonVerticies[0].x,_polygonVerticies[0].y), bosspos,_colour);

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

 void Light::drawLine( const CCPoint& origin, const CCPoint& destination ,ccColor4F colour)
{

    ccVertex2F vertices[2] = {
        {origin.x, origin.y},
        {destination.x, destination.y}
    };

	_shaderProgram->use();
    CHECK_GL_ERROR_DEBUG();
    _shaderProgram->setUniformForModelViewProjectionMatrix();
    CHECK_GL_ERROR_DEBUG();
	float r= colour.r; 
	float g= colour.g; 
	float b= colour.b; 
	
	const GLuint program = _shaderProgram->getProgram();
	_shaderProgram->setUniformLocationWith1f(glGetUniformLocation( program, "r"), r);
	_shaderProgram->setUniformLocationWith1f(glGetUniformLocation( program, "g"), g);
	_shaderProgram->setUniformLocationWith1f(glGetUniformLocation( program, "b"), b);
 ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
    CHECK_GL_ERROR_DEBUG();
    glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    CHECK_GL_ERROR_DEBUG();
    glDrawArrays(GL_LINES, 0, 2);

    CC_INCREMENT_GL_DRAWS(1);
}

 void Light::setMix(ccColor4F mix){
	_mix=mix;
}

void Light::nextColour(){
	float red= rand()/(RAND_MAX + 1.0); 
	float green= rand()/(RAND_MAX + 1.0); 
	float blue= rand()/(RAND_MAX + 1.0); 

	// mix the color
	if (_mix.r!=0&&_mix.g!=0&&_mix.b!=0&&_mix.a!=0) {
        red = (red + _mix.r) / 2;
        green = (green + _mix.g) / 2;
        blue = (blue +_mix.b) / 2;
    }
	ccColor4F colour = {red,green,blue,1};
	_colour=colour;
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