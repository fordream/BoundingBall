#include "b2Layer.h"

b2Layer::b2Layer() :_pb2World(NULL)
{

}

b2Layer::~b2Layer()
{
	_vectBodyToDelArr.clear();
	CC_SAFE_DELETE(_pDebugDraw);
	CC_SAFE_DELETE(_pb2World);
	CCLOG("b2Layer release");
}

bool b2Layer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	initb2World();

	return true;
}

b2World* b2Layer::getPhysicsWorld()
{
	return _pb2World;
}


void b2Layer::initb2World()
{
	//创建一个无重力的世界，只用box2d来做碰撞检测
	b2Vec2 gravity;
	gravity.Set(0.0f, 0.0f);
	_pb2World = new b2World(gravity);
	_pb2World->SetAllowSleeping(true);
	_pb2World->SetContinuousPhysics(true);

	_pDebugDraw = new GLESDebugDraw(Constants::PTM_RATIO);
	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	flags += b2Draw::e_jointBit;
	flags += b2Draw::e_aabbBit;
	flags += b2Draw::e_pairBit;
	flags += b2Draw::e_centerOfMassBit;
	_pDebugDraw->SetFlags(flags);
	_pb2World->SetDebugDraw(_pDebugDraw);

}

void b2Layer::openDebug()
{
	_bIsOpenDebug = true;
}

void b2Layer::closeDebug()
{
	_bIsOpenDebug = false;
}

void b2Layer::draw()
{
	if (!_bIsOpenDebug)
		return;

	ccGLEnableVertexAttribs(kCCVertexAttribFlag_Position);

	kmGLPushMatrix();

	_pb2World->DrawDebugData();

	kmGLPopMatrix();
}

void b2Layer::update(float delta)
{
	Layer::update(delta);
	_pb2World->Step(delta, 8, 3);
	
	vector<b2Body*>::iterator it = _vectBodyToDelArr.begin();
	while (it != _vectBodyToDelArr.end())
	{
		b2Body* pBody = *it;
		if (pBody)
		{
			_pb2World->DestroyBody(pBody);
			pBody = NULL;
		}
		++it;
	}
	_vectBodyToDelArr.clear();
}

