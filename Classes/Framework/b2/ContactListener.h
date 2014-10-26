#ifndef _SCENE_CONTACT_LISTENER_H

#define _SCENE_CONTACT_LISTENER_H

#include <list>
#include "Box2D/Box2D.h"

class b2Layer;

struct Contact
{
	b2Fixture* _fixtureA;
	b2Fixture* _fixtureB;
};

class ContactListener : public b2ContactListener
{
public:
	ContactListener(b2Layer* pLayer);
	virtual void BeginContact(b2Contact* contact);
	virtual void EndContact(b2Contact* contact);
	virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);

	std::list<Contact> contact_vec;

private:
	b2Layer* _pb2Layer;
};
#endif