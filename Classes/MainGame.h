#ifndef _MAINGAME_H

#define _MAINGAME_H

#include "Framework/b2/b2Layer.h"

class MainGame : public b2Layer
{
public:
	MainGame();
	~MainGame();

	static CCScene* createScene();

	CREATE_FUNC(MainGame);

protected:
	virtual bool init();
	//ππ‘Ïbianjie
	virtual void initBounding();
	virtual void update(float delta);
};

#endif