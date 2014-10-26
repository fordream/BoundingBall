#ifndef _UI_B2_B2LAYER_H

#define _UI_B2_B2LAYER_H

#include "../Layer.h"
#include "Box2D/Box2D.h"
#include "GLES-Render.h"
#include "../Common/Constants.h"
USING_NS_CC;

class ContactListener;
class b2Layer : public Layer
{
public:
	b2Layer();
	virtual ~b2Layer();


	virtual bool init();

	void openDebug();
	void closeDebug();

	virtual void draw();
	virtual void update(float delta);

	b2World* getPhysicsWorld();

	virtual void beginContact(b2Contact* pb2Contact){}
	virtual void endContact(b2Contact* pb2Contact){}

protected:

	void initb2World();

	vector<b2Body*> _vectBodyToDelArr;
	b2World* _pb2World;
	GLESDebugDraw* _pDebugDraw;

private:
	bool _bIsOpenDebug;
	
};
#endif