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

#include "MinionBoss.h"
#include "Definitions.h"
#include "MinionManager.h"
#include "TrapManager.h"
#include "Minions.h"
#include "Spider.h"
#include "ui\CocosGUI.h"
#include "SoundManager.h"
#include"Trapthorn.h"
USING_NS_CC;

MinionBoss::MinionBoss(Player * playerScene, float mapspeed):	Minions( playerScene, mapspeed)
{
	MinionBoss::setAnimation();
}
MinionBoss::MinionBoss() : Minions("prefap/Minions/boss/cultist_priest_idle_1.png", Rect(0, 0, 200, 200))
{
	checkpower = false;
	midpos = -3;
	type = 2;
	Booldie = false;
	MinionBoss::setAnimation();
	this->setScale(1.0f);
	percentPower = 1;
	enegy = ui::Slider::create();
	enegy->loadBarTexture("Slider_Backs.png");
	//enegy->loadSlidBallTextures("SliderNode_Normal.png", "SliderNode_Press.png", "SliderNode_Disable.png");
	enegy->loadProgressBarTexture("Slider_PressBars_heal.png");
	enegy->setPosition(Vec2(this->getPositionX() + enegy->getContentSize().width / 3 * 1.5f, this->getPositionY() + this->getContentSize().height / 2.5 * 3.0f));
	enegy->setMaxPercent(10);
	enegy->setPercent(enegy->getMaxPercent());
	enegy->setScale(1.0f);
	this->addChild(enegy);

	power = ui::Slider::create();
	power->loadBarTexture("Slider_Backs.png");
	//enegy->loadSlidBallTextures("SliderNode_Normal.png", "SliderNode_Press.png", "SliderNode_Disable.png");
	power->loadProgressBarTexture("Slider_PressBars_power.png");
	power->setPosition(Vec2(this->getPositionX() + enegy->getContentSize().width / 3 * 1.5f, this->getPositionY() + this->getContentSize().height / 2.65f * 3.0f));
	power->setMaxPercent(30);
	power->setPercent(0);
	power->setScale(1.0f);
	this->addChild(power);

	posSpider = -2;
}
void MinionBoss::start()
{
	this->schedule(CC_SCHEDULE_SELECTOR(MinionBoss::plusPower), 1.0f);
	auto action = RepeatForever::create(Animates.at(0));
	this->runAction(action);
	SoundManager::getInstance()->PlayMusics(Roar_sound, false, 0.5f);
	this->schedule(CC_SCHEDULE_SELECTOR(MinionBoss::atack), 2.5f);
}
void MinionBoss::atack(float dt)
{
	if (checkpower == true)
		return;
	this->stopAllActions();
	auto callback = CallFunc::create([&]() {
		this->stopAllActions();
		auto action = RepeatForever::create(Animates.at(0));
		this->runAction(action);
	});
	auto sequence = Sequence::create(Animates.at(1), callback, nullptr);
	this->runAction(sequence);
	pos = cocos2d::RandomHelper::random_int(-2, 2);
	while (pos==midpos)
	{
		pos = cocos2d::RandomHelper::random_int(-2, 2);
	}
	midpos = pos;
	auto minion = MinionManager::getInstance()->CreateMinion(0);
	minion->setPosition(Vec2(this->getPositionX() + speed, this->getPositionY() + pos * speed));
	minion->setplayer(player,speed);
	auto spider = dynamic_cast<Spider*>(minion);
	spider->Roar(1);
	scene->addChild(minion, this->getLocalZOrder());
}
void MinionBoss::atack2(float dt)
{
	int numberTrap = RandomHelper::random_int(2, 3);
	for (int i = 0; i < numberTrap; i++)
	{
		int X = RandomHelper::random_int(-3, -1);
		int Y = RandomHelper::random_int(-2, 2);
		auto node = Sprite::create("prefap/Minions/boss/target_PNG69.png");
		node->setPosition(Vec2(this->getPositionX() + X*speed, this->getPositionY() + Y * speed));
		node->setScale(0.5f);
		auto fadeOut = FadeTo::create(0.1f, 10);
		auto fadeIn = FadeTo::create(2, 255);
		auto sequence = Sequence::create(fadeOut, fadeIn, nullptr);
		scene->addChild(node,this->getLocalZOrder());
		node->runAction(sequence);
		Alltaget.pushBack(node);
	}
	this->schedule(CC_SCHEDULE_SELECTOR(MinionBoss::addtrap), 2.0f, 0, 0);
}
void MinionBoss::addtrap(float dt)
{
	for (int i = 0; i < Alltaget.size(); i++)
	{
		auto trap = TrapManager::getInstance()->CreateTrap(0);
		trap->setPosition(Alltaget.at(i)->getPosition());
		scene->addChild(trap, this->getLocalZOrder());
		auto trapthorn = dynamic_cast<Trapthorn*>(trap);
		trapthorn->atack();
		AllTrap.pushBack(trap);
		Alltaget.at(i)->removeFromParent();
	}
	Alltaget.clear();
}
void MinionBoss::plusPower(float dt)
{
	power->setPercent(power->getPercent()+ percentPower);
	if (power->getPercent() >= power->getMaxPercent() && checkpower == false)
	{
		SoundManager::getInstance()->PlayMusics(Roar_sound, false, 0.5f);
		this->unscheduleAllCallbacks();
		checkpower = true;
		this->stopAllActions();
		auto callback = CallFunc::create([&]() {
			this->stopAllActions();
			auto action = RepeatForever::create(Animates.at(0));
			this->runAction(action);
			this->schedule(CC_SCHEDULE_SELECTOR(MinionBoss::atack), 2.0f,100,2.0f);
			this->schedule(CC_SCHEDULE_SELECTOR(MinionBoss::atack2), 3.0f, 100, 2.0f);
			checkpower = false;
		});
		auto sequence = Sequence::create(Animates.at(4), callback, nullptr);
		this->runAction(sequence);
		this->unscheduleAllCallbacks();
	}
}
void MinionBoss::Roar(float dt)
{
	
}
void MinionBoss::CreateMinion(float dt)
{
	auto minion = MinionManager::getInstance()->CreateMinion(0);

}
void MinionBoss::reduceEnegy(float dame)
{
	if (Booldie == true)
		return;
	if (checkpower == true)
		return;
	enegy->setPercent(enegy->getPercent() - dame);
	power->setPercent(power->getPercent() + 3);
	if (enegy->getPercent() <= 0 )
	{
		SoundManager::getInstance()->PlayMusics(SHADOWDIE, false, 0.5f);
		this->stopAllActions();
		auto callback = CallFunc::create([&]() {
			this->stopAllActions();
			Booldie = true;
		});
		auto sequence = Sequence::create(Animates.at(3), callback, nullptr);
		this->runAction(sequence);
		this->unscheduleAllCallbacks();
	}
	else
	{
		if (Booldie == true)
			return;
		this->stopAllActions();
		auto callback = CallFunc::create([&]() {
			this->stopAllActions();
			auto action = RepeatForever::create(Animates.at(0));
			this->runAction(action);
			
		});
		auto sequence = Sequence::create(Animates.at(2), callback, nullptr);
		this->runAction(sequence);
	}
}
void MinionBoss::setAnimation()
{
	//idle
	Vector<SpriteFrame*>  animFrames;
	animFrames.pushBack(SpriteFrame::create("prefap/Minions/boss/cultist_priest_idle_1.png", Rect(0, 0, 200, 200)));
	animFrames.pushBack(SpriteFrame::create("prefap/Minions/boss/cultist_priest_idle_2.png", Rect(0, 0, 200, 200)));
	animFrames.pushBack(SpriteFrame::create("prefap/Minions/boss/cultist_priest_idle_3.png", Rect(0, 0, 200, 200)));
	animFrames.pushBack(SpriteFrame::create("prefap/Minions/boss/cultist_priest_idle_4.png", Rect(0, 0, 200, 200)));
	animFrames.pushBack(SpriteFrame::create("prefap/Minions/boss/cultist_priest_idle_5.png", Rect(0, 0, 200, 200)));

	//default
	this->setSpriteFrame(animFrames.at(0));
	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f);

	Animate* animate = Animate::create(animation);
	Animates.pushBack(animate);
	animFrames.clear();

	//atack
	animFrames.pushBack(SpriteFrame::create("prefap/Minions/boss/cultist_priest_attack_1.png", Rect(0, 0, 200, 200)));
	animFrames.pushBack(SpriteFrame::create("prefap/Minions/boss/cultist_priest_attack_2.png", Rect(0, 0, 200, 200)));
	animFrames.pushBack(SpriteFrame::create("prefap/Minions/boss/cultist_priest_attack_3.png", Rect(0, 0, 200, 200)));
	animFrames.pushBack(SpriteFrame::create("prefap/Minions/boss/cultist_priest_attack_4.png", Rect(0, 0, 200, 200)));
	animFrames.pushBack(SpriteFrame::create("prefap/Minions/boss/cultist_priest_attack_5.png", Rect(0, 0, 200, 200)));

	animation = Animation::createWithSpriteFrames(animFrames, 0.07f);

	animate = Animate::create(animation);
	Animates.pushBack(animate);
	animFrames.clear();

	//hit
	animFrames.pushBack(SpriteFrame::create("prefap/Minions/boss/cultist_priest_takehit_2.png", Rect(0, 0, 200, 200)));
	animFrames.pushBack(SpriteFrame::create("prefap/Minions/boss/cultist_priest_takehit_1.png", Rect(0, 0, 200, 200)));
	animFrames.pushBack(SpriteFrame::create("prefap/Minions/boss/cultist_priest_takehit_3.png", Rect(0, 0, 200, 200)));
	animFrames.pushBack(SpriteFrame::create("prefap/Minions/boss/cultist_priest_takehit_1.png", Rect(0, 0, 200, 200)));
	animFrames.pushBack(SpriteFrame::create("prefap/Minions/boss/cultist_priest_takehit_4.png", Rect(0, 0, 200, 200)));

	animation = Animation::createWithSpriteFrames(animFrames, 0.07f);

	animate = Animate::create(animation);
	Animates.pushBack(animate);
	animFrames.clear();

	//die
	animFrames.pushBack(SpriteFrame::create("prefap/Minions/boss/cultist_priest_die_1.png", Rect(0, 0, 200, 200)));
	animFrames.pushBack(SpriteFrame::create("prefap/Minions/boss/cultist_priest_die_2.png", Rect(0, 0, 200, 200)));
	animFrames.pushBack(SpriteFrame::create("prefap/Minions/boss/cultist_priest_die_3.png", Rect(0, 0, 200, 200)));
	animFrames.pushBack(SpriteFrame::create("prefap/Minions/boss/cultist_priest_die_4.png", Rect(0, 0, 200, 200)));
	animFrames.pushBack(SpriteFrame::create("prefap/Minions/boss/cultist_priest_die_5.png", Rect(0, 0, 200, 200)));


	animation = Animation::createWithSpriteFrames(animFrames, 0.1f);

	animate = Animate::create(animation);
	Animates.pushBack(animate);
	animFrames.clear();
	goUp = true;

	// power
	std::string minionnamedie = "prefap/Minions/ryuk.png";
	animFrames.pushBack(SpriteFrame::create("prefap/Minions/boss/cultist_priest_Power_3.png", Rect(0, 0, 200, 200)));
	animFrames.pushBack(SpriteFrame::create("prefap/Minions/boss/cultist_priest_Power_3.png", Rect(0, 0, 200, 200)));
	animFrames.pushBack(SpriteFrame::create("prefap/Minions/boss/cultist_priest_Power_2.png", Rect(0, 0, 200, 200)));
	animFrames.pushBack(SpriteFrame::create("prefap/Minions/boss/cultist_priest_Power_2.png", Rect(0, 0, 200, 200)));
	animFrames.pushBack(SpriteFrame::create("prefap/Minions/boss/cultist_priest_Power_5.png", Rect(0, 0, 200, 200)));
	animFrames.pushBack(SpriteFrame::create("prefap/Minions/boss/cultist_priest_Power_5.png", Rect(0, 0, 200, 200)));
	animFrames.pushBack(SpriteFrame::create("prefap/Minions/boss/cultist_priest_Power_4.png", Rect(0, 0, 200, 200)));
	animFrames.pushBack(SpriteFrame::create("prefap/Minions/boss/cultist_priest_Power_4.png", Rect(0, 0, 200, 200)));
	animFrames.pushBack(SpriteFrame::create("prefap/Minions/boss/cultist_priest_Power_1.png", Rect(0, 0, 200, 200)));
	animFrames.pushBack(SpriteFrame::create("prefap/Minions/boss/cultist_priest_Power_1.png", Rect(0, 0, 200, 200)));
	animFrames.pushBack(SpriteFrame::create("prefap/Minions/boss/cultist_priest_Power_1.png", Rect(0, 0, 200, 200)));
	animFrames.pushBack(SpriteFrame::create("prefap/Minions/boss/cultist_priest_Power_1.png", Rect(0, 0, 200, 200)));
	animation = Animation::createWithSpriteFrames(animFrames, 0.2f);

	animate = Animate::create(animation);
	Animates.pushBack(animate);
	animFrames.clear();
}
void MinionBoss::reset()
{
	Minions::reset();
	this->setTexture("prefap/Minions/boss/cultist_priest_idle_1.png");
	this->setTextureRect(Rect(0, 0, 200, 200));
	enegy->setPercent(enegy->getMaxPercent());
	power->setPercent(0);
}
void MinionBoss::setStatus(bool checkdie)
{
	if (checkdie == true)
	{
		goUp = false;
		this->setTexture("prefap/Minions/boss/cultist_priest_die_5.png");
		this->setTextureRect(Rect(0, 0, 200, 200));
	}
	else
	{
		goUp = true;
		this->setTexture("prefap/Minions/boss/cultist_priest_idle_1.png");
		this->setTextureRect(Rect(0, 0, 200, 200));
	}
}