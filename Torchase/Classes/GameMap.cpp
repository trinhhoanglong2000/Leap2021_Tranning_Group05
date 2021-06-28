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
#include "Minions.h"
USING_NS_CC;


GameMap::GameMap(cocos2d::Scene *scene, Player *playerScene)
{
	_player = playerScene;
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	_tileMap = new TMXTiledMap();
	_tileMap->initWithTMXFile("Maptest/gamemap.tmx");
	

	_tileMap->setScale(MAP_SCALE);
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
		_player->speed = _tileMap->getTileSize().width*MAP_SCALE;
		_player->setPosition(Vec2(x, y)*MAP_SCALE);
	}

	TMXObjectGroup *objectGroupminions = _tileMap->getObjectGroup("minions");
	if (objectGroupminions == NULL) {
		
	}
	else
	{
		auto spawnPointminions = objectGroupminions->getObjects();
		for each (Value objMinion in spawnPointminions)
		{
			int x = objMinion.asValueMap()["x"].asInt();
			int y = objMinion.asValueMap()["y"].asInt();
			Minions *minion = new Minions(playerScene);
			minion->setPosition(Vec2(x, y)*MAP_SCALE);
			minion->speed = _tileMap->getTileSize().width*MAP_SCALE;
			scene->addChild(minion, 30);
		}
	}
	
	_meta = _tileMap->getLayer("meta");

	for (int i = 0; i <16; i++)
	{
		for (int j = 0; j <14; j++) // tile map size 40X40, starting from 0, this loop traverses all tiles
		{
			auto tileSprite = _meta->getTileAt(Vec2(i,j));
			if (tileSprite)
			{
				auto PlayerBody = PhysicsBody::createBox(tileSprite->getContentSize()*MAP_SCALE);

				PlayerBody->setCollisionBitmask(MAP_COLISION_BITMASK);
				PlayerBody->setContactTestBitmask(true);
				PlayerBody->setDynamic(false);
				auto node = Node::create();
				float x =  _tileMap->getTileSize().width * (i+0.5) * MAP_SCALE;
				float y = _tileMap->getTileSize().height * (13.5-j)*MAP_SCALE;
				node->setPosition(Vec2(x, y));
				node->setPhysicsBody(PlayerBody);
				scene->addChild(node, 40);
			}
		}
	}
	_meta->setVisible(false);
}
cocos2d::Size GameMap::returnSizeMap()
{
	return _tileMap->getMapSize()*MAP_SCALE;
}