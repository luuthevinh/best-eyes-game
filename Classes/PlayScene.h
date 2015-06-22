#ifndef __PLAY_SCENE_H__
#define __PLAY_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class PlayScene : public cocos2d::LayerColor
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
	CREATE_FUNC(PlayScene);

private:
	float _squareWidth;
	Color4F _colorLevel;

	float _opacityScoreSquare;
	Vec2 _scoreIndex;
	Vec2 _touchIndex;
	int _score;
	int _error;

	int _gridRow;
	int _gridColumn;
	Vec2 _gridTopLeft;
	Vec2 _gridCenter;

	float _timer;
	float _totalTime;
	ProgressTimer* _progress;

	void drawSquare(int width, Vec2 position, float opacity = 1);
	void drawGrid(int row, int col);
	void randomColor();
	Vec2 calculateTopLeft();
	Vec2 getTouchIndex(Vec2 touchlocation);
	void checkScore();
	void createLevel();

	bool onTouchBegan(Touch* touch, Event* event);
	void update(float dt);
};

#endif // __PLAY_SCENE_H__
