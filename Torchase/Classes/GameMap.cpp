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

#include "GameMap.h"
#include "Definitions.h"
#include "GameScene.h"

USING_NS_CC;


GameMap::GameMap(cocos2d::Scene *scene, cocos2d::Sprite *playerScene)
{
	_player = playerScene;
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	_tileMap = new TMXTiledMap();
	_tileMap->initWithTMXFile("Maptest/gamemap.tmx");
	//_background = _tileMap->getLayer("background");
	_tileMap->setScale(5.0f);
	//_tileMap->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	scene->addChild(_tileMap);

	TMXObjectGroup *objectGroup = _tileMap->getObjectGroup("Player");

	if (objectGroup == NULL) {
		CCLOG("tile map has no objects object layer");
		return;
	}
	else
	{
		auto spawnPoint = objectGroup->getObject("SpawnPoint");
		int x = spawnPoint["x"].asInt();
		int y = spawnPoint["y"].asInt();
		CCLOG("okeeeeeeee");
		_player->setPosition(Vec2(x, y));
	}
	

}
void GameMap::setViewPointCenter(Point position) {

	/*Size winSize = Director::getInstance()->getWinSize();
	//CCLOG("% d %d",position.x,position.y);
	int x = MAX(position.x, winSize.width / 2);
	int y = MAX(position.y, winSize.height / 2);
	x = MIN(x, (_tileMap->getMapSize().width * this->_tileMap->getTileSize().width) - winSize.width / 2);
	y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height) - winSize.height / 2);
	Point actualPosition = Point(x, y);

	Point centerOfView = Point(winSize.width / 2, winSize.height / 2);
	Point viewPoint = centerOfView - actualPosition;
	this->setPosition(viewPoint);*/
}

