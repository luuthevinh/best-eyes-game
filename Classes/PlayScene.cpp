#include "PlayScene.h"
#include "Definitions.h"
#include "OverScene.h"
#include "MenuScene.h"

USING_NS_CC;

Scene* PlayScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = PlayScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool PlayScene::init()
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

	//Touch
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(PlayScene::onTouchBegan, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	//Update
	this->scheduleUpdate();

	//Init
	_score = 0;
	_error = 0;
	_timer = 0.0f;
	_totalTime = 10.0f;

	_gridCenter = Vec2(visibleSize.width / 2, (visibleSize.height / 5) * 2);

	createLevel();

	//Progress bar
	auto progressBG = Sprite::create("TimerBG.png");
	progressBG->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - progressBG->getContentSize().height / 2));
	this->addChild(progressBG);

	_progress = ProgressTimer::create(Sprite::create("TimerBG_01.png"));
	_progress->setType(ProgressTimerType::BAR);
	_progress->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height -  _progress->getContentSize().height / 2));
	_progress->setBarChangeRate(Vec2(1, 0));
	_progress->setPercentage(0);
	_progress->setMidpoint(Vec2(0.0, 0.0f));
	this->addChild(_progress);

	//Score
	auto scoreLabel = LabelTTF::create("0", "fonts/Roboto-Bold.ttf", 50);
	scoreLabel->setPosition(origin.x + 20, origin.y + visibleSize.height - 150);
	scoreLabel->setAnchorPoint(Vec2(0, 0.5f));
	scoreLabel->setColor(Color3B::BLACK);
	scoreLabel->setName("score");
	scoreLabel->setHorizontalAlignment(TextHAlignment::LEFT);

	this->addChild(scoreLabel);

	//TEXT
	auto scoreText = LabelTTF::create("score", "fonts/arial.ttf", 20);
	scoreText->setPosition(scoreLabel->getBoundingBox().getMidX(), scoreLabel->getBoundingBox().getMinY() - scoreText->getContentSize().height / 2 - 2);
	scoreText->setColor(Color3B::BLACK);

	this->addChild(scoreText);

	//Error
	auto errorLabel = LabelTTF::create("0", "fonts/Roboto-Bold.ttf", 50);
	errorLabel->setPosition(origin.x + visibleSize.width - 20, origin.y + visibleSize.height - 150);
	errorLabel->setAnchorPoint(Vec2(1.0f, 0.5f));
	errorLabel->setColor(Color3B::RED);
	errorLabel->setName("error");
	errorLabel->setHorizontalAlignment(TextHAlignment::RIGHT);

	this->addChild(errorLabel);

	//Text
	auto errorText = LabelTTF::create("error", "fonts/arial.ttf", 20);
	errorText->setPosition(errorLabel->getBoundingBox().getMidX(), errorLabel->getBoundingBox().getMinY() - errorText->getContentSize().height / 2 - 2);
	errorText->setColor(Color3B::BLACK);
	this->addChild(errorText);

	//Menu
	auto menuBtn = MenuItemImage::create("MenuBtn_48x43.png", "MenuBtn_48x43.png", CC_CALLBACK_0(PlayScene::gotoMenuScene, this));
	menuBtn->setPosition(	origin.x + menuBtn->getContentSize().width,
							origin.y + menuBtn->getContentSize().height);

	auto menu = Menu::create(menuBtn, nullptr);
	menu->setPosition(0, 0);
	this->addChild(menu);

    return true;
}

void PlayScene::drawSquare(int width, Vec2 position, float opacity)
{
	DrawNode* drawnode = DrawNode::create();
	Vec2 rectangle[4];
	int wid = width / 2;

	rectangle[0] = Vec2(-wid, -wid);
	rectangle[1] = Vec2(wid, -wid);
	rectangle[2] = Vec2(wid, wid);
	rectangle[3] = Vec2(-wid, wid);

	this->addChild(drawnode);

	auto color = Color4F(_colorLevel.r, _colorLevel.g, _colorLevel.b, opacity);
	
	drawnode->drawPolygon(rectangle, 4, color, 0, color);
	drawnode->setPosition(position.x + _squareWidth / 2, position.y - _squareWidth / 2);
	drawnode->setName("square");

}

void PlayScene::drawGrid(int row, int col)
{
	for (int r = 0; r < row; r++)
	{
		for (int c = 0; c < col; c++)
		{
			if (r == _scoreIndex.x && c == _scoreIndex.y)
			{
				drawSquare(_squareWidth, Vec2(_gridTopLeft.x + c * (_squareWidth + BUTTON_GAP), _gridTopLeft.y - r * (_squareWidth + BUTTON_GAP)), _opacityScoreSquare);
				continue;
			}

			drawSquare(_squareWidth, Vec2(_gridTopLeft.x + c * (_squareWidth + BUTTON_GAP), _gridTopLeft.y - r * (_squareWidth + BUTTON_GAP)));
		}
	}
}

void PlayScene::randomColor()
{
	_colorLevel = Color4F(random(0.0f, 1.0f), random(0.0f, 1.0f), random(0.0f, 1.0f), 1);

	_scoreIndex = Vec2(random(0, _gridRow - 1), random(0, _gridColumn - 1));
}

Vec2 PlayScene::calculateTopLeft()
{
	//chieu dai grid
	float width = _gridColumn * _squareWidth + BUTTON_GAP * (_gridColumn - 1);
	//chieu rong grid
	float height = _gridRow * _squareWidth + BUTTON_GAP * (_gridRow - 1);

	return Vec2(_gridCenter.x - width / 2, _gridCenter.y + height / 2);
}

Vec2 PlayScene::getTouchIndex(Vec2 touchlocation)
{
	//chieu dai grid
	float width = _gridColumn * _squareWidth + BUTTON_GAP * (_gridColumn - 1);
	//chieu rong grid
	float height = _gridRow * _squareWidth + BUTTON_GAP * (_gridRow - 1);

	if (touchlocation.x > _gridTopLeft.x && touchlocation.x  < (_gridTopLeft.x + width) &&
		touchlocation.y < _gridTopLeft.y && touchlocation.y >(_gridTopLeft.y - height))
	{
		//Tọa độ trong grid = khoảng cách touch hiện tại đến gốc top left grid chia cho _squareWidth lấy phần nguyên
		int row = (_gridTopLeft.y - touchlocation.y) / (_squareWidth + BUTTON_GAP);
		//Tuong tu
		int col = (touchlocation.x - _gridTopLeft.x) / (_squareWidth + BUTTON_GAP);

		//Neu nam trong row/column grid thi lay
		if (row < _gridRow && row >= 0 && col < _gridColumn && col >= 0)
		{
			return Vec2(row, col);
		}
	}

	return Vec2(-1, -1);
}

void PlayScene::checkScore()
{
	if (_touchIndex == Vec2(-1, -1))
		return;

	if (_touchIndex == _scoreIndex)
	{
		_score++;

		auto label = this->getChildByName("score");
		//if (auto lb = dynamic_cast<LabelTTF*>(label))
		//if (typeid(label) == typeid(LabelTTF*))
		{
			//lb->setString(String::createWithFormat("%d", _score)->getCString());
			static_cast<LabelTTF*>(label)->setString(String::createWithFormat("%d", _score)->getCString());
		}

		//Xoa grid
		auto squares = this->getChildren();
		for (Vector<Node*>::iterator it = squares.begin(); it != squares.end(); it++)
		{
			//if (auto dn = dynamic_cast<DrawNode*>(*it))
			if ((*it)->getName() == "square")
			{
				(*it)->removeFromParent();
			}
		}

		//Khoi tao moi
		createLevel();
	}
	else
	{
		_error++;

		auto label = this->getChildByName("error");
		if (auto lb = dynamic_cast<LabelTTF*>(label))
		{
			lb->setString(String::createWithFormat("%d", _error)->getCString());
		}

		_timer += 5;
	}
}

void PlayScene::createLevel()
{
	_timer = 0;

	switch (_score)
	{
		case 0:
		{
			_gridColumn = 2;
			_gridRow = 2;
			_squareWidth = (Director::getInstance()->getVisibleSize().width - (BUTTON_GAP * (_gridColumn + 1))) / _gridColumn;
			_opacityScoreSquare = 0.5f;
			break;
		}
		case 1:
		{
			_gridColumn = 3;
			_gridRow = 3;
			_squareWidth = (Director::getInstance()->getVisibleSize().width - (BUTTON_GAP * (_gridColumn + 1))) / _gridColumn;
			_opacityScoreSquare = 0.55f;
			break;
		}
		case 3:
		{
			_gridColumn = 4;
			_gridRow = 4;
			_squareWidth = (Director::getInstance()->getVisibleSize().width - (BUTTON_GAP * (_gridColumn + 1))) / _gridColumn;
			_opacityScoreSquare = 0.6f;
			break;
		}
		case 6:
		{
			_gridColumn = 5;
			_gridRow = 5;
			_squareWidth = (Director::getInstance()->getVisibleSize().width - (BUTTON_GAP * (_gridColumn + 1))) / _gridColumn;
			_opacityScoreSquare = 0.65f;
			break;
		}
		case 9:
		{
			_gridColumn = 7;
			_gridRow = 7;
			_squareWidth = (Director::getInstance()->getVisibleSize().width - (BUTTON_GAP * (_gridColumn + 1))) / _gridColumn;
			_opacityScoreSquare = 0.7f;
			break;
		}

		case 13:
		{
			_opacityScoreSquare = 0.8f;
			break;
		}

		case 18:
		{
			_opacityScoreSquare = 0.9f;
			break;
		}
	}

	_gridTopLeft = calculateTopLeft();

	randomColor();

	drawGrid(_gridRow, _gridColumn);

	
}

bool PlayScene::onTouchBegan(Touch* touch, Event* event)
{
	_touchIndex = getTouchIndex(touch->getLocation());
	checkScore();

	return true;
}

void PlayScene::update(float dt)
{
	_timer += dt;

	_progress->setPercentage(100 - ((_timer / _totalTime) * 100.0f));

	if (_timer > _totalTime)
	{
		//log("THUA THUA THUA...");
		this->pause();
		auto overscene = OverScene::createScene(_score, _error);
		Director::getInstance()->replaceScene(overscene);
	}
}

void PlayScene::gotoMenuScene()
{
	auto menu = MenuScene::createScene();
	Director::getInstance()->replaceScene(menu);
}