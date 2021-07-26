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
#include "Minions.h"
#include "Spider.h"
#include "ui\CocosGUI.h"
#include "SoundManager.h"
USING_NS_CC;

MinionBoss::MinionBoss(Player * playerScene, float mapspeed):	Minions( playerScene, mapspeed)
{
	MinionBoss::setAnimation();
}
MinionBoss::MinionBoss() : Minions("prefap/Minions/ryuk.png", Rect(0, 0, 48, 64))
{
	midpos = -3;
	type = 2;
	MinionBoss::setAnimation();
	this->setScale(3.0f);
	enegy = ui::Slider::create();
	enegy->loadBarTexture("Slider_Backs.png");
	//enegy->loadSlidBallTextures("SliderNode_Normal.png", "SliderNode_Press.png", "SliderNode_Disable.png");
	enegy->loadProgressBarTexture("Slider_PressBars.png");
	enegy->setPosition(Vec2(this->getPositionX() + enegy->getContentSize().width / 3 * 0.4f, this->getPositionY() + this->getContentSize().height / 2.5 * 3.0f));
	enegy->setMaxPercent(10);
	enegy->setPercent(enegy->getMaxPercent());
	enegy->setScale(0.25f);
	this->addChild(enegy);
	posSpider = -2;
	//this->schedule(CC_SCHEDULE_SELECTOR(MinionBoss::atack), 2.0f,100,15.0f);
}
void MinionBoss::start()
{
	SoundManager::getInstance()->PlayMusics(Roar_sound, false, 0.5f);
	this->schedule(CC_SCHEDULE_SELECTOR(MinionBoss::atack), 2.0f);
}
void MinionBoss::atack(float dt)
{
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
	scene->addChild(minion);
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
	enegy->setPercent(enegy->getPercent() - dame);
	if (enegy->getPercent() <= 0)
		this->die();
}
void MinionBoss::setAnimation()
{
	//down
	Vector<SpriteFrame*>  animFrames;
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(0, 0, 48, 64)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(0, 0, 48, 64)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(0, 0, 48, 64)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(0, 0, 48, 64)));

	//default
	this->setSpriteFrame(animFrames.at(0));
	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f);

	Animate* animate = Animate::create(animation);
	Animates.pushBack(animate);
	animFrames.clear();

	//up
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(0, 0, 48, 64)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(0, 0, 48, 64)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(0, 0, 48, 64)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(0, 0, 48, 64)));

	animation = Animation::createWithSpriteFrames(animFrames, 0.1f);

	animate = Animate::create(animation);
	Animates.pushBack(animate);
	animFrames.clear();

	//left
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(0, 0, 48, 64)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(0, 0, 48, 64)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(0, 0, 48, 64)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(0, 0, 48, 64)));

	animation = Animation::createWithSpriteFrames(animFrames, 0.1f);

	animate = Animate::create(animation);
	Animates.pushBack(animate);
	animFrames.clear();

	//right 
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(0, 0, 48, 64)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(0, 0, 48, 64)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(0, 0, 48, 64)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(0, 0, 48, 64)));

	animation = Animation::createWithSpriteFrames(animFrames, 0.1f);

	animate = Animate::create(animation);
	Animates.pushBack(animate);
	animFrames.clear();
	goUp = true;

	// die
	std::string minionnamedie = "prefap/Minions/ryuk.png";
	animFrames.pushBack(SpriteFrame::create(minionnamedie, Rect(0, 0, 48, 64)));
	animFrames.pushBack(SpriteFrame::create(minionnamedie, Rect(0, 0, 48, 64)));
	animFrames.pushBack(SpriteFrame::create(minionnamedie, Rect(0, 0, 48, 64)));
	animFrames.pushBack(SpriteFrame::create(minionnamedie, Rect(0, 0, 48, 64)));

	animation = Animation::createWithSpriteFrames(animFrames, 0.1f);

	animate = Animate::create(animation);
	Animates.pushBack(animate);
	animFrames.clear();
}
void MinionBoss::reset()
{
	Minions::reset();
	this->setTexture("prefap/Minions/ryuk.png");
	this->setTextureRect(Rect(0, 0, 48, 64));
}
void MinionBoss::setStatus(bool checkdie)
{
	if (checkdie == true)
	{
		goUp = false;
		this->setTexture("prefap/Minions/ryuk.png");
		this->setTextureRect(Rect(0, 0, 48, 64));
	}
	else
	{
		goUp = true;
		this->setTexture("prefap/Minions/ryuk.png");
		this->setTextureRect(Rect(0, 0, 48, 64));
	}
}