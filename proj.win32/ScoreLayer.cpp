#include "ScoreLayer.h"

using namespace cocos2d;

bool ScoreLayer::init(){
winSize = CCDirector::sharedDirector()->getWinSize();
//Create Individual sprites for objects that will persist all game
//player
CCPoint pos = this->getPosition();
//	this->setPosition(ccp(-_player->getBody()->GetPosition().x*PTM_RATIO+winSize.width * 0.1,0));
_score = CCLabelTTF::create("Score", "Arial", 12);
_score->setHorizontalAlignment(CCTextAlignment::kCCTextAlignmentRight);
_score->setPosition(ccp(0, winSize.height-10));
_score->setVisible(true);
_score->setColor(ccc3(234,0,12));
_velocity = CCLabelTTF::create("Velocity", "Arial", 12);
_velocity->setHorizontalAlignment(CCTextAlignment::kCCTextAlignmentRight);
_velocity->setPosition(ccp(0, winSize.height-20));
_velocity->setVisible(true);
_velocity->setColor(ccc3(234,0,12));
_multiplier = CCLabelTTF::create("Multiplier", "Arial", 12);
_multiplier->setPosition(ccp(0, winSize.height-30));
_multiplier->setVisible(true);
_multiplier->setColor(ccc3(234,0,12));
_multiplier->setHorizontalAlignment(CCTextAlignment::kCCTextAlignmentRight);
_distanceTraveled = CCLabelTTF::create("Distance", "Arial", 12);
_distanceTraveled->setPosition(ccp(0, winSize.height-40));
_distanceTraveled->setVisible(true);
_distanceTraveled->setColor(ccc3(234,0,12));
_distanceTraveled->setHorizontalAlignment(CCTextAlignment::kCCTextAlignmentRight);
this->addChild(_multiplier);
this->addChild(_velocity);
this->addChild(_score);
this->addChild(_distanceTraveled);
_multiplier->setAnchorPoint(ccp(0,0));
_velocity->setAnchorPoint(ccp(0,0));
_score->setAnchorPoint(ccp(0,0));
_distanceTraveled->setAnchorPoint(ccp(0,0));
this->scheduleUpdate();
///LABEL SPAMMAGE IS NOW COMPLETE
return true;
}

void ScoreLayer::draw(){
}

void ScoreLayer::update(float dt){
	float velocity = _stats->GetVelocity();
	
	string str =  "Velocity :"+floatToStr(velocity);
	_velocity->setString(str.c_str());
    stringstream pp (stringstream::in | stringstream::out);
	pp << (_stats->GetDistanceTraveled()/32);
	str = "Distance :"+floatToStr(_stats->GetDistanceTraveled());
	_distanceTraveled->setString(str.c_str());
	str = "Multiplier :"+floatToStr(_stats->GetMultiplier());
	_multiplier->setString(str.c_str());
	str = "Score :"+floatToStr(_stats->GetScore());
	_score->setString(str.c_str());
}


string ScoreLayer::floatToStr(float f){
	stringstream ss (stringstream::in | stringstream::out);
	ss << f;
	string str = ss.str();
	return str;
}
void ScoreLayer::SetStatistics(Statistics* stats){
	this->_stats = stats;
}