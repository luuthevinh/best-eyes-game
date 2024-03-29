#ifndef __ABOUT_SCENE_H__
#define __ABOUT_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class AboutScene : public cocos2d::LayerColor
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
	CREATE_FUNC(AboutScene);

	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* unused_event);

private:
	void gotoMenuScene();
	void likeFB();
};

#endif // __ABOUT_SCENE_H__
