#include "Segment.h"
#include "GameScene.h"

Segment::Segment(){
		CCNode::CCNode();
}

Segment::Segment(b2World *world, CCPoint position){
		CCNode::CCNode();
		this->setPosition(position);
		generate(world);
}


void Segment::generate(b2World *world){
	
}

float Segment::getEndVerticeNum(){
	return 0;
}

float Segment::getStartVerticeNum(){
	return 2;
}

CCPoint* Segment::getGameWorldVertice(int vertice){
	return &_gameWorldVerticesCCW[vertice];
}

CCPoint* Segment::getPolygonVertice(int vertice){
	return &_polygonVerticesCCW[vertice];
}

CCPoint Segment::offsetStartPosition(CCPoint* sourceVert,CCPoint* targetVert,Segment* target ){
	float x=(targetVert->x)-sourceVert->x;
	float y=(targetVert->y)-sourceVert->y;
	return ccp(x,y);
}

bool Segment::insideBoundingBox(){
	return TRUE;
}

void Segment::addSprites(Game* game){
	
}

void Segment::setBounds(b2AABB* bounds){
	this->_pixelBounds=bounds;
}

	b2AABB* Segment::getBounds(){
		return this->_pixelBounds;
}