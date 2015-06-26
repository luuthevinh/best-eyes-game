#include "MenuScene.h"
#include "PlayScene.h"
#include "AchievementScene.h"

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
	auto playBtn = MenuItemImage::create("PlayBtn.png", "PlayBtn.png", CC_CALLBACK_0(MenuScene::gotoPlayScene, this));
	playBtn->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);

	auto achievBtn = MenuItemImage::create("AchievementBtn.png", "AchievementBtn.png", CC_CALLBACK_0(MenuScene::gotoAchievementScene, this));
	achievBtn->setPosition(	playBtn->getPositionX() + playBtn->getContentSize().width / 2 + achievBtn->getContentSize().width / 2 + BUTTON_GAP, 
							playBtn->getPositionY() + playBtn->getContentSize().height / 2 - achievBtn->getContentSize().height / 2);

	auto rateBtn = MenuItemImage::create("RateBtn.png", "RateBtn.png");
	rateBtn->setPosition( playBtn->getPositionX() + playBtn->getContentSize().width / 2 - rateBtn->getContentSize().width / 2, 
						  playBtn->getPositionY() + playBtn->getContentSize().height / 2 + rateBtn->getContentSize().height / 2 + BUTTON_GAP);

	auto optionBtn = MenuItemImage::create("RemoveAdsBtn.png", "RemoveAdsBtn.png");
	optionBtn->setPosition(	playBtn->getBoundingBox().getMinX() + optionBtn->getContentSize().width / 2,
							playBtn->getBoundingBox().getMinY() - optionBtn->getContentSize().height / 2 - BUTTON_GAP);

	auto exitBtn = MenuItemImage::create("ExitBtn.png", "ExitBtn.png", CC_CALLBACK_0(MenuScene::exitGame, this));
	exitBtn->setPosition( optionBtn->getBoundingBox().getMaxX() + exitBtn->getContentSize().width / 2 + BUTTON_GAP, 
						  optionBtn->getBoundingBox().getMaxY() - exitBtn->getContentSize().height / 2);

	auto aboutBtn = MenuItemImage::create("AboutBtn.png", "AboutBtn.png");
	aboutBtn->setPosition(	playBtn->getBoundingBox().getMinX() - aboutBtn->getContentSize().width / 2 - BUTTON_GAP, 
							playBtn->getBoundingBox().getMinY() + aboutBtn->getContentSize().height / 2);

	auto menu = Menu::create(playBtn, achievBtn, rateBtn, optionBtn, exitBtn, aboutBtn, nullptr);
	menu->setPosition(0, 0);
	this->addChild(menu);

    return true;
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
	exit(0);
}