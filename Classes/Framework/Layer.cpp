#include "Layer.h"

Layer::Layer()
{
	_layerColor = cocos2d::ccc4(0, 0, 0, 0);
}


Layer::~Layer(){
	
}

bool Layer::init(){
	return initWithColor(_layerColor);
}

bool Layer::initWithColor(const cocos2d::ccColor4B& color){
	if (!CCLayerColor::initWithColor(color)) {
		return false;
	}
	m_bTouchEnabled = true;
	m_bKeypadEnabled = true;
	return true;
}

void Layer::onEnter(){
	CCLayerColor::onEnter();
}

void Layer::onExit(){
	CCLayerColor::onExit();
}







