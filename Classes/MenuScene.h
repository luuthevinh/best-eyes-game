#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"
#include "Definitions.h"

USING_NS_CC;

class MenuScene : public cocos2d::LayerColor
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
	CREATE_FUNC(MenuScene);

	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* unused_event);

private:
	void gotoPlayScene();
	void gotoAchievementScene();
	void exitGame();
	void gotoAboutScene();
	void removeAds();
	void rateGame();
};

#endif // __MENU_SCENE_H__
