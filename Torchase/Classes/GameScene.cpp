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
#include "SoundManager.h"
#include "Shadow.h"
#include "Spider.h"
#include "TrapBear.h"
USING_NS_CC;

int Level_of_difficult;
int controller;
Scene* GameScene::createScene(int Level_of_difficult_Scene, int controller_Scene)
{
	Level_of_difficult = Level_of_difficult_Scene;
	controller = controller_Scene;
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

	AllTrap = gameMap->AllTrap;

	Size size = gameMap->returnSizeMap();
	player->setBlackVisionBG(size);
	width = MAX(size.width*2+visibleSize.width, size.height*2+visibleSize.height);
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
	
	this->addChild(background_off, 25);
	background_off->setVisible(false);

	canvas = new Canvas(player, background_off, controller,this);
	canvas->setPosition(Vec2(0, 0));
	player->addChild(canvas, 50);
	canvas->AllMinions = AllMinions;
	canvas->AllTrap = &AllTrap;
	canvas->_meta = gameMap->_meta;
	canvas->maxmap = (int)(gameMap->_tileMap->getMapSize().height);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
	playerdie = false;

	SoundManager::getInstance()->PlayMusics(softbackground_sound,true,1.0f);
	
	effect = Sprite::create();
	effect->setPosition(player->getPosition());
	//effect->setScale(1.5f);
	this->addChild(effect, 200);

	this->schedule(CC_SCHEDULE_SELECTOR(GameScene::Lighting), 5.0f);

	return true;
}
bool GameScene::onContactBegin(cocos2d::PhysicsContact &contact)
{
	PhysicsBody *a = contact.getShapeA()->getBody();
	PhysicsBody *b = contact.getShapeB()->getBody();
	CCLOG("Overlap on");
	CCLOG("%d %d", a->getCategoryBitmask(), b->getCategoryBitmask());
	CCLOG("%d %d", a->getCollisionBitmask(), b->getCollisionBitmask());
	//CCLOG("%d", a->getCollisionBitmask() & b->getCategoryBitmask());
	//if ((a->getCollisionBitmask() & b->getCategoryBitmask() != 0) || (b->getCollisionBitmask() & a->getCategoryBitmask() != 0))
	
		CCLOG("Overlap");
		//Get item
		if (a->getCategoryBitmask() == ITEM_CATEGORY_BITMASK)
		{
			if(b->getCategoryBitmask() == PLAYER_CATEGORY_BITMASK)
			{
				canvas->plusenergy((int)canvas->enegy->getMaxPercent()/3);
					this->removeChild(a->getOwner());
			}
		}
		else if (b->getCategoryBitmask() == ITEM_CATEGORY_BITMASK)
		{
			if(a->getCategoryBitmask() == PLAYER_CATEGORY_BITMASK)
			{
				canvas->plusenergy((int)canvas->enegy->getMaxPercent() / 3);
					this->removeChild(a->getOwner());
			}
		}

		//Wall detect collision
		if (a->getCategoryBitmask() == WALL_CATEGORY_BITMASK)
		{
			if(b->getCategoryBitmask() == PLAYER_CATEGORY_BITMASK)
			player->removeAction();

			if (b->getCategoryBitmask() == ENEMY_CATEGORY_BITMASK)
			{
				CCLOG("Hit wall");
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
		else if (b->getCategoryBitmask() == WALL_CATEGORY_BITMASK)
		{
			if (a->getCategoryBitmask() == PLAYER_CATEGORY_BITMASK)
			player->removeAction();

			if (a->getCategoryBitmask() == ENEMY_CATEGORY_BITMASK)
			{
				CCLOG("Hit wall");
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
		if (a->getCategoryBitmask() == TRAP_CATEGORY_BITMASK)
		{
			for (int i = 0; i < AllTrap.size(); i++)
			{
				if (AllTrap.at(i)->getPhysicsBody() == a)
				{
					if (AllTrap.at(i)->type == 0 || AllTrap.at(i)->type == 2)
					{
						if (AllTrap.at(i)->type == 2)
						{
							TrapBear *trapbear = dynamic_cast<TrapBear*>(AllTrap.at(i));
							if (trapbear->work == false)
								break;
							else
							{
								trapbear->HitPlayer();
							}
						}
						if (!playerdie && b->getCategoryBitmask() == PLAYER_CATEGORY_BITMASK)
						{
							playerdie = true;
							player->Playerdie();
						}
						if (b->getCategoryBitmask() == ENEMY_CATEGORY_BITMASK)
						{
							CCLOG("ene die");
							for (int i = 0; i < AllMinions.size(); i++)
							{
								if (AllMinions.at(i)->getPhysicsBody() == b)
								{

									AllMinions.at(i)->die();
									AllMinions.erase(AllMinions.begin() + i);
									break;
								}
							}
						}
					}
					if (AllTrap.at(i)->type == 1 && b->getCategoryBitmask() == PLAYER_CATEGORY_BITMASK)
					{
						TrapPlant *trapPlant = dynamic_cast<TrapPlant*>(AllTrap.at(i));
						if (trapPlant->enegy->isVisible() == false)
						{
							canvas->plant = dynamic_cast<TrapPlant*>(AllTrap.at(i));
							player->stop = false;
							trapPlant->HitPlayer();
						}
					}
					break;
				}
			}
		}
		else if (b->getCategoryBitmask() == TRAP_CATEGORY_BITMASK)
		{
		
			for (int i = 0; i < AllTrap.size(); i++)
			{
				if (AllTrap.at(i)->getPhysicsBody() == b)
				{
					if (AllTrap.at(i)->type == 0 || AllTrap.at(i)->type == 2)
					{
						if (AllTrap.at(i)->type == 2)
						{
							TrapBear *trapbear = dynamic_cast<TrapBear*>(AllTrap.at(i));
							if (trapbear->work == false)
								break;
							else
							{
								trapbear->HitPlayer();
							}
						}
						if (!playerdie && a->getCategoryBitmask() == PLAYER_CATEGORY_BITMASK)
						{
							playerdie = true;
							player->Playerdie();
						}
						if (a->getCategoryBitmask() == ENEMY_CATEGORY_BITMASK)
						{
							CCLOG("ene die");
							for (int i = 0; i < AllMinions.size(); i++)
							{
								if (AllMinions.at(i)->getPhysicsBody() == a)
								{

									AllMinions.at(i)->die();
									AllMinions.erase(AllMinions.begin() + i);
									break;
								}
							}
						}
					}
					if (AllTrap.at(i)->type == 1 && a->getCategoryBitmask() == PLAYER_CATEGORY_BITMASK)
					{
						TrapPlant *trapPlant = dynamic_cast<TrapPlant*>(AllTrap.at(i));
						if (trapPlant->enegy->isVisible() == false)
						{
							canvas->plant = dynamic_cast<TrapPlant*>(AllTrap.at(i));
							player->stop = false;
							trapPlant->HitPlayer();
						}
					}
					break;
				}
			}
		}
		//Enemy detect collision
		if (a->getCategoryBitmask() == ENEMY_CATEGORY_BITMASK)
		{
			CCLOG("enemy");
			if (!playerdie && b->getCategoryBitmask() == PLAYER_CATEGORY_BITMASK)
			{
				playerdie = true;
				this->stopAllActions();
				player->Playerdie();
			}
			if (b->getCategoryBitmask() == PLAYER_BG_CATEGORY_BITMASK)
			{
				CCLOG("activated");
				//SoundManager::getInstance()->PlayMusic(thrillingbackground_sound, false, 0.2f);
				for (int i = 0; i < AllMinions.size(); i++)
				{
					if (AllMinions.at(i)->getPhysicsBody() == a)
					{
						if (AllMinions.at(i)->boolFind == false)
						{
							AllMinions.at(i)->boolFind = true;
							Schedule_shake = CC_SCHEDULE_SELECTOR(GameScene::shakeScreen);
							this->schedule(Schedule_shake, 0.1f);
							SoundManager::getInstance()->PlayMusics(Roar_sound, false, 0.5f);

							if (AllMinions.at(i)->type == 0)
							{
								auto minion = dynamic_cast<Spider*>(AllMinions.at(i));
								minion->Roar(1);
							}
							if (AllMinions.at(i)->type == 1)
							{
								auto minion = dynamic_cast<Shadow*>(AllMinions.at(i));
								minion->Roar(1);
							}
						}
						break;
					}
				}
			}
		}
		else if (b->getCategoryBitmask() == ENEMY_CATEGORY_BITMASK)
		{
			CCLOG("enemy");
			if (!playerdie && a->getCategoryBitmask() == PLAYER_COLISION_BITMASK)
			{
				playerdie = true;
				player->Playerdie();
			}
			if (a->getCategoryBitmask() == PLAYER_BG_CATEGORY_BITMASK)
			{
				CCLOG("activated");
				//SoundManager::getInstance()->PlayMusic(thrillingbackground_sound,false,0.2f);
				for (int i = 0; i < AllMinions.size(); i++)
				{
					if (AllMinions.at(i)->getPhysicsBody() == b)
					{
						if (AllMinions.at(i)->boolFind == false)
						{
							AllMinions.at(i)->boolFind = true;
							Schedule_shake = CC_SCHEDULE_SELECTOR(GameScene::shakeScreen);
							this->schedule(Schedule_shake, 0.1f);
							SoundManager::getInstance()->PlayMusics(Roar_sound,false,0.5f);
							if (AllMinions.at(i)->type == 0)
							{
								auto minion = dynamic_cast<Spider*>(AllMinions.at(i));
								minion->Roar(1);
							}
							if (AllMinions.at(i)->type == 1)
							{
								auto minion = dynamic_cast<Shadow*>(AllMinions.at(i));
								minion->Roar(1);
							}
						}
						break;
					}
				}
			}
		}
	
	return true;
}
void GameScene::shakeScreen(float dt)
{
	float randx = rangeRandom(-5.0f, 5.0);
	float randy = rangeRandom(-5.0f, 5.0);
	Node *map = this->getChildByTag(100);
	map->setPosition(Point(randx, randy));
	map->setPosition(Point(map->getPositionX() + randx, map->getPositionY() + randy));

	SET_SHAKE_DURATION -= 1;
	if (SET_SHAKE_DURATION <= 0)
	{
		map->setPosition(Point(map->getPositionX(), map->getPositionY()));
		this->unschedule(Schedule_shake);
		SET_SHAKE_DURATION = 10;
	}
}
float GameScene::rangeRandom(float min, float max)
{
	float rnd = ((float)rand() / (float)RAND_MAX);
	return rnd * (max - min) + min;
}
void GameScene::Lighting(float dt)
{
	int num = cocos2d::RandomHelper::random_int(1, 20);
	if (num < 18)
		return;
	else
	{
		
		SoundManager::getInstance()->PlayMusics(LIGHTING);
		if (player->background->isVisible() == true)
			light = false;
		else
			light = true;
		if (Level_of_difficult != 1)
		{
			this->schedule(CC_SCHEDULE_SELECTOR(GameScene::Lightingbg), 0.25);
			canvas->endlight = false;
		}
		if (Level_of_difficult == 2)
		{
			SoundManager::getInstance()->PlayMusics(Roar_sound, false, 0.5f);
			Schedule_shake = CC_SCHEDULE_SELECTOR(GameScene::shakeScreen);
			this->schedule(Schedule_shake, 0.1f);
			for (int i = 0; i < AllMinions.size(); i++)
			{
				AllMinions.at(i)->Roar(1);
			}
		}
		effect->setVisible(true);
		Schedule_lighting = CC_SCHEDULE_SELECTOR(GameScene::Lightingstart);
		this->schedule(Schedule_lighting, 0.5f);
		Schedule_shake = CC_SCHEDULE_SELECTOR(GameScene::shakeScreen);
		SET_SHAKE_DURATION = 20;
		this->schedule(Schedule_shake, 0.1f);
		
	}
}
void GameScene::Lightingstart(float dt)
{

	if (SET_LIGHTING_DURATION <=0)
	{
		effect->setVisible(false);
		SET_LIGHTING_DURATION = 3;
		this->unschedule(Schedule_lighting);
	}
	SET_LIGHTING_DURATION -= 1;
	int num = cocos2d::RandomHelper::random_int(1,8);
	int numpos = cocos2d::RandomHelper::random_int((int)(player->getPositionX()-visibleSize.width/4),(int) (player->getPositionX() + visibleSize.width / 4));
	int numposY = cocos2d::RandomHelper::random_int((int)(player->getPositionY() - visibleSize.height / 4), (int)(player->getPositionY() + visibleSize.height / 4));
	effect->setTexture("effect/lingning.png");
	effect->setTextureRect(Rect(200 * num, 0, 200, 600));
	//effect->setPosition(Vec2(numpos, numposY));
	effect->setPosition(Vec2(numpos, player->getPositionY()));
}
void GameScene::Lightingbg(float dt)
{
	if (SET_LIGHTINGBG_DURATION <= 0)
	{
		SET_LIGHTINGBG_DURATION = 5;
		if (light == false)
		{
			player->background->setVisible(true);
			canvas->background_off->setVisible(false);
		}
		else
		{
			player->background->setVisible(false);
			canvas->background_off->setVisible(true);
		}
		if(canvas->enegy->getPercent()>0)
		canvas->endlight = true;
		this->unschedule(CC_SCHEDULE_SELECTOR(GameScene::Lightingbg));
		return;
	}
	SET_LIGHTINGBG_DURATION -= 1;
	if (player->background->isVisible() == true || canvas->background_off->isVisible()==true)
	{
		player->background->setVisible(false);
		canvas->background_off->setVisible(false);
	}
	else
	{
		player->background->setVisible(true);
		canvas->background_off->setVisible(true);
	}
}