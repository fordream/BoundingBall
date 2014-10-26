#include "MainGame.h"
#include "Framework/Common/Constants.h"
#include "Board.h"
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

	_visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	_pBoard1 = Board::createWithPhysicsWorld("images/board.png",_pb2World);
	this->addChild(_pBoard1);
	_pBoard1->setPosition(ccp(_visibleSize.width / 2, _visibleSize.height / 10));
	_pBoard1->setOriginalPosition(_pBoard1->getPosition());

	_pBoard2 = Board::createWithPhysicsWorld("images/board.png", _pb2World);
	this->addChild(_pBoard2);
	_pBoard2->setPosition(ccp(_visibleSize.width / 2, 9 * _visibleSize.height / 10));
	_pBoard2->setRotation(-180.0f);
	_pBoard2->setOriginalPosition(_pBoard2->getPosition());

	_pBall = Ball::createWithPhysicsWorld("images/ball.png", _pb2World);
	_pBall->setBallPosition(ccp(_pBoard1->getPositionX(), _pBoard1->getPositionY() + _pBoard1->getContentSize().height / 2));
	this->addChild(_pBall);
//	pBall->getBody()->ApplyLinearImpulse(b2Vec2(0, 100), pBall->getBody()->GetWorldCenter());
	_pBall->getBody()->SetLinearVelocity(b2Vec2(0, 50));

	CCMenuItem* pItem = CCMenuItemSprite::create(CCSprite::create("images/pause_retry_up.png"),
		CCSprite::create("images/pause_retry_down.png"),
		this, menu_selector(MainGame::retryCallBack));
	pItem->setScale(0.8f);
	pItem->setPosition(ccp(_visibleSize.width - pItem->getContentSize().width / 2-10.0f, _visibleSize.height - pItem->getContentSize().height/2));
	CCMenu* pMenu = CCMenu::create();
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu);
	pMenu->addChild(pItem);

	scheduleUpdate();

	return true;
}

void MainGame::initBounding()
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	b2BodyDef bodyDef;
	b2Body* pBound = _pb2World->CreateBody(&bodyDef);

	b2Vec2 v1(10.0f / Constants::PTM_RATIO, 0.0f / Constants::PTM_RATIO);
	b2Vec2 v2((visibleSize.width - 10.0f) / Constants::PTM_RATIO, 0.0f);
	b2Vec2 v3((visibleSize.width - 10.0f) / Constants::PTM_RATIO, visibleSize.height / Constants::PTM_RATIO);
	b2Vec2 v4(10.0f / Constants::PTM_RATIO, visibleSize.height / Constants::PTM_RATIO);
	b2EdgeShape shape;
	shape.Set(v1, v2);
	b2FixtureDef fixtureDef;
	fixtureDef.friction = 0.0f;
	fixtureDef.shape = &shape;
	pBound->CreateFixture(&fixtureDef);

	shape.Set(v2, v3);
	fixtureDef.shape = &shape;
	pBound->CreateFixture(&fixtureDef);

	shape.Set(v3, v4);
	fixtureDef.shape = &shape;
	pBound->CreateFixture(&fixtureDef);

	shape.Set(v4, v1);
	fixtureDef.shape = &shape;
	pBound->CreateFixture(&fixtureDef);

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

	if (_pBall->getPositionY() + _pBall->getContentSize().height / 2 <= 0 ||
		_pBall->getPositionY() - _pBall->getContentSize().height / 2 >= _visibleSize.height)
	{
		this->unscheduleUpdate();
		retryCallBack(NULL);
	}
}


void MainGame::keyBackClicked()
{
	CCDirector::sharedDirector()->end();
}

void MainGame::beginContact(b2Contact* pb2Contact)
{
	CCLog("begin contact");
}

void MainGame::endContact(b2Contact* pb2Contact)
{
}

void MainGame::retryCallBack(CCObject* pSender)
{
	CCDirector::sharedDirector()->replaceScene(MainGame::createScene());
}



