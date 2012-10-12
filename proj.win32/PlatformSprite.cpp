#include "PlatformSprite.h"
#include "GameScene.h"

PlatformSprite::PlatformSprite()
{
	Light::Light();
}

PlatformSprite::PlatformSprite(CCPoint position,float width,float height)
{;
	Light::Light();
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
 
 void PlatformSprite::draw(){
	glLineWidth( 1.0f );
	//polygonvertices are:
	//0		1      <maybe wrong and flipped vertically
	//3		2
	CCPoint bosspos = worldToLocalPoint(gameDelegate->getBoss()->getPosition());
	drawLine( bosspos,ccp(bosspos.x,_polygonVerticies[0].y));

	//ccDrawLine( ccp(_polygonVerticies[0].x,_polygonVerticies[0].y), ccp(_polygonVerticies[1].x,_polygonVerticies[1].y));
	//ccDrawLine( ccp(_polygonVerticies[2].x,_polygonVerticies[2].y), ccp(_polygonVerticies[3].x,_polygonVerticies[3].y));
	float wat= rand()/(RAND_MAX + 1.0); 
	float the= rand()/(RAND_MAX + 1.0); 
	float fuck= rand()/(RAND_MAX + 1.0); 
	CCPoint* vertices = (CCPoint*)malloc(sizeof(CCPoint)*4);
	vertices[0]=ccp(_polygonVerticies[0].x,_polygonVerticies[0].y);
	vertices[1]=ccp(bosspos.x,_polygonVerticies[1].y);
	vertices[2]=ccp(bosspos.x,_polygonVerticies[2].y);
	vertices[3]=ccp(_polygonVerticies[3].x,_polygonVerticies[3].y);
	ccColor4F colour = {wat,the,fuck,1};
	ccDrawSolidPoly(vertices,4,colour);
	glLineWidth(1);
 }

 CCPoint PlatformSprite::worldToLocalPoint(CCPoint point){
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

 void PlatformSprite::drawLine( const CCPoint& origin, const CCPoint& destination )
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
