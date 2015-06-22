#include "OverScene.h"
#include "Definitions.h"
#include "PlayScene.h"
#include "MenuScene.h"

USING_NS_CC;

Scene* OverScene::createScene(int score, int error)
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = OverScene::create();
	layer->setScore(score);
	layer->setError(error);

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool OverScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !LayerColor::initWithColor(Color4B::WHITE) )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////

	auto scoreBG = Sprite::create("ScoreBG.png");
	scoreBG->setPosition(origin.x + visibleSize.width / 2, origin.y + (visibleSize.height / 5) * 2);
	this->addChild(scoreBG);

	auto errorBG = Sprite::create("ErrorBG.png");
	errorBG->setPosition(scoreBG->getBoundingBox().getMaxX() - errorBG->getContentSize().width / 2, 
						scoreBG->getBoundingBox().getMaxY() + errorBG->getContentSize().height / 2 + BUTTON_GAP);
	this->addChild(errorBG);

	auto highBG = Sprite::create("BestBG.png");
	highBG->setPosition(scoreBG->getBoundingBox().getMinX() - highBG->getContentSize().width / 2 - BUTTON_GAP,
						scoreBG->getBoundingBox().getMaxY() - highBG->getContentSize().height / 2);
	this->addChild(highBG);

	auto menuBtn = MenuItemImage::create("MenuBtn.png", "MenuBtn.png", CC_CALLBACK_0(OverScene::gotoMenuScene, this));
	menuBtn->setPosition(	scoreBG->getBoundingBox().getMaxX() + menuBtn->getContentSize().width / 2 + BUTTON_GAP, 
							scoreBG->getBoundingBox().getMinY() + menuBtn->getContentSize().height / 2);

	auto replayBtn = MenuItemImage::create("ReplayBtn.png", "ReplayBtn.png", CC_CALLBACK_0(OverScene::gotoPlayScene, this));
	replayBtn->setPosition(	scoreBG->getBoundingBox().getMaxX() - replayBtn->getContentSize().width / 2,
							scoreBG->getBoundingBox().getMinY() - replayBtn->getContentSize().height / 2 - BUTTON_GAP);

	auto shareBtn = MenuItemImage::create("ShareBtn.png", "ShareBtn.png");
	shareBtn->setPosition(	replayBtn->getBoundingBox().getMinX() - shareBtn->getContentSize().width / 2 - BUTTON_GAP,
							replayBtn->getBoundingBox().getMaxY() - shareBtn->getContentSize().height / 2);
					
	auto menu = Menu::create(menuBtn, replayBtn, shareBtn, nullptr);
	menu->setPosition(0, 0);
	this->addChild(menu);

	//Score
	auto scoreLabel = LabelTTF::create("0", "fonts/arial.ttf", 120);
	scoreLabel->setPosition(scoreBG->getBoundingBox().getMidX(), scoreBG->getBoundingBox().getMidY());
	scoreLabel->setColor(Color3B::WHITE);
	scoreLabel->setName("score");

	this->addChild(scoreLabel);

	//Error
	auto errorLabel = LabelTTF::create("0", "fonts/arial.ttf", 30);
	errorLabel->setPosition(errorBG->getBoundingBox().getMidX(), errorBG->getBoundingBox().getMidY() - 10);
	errorLabel->setColor(Color3B::WHITE);
	errorLabel->setName("error");

	this->addChild(errorLabel);

	//Score
	int best = UserDefault::getInstance()->getIntegerForKey("HIGHSCORE");
	auto bestLabel = LabelTTF::create(String::createWithFormat("%d", best)->getCString(), "fonts/arial.ttf", 50);
	bestLabel->setPosition(highBG->getBoundingBox().getMidX(), highBG->getBoundingBox().getMidY() - 10);
	bestLabel->setColor(Color3B::WHITE);
	bestLabel->setName("best");

	this->addChild(bestLabel);

	//Update
	this->scheduleUpdate();

	//Eye
	auto eye = Sprite::create("Eye.png");
	eye->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - 100);
	this->addChild(eye);

	//Text
	auto resultText = LabelTTF::create("Wow! You have dog's eyesight.", "fonts/arial.ttf", 20);
	resultText->setPosition(eye->getPositionX(), eye->getBoundingBox().getMinY() - 20);
	resultText->setName("result");
	resultText->setColor(Color3B::BLACK);
	resultText->setVisible(false);

	this->addChild(resultText);

	//RankProgress
	_rankProgress = RankProgress::create();
	_rankProgress->setPosition(origin.x + visibleSize.width / 2, eye->getBoundingBox().getMinY() - 50);

	this->addChild(_rankProgress);


    return true;
}

void OverScene::setScore(int score)
{
	_score = score;
}

void OverScene::setError(int error)
{
	_error = error;
}

void OverScene::gotoPlayScene()
{
	auto playscene = PlayScene::createScene();
	Director::getInstance()->replaceScene(TransitionMoveInL::create(0.25f, playscene));
}

void OverScene::gotoMenuScene()
{
	auto menuscene = MenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionMoveInL::create(0.25f, menuscene));
}

void OverScene::showResult(float dt)
{
	auto label = this->getChildByName("result");
	if (auto lb = dynamic_cast<LabelTTF*>(label))
	{
		std::string text = "Let's play again.";

		if (_score > 0)
		{
			int type = _score / (MAX_SCORE / 6);
			
			switch (type)
			{
			case 0:
			{
				text = "You have bat's eyesight.";
				break;
			}
			case 1:
			{
				text = "You have mole's eyesight.";
				break;
			}
			case 2:
			{
				text = "Ohh! You have dog's eyesight.";
				break;
			}
			case 3:
			{
				text = "Ohh! You have cat's eyesight.";
				break;
			}
			case 4:
			{
				text = "Wow! You have tiger's eyesight.";
				break;
			}
			case 5:
			{
				text = "Wow! You have hawk's eyesight.";
				break;
			}
			default:
			{
				text = "Huh! Are you robot?";
				break;
			}
			}
		}

		lb->setString(text);
		lb->setVisible(true);
	}
}

void OverScene::onEnter()
{
	LayerColor::onEnter();

	auto label = this->getChildByName("score");
	if (auto lb = dynamic_cast<LabelTTF*>(label))
	{
		lb->setString(String::createWithFormat("%d", _score)->getCString());
	}

	auto label2 = this->getChildByName("error");
	if (auto lb = dynamic_cast<LabelTTF*>(label2))
	{
		lb->setString(String::createWithFormat("%d", _error)->getCString());
	}

	//So voi HighScore
	int highScore = UserDefault::getInstance()->getIntegerForKey("HIGHSCORE");

	if (_score > highScore)
	{
		UserDefault::getInstance()->setIntegerForKey("HIGHSCORE", _score);
		UserDefault::getInstance()->setIntegerForKey("ERROR", _error);
	}

	//
	if (_score > MAX_SCORE)
	{
		_rankProgress->runToPercent(1.0f, 100);
	}
	else
	{
		_rankProgress->runToPercent(1.0f, ((float)_score / MAX_SCORE) * 100);
	}

	scheduleOnce(schedule_selector(OverScene::showResult), 1.0f);
}

void OverScene::update(float dt)
{
	
}