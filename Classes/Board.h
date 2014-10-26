#ifndef _BALL_H

#define _BALL_H

#include "cocos2d.h"
USING_NS_CC;

class b2Body;
class b2World;
class Board : public CCSprite, public CCTouchDelegate{
public:
	Board();
	~Board();

	static Board* createWithPhysicsWorld(const char* pFileName, b2World* pWorld);

	CC_SYNTHESIZE(b2Body*, _pBody, Body);
	CC_SYNTHESIZE(CCPoint, _originalPosition, OriginalPosition);
	CC_SYNTHESIZE(bool, _bIsMoved, IsMove);
protected:
	virtual bool initWithBody(const char* pFile, b2World* pWorld);
	virtual void onEnter();

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	// optional

	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	

private:
	float _fLitmitHeight;
};


#endif