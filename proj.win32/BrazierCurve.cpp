#include "BrazierCurve.h"
#include "GameObject.h"

	BrazierCurve::BrazierCurve(){

	}

	BrazierCurve::BrazierCurve(CCPoint p1,CCPoint p2, CCPoint p3,CCPoint p4){
		this->p1 = p1;
		this->p2 = p2;
		this->p3 = p3;
		this->p4 = p4;
	}
   // BrazierCurve:: BrazierCurve::BrzierCurve* retainedLight(CCRect* scr);
	void BrazierCurve::draw(){

	}
	void BrazierCurve::removeFromParentAndCleanup(){

	}

	CCPoint BrazierCurve::PointForT(float t){
		float sect1 = pow((1-t),3.0f) * 3;
		//sect1 = sect1 * p1;
		sect1 = 1 * 2;
		return CCPoint();
	}
//B(t) = (1-t)^3P0+3(1-t)^2tP1+3(1-t)t^2P2+t^3P3 where t[0,1]