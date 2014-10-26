#ifndef _BOARD_H

#define _BOARD_H

#include "cocos2d.h"
USING_NS_CC;

class b2World;
class b2Body;
class Ball : public CCSprite
{
public:
	Ball();
	~Ball();

	static Ball* createWithPhysicsWorld(const char* pFileName, b2World* pWorld);

	CC_SYNTHESIZE(b2Body*, _pBody, Body);
	void setBallPosition(CCPoint position);
protected:
	virtual bool initWithBody(const char* pFile, b2World *pWorld);
	virtual void update(float delta);

};
#endif // !_BALL_H
