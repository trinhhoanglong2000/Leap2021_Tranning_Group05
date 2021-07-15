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

	gameState = STATE_PLAYING;
	CCLOG("gamescene init %d", gameState);

	MinionManager::getInstance()->SetFalseAllMinion();
	TrapManager::getInstance()->SetFalseAllTrap();
	IteamManager::getInstance()->SetFalseAllIteam();

	player = new Player();	
	this->addChild(player,30);
	
	this->runAction(Follow::create(player)); // add action camera follow player	

	gameMap = new GameMap(this,player); // add gamemap
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

	canvas = new Canvas(player, background_off, controller,this,gameState);
	canvas->setPosition(Vec2(0, 0));
	player->addChild(canvas, 50);
	canvas->_meta = gameMap->_meta;
	canvas->maxmap = (int)(gameMap->_tileMap->getMapSize().height);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
	
	checkLighting = true;

	SoundManager::getInstance()->PlayMusics(softbackground_sound,true,1.0f);
	
	effect = Sprite::create();
	effect->setPosition(player->getPosition());
	//effect->setScale(1.5f);
	this->addChild(effect, 200);
	
	
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
			if(b->getCategoryBitmask() == PLAYER_CATEGORY_BITMASK)
			{
				auto item = dynamic_cast<Iteam*>(a->getOwner());
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
					GameScene::SaveInGame(item);
					item->setVisible(false);
					this->removeChild(item);
				}
			}
		}
		else if (b->getCategoryBitmask() == ITEM_CATEGORY_BITMASK)
		{
			if(a->getCategoryBitmask() == PLAYER_CATEGORY_BITMASK)
			{
				auto item = dynamic_cast<Iteam*>(b->getOwner());
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
					GameScene::SaveInGame(item);
					item->setVisible(false);
					this->removeChild(item);
				}
			}
		}
		// door detect collision
		if (a->getCategoryBitmask() == DOOR_CATEGORY_BITMASK)
		{
			if (b->getCategoryBitmask() == PLAYER_CATEGORY_BITMASK)
			{
				if(door->numberkey<=0)
					this->schedule(CC_SCHEDULE_SELECTOR(GameScene::GoToGameOver), DISPLAY_TIME_SPLASH_SCENE/2);
				else
					player->removeAction();
			}
		}
		else if (b->getCategoryBitmask() == DOOR_CATEGORY_BITMASK)
		{
			if (a->getCategoryBitmask() == PLAYER_CATEGORY_BITMASK)
			{
				if (door->numberkey <= 0)
					this->schedule(CC_SCHEDULE_SELECTOR(GameScene::GoToGameOver), DISPLAY_TIME_SPLASH_SCENE / 2);
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
			if (trap->type == 0 || trap->type == 3)
			{
				trap->setLocalZOrder(40);
				if (!player->die && b->getCategoryBitmask() == PLAYER_CATEGORY_BITMASK)
				{
					player->Playerdie();
					GameScene::checkdie();
				}
				if (b->getCategoryBitmask() == ENEMY_CATEGORY_BITMASK)
				{
					auto minion = dynamic_cast<Minions*>(b->getOwner());
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
			if (trap->type == 0  || trap->type == 3)
			{
				trap->setLocalZOrder(40);
				if (!player->die && a->getCategoryBitmask() == PLAYER_CATEGORY_BITMASK)
				{
					player->Playerdie();
					GameScene::checkdie();
				}
				if (a->getCategoryBitmask() == ENEMY_CATEGORY_BITMASK)
				{
					auto minion = dynamic_cast<Minions*>(a->getOwner());
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
			CCLOG("enemy");
			if (!player->die && b->getCategoryBitmask() == PLAYER_CATEGORY_BITMASK)
			{
				auto minion = dynamic_cast<Minions*>(a->getOwner());
				if (minion->Booldie == false)
				{
					player->Playerdie();
					GameScene::checkdie();
				}
			}
			if (b->getCategoryBitmask() == PLAYER_BG_CATEGORY_BITMASK)
			{
				auto minion = dynamic_cast<Minions*>(a->getOwner());
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
			if (!player->die && a->getCategoryBitmask() == PLAYER_CATEGORY_BITMASK)
			{
				auto minion = dynamic_cast<Minions*>(b->getOwner());
				if (minion->Booldie == false)
				{
					player->Playerdie();
					GameScene::checkdie();
				}
			}
			if (a->getCategoryBitmask() == PLAYER_BG_CATEGORY_BITMASK)
			{
				auto minion = dynamic_cast<Minions*>(b->getOwner());
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
	auto scene = GameOver::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}
void GameScene::SaveInGame(cocos2d::Node *item)
{
	def = UserDefault::getInstance();

	auto PosX = def->getFloatForKey("INGAME_PLAYERPOSX", item->getPositionX());
	auto PosY = def->getFloatForKey("INGAME_PLAYERPOSY", item->getPositionY());
	auto enegy = def->getFloatForKey("INGAME_PLAYERENEGY", canvas->enegy->getPercent());

	def->setFloatForKey("INGAME_PLAYERENEGY", canvas->enegy->getPercent());
	def->setFloatForKey("INGAME_PLAYERPOSX", item->getPositionX());
	def->setFloatForKey("INGAME_PLAYERPOSY", item->getPositionY());
	def->flush();
	
}
void GameScene::checkdie()
{
	if (player->NumHeal > 1)
		this->schedule(CC_SCHEDULE_SELECTOR(GameScene::GotoAgain), DISPLAY_TIME_SPLASH_SCENE, 0, 0);
}
void GameScene::GotoAgain(float dt)
{
	auto enegy = def->getFloatForKey("INGAME_PLAYERENEGY", canvas->enegy->getPercent());
	canvas->enegy->setPercent(enegy);
}