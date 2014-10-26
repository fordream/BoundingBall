#include "Board.h"
#include <Box2D/Box2D.h>
#include "Framework/Common/Constants.h"
#include <cmath>
Board::Board() :
_fLitmitHeight(0.0f),
_bIsMoved(true)
{

}

Board::~Board()
{

}

Board* Board::createWithPhysicsWorld(const char* pFileName, b2World* pWorld)
{
	Board* pRet = new Board();
	if (pRet && pRet->initWithBody(pFileName, pWorld))
	{
		pRet->autorelease();
		return pRet;
	}
	CC_SAFE_DELETE(pRet);
	pRet = NULL;
	return NULL;
}

bool Board::initWithBody(const char *pszFilename, b2World* pWorld)
{
	if (!CCSprite::initWithFile(pszFilename))
		return false;

	b2BodyDef bodyDef;
	bodyDef.type = b2_kinematicBody;

	_pBody = pWorld->CreateBody(&bodyDef);

	//µ×±ß
	b2PolygonShape shape;
	b2Vec2 vertices[4];
	vertices[0].Set(-this->getContentSize().width / 2 / Constants::PTM_RATIO, -this->getContentSize().height / 2 / Constants::PTM_RATIO);
	vertices[1].Set(this->getContentSize().width / 2 / Constants::PTM_RATIO, -this->getContentSize().height / 2 / Constants::PTM_RATIO);
	vertices[2].Set(this->getContentSize().width / 2 / Constants::PTM_RATIO, 0.0f);
	vertices[3].Set(-this->getContentSize().width / 2 / Constants::PTM_RATIO, 0.0f);
	shape.Set(vertices, 4);
	
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	_pBody->CreateFixture(&fixtureDef);

	//y = ax^2+k
	float h = 0.0f;
	float k = this->getContentSize().height / 2;
	float x2 = pow(this->getContentSize().width / 2, 2);
	float a = -k / x2;
	float fGap = this->getContentSize().width / 8;
	b2Vec2 vertices2[9];
	float x, y;
	for (unsigned int i = 0; i < 9; i++)
	{
		x = this->getContentSize().width/2 - fGap*i;
		y = a*pow(x, 2) + k;
		vertices2[i].Set(x/Constants::PTM_RATIO, y/Constants::PTM_RATIO);
	}
	shape.Set(vertices2, 9);
	fixtureDef.shape = &shape;
	_pBody->CreateFixture(&fixtureDef);

	_pBody->SetUserData(this);
	
	return true;
}

void Board::onEnter()
{
	CCSprite::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
}

bool Board::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	CCRect rect = CCRectMake(0, 0, this->getContentSize().width*3.0f, this->getContentSize().height*3.0f);
	CCPoint position = this->convertToNodeSpace(pTouch->getLocation());
	if (rect.containsPoint(position))
	{
		CCLog("begin");
		return true;
	}
	return false;
}

void Board::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{

	CCSize _visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint position = pTouch->getLocation();
	if (position.x+ this->getContentSize().width / 2 >= _visibleSize.width)
	{
		this->setPosition(ccp(_visibleSize.width - this->getContentSize().width / 2, this->getOriginalPosition().y));
	}
	else if (position.x- this->getContentSize().width / 2 <= 0)
	{
		this->setPosition(ccp(this->getContentSize().width / 2, this->getOriginalPosition().y));
	}
	else
	{
		this->setPosition(ccp(position.x, _originalPosition.y));
	}
}

