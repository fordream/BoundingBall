#ifndef _MAINGAME_H

#define _MAINGAME_H

#include "Framework/b2/b2Layer.h"
class Board;
class Ball;
class MainGame : public b2Layer
{
public:
	MainGame();
	~MainGame();

	static CCScene* createScene();

	CREATE_FUNC(MainGame);

	virtual void beginContact(b2Contact* pb2Contact);
	virtual void endContact(b2Contact* pb2Contact);

protected:
	virtual bool init();
	//ππ‘Ïbianjie
	virtual void initBounding();
	virtual void update(float delta);
	virtual void keyBackClicked();

	void retryCallBack(CCObject* pSender);


	Board *_pBoard1, *_pBoard2;
	Ball *_pBall;
	CCSize _visibleSize;

};

#endif