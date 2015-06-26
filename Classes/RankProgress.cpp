#include "RankProgress.h"

bool RankProgress::init()
{
	//Size visibleSize = Director::getInstance()->getVisibleSize();
	//Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	auto progressBG = Sprite::create("RankProgressBG.png");
	progressBG->setPosition(Point(this->getPositionX(), this->getPositionY()));
	this->addChild(progressBG);

	_progressBar = ProgressTimer::create(Sprite::create("RankProgress.png"));
	_progressBar->setType(ProgressTimerType::BAR);
	_progressBar->setPosition(Point(this->getPositionX(), this->getPositionY()));
	_progressBar->setBarChangeRate(Vec2(1, 0));
	_progressBar->setPercentage(0);
	_progressBar->setMidpoint(Vec2(0, 1));

	this->addChild(_progressBar);

	//Update
	this->scheduleUpdate();

	//Init
	_toPercent = 0.0f;

	//Sun
	for (int i = 0; i < 5; i++)
	{
		auto sun = Sprite::create("BlackSun.png");
		float posX = _progressBar->getBoundingBox().getMinX() + (_progressBar->getContentSize().width / 6) * (i + 1);
		sun->setPosition(posX, _progressBar->getBoundingBox().getMinY() - 30);
		sun->setName(String::createWithFormat("sun_%d", i + 1)->getCString());
		this->addChild(sun);
	}

	return true;
}

void RankProgress::setPercent(float percent)
{
	_progressBar->setPercentage(percent);
}

void RankProgress::runToPercent(float time, float percent)
{
	ProgressFromTo* to = ProgressFromTo::create(time, 0, percent);
	_progressBar->runAction(to);

	_toPercent = percent;
	
}

void RankProgress::update(float dt)
{
	if (_progressBar->getNumberOfRunningActions() != 0)
	{
		float percent = _progressBar->getPercentage();
		int num = ((percent / 100) * _progressBar->getContentSize().width) / (_progressBar->getContentSize().width / 6);
		auto child = this->getChildByName(String::createWithFormat("sun_%d", num)->getCString());

		float topercent = _toPercent;

		if (auto sprite = dynamic_cast<Sprite*>(child))
		{
			auto func = CallFunc::create([sprite, topercent]()
			{
				if (topercent >= 100)
				{
					sprite->setSpriteFrame(SpriteFrame::create("RedSun.png", sprite->getTextureRect()));
				}
				else
				{
					sprite->setSpriteFrame(SpriteFrame::create("YellowSun.png", sprite->getTextureRect()));
				}
			});

			sprite->setName("sun_yellow");
			sprite->runAction(Sequence::create(ScaleTo::create(0.1f, 1.1f), ScaleTo::create(0.1f, 1.0f), func, nullptr));
		}
	}
}

void RankProgress::updateSun(int i)
{

}