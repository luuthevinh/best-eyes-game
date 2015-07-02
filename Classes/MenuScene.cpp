#include "MenuScene.h"
#include "PlayScene.h"
#include "AchievementScene.h"
#include "AboutScene.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
#include "CallCSharp.h"
#endif

Scene* MenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MenuScene::init()
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

	//Background
	auto background = Sprite::create("Background.png");
	background->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	this->addChild(background);

	auto playBtn = MenuItemImage::create("PlayBtn.png", "PlayBtn.png", CC_CALLBACK_0(MenuScene::gotoPlayScene, this));
	playBtn->setPosition(origin.x + visibleSize.width / 2, origin.y + (visibleSize.height / 3) + 10);

	auto achievBtn = MenuItemImage::create("AchievementBtn.png", "AchievementBtn.png", CC_CALLBACK_0(MenuScene::gotoAchievementScene, this));
	achievBtn->setPosition(	playBtn->getPositionX() + playBtn->getContentSize().width / 2 + achievBtn->getContentSize().width / 2 + BUTTON_GAP, 
							playBtn->getPositionY() + playBtn->getContentSize().height / 2 - achievBtn->getContentSize().height / 2);

	auto rateBtn = MenuItemImage::create("RateBtn.png", "RateBtn.png", CC_CALLBACK_0(MenuScene::rateGame, this));
	rateBtn->setPosition( playBtn->getPositionX() + playBtn->getContentSize().width / 2 - rateBtn->getContentSize().width / 2, 
						  playBtn->getPositionY() + playBtn->getContentSize().height / 2 + rateBtn->getContentSize().height / 2 + BUTTON_GAP);

	auto optionBtn = MenuItemImage::create("RemoveAdsBtn.png", "RemoveAdsBtn.png", CC_CALLBACK_0(MenuScene::removeAds, this));
	optionBtn->setPosition(	playBtn->getBoundingBox().getMinX() + optionBtn->getContentSize().width / 2,
							playBtn->getBoundingBox().getMinY() - optionBtn->getContentSize().height / 2 - BUTTON_GAP);

	auto exitBtn = MenuItemImage::create("ExitBtn.png", "ExitBtn.png", CC_CALLBACK_0(MenuScene::exitGame, this));
	exitBtn->setPosition( optionBtn->getBoundingBox().getMaxX() + exitBtn->getContentSize().width / 2 + BUTTON_GAP, 
						  optionBtn->getBoundingBox().getMaxY() - exitBtn->getContentSize().height / 2);

	auto aboutBtn = MenuItemImage::create("AboutBtn.png", "AboutBtn.png", CC_CALLBACK_0(MenuScene::gotoAboutScene, this));
	aboutBtn->setPosition(	playBtn->getBoundingBox().getMinX() - aboutBtn->getContentSize().width / 2 - BUTTON_GAP, 
							playBtn->getBoundingBox().getMinY() + aboutBtn->getContentSize().height / 2);

	auto menu = Menu::create(playBtn, achievBtn, rateBtn, optionBtn, exitBtn, aboutBtn, nullptr);
	menu->setPosition(0, 0);
	this->addChild(menu);

	//Listener
	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyReleased = CC_CALLBACK_2(MenuScene::onKeyReleased, this);
	
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);

    return true;
}

void MenuScene::onEnter()
{
	LayerColor::onEnter();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	if (!BroswerEventHelper::isBuyRemoveAds())
	{
		BroswerEventHelper::showAds(true);
	}
#endif
}

void MenuScene::gotoPlayScene()
{
	auto playScene = PlayScene::createScene();
	Director::getInstance()->replaceScene(playScene);
}

void MenuScene::gotoAchievementScene()
{
	auto achiev = AchievementScene::createScene();
	Director::getInstance()->replaceScene(TransitionMoveInR::create(0.25f, achiev));
}

void MenuScene::exitGame()
{
	Director::getInstance()->end();
	exit(0);
}

void MenuScene::gotoAboutScene()
{
	auto about = AboutScene::createScene();
	Director::getInstance()->replaceScene(TransitionMoveInT::create(0.25f, about));
}

void MenuScene::removeAds()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	if (!BroswerEventHelper::isBuyRemoveAds())
		BroswerEventHelper::removeAds();
#endif
}

void MenuScene::rateGame()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	BroswerEventHelper::rateGame();
#endif
}

void MenuScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* unused_event)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
	{
		MenuScene::exitGame();
	}
#endif
}