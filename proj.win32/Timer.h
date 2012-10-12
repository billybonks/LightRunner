
#include "cocos2d.h"
using namespace cocos2d;

class Timer : public CCNode
{
public:
	Timer();
	CCCallFunc forJumpTimeout;
	void doJumpTimeout();
};

