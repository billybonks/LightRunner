#include "Segment.h"

	B2Segment::B2Segment(){
		Segment::Segment();
	}

	B2Segment::B2Segment(CCPoint position){
		Segment::Segment(position);
	}

	 b2Body* B2Segment::getBody(){
		 return _body;
	}

	 CCSprite* B2Segment::getSprite(){
		 return _sprite;
	}

	void B2Segment::genBoundingBox(){
	b2AABB aabb;
	aabb.lowerBound = b2Vec2(FLT_MAX,FLT_MAX);
	aabb.upperBound = b2Vec2(-FLT_MAX,-FLT_MAX); 
	b2Fixture* fixture = this->_body->GetFixtureList();
	while (fixture != NULL)
	{
		aabb.Combine(aabb, fixture->GetAABB(0));
		fixture = fixture->GetNext();
	}
	aabb.lowerBound*=PTM_RATIO;
	aabb.upperBound*=PTM_RATIO;
	this->setBounds(&aabb);
}