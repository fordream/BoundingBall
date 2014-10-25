#ifndef UI_LAYER_H_
#define UI_LAYER_H_

#include <iostream>
#include "cocos2d.h"

class Layer : public cocos2d::CCLayerColor {
public:
    bool init();
	Layer();
    virtual ~Layer();
    virtual void onEnter();
    virtual void onExit();
    virtual bool initWithColor(const cocos2d::ccColor4B& color);

protected:
	cocos2d::ccColor4B _layerColor;

};
#endif /* defined(__Cocos2dDemo__Layer__) */
