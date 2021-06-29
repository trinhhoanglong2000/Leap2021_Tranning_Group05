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

#include "GameScene.h"
#include "Definitions.h"
#include "AudioEngine.h"
USING_NS_CC;
Scene* GameScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	//scene->getPhysicsWorld()->setGravity(Vec2(0, 0));

	auto Scene_layer = GameScene::create();
	Scene_layer->SetPhysicWorld(scene->getPhysicsWorld());
	Scene_layer->removeChild(Scene_layer->getDefaultCamera());

	scene->addChild(Scene_layer);

	return scene;
	//return GameScene::create();
}

bool GameScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

	player = new Player();	
	this->addChild(player,30);

	this->runAction(Follow::create(player)); // add action camera follow player	

	gameMap = new GameMap(this,player, AllMinions); // add gamemap
	Size size = gameMap->returnSizeMap();
	player->setBlackVisionBG(size);
	width = MAX(size.width+visibleSize.width, size.height+visibleSize.height);
	height = width;

	background_off = DrawNode::create();
	Vec2 vertices[] =
	{
		Vec2(0,height),
		Vec2(width,height),
		Vec2(width,0),
		Vec2(0,0)
	};
	background_off->setContentSize(Size(width, height));
	background_off->drawPolygon(vertices, 4, Color4F(Color3B::BLACK, 1), thickness, Color4F(Color3B::BLACK, 1));
	background_off->setAnchorPoint(Vec2(0.5f, 0.5f));
	background_off->setPosition(+this->getBoundingBox().size.width / 2, +this->getBoundingBox().size.height / 2 + (height - thickness * 2) / 4);
	
	this->addChild(background_off, 20);
	background_off->setVisible(false);

	canvas = new Canvas(player, background_off);
	canvas->setPosition(Vec2(0, 0));
	player->addChild(canvas, 50);
	

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
	playerdie = false;

	return true;
}
bool GameScene::onContactBegin(cocos2d::PhysicsContact &contact)
{
	PhysicsBody *a = contact.getShapeA()->getBody();
	PhysicsBody *b = contact.getShapeB()->getBody();
	
	if ((a->getCollisionBitmask() & b->getCategoryBitmask() != 0) || (b->getCollisionBitmask() & a->getCategoryBitmask() != 0))
	{
		CCLOG("Overlap");
		if (a->getCollisionBitmask() == ITEM_COLISION_BITMASK)
		{
			canvas->plusenergy(5);
			this->removeChild(a->getOwner());
		}
		else if (b->getCollisionBitmask() == ITEM_COLISION_BITMASK)
		{
			canvas->plusenergy(5);
			this->removeChild(b->getOwner());
		}

		//Wall detect collision
		if (a->getCollisionBitmask() == WALL_COLISION_BITMASK)
		{
			if(b->getCollisionBitmask() == PLAYER_COLISION_BITMASK)
			player->removeAction();

			if (b->getCollisionBitmask() == ENEMY_COLISION_BITMASK)
			{
				for (int i = 0; i < AllMinions.size(); i++)
				{
					if (AllMinions.at(i)->getPhysicsBody() == b)
					{

						AllMinions.at(i)->removeAction();
						break;
					}
				}
			}
		}
		else if (b->getCollisionBitmask() == WALL_COLISION_BITMASK)
		{
			if (a->getCollisionBitmask() == PLAYER_COLISION_BITMASK)
			player->removeAction();

			if (a->getCollisionBitmask() == ENEMY_COLISION_BITMASK)
			{
				for (int i = 0; i < AllMinions.size(); i++)
				{
					if (AllMinions.at(i)->getPhysicsBody() == a)
					{

						AllMinions.at(i)->removeAction();
						break;
					}
				}
			}
		}
		// Trap detect colision
		if (a->getCollisionBitmask() == TRAP_COLISION_BITMASK)
		{
			if (!playerdie && b->getCollisionBitmask()== PLAYER_COLISION_BITMASK)
			{
				playerdie = true;
				player->Playerdie();
			}
			if (b->getCollisionBitmask() == ENEMY_COLISION_BITMASK)
			{
				
				for (int i = 0; i < AllMinions.size(); i++)
				{
					if (AllMinions.at(i)->getPhysicsBody() == b)
					{

						AllMinions.erase(AllMinions.begin() + i);
						break;
					}
				}
				this->removeChild(b->getOwner());
			}
		}
		else if (b->getCollisionBitmask() == TRAP_COLISION_BITMASK)
		{
			if (!playerdie&& a->getCollisionBitmask() == PLAYER_COLISION_BITMASK)
			{
				playerdie = true;
				player->Playerdie();
			}
			if (a->getCollisionBitmask() == ENEMY_COLISION_BITMASK)
			{

				for (int i = 0; i < AllMinions.size(); i++)
				{
					if (AllMinions.at(i)->getPhysicsBody() == a)
					{

						AllMinions.erase(AllMinions.begin() + i);
						break;
					}
				}
				this->removeChild(a->getOwner());
			}
		}
		//Enemy detect collision
		if (a->getCollisionBitmask() == ENEMY_COLISION_BITMASK)
		{
			/*CCLOG("aloooooooooooooo      %d", AllMinions.size());
			if (b->getCollisionBitmask() == WALL_COLISION_BITMASK)
			{
				
				for (int i = 1; i <= AllMinions.size(); i++)
				{
					if (AllMinions.at(i)->getPhysicsBody() == a)
					{
						
						/*AllMinions.at(i)->removeAction();
						break;
					}
				}
			}*/
		}
		else if (b->getCollisionBitmask() == ENEMY_COLISION_BITMASK)
		{
			//CCLOG("00000000000loooooooooooooo      %d", AllMinions.size());
			/*if (a->getCollisionBitmask() == WALL_COLISION_BITMASK)
			{
				
				for (int i = 1; i <= AllMinions.size(); i++)
				{
					if (AllMinions.at(i)->getPhysicsBody() == b)
					{
						AllMinions.at(i)->removeAction();
						break;
					}
				}
			}*/
		}

	}
	return true;
}