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
#include "MinionManager.h"
#include "TrapManager.h"
#include "IteamManager.h"
#include "Shadow.h"
#include "Spider.h"
#include "TrapBear.h"
#include "TrapRock.h"
#include "TrapCheckBoss.h"
#include "Iteam.h"
#include "GameOver.h"
#include "IteamBox.h"
#include "Son.h"
#include "WallCrake.h"
USING_NS_CC;

int Level_of_difficult;
int controller;
Scene* GameScene::createScene(int Level_of_difficult_Scene, int controller_Scene)
{
	Level_of_difficult = Level_of_difficult_Scene;
	controller = controller_Scene;
	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));

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
	continueGame = false;
	again = false;
	def = UserDefault::getInstance();
	if (Level_of_difficult == 4)
	{
		again = true;
	}
	if (Level_of_difficult >= 3)
	{
		Level_of_difficult = def->getIntegerForKey("INGAME_CONTINUE_LEVEL", 1);
		continueGame = true;
	}

	gameState = STATE_PLAYING;
	CCLOG("gamescene init %d", gameState);

	MinionManager::getInstance()->SetFalseAllMinion();
	TrapManager::getInstance()->SetFalseAllTrap();
	IteamManager::getInstance()->SetFalseAllIteam();

	player = new Player();
	this->addChild(player,30);
	
	this->runAction(Follow::create(player)); // add action camera follow player	
	if (again == true)
	{
		level = def->getIntegerForKey("INGAME_Level", 1);
	}
	else
	{
		if (continueGame == true)
		{
			level = def->getIntegerForKey("INGAME_Level", 1);
		}
		else
		{
			def->setIntegerForKey("INGAME_Level", 1);
			level = 1;
		}
	}
	gameMap = new GameMap(this,player, level); // add gamemap
	door = gameMap->door;
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

	
	canvas = new Canvas(player, background_off, controller, this, gameState, level);
	canvas->setPosition(Vec2(0, 0));
	player->addChild(canvas, 50);
	canvas->_meta = gameMap->_meta;
	canvas->maxmap = (int)(gameMap->_tileMap->getMapSize().height);
	bool checkover = def->getBoolForKey("INGAME_OverGame", false);
	if (continueGame == true && checkover==false)
	{
		canvas->num_talk = def->getIntegerForKey("INGAME_NumTalk", -2);
	}
	else
	{
		def->setIntegerForKey("INGAME_NumTalk", -2);
		canvas->num_talk = -2;
	}

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
	
	checkLighting = true;

	SoundManager::getInstance()->PlayMusics(softbackground_sound,true,1.0f);
	
	effect = Sprite::create();
	effect->setPosition(player->getPosition());
	//effect->setScale(1.5f);
	this->addChild(effect, 200);
	if (continueGame == true && checkover == false)
	{
		GameScene::GotoAgain(1);
		canvas->offtalk();
	}
	else 
	{
		GameScene::meet();
	}
	finish = false;
	return true;
}

bool GameScene::onContactBegin(cocos2d::PhysicsContact &contact)
{
	AllMinions = MinionManager::getInstance()->AllMinions;
	AllTrap = TrapManager::getInstance()->AllTrap;
	PhysicsBody *a = contact.getShapeA()->getBody();
	PhysicsBody *b = contact.getShapeB()->getBody();
	CCLOG("Overlap on");
	CCLOG("%d %d", a->getCategoryBitmask(), b->getCategoryBitmask());
	//CCLOG("%d %d", a->getCategoryBitmask(), b->getCategoryBitmask());
	//CCLOG("%d", a->getCollisionBitmask() & b->getCategoryBitmask());
	//if ((a->getCollisionBitmask() & b->getCategoryBitmask() != 0) || (b->getCollisionBitmask() & a->getCategoryBitmask() != 0))
	
		CCLOG("Overlap");
		//Get item
		if (a->getCategoryBitmask() == ITEM_CATEGORY_BITMASK)
		{
			auto item = dynamic_cast<Iteam*>(a->getOwner());
			item->hit = true;
			if(b->getCategoryBitmask() == PLAYER_CATEGORY_BITMASK)
			{
				if (item->type == 1)
				{
					canvas->plusenergy((int)canvas->enegy->getMaxPercent() / 3);
					this->removeChild(item);
					item->setVisible(false);
				}
				if (item->type == 2)
				{
					this->removeChild(item);
					door->reduceNumberKey();
					item->setVisible(false);
				}
				if (item->type == 3)
				{
					auto itemBox = dynamic_cast<IteamBox*>(item);
					if (itemBox->check == false)
					{
						itemBox->HitPlater();
					}
				}
				if (item->type == 4)
				{
					
					item->setVisible(false);
					this->removeChild(item);
					itemsave = item;
					canvas->ontalk();
					this->schedule(CC_SCHEDULE_SELECTOR(GameScene::SaveInGame), 0.5f, 0, 0);
					//GameScene::SaveInGame(item);
				}
				if (item->type == 5)
				{
					item->setLocalZOrder(30);
					auto wallcrake = dynamic_cast<WallCrake*>(item);
					if (wallcrake->check == false)
					{
						player->removeAction();
					}
				}
			}
			if (b->getCategoryBitmask() == ENEMY_CATEGORY_BITMASK)
			{
				auto wallcrake = dynamic_cast<WallCrake*>(item);
				if (wallcrake->check == false)
				{
					wallcrake->HitMinion();
				}
			}
		}
		else if (b->getCategoryBitmask() == ITEM_CATEGORY_BITMASK)
		{
			auto item = dynamic_cast<Iteam*>(b->getOwner());
			item->hit = true;
			if(a->getCategoryBitmask() == PLAYER_CATEGORY_BITMASK)
			{
				if (item->type == 1)
				{
					canvas->plusenergy((int)canvas->enegy->getMaxPercent() / 3);
					this->removeChild(item);
					item->setVisible(false);
				}
				if (item->type == 2)
				{
					this->removeChild(item);
					door->reduceNumberKey();
					item->setVisible(false);
				}
				if (item->type == 3)
				{
					auto itemBox = dynamic_cast<IteamBox*>(item);
					if (itemBox->check == false)
					{
						itemBox->HitPlater();
					}
				}
				if (item->type == 4)
				{
					item->setVisible(false);
					this->removeChild(item);
					itemsave = item;
					canvas->ontalk();
					this->schedule(CC_SCHEDULE_SELECTOR(GameScene::SaveInGame), 0.5f, 0,0);
					//GameScene::SaveInGame(item);
				}
				if (item->type == 5)
				{
					item->setLocalZOrder(30);
					auto wallcrake = dynamic_cast<WallCrake*>(item);
					if (wallcrake->check == false)
					{
						player->removeAction();
					}
				}
			}
			if (a->getCategoryBitmask() == ENEMY_CATEGORY_BITMASK)
			{
				auto wallcrake = dynamic_cast<WallCrake*>(item);
				if (wallcrake->check == false)
				{
					wallcrake->HitMinion();
				}
			}
		}
		// door detect collision
		if (a->getCategoryBitmask() == DOOR_CATEGORY_BITMASK)
		{
			if (b->getCategoryBitmask() == PLAYER_CATEGORY_BITMASK)
			{
				if (door->numberkey <= 0)
				{
					this->schedule(CC_SCHEDULE_SELECTOR(GameScene::GoToGameOver), DISPLAY_TIME_SPLASH_SCENE / 2);
					finish = true;
				}
				else
					player->removeAction();
			}
		}
		else if (b->getCategoryBitmask() == DOOR_CATEGORY_BITMASK)
		{
			if (a->getCategoryBitmask() == PLAYER_CATEGORY_BITMASK)
			{
				if (door->numberkey <= 0)
				{
					this->schedule(CC_SCHEDULE_SELECTOR(GameScene::GoToGameOver), DISPLAY_TIME_SPLASH_SCENE / 2);
					finish = true;
				}
				else
					player->removeAction();
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
				auto minion = dynamic_cast<Minions*>(b->getOwner());
				minion->removeAction();
			}
			if (b->getCategoryBitmask() == TRAP_CATEGORY_BITMASK)
			{
				CCLOG("Hit wall");
				auto trap = dynamic_cast<Trap*>(b->getOwner());
				if (trap->type == 3)
				{
					auto traprock = dynamic_cast<TrapRock*>(trap);
					traprock->removeTrap();
				}
			}
		}
		else if (b->getCategoryBitmask() == WALL_CATEGORY_BITMASK)
		{
			if (a->getCategoryBitmask() == PLAYER_CATEGORY_BITMASK)
			player->removeAction();

			if (a->getCategoryBitmask() == ENEMY_CATEGORY_BITMASK)
			{
				auto minion = dynamic_cast<Minions*>(a->getOwner());
				minion->removeAction();
			}
			if (a->getCategoryBitmask() == TRAP_CATEGORY_BITMASK)
			{
				CCLOG("Hit wall");
				auto trap = dynamic_cast<Trap*>(a->getOwner());
				if (trap->type == 3)
				{
					auto traprock = dynamic_cast<TrapRock*>(trap);
					traprock->removeTrap();
				}
			}
		}
		// Trap detect colision
		if (a->getCategoryBitmask() == TRAP_CATEGORY_BITMASK)
		{
			auto trap = dynamic_cast<Trap*>(a->getOwner());
			trap->hit = true;
			if (trap->type == 0 || trap->type == 3)
			{
				if(trap->type == 0)
				trap->setLocalZOrder(40);
				if (!player->die && b->getCategoryBitmask() == PLAYER_CATEGORY_BITMASK)
				{
					player->Playerdie();
					GameScene::checkdie();
				}
				if (b->getCategoryBitmask() == ENEMY_CATEGORY_BITMASK)
				{
					auto minion = dynamic_cast<Minions*>(b->getOwner());
					if (minion->type == 0)
						return true;
					if(minion->Booldie==false)
					minion->die();
				}
			}
			if (trap->type == 2)
			{
				TrapBear *trapbear = dynamic_cast<TrapBear*>(trap);
				if (trapbear->work != false)
				{
					trapbear->HitPlayer();
				}
				else
					return true;
				if (!player->die && b->getCategoryBitmask() == PLAYER_CATEGORY_BITMASK)
				{
					player->changeTravelTime(VALUE_SLOW);
				}
				if (b->getCategoryBitmask() == ENEMY_CATEGORY_BITMASK)
				{
					auto minion = dynamic_cast<Minions*>(b->getOwner());
					if (minion->type == 0)
						return true;
					minion->changeTravelTime(VALUE_SLOW);
				}
			}
			if (trap->type == 1 && b->getCategoryBitmask() == PLAYER_CATEGORY_BITMASK)
			{
				TrapPlant *trapPlant = dynamic_cast<TrapPlant*>(trap);
				if (trapPlant->enegy->isVisible() == false)
				{
					canvas->plant = dynamic_cast<TrapPlant*>(trap);
					player->stop = false;
					trapPlant->HitPlayer();
				}
			}
			if (trap->type == 4)
			{
				canvas->goup(1);
				auto trapCheckBoss = dynamic_cast<TrapCheckBoss*>(trap);
				trapCheckBoss->hitplayer(this);
			}
		}
		else if (b->getCategoryBitmask() == TRAP_CATEGORY_BITMASK)
		{
			auto trap = dynamic_cast<Trap*>(b->getOwner());
			trap->hit = true;
			if (trap->type == 0  || trap->type == 3)
			{
				if (trap->type == 0)
				trap->setLocalZOrder(40);
				if (!player->die && a->getCategoryBitmask() == PLAYER_CATEGORY_BITMASK)
				{
					player->Playerdie();
					GameScene::checkdie();
				}
				if (a->getCategoryBitmask() == ENEMY_CATEGORY_BITMASK)
				{
					auto minion = dynamic_cast<Minions*>(a->getOwner());
					if (minion->type == 0)
						return true;
					if (minion->Booldie == false)
					minion->die();
				}
			}
			if (trap->type == 2)
			{
				TrapBear *trapbear = dynamic_cast<TrapBear*>(trap);
				if (trapbear->work != false)
				{
					trapbear->HitPlayer();
				}
				else
					return true;
				if (!player->die && a->getCategoryBitmask() == PLAYER_CATEGORY_BITMASK)
				{
					player->changeTravelTime(VALUE_SLOW);
				}
				if (a->getCategoryBitmask() == ENEMY_CATEGORY_BITMASK)
				{
					auto minion = dynamic_cast<Minions*>(a->getOwner());
					if (minion->type == 0)
						return true;
					minion->changeTravelTime(VALUE_SLOW);
				}
			}
			if (trap->type == 1 && b->getCategoryBitmask() == PLAYER_CATEGORY_BITMASK)
			{
				TrapPlant *trapPlant = dynamic_cast<TrapPlant*>(trap);
				if (trapPlant->enegy->isVisible() == false)
				{
					canvas->plant = dynamic_cast<TrapPlant*>(trap);
					player->stop = false;
					trapPlant->HitPlayer();
				}
			}
			if (trap->type == 4)
			{
				canvas->goup(1);
				auto trapCheckBoss = dynamic_cast<TrapCheckBoss*>(trap);
				trapCheckBoss->hitplayer(this);
			}
		}
		//Enemy detect collision
		if (a->getCategoryBitmask() == ENEMY_CATEGORY_BITMASK)
		{
			auto minion = dynamic_cast<Minions*>(a->getOwner());
			minion->hit = true;
			if(minion->Booldie == true)
				return true;
			if (!player->die && b->getCategoryBitmask() == PLAYER_CATEGORY_BITMASK)
			{
				//auto minion = dynamic_cast<Minions*>(a->getOwner());
				if (minion->Booldie == false)
				{
					minion->unscheduleAllCallbacks();
					player->Playerdie();
					GameScene::checkdie();
				}
			}
			if (b->getCategoryBitmask() == PLAYER_BG_CATEGORY_BITMASK)
			{
				//auto minion = dynamic_cast<Minions*>(a->getOwner());
				if (minion->boolFind == false)
				{
					Schedule_shake = CC_SCHEDULE_SELECTOR(GameScene::shakeScreen);
					this->schedule(Schedule_shake, 0.1f);
					SoundManager::getInstance()->PlayMusics(Roar_sound, false, 0.5f);

					if (minion->type == 0)
					{
						auto spider = dynamic_cast<Spider*>(minion);
						spider->Roar(1);
					}
					if (minion->type == 1)
					{
						auto shadow = dynamic_cast<Shadow*>(minion);
						shadow->Roar(1);
					}
				}
			}
		}
		else if (b->getCategoryBitmask() == ENEMY_CATEGORY_BITMASK)
		{
			auto minion = dynamic_cast<Minions*>(b->getOwner());
			minion->hit = true;
			if (minion->Booldie == true)
				return true;
			if (!player->die && a->getCategoryBitmask() == PLAYER_CATEGORY_BITMASK)
			{
				//auto minion = dynamic_cast<Minions*>(b->getOwner());
				if (minion->Booldie == false)
				{
					minion->unscheduleAllCallbacks();
					player->Playerdie();
					GameScene::checkdie();
				}
			}
			if (a->getCategoryBitmask() == PLAYER_BG_CATEGORY_BITMASK)
			{
				//auto minion = dynamic_cast<Minions*>(b->getOwner());
				if (minion->boolFind == false)
				{
					Schedule_shake = CC_SCHEDULE_SELECTOR(GameScene::shakeScreen);
					this->schedule(Schedule_shake, 0.1f);
					SoundManager::getInstance()->PlayMusics(Roar_sound, false, 0.5f);

					if (minion->type == 0)
					{
						auto spider = dynamic_cast<Spider*>(minion);
						spider->Roar(1);
					}
					if (minion->type == 1)
					{
						auto shadow = dynamic_cast<Shadow*>(minion);
						shadow->Roar(1);
					}
				}
			}
		}
		if (a->getCategoryBitmask() == PLAYER_EDGE_CATEGORY_BITMASK)
		{
			if (b->getCategoryBitmask() == ENEMY_CATEGORY_BITMASK)
			{
				auto minion = dynamic_cast<Minions*>(b->getOwner());
				if (minion->Booldie == true)
					return true;
				if (checkLighting == true)
				{
					checkLighting = false;
					this->schedule(CC_SCHEDULE_SELECTOR(GameScene::setcheckLighting), CHECK_LIGHTING, 0, 0);
					GameScene::Lighting(1);
				}
			}
		}
		else if (b->getCategoryBitmask() == PLAYER_EDGE_CATEGORY_BITMASK)
		{
			if (a->getCategoryBitmask() == ENEMY_CATEGORY_BITMASK)
			{
				auto minion = dynamic_cast<Minions*>(a->getOwner());
				if (minion->Booldie == true)
					return true;
				if (checkLighting == true)
				{
					checkLighting = false;
					this->schedule(CC_SCHEDULE_SELECTOR(GameScene::setcheckLighting), CHECK_LIGHTING, 0, 0);
					GameScene::Lighting(1);
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
	int num = cocos2d::RandomHelper::random_int(1, 10);
	if (num < 7)
		return;
	else
	{
		
		SoundManager::getInstance()->PlayMusics(LIGHTING);
		if (player->background->isVisible() == true)
			light = false;
		else
			light = true;
		canvas->endlight = false;
		if (Level_of_difficult != 1)
		{
			this->schedule(CC_SCHEDULE_SELECTOR(GameScene::Lightingbg), 0.25);
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
void GameScene::setcheckLighting(float dt)
{
	checkLighting = true;
}
void  GameScene::GoToGameOver(float dt)
{
	def->setIntegerForKey("INGAME_Level", level);
	SoundManager::getInstance()->stopMusic(softbackground_sound);
	auto scene = GameOver::createScene(controller, finish);
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}
void GameScene::SaveInGame(float dt)
{
	
	//Game
	def->setBoolForKey("INGAME_CONTINUE", true);
	def->setIntegerForKey("INGAME_CONTINUE_LEVEL", Level_of_difficult);
	def->setBoolForKey("INGAME_OverGame", false);
	//player

	def->setBoolForKey("INGAME_PLAYERLight", canvas->background_off->isVisible());
	def->setFloatForKey("INGAME_PLAYERENEGY", canvas->enegy->getPercent());
	def->setFloatForKey("INGAME_PLAYERPOSX", itemsave->getPositionX());
	def->setFloatForKey("INGAME_PLAYERPOSY", itemsave->getPositionY());
	//minion
	AllMinions = MinionManager::getInstance()->AllMinions;
	int Num = 0;
	for (int i = 0; i < AllMinions.size(); i++)
	{
		if (AllMinions.at(i)->isVisible() == true )
		{
			Num++;
			
			def->setFloatForKey(StringUtils::format("INGAME_MinionPOSX%d", Num).c_str(), AllMinions.at(i)->mindPositison.x);
			def->setFloatForKey(StringUtils::format("INGAME_MinionPOSY%d", Num).c_str(), AllMinions.at(i)->mindPositison.y);
			def->setBoolForKey(StringUtils::format("INGAME_MinionBoolFind%d", Num).c_str(), AllMinions.at(i)->boolFind);
			def->setBoolForKey(StringUtils::format("INGAME_MinionDie%d", Num).c_str(), AllMinions.at(i)->Booldie);
			def->setIntegerForKey(StringUtils::format("INGAME_MinionType%d", Num).c_str(), AllMinions.at(i)->type);
			def->setIntegerForKey(StringUtils::format("INGAME_MinionZ%d", Num).c_str(), AllMinions.at(i)->getLocalZOrder());
		}
	}
	def->setIntegerForKey("INGAME_NUMMINION", Num);
	// trap
	AllTrap = TrapManager::getInstance()->AllTrap;
	int Numtrap = 0;
	for (int i = 0; i < AllTrap.size(); i++)
	{
		if (AllTrap.at(i)->isVisible() == true)
		{
			Numtrap++;
			def->setFloatForKey(StringUtils::format("INGAME_TrapPOSX%d", Numtrap).c_str(), AllTrap.at(i)->getPositionX());
			def->setFloatForKey(StringUtils::format("INGAME_TrapPOSY%d", Numtrap).c_str(), AllTrap.at(i)->getPositionY());
			def->setIntegerForKey(StringUtils::format("INGAME_TrapTP%d", Numtrap).c_str(), AllTrap.at(i)->type);
			def->setIntegerForKey(StringUtils::format("INGAME_TrapZ%d", Numtrap).c_str(), AllTrap.at(i)->getLocalZOrder());
			if (AllTrap.at(i)->type == 4)
			{
				auto traptemp = dynamic_cast<TrapCheckBoss*>(AllTrap.at(i));
				def->setIntegerForKey(StringUtils::format("INGAME_TrapTg%d",Numtrap).c_str(), traptemp->taget);
				
			}
		}
	}
	def->setIntegerForKey("INGAME_NUMTrap", Numtrap);
	
	//iteam
	AllIteam = IteamManager::getInstance()->AllIteam;
	int NumIteam = 0;
	for (int i = 0; i < AllIteam.size(); i++)
	{
		if (AllIteam.at(i)->isVisible() == true)
		{
			NumIteam++;
			def->setFloatForKey(StringUtils::format("INGAME_ItemPOSX%d", NumIteam).c_str(), AllIteam.at(i)->getPositionX());
			def->setFloatForKey(StringUtils::format("INGAME_ItemPOSY%d", NumIteam).c_str(), AllIteam.at(i)->getPositionY());
			def->setIntegerForKey(StringUtils::format("INGAME_ItemTP%d", NumIteam).c_str(), AllIteam.at(i)->type);
			def->setIntegerForKey(StringUtils::format("INGAME_ItemZ%d", NumIteam).c_str(), AllIteam.at(i)->getLocalZOrder());
		}
	}
	def->setIntegerForKey("INGAME_NUMIteam", NumIteam);
}
void GameScene::checkdie()
{
	if (player->NumHeal > 1)
		this->schedule(CC_SCHEDULE_SELECTOR(GameScene::GotoAgain), DISPLAY_TIME_SPLASH_SCENE*1.5, 0, 0);
	else
		this->schedule(CC_SCHEDULE_SELECTOR(GameScene::GoToGameOver), DISPLAY_TIME_SPLASH_SCENE*1.5, 0, 0);
}

void GameScene::GotoAgain(float dt)
{
	//sound 
	SoundManager::getInstance()->stopALLMusic();
	SoundManager::getInstance()->PlayMusics(softbackground_sound, true, 1.0f);
	//player
	//UserDefault *def= UserDefault::getInstance();
	auto PosX = def->getFloatForKey("INGAME_PLAYERPOSX", 0);
	auto PosY = def->getFloatForKey("INGAME_PLAYERPOSY", 0);
	auto enegy = def->getFloatForKey("INGAME_PLAYERENEGY", 0);
	auto light = def->getBoolForKey("INGAME_PLAYERLight", false);
	auto heal = def->getIntegerForKey("INGAME_PLAYERHEAL", player->NumHeal);

	canvas->enegy->setPercent(enegy);
	player->setPosition(Vec2(PosX, PosY));
	player->die = false;
	player->checkMove = true;
	player->setTexture("prefap/Player/Player.png");
	player->setTextureRect(Rect(360, 1, 80, 95));
	player->NumHeal = heal;
	player->changeHeal();

	//mininon
	AllMinions = MinionManager::getInstance()->AllMinions;
	for (int i = 0; i < AllMinions.size(); i++)
	{
		if (AllMinions.at(i)->isVisible()==true )
		{
			//MinionManager::getInstance()->setfalseMinion(AllMinions.at(i));
			this->removeChild(AllMinions.at(i));	
		}
	}
	MinionManager::getInstance()->SetFalseAllMinion();
	auto NumMinion = def->getIntegerForKey("INGAME_NUMMINION", 0);
	for (int i = 1; i <=NumMinion; i++)
	{
		auto MinionPosx = def->getFloatForKey(StringUtils::format("INGAME_MinionPOSX%d", i).c_str(), 0);
		auto MinionPosy = def->getFloatForKey(StringUtils::format("INGAME_MinionPOSY%d", i).c_str(), 0);
		auto MinionBoolfind = def->getBoolForKey(StringUtils::format("INGAME_MinionBoolFind%d", i).c_str(),false);
		auto MinionDie = def->getBoolForKey(StringUtils::format("INGAME_MinionDie%d", i).c_str(), false);
		auto MInionType = def->getIntegerForKey(StringUtils::format("INGAME_MinionType%d", i).c_str(), 1);
		auto MInionZ = def->getIntegerForKey(StringUtils::format("INGAME_MinionZ%d", i).c_str(), 20);

		auto minion = MinionManager::getInstance()->CreateMinion(MInionType);
		minion->setPosition(Vec2(MinionPosx, MinionPosy));
		minion->boolFind = MinionBoolfind;
		minion->Booldie = MinionDie;
		if (light == false && MinionDie == false && MinionBoolfind == true)
		{
			minion->lighton(1);
		}
		if (MInionType == 0)
		{
			auto spider = dynamic_cast<Spider*>(minion);
			spider->setStatus(MinionDie);
		}
		if (MInionType == 1)
		{
			auto spider = dynamic_cast<Shadow*>(minion);
			spider->setStatus(MinionDie);
		}
		if (MInionType == 2)
		{
			auto spider = dynamic_cast<MinionBoss*>(minion);
			spider->setStatus(MinionDie);
		}
		this->addChild(minion, MInionZ);
	}
	// create trap
	AllTrap = TrapManager::getInstance()->AllTrap;
	for (int i = 0; i < AllTrap.size(); i++)
	{
		if (AllTrap.at(i)->isVisible() == true)
		{
			this->removeChild(AllTrap.at(i));
		}
	}
	TrapManager::getInstance()->SetFalseAllTrap();
	auto NumTrap = def->getIntegerForKey("INGAME_NUMTrap", 0);
	for (int i = 1; i <= NumTrap; i++)
	{
		auto trapPosx = def->getFloatForKey(StringUtils::format("INGAME_TrapPOSX%d", i).c_str(),0);
		auto trapPosy = def->getFloatForKey(StringUtils::format("INGAME_TrapPOSY%d", i).c_str(), 0);
		auto trapType = def->getIntegerForKey(StringUtils::format("INGAME_TrapTP%d", i).c_str(), 0);
		auto trapz= def->getIntegerForKey(StringUtils::format("INGAME_TrapZ%d", i).c_str(), 0);

		auto trap = TrapManager::getInstance()->CreateTrap(trapType);
		trap->setPosition(Vec2(trapPosx, trapPosy));

		if (trapType == 4)
		{
			auto traptaget = def->getIntegerForKey(StringUtils::format("INGAME_TrapTg%d", i).c_str(), 0);
			auto checkboss = dynamic_cast<TrapCheckBoss*>(trap);
			checkboss->taget = traptaget;
		}
		this->addChild(trap, trapz);
	}
	//create iteam
	AllIteam = IteamManager::getInstance()->AllIteam;
	for (int i = 0; i < AllIteam.size(); i++)
	{
		if (AllIteam.at(i)->isVisible() == true)
		{
			this->removeChild(AllIteam.at(i));
		}
	}
	IteamManager::getInstance()->SetFalseAllIteam();
	auto Numitem = def->getIntegerForKey("INGAME_NUMIteam", 0);
	int NumberKey=0;
	for (int i = 1; i <= Numitem; i++)
	{
		auto ItemPosX =  def->getFloatForKey(StringUtils::format("INGAME_ItemPOSX%d", i).c_str(),0);
		auto ItemPosY = def->getFloatForKey(StringUtils::format("INGAME_ItemPOSY%d", i).c_str(), 0);
		auto ItemType = def->getIntegerForKey(StringUtils::format("INGAME_ItemTP%d", i).c_str(),0);
		auto ItemZ = def->getIntegerForKey(StringUtils::format("INGAME_ItemZ%d", i).c_str(),0);
		if (ItemType == 2)
			NumberKey++;

		auto item =  IteamManager::getInstance()->CreateIteam(ItemType);
		item->setPosition(Vec2(ItemPosX, ItemPosY));
		this->addChild(item, ItemZ);
	}
	//Game Ma1;
	door->numberkey = 1;
	door->reduceNumberKey();
	gameMap->GoAgain();
	//Door
	door->numberkey = NumberKey;
	door->_tileMap = gameMap->_tileMap;
	door->_meta = gameMap->_meta;
	//canvas
	canvas->Goagain(light);
}
void GameScene::meet()
{
	canvas->playerNow = player->getPosition();
	player->setPosition(gameMap->PlayerMeet);
	son = new Son();
	son->setPosition(gameMap->SonMeet);
	this->addChild(son, 50);
	canvas->son = son;
	player->checkMove = false;
	player->background->setVisible(false);
	player->background->getPhysicsBody()->setEnabled(false);
	player->getPhysicsBody()->setEnabled(false);
	player->setTextureRect(Rect(360, 359, 80, 95));
	canvas->ontalk();
	//canvas->meet();
}