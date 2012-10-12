#include "Timer.h"

void Timer::doJumpTimeout()
{
	CCDelayTime *delayAction = CCDelayTime::create(0.2f);
	// perform the selector call
	//CCCallFunc *callSelectorAction = CCCallFunc::create(this, callfunc_selector(Player::timeOutJump));
     this->forJumpTimeout.execute();
}

Timer::Timer(){

}
