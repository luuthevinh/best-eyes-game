#ifndef __RANK_PROGRESS_H__
#define __RANK_PROGRESS_H__

#include "cocos2d.h"

USING_NS_CC;

class RankProgress : public Node
{
public:
	CREATE_FUNC(RankProgress);

	bool init();

	void setPercent(float percent);

	void runToPercent(float time, float percent);

private:
	float _toPercent;

	ProgressTimer* _progressBar;

	void update(float dt);
	void updateSun(int i);
};

#endif //__RANK_PROGRESS_H__