#include "OverScene.h"
#include "Definitions.h"
#include "PlayScene.h"

USING_NS_CC;

Scene* OverScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = OverScene::create();

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
	scoreBG->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	this->addChild(scoreBG);

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

    return true;
}

void OverScene::gotoPlayScene()
{
	auto playscene = PlayScene::createScene();
	Director::getInstance()->replaceScene(TransitionMoveInL::create(0.25f, playscene));
}

void OverScene::gotoMenuScene()
{
	auto menuscene = PlayScene::createScene();
	Director::getInstance()->replaceScene(TransitionMoveInL::create(0.25f, menuscene));
}