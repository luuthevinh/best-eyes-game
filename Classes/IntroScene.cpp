#include "IntroScene.h"
#include "MenuScene.h"

USING_NS_CC;

Scene* IntroScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = IntroScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool IntroScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////

	auto logo = Sprite::create("logo.png");
	logo->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	this->addChild(logo);

	this->scheduleOnce(schedule_selector(IntroScene::gotoMenuScene), 2.0f);

    return true;
}

void IntroScene::gotoMenuScene(float dt)
{
	auto menu = MenuScene::createScene();
	Director::getInstance()->replaceScene(menu);
}