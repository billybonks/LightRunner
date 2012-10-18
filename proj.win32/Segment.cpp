#include "Segment.h"

Segment::Segment(){
		CCNode::CCNode();
}

Segment::Segment(CCPoint position){
		CCNode::CCNode();
		this->setPosition(position);
		generate();
}


void Segment::generate(){

}

CCPoint* Segment::getEndVertice(){
	return &_gameWorldVerticesCCW[0];
}

CCPoint* Segment::getStartVertice(){
	return &_gameWorldVerticesCCW[2];
}

CCPoint* Segment::getGameWorldVertice(int vertice){
	return &_gameWorldVerticesCCW[vertice];
}

CCPoint* Segment::getPolygonVertice(int vertice){
	return &_polygonVerticesCCW[vertice];
}

void Segment::offsetStartPosition(CCPoint* sourceVert,CCPoint* targetVert,Segment* target ){
	float x=(targetVert->x/PTM_RATIO)-sourceVert->x;
	float y=(targetVert->y/PTM_RATIO)-sourceVert->y;
	this->setPosition(ccp(x,y));
}

bool Segment::insideBoundingBox(){
	return TRUE;
}

void Segment::setBounds(b2AABB* bounds){
	this->_pixelBounds=bounds;
}

	b2AABB* Segment::getBounds(){
		return this->_pixelBounds;
}