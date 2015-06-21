#ifndef __OVER_SCENE_H__
#define __OVER_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class OverScene : public cocos2d::LayerColor
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
	CREATE_FUNC(OverScene);
private:
	void gotoPlayScene();
	void gotoMenuScene();
};

#endif // __OVER_SCENE_H__
