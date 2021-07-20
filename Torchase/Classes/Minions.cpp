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

#include "Minions.h"
#include "Definitions.h"

USING_NS_CC;

Minions::Minions(Player* playerScene, float mapspeed):  Actor("prefap/Minions/spider.png", Rect(100, 0, 100, 100))
{
	hit = false;

	traveltime = MININON_SPEED;
	player = playerScene;
	this->speed = mapspeed;
	auto EnemyBody = PhysicsBody::createBox(this->getContentSize());
	EnemyBody->setCollisionBitmask(ENEMY_COLISION_BITMASK);
	EnemyBody->setCategoryBitmask(ENEMY_CATEGORY_BITMASK);
	EnemyBody->setContactTestBitmask(ENEMY_COLISION_BITMASK);
	EnemyBody->setDynamic(false);
	this->setPhysicsBody(EnemyBody);
	boolFind = false;
	Booldie = false;
	std::string minionname = "prefap/Minions/spider.png";
	//animation
}	
Minions::Minions() : Actor("prefap/Minions/spider.png", Rect(100, 0, 100, 100))
{
	hit = false;
	traveltime = MININON_SPEED;

	auto EnemyBody = PhysicsBody::createBox(this->getContentSize()/2);
	EnemyBody->setCollisionBitmask(ENEMY_COLISION_BITMASK);
	EnemyBody->setCategoryBitmask(ENEMY_CATEGORY_BITMASK);
	EnemyBody->setContactTestBitmask(ENEMY_COLISION_BITMASK);
	EnemyBody->setDynamic(false);
	this->setPhysicsBody(EnemyBody);
	boolFind = false;
	Booldie = false;
	std::string minionname = "prefap/Minions/spider.png";
}
void Minions::findPlayer(float dt)
{
	if (goUp == false)
		return;
	this->mindPositison = this->getPosition();
	cocos2d::Vec2 point = this->getPosition();
	cocos2d::Vec2 pointup = Vec2(point.x, point.y + this->speed) - player->getPosition();
	cocos2d::Vec2 pointdow = Vec2(point.x, point.y - this->speed) - player->getPosition();
	cocos2d::Vec2 pointleft = Vec2(point.x - this->speed, point.y ) - player->getPosition();
	cocos2d::Vec2 pointright = Vec2(point.x + this->speed, point.y) - player->getPosition();
	booltro = &booltop;
	
	if (booltop == false)
	{
		pointup = pointdow;
		booltro = &booldow;
		goUp = false;
	}
	if ((abs(pointup.x) + abs(pointup.y)) > (abs(pointdow.x) + abs(pointdow.y)) && booldow)
	{
		pointup = pointdow;
		booltro = &booldow;
		goUp = false;

	}
	if ((abs(pointup.x) + abs(pointup.y)) > (abs(pointleft.x) + abs(pointleft.y)) && boolleft)
	{
		pointup = pointleft;
		booltro = &boolleft;
		goUp = false;

	}
	if ((abs(pointup.x) + abs(pointup.y)) > (abs(pointright.x) + abs(pointright.y)) && boolright)
	{
		pointup = pointright;
		booltro = &boolright;
		goUp = false;

	}
	booltop = true;
	booldow = true;
	boolleft = true;
	boolright = true;
	int mind = 2;
	if (goUp) {
		mind = 2;
	}
	else {
		if (pointup == pointleft) {
			mind = 3;
		}
		else if (pointup == pointright) {
			mind = 4;
		}
		else if (pointup == pointdow) {
			mind = 1;
		}
	}
	this->stopAllActions();
	auto moveAction = MoveTo::create(traveltime, pointup + player->getPosition());
	auto animationAction = RepeatForever::create(Animates.at(mind-1));
	auto callback = CallFunc::create([&]() {
		this->stopAllActions();
		Minions::findPlayer(1);
		});
	auto sequence = Sequence::create(moveAction, callback, nullptr);
	this->runAction(animationAction);
	this->runAction(sequence);
	goUp = true;
}
void Minions::removeAction()
{
	if (type == 1)
	{
		//Actor::removeAction();
	this->stopAllActions();
	auto reverAction = MoveTo::create(traveltime / 2, mindPositison);
	auto callback = CallFunc::create([&]() {
		this->stopAllActions();
		Minions::findPlayer(1);
	});
	auto sequence = Sequence::create(reverAction, callback, nullptr);
	this->runAction(sequence);
	*booltro = false;
	}
	if (type == 0)
	{
		this->stopAllActions();
		Booldie = true;
		this->unscheduleAllCallbacks();
		goUp = false;
		Minions::actiondie(1);
	}
}
void Minions::Roar(float dt)
{
	//this->setLocalZOrder(30);
	/*if (type == 1)
	{
		Schedule_findPlayer = CC_SCHEDULE_SELECTOR(Minions::findPlayer);
		this->schedule(Schedule_findPlayer, 1.3f, 100, 1.0f);
	}
	if (type == 0)
	{
		Schedule_findPlayer = CC_SCHEDULE_SELECTOR(Minions::findPlayerType0);
		this->schedule(Schedule_findPlayer, 1.3f, 0, 1.0f);
	}*/
}
void Minions::lightoff()
{
	//this->setLocalZOrder(20);
	goUp = false;
}
void Minions::lighton(float dt)
{
	goUp = true;
	Minions::findPlayer(1);
}
void Minions::die()
{
	Booldie = true;
	this->unscheduleAllCallbacks();
	goUp = false;
	this->schedule(CC_SCHEDULE_SELECTOR(Minions::actiondie),0.5f, 0, 0.5f);
	
}
void Minions::actiondie(float dt)
{
	this->mindPositison = this->getPosition();
	//this->setLocalZOrder(20);
	SoundManager::getInstance()->PlayMusics(HitTrap_sound, false, 0.3f);
	this->stopAllActions();
	auto animationAction = RepeatForever::create(Animates.at(4));
	this->runAction(Animates.at(4));
}
void Minions::findPlayerType0(float dt)
{
	this->stopAllActions();
	auto moveAction = MoveBy::create(traveltime/3, mindPlayer);
	auto animationAction = RepeatForever::create(Animates.at(3));
	auto callback = CallFunc::create([&]() {
		this->stopAllActions();
		Minions::findPlayerType0(1);
	});
	auto sequence = Sequence::create(moveAction, callback, nullptr);
	this->runAction(animationAction);
	this->runAction(sequence);
}
void Minions::setplayer(Player* playerScene, float mapspeed)
{
	mindPositison = this->getPosition();
	player = playerScene;
	this->speed = mapspeed;
}
void Minions::changeTravelTime(float value)
{
	traveltime = MININON_SPEED+ value;
	this->schedule(CC_SCHEDULE_SELECTOR(Player::resetTravelTime), TIME_SLOW, 0, 0);
}
void Minions::resetTravelTime(float dt)
{
	traveltime = MININON_SPEED;
}
void Minions::reset()
{
	goUp = true;
	boolFind = false;
	Booldie = false;
}