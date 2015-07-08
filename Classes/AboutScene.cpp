#include "AboutScene.h"
#include "MenuScene.h"
#include "CallCSharp.h"

Scene* AboutScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = AboutScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool AboutScene::init()
{
    //////////////////////////////
    // 1. super init first
	if (!LayerColor::initWithColor(Color4B::WHITE))
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    
	auto logo = Sprite::create("logo.png");
	logo->setPosition(origin.x + visibleSize.width / 2, origin.y + (visibleSize.height / 4) * 3);
	this->addChild(logo);

	auto nameLabel = LabelTTF::create("The Best Eyes - 1.0.0.3", "fonts/arial.ttf", 30);
	nameLabel->setColor(Color3B::BLACK);
	nameLabel->setPosition(origin.x + visibleSize.width / 2, logo->getBoundingBox().getMinY() - nameLabel->getContentSize().height / 2 - 50);
	this->addChild(nameLabel);

	//
	auto aboutLabel = LabelTTF::create("Author: Luu The Vinh\nWebsite: 14gamez.com\nLike us on Facebook", "fonts/arial.ttf", 21);
	aboutLabel->setColor(Color3B::BLACK);
	aboutLabel->setPosition(origin.x + visibleSize.width / 2, nameLabel->getBoundingBox().getMinY() - aboutLabel->getContentSize().height / 2 - 80);
	this->addChild(aboutLabel);

	auto likeBtn = MenuItemImage::create("LikeBtn.png", "LikeBtn.png", CC_CALLBACK_0(AboutScene::likeFB, this));
	likeBtn->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 3);
	
	auto backBtn = MenuItemImage::create("BackBtn.png", "BackBtn.png", CC_CALLBACK_0(AboutScene::gotoMenuScene, this));
	backBtn->setPosition(origin.x + visibleSize.width / 2, likeBtn->getBoundingBox().getMinY() - backBtn->getContentSize().height / 2);

	auto menu = Menu::create(likeBtn, backBtn, nullptr);
	menu->setPosition(0, 0);
	this->addChild(menu);

	//Listener
	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyReleased = CC_CALLBACK_2(AboutScene::onKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);

    return true;
}

void AboutScene::gotoMenuScene()
{
	auto menuscene = MenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionMoveInL::create(0.25f, menuscene));
}

void AboutScene::likeFB()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	BroswerEventHelper::likePage();
#endif
}

void AboutScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* unused_event)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
	{
		AboutScene::gotoMenuScene();
	}
#endif
}