#include "AchievementScene.h"
#include "Definitions.h"
#include "MenuScene.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
#include "CallCSharp.h"
#endif

Scene* AchievementScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = AchievementScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool AchievementScene::init()
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

	auto eye = Sprite::create("Eye.png");
	eye->setPosition(origin.x + visibleSize.width / 2, origin.y + (visibleSize.height / 5) * 4);
	this->addChild(eye);

	//RankProgress
	_rankProgress = RankProgress::create();
	_rankProgress->setPosition(origin.x + visibleSize.width / 2, eye->getBoundingBox().getMinY() - 50);

	this->addChild(_rankProgress);

	//Text
	auto resultText = LabelTTF::create("Wow! You have dog's eyesight.", "fonts/arial.ttf", 20);
	resultText->setPosition(eye->getPositionX(), eye->getBoundingBox().getMinY() - 20);
	resultText->setName("result");
	resultText->setColor(Color3B::BLACK);
	resultText->setVisible(false);

	this->addChild(resultText);

	//BG
	auto scoreBG = Sprite::create("BestBG_150x150.png");
	scoreBG->setPosition(origin.x + visibleSize.width / 2, origin.y + (visibleSize.height / 5) * 2);
	this->addChild(scoreBG);

	auto errorBG = Sprite::create("ErrorBG.png");
	errorBG->setPosition(scoreBG->getBoundingBox().getMinX() - errorBG->getContentSize().width / 2 - BUTTON_GAP,
						 scoreBG->getBoundingBox().getMaxY() - errorBG->getContentSize().height / 2);
	this->addChild(errorBG);

	//Share
	auto shareBtn = MenuItemImage::create("ShareBtn_96x96.png", "ShareBtn_96x96.png", CC_CALLBACK_0(AchievementScene::shareScore, this));
	shareBtn->setPosition(	scoreBG->getBoundingBox().getMaxX() + shareBtn->getContentSize().width / 2 + BUTTON_GAP,
							scoreBG->getBoundingBox().getMinY() + shareBtn->getContentSize().height / 2);

	auto backBtn = MenuItemImage::create("BackBtn.png", "BackBtn.png", CC_CALLBACK_0(AchievementScene::gotoMenuScene, this));
	backBtn->setPosition(	scoreBG->getBoundingBox().getMaxX() - backBtn->getContentSize().width / 2,
							scoreBG->getBoundingBox().getMinY() - backBtn->getContentSize().height / 2 - BUTTON_GAP);
	auto menu = Menu::create(shareBtn, backBtn, nullptr);
	menu->setPosition(0, 0);
	this->addChild(menu);

	//Error
	int error = UserDefault::getInstance()->getIntegerForKey("ERROR");
	auto errorLabel = LabelTTF::create(String::createWithFormat("%d", error)->getCString(), "fonts/arial.ttf", 30);
	errorLabel->setPosition(errorBG->getBoundingBox().getMidX(), errorBG->getBoundingBox().getMidY() - 10);
	errorLabel->setColor(Color3B::WHITE);
	errorLabel->setName("error");

	this->addChild(errorLabel);

	//Score
	_bestScore = UserDefault::getInstance()->getIntegerForKey("HIGHSCORE");
	auto bestLabel = LabelTTF::create(String::createWithFormat("%d", _bestScore)->getCString(), "fonts/arial.ttf", 80);
	bestLabel->setPosition(scoreBG->getBoundingBox().getMidX(), scoreBG->getBoundingBox().getMidY());
	bestLabel->setColor(Color3B::WHITE);
	bestLabel->setName("best");

	this->addChild(bestLabel);

	//Listener
	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyReleased = CC_CALLBACK_2(AchievementScene::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);

    return true;
}

void AchievementScene::onEnter()
{
	LayerColor::onEnter();

	//
	if (_bestScore > MAX_SCORE)
	{
		_rankProgress->runToPercent(1.0f, 100);
	}
	else
	{
		_rankProgress->runToPercent(1.0f, ((float)_bestScore / MAX_SCORE) * 100);
	}

	this->scheduleOnce(schedule_selector(AchievementScene::showResult), 1.0f);
}

void AchievementScene::showResult(float dt)
{
	auto label = this->getChildByName("result");
	if (auto lb = dynamic_cast<LabelTTF*>(label))
	{
		std::string text = "Let's play!";

		if (_bestScore > 0)
		{
			int type = _bestScore / (MAX_SCORE / 6);

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
				text = "Great! You have dog's eyesight.";
				break;
			}
			case 3:
			{
				text = "Great! You have cat's eyesight.";
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
				text = "OMG! Are you robot?";
				break;
			}
			}
		}

		lb->setString(text);
		lb->setVisible(true);
	}
}

void AchievementScene::gotoMenuScene()
{
	auto menu = MenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionMoveInL::create(0.25f, menu));
}

void AchievementScene::afterCaptured(bool succeed, const std::string& outputFile)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	if (succeed)
	{
		std::wstring wstr;
		wstr.assign(outputFile.begin(), outputFile.end());

		BroswerEventHelper::sharePhoto(ref new Platform::String(wstr.c_str()));
	}
	else
	{
		log("Capture screen failed.");
	}
#endif
}

void AchievementScene::shareScore()
{
	//utils::captureScreen(CC_CALLBACK_2(AchievementScene::afterCaptured, this), "screenShot_BestScore.png");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	std::string str = String::createWithFormat("I got %d scores in #TheBestEyes games.", _bestScore)->getCString();

	std::wstring wstr;
	wstr.assign(str.begin(), str.end());

	BroswerEventHelper::shareGame(ref new Platform::String(wstr.c_str()));
#endif
}

void AchievementScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* unused_event)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
	{
		AchievementScene::gotoMenuScene();
	}
#endif
}