#include "MainGame.h"
#include "Framework/Common/Constants.h"
#include "Ball.h"
MainGame::MainGame()
{

}

MainGame::~MainGame()
{

}

CCScene* MainGame::createScene()
{
	CCScene* pRet = CCScene::create();
	MainGame* pLayer = MainGame::create();
	pRet->addChild(pLayer);
	return pRet;
}

bool MainGame::init()
{
	if (!b2Layer::init())
		return false;

	initBounding();

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	Ball* pBall = Ball::createWithPhysicsWorld("images/board.png",_pb2World);
	this->addChild(pBall);
	pBall->setVisible(false);
	pBall->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));

	scheduleUpdate();

	return true;
}

void MainGame::initBounding()
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	b2BodyDef bodyDef;
	b2Body* pBound = _pb2World->CreateBody(&bodyDef);

	b2Vec2 v1(10.0f / Constants::PTM_RATIO, 0.0f / Constants::PTM_RATIO);
	b2Vec2 v2(10.0f / Constants::PTM_RATIO, visibleSize.height / Constants::PTM_RATIO);
	b2EdgeShape shape;
	shape.Set(v1, v2);
	pBound->CreateFixture(&shape, 0.0f);

	b2Vec2 v3((visibleSize.width - 10.0f) / Constants::PTM_RATIO, 0.0f);
	b2Vec2 v4((visibleSize.width - 10.0f) / Constants::PTM_RATIO, visibleSize.height / Constants::PTM_RATIO);
	shape.Set(v3, v4);
	pBound->CreateFixture(&shape, 0.0f);

}

void MainGame::update(float delta)
{
	b2Layer::update(delta);

	for (b2Body* pBody = _pb2World->GetBodyList(); NULL != pBody; pBody = pBody->GetNext())
	{
		CCNode* pNode = static_cast<CCNode*>(pBody->GetUserData());
		if (pNode)
		{
			pBody->SetTransform(b2Vec2(pNode->getPositionX() / Constants::PTM_RATIO, pNode->getPositionY() / Constants::PTM_RATIO),
				(-1)*CC_DEGREES_TO_RADIANS(pNode->getRotation()));
		}
	}
}

