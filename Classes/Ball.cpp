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

bool Ball::initWithBody(const char* pFile, b2World *pWorld)
{
	if (!CCSprite::initWithFile(pFile))
		return false;

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;

	_pBody = pWorld->CreateBody(&bodyDef);
	b2CircleShape shape;
	shape.m_radius = this->getContentSize().width / 2/Constants::PTM_RATIO;

	b2FixtureDef fixtureDef;
	fixtureDef.density = 0.0f;
	fixtureDef.friction = 0.0f;
	fixtureDef.restitution = 1.0f;
	fixtureDef.shape = &shape;
	_pBody->CreateFixture(&fixtureDef);

	scheduleUpdate();

	return true;
}

void Ball::update(float delta)
{
	CCSprite::update(delta);
	this->setPosition(ccp(_pBody->GetPosition().x*Constants::PTM_RATIO, _pBody->GetPosition().y*Constants::PTM_RATIO));
	this->setRotation((-1)*CC_RADIANS_TO_DEGREES(_pBody->GetAngle()));
}

void Ball::setBallPosition(CCPoint position)
{
	_pBody->SetTransform(b2Vec2(position.x / Constants::PTM_RATIO, position.y / Constants::PTM_RATIO), _pBody->GetAngle());
}

