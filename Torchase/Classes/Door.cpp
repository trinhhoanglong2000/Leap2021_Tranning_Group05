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

#include "Door.h"
#include "Definitions.h"

USING_NS_CC;
Door::Door() {

	
}
void Door::setmeta(cocos2d::TMXLayer *objectGroupDoorGame, cocos2d::TMXTiledMap *_tileMapGame, int numberKeyGame)
{
	
	_meta = objectGroupDoorGame;
	_tileMap = _tileMapGame;
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	numberkey = numberKeyGame;
	for (int i = 0; i < _tileMap->getMapSize().width; i++)
	{
		for (int j = 0; j < _tileMap->getMapSize().height; j++) 
		{
			auto tileSprite = _meta->getTileAt(Vec2(i, j));
			if (tileSprite)
			{
				auto DoorBody = PhysicsBody::createBox(tileSprite->getContentSize()*MAP_SCALE);
				DoorBody->setCollisionBitmask(DOOR_COLISION_BITMASK);
				DoorBody->setCategoryBitmask(DOOR_CATEGORY_BITMASK);
				DoorBody->setContactTestBitmask(DOOR_COLISION_BITMASK);
				DoorBody->setDynamic(false);
				float x = _tileMap->getTileSize().width * (i + 0.5) * MAP_SCALE;
				float y = _tileMap->getTileSize().height * (_tileMap->getMapSize().height - 0.5 - j)*MAP_SCALE;
				auto node = Node::create();
				node = Node::create();
				node->setPosition(Vec2(x, y));
				node->setPhysicsBody(DoorBody);
				this->addChild(node, 40);
			}
		}
	}
}
void Door::reduceNumberKey()
{
	numberkey--;
}