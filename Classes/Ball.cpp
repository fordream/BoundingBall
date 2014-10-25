#include "Ball.h"
#include <Box2D/Box2D.h>
#include "Framework/Common/Constants.h"
Ball::Ball()
{

}

Ball::~Ball()
{

}

Ball* Ball::createWithPhysicsWorld(const char* pFileName, b2World* pWorld)
{
	Ball* pRet = new Ball();
	if (pRet && pRet->initWithBody(pFileName, pWorld))
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	pRet = NULL;
	return NULL;
}

bool Ball::initWithBody(const char *pszFilename, b2World* pWorld)
{
	if (!CCSprite::initWithFile(pszFilename))
		return false;

	b2BodyDef bodyDef;
	bodyDef.type = b2_kinematicBody;

	_pBody = pWorld->CreateBody(&bodyDef);

	b2EdgeShape shape;
	b2Vec2 v1(-this->getContentSize().width / 2 / Constants::PTM_RATIO, -this->getContentSize().height / 2 / Constants::PTM_RATIO);
	b2Vec2 v2(this->getContentSize().width / 2 / Constants::PTM_RATIO, -this->getContentSize().height / 2 / Constants::PTM_RATIO);
	b2Vec2 v3(10.0f, this->getContentSize().height / 2 / Constants::PTM_RATIO);
	shape.Set(v1, v2);
	shape.m_hasVertex3 = true;
	shape.m_vertex3 = v3;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	_pBody->CreateFixture(&fixtureDef);
	_pBody->SetUserData(this);
	
	return true;
}

