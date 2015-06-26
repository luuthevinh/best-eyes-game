#ifndef __ACHIEVEMENT_SCENE_H__
#define __ACHIEVEMENT_SCENE_H__

#include "cocos2d.h"
#include "RankProgress.h"

USING_NS_CC;

class AchievementScene : public cocos2d::LayerColor
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
	CREATE_FUNC(AchievementScene);
private:
	RankProgress* _rankProgress;
	int _bestScore;

	void onEnter();
	void showResult(float dt);
	void gotoMenuScene();

	void afterCaptured(bool succeed, const std::string& outputFile);
	void shareScore();
};

#endif // __ACHIEVEMENT_SCENE_H__
