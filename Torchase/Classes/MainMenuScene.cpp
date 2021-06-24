/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "MainMenuScene.h"
#include "Definitions.h"
#include "GameScene.h"

USING_NS_CC;

Scene* MainMenuScene::createScene()
{
    //return MainMenuScene::create();
	Scene *scene = Scene::create();

	// 'layer' is an autorelease object
	MainMenuScene *layer = MainMenuScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

<<<<<<< HEAD
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
=======
	_tileMap = new TMXTiledMap();
	_tileMap->initWithTMXFile("Maptest/TileMap.tmx");
	_background = _tileMap->getLayer("Background");

	this->addChild(_tileMap);

	TMXObjectGroup *objectGroup = _tileMap->getObjectGroup("Object");

	if (objectGroup == NULL) {
		CCLOG("tile map has no objects object layer");
		return false;
	}

	auto spawnPoint = objectGroup->getObject("SpawnPoint");

	int x = spawnPoint["x"].asInt(); 
	int y = spawnPoint["y"].asInt();

	_player = new Sprite();
	_player->initWithFile("Maptest/Player.png");
	_player->setPosition(Point(x, y));
	//CCLOG("%d %d", x, y);
	//CCLOG("%f %f", _player->getPosition().x, _player->getPosition().y);
	this->addChild(_player);
	this->setViewPointCenter(_player->getPosition());

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [&](Touch *touch, Event *unused_event)->bool {return true; };
	listener->onTouchEnded = CC_CALLBACK_2(MainMenuScene::onTouchEnded, this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
>>>>>>> 8e13b419bd9bf89e1b1643c22614168c2e8a5dfc
    return true;
}


<<<<<<< HEAD
=======
void MainMenuScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

void MainMenuScene::setViewPointCenter(Point position) {

	Size winSize = Director::getInstance()->getWinSize();
	//CCLOG("% d %d",position.x,position.y);
	int x = MAX(position.x, winSize.width / 2);
	int y = MAX(position.y, winSize.height / 2);
	x = MIN(x, (_tileMap->getMapSize().width * this->_tileMap->getTileSize().width) - winSize.width / 2);
	y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height) - winSize.height / 2);
	Point actualPosition = Point(x, y);

	Point centerOfView = Point(winSize.width / 2, winSize.height / 2);
	Point viewPoint = centerOfView - actualPosition;
	this->setPosition(viewPoint);
}

void MainMenuScene::onTouchEnded(Touch *touch, Event *unused_event)
{
	auto actionTo1 = RotateTo::create(0, 0, 180);
	auto actionTo2 = RotateTo::create(0, 0, 0);
	auto touchLocation = touch->getLocation();

	touchLocation = this->convertToNodeSpace(touchLocation);

	auto playerPos = _player->getPosition();
	auto diff = touchLocation - playerPos;
	if (abs(diff.x) > abs(diff.y)) {
		if (diff.x > 0) {
			playerPos.x += _tileMap->getTileSize().width / 2;
			_player->runAction(actionTo2);
		}
		else {
			playerPos.x -= _tileMap->getTileSize().width / 2;
			_player->runAction(actionTo1);
		}
	}
	else {
		if (diff.y > 0) {
			playerPos.y += _tileMap->getTileSize().height / 2;
		}
		else {
			playerPos.y -= _tileMap->getTileSize().height / 2;
		}
	}

	if (playerPos.x <= (_tileMap->getMapSize().width * _tileMap->getMapSize().width) &&
		playerPos.y <= (_tileMap->getMapSize().height * _tileMap->getMapSize().height) &&
		playerPos.y >= 0 &&
		playerPos.x >= 0)
	{
		this->setPlayerPosition(playerPos);

	}

	this->setViewPointCenter(_player->getPosition());
}

void MainMenuScene::setPlayerPosition(Point position)
{
	_player->setPosition(position);
}
>>>>>>> 8e13b419bd9bf89e1b1643c22614168c2e8a5dfc
