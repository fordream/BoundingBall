#ifndef _BALL_H

#define _BALL_H

#include "cocos2d.h"
USING_NS_CC;

class b2Body;
class b2World;
class Ball : public CCSprite{
public:
	Ball();
	~Ball();

	static Ball* createWithPhysicsWorld(const char* pFileName, b2World* pWorld);

	CC_SYNTHESIZE(b2Body*, _pBody, Body);
protected:
	virtual bool initWithBody(const char* pFile, b2World* pWorld);
};


#endif