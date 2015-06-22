#ifndef __OVER_SCENE_H__
#define __OVER_SCENE_H__

#include "cocos2d.h"
#include "RankProgress.h"

USING_NS_CC;

class OverScene : public cocos2d::LayerColor
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene(int score, int error);

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
	CREATE_FUNC(OverScene);

	void setScore(int score);
	void setError(int error);
private:
	int _score;
	int _error;

	float _currentPercent;
	RankProgress* _rankProgress;

	void gotoPlayScene();
	void gotoMenuScene();
	void showResult(float dt);
	
	void onEnter();
	void update(float dt);
};

#endif // __OVER_SCENE_H__
