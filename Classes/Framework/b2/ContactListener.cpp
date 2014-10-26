#include "ContactListener.h"
#include "b2Layer.h"

ContactListener::ContactListener(b2Layer* pLayer)
{
	_pb2Layer = pLayer;
}


void ContactListener::BeginContact(b2Contact* contact)
{
	_pb2Layer->beginContact(contact);
	B2_NOT_USED(contact);
}

void ContactListener::EndContact(b2Contact* contact)
{
	_pb2Layer->endContact(contact);
	B2_NOT_USED(contact);
}

void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
	
}

void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
	
}

