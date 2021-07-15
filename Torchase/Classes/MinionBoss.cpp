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
#include "ui\CocosGUI.h"
USING_NS_CC;

MinionBoss::MinionBoss(Player * playerScene, float mapspeed):	Minions( playerScene, mapspeed)
{
	MinionBoss::setAnimation();
}
MinionBoss::MinionBoss() : Minions()
{
	MinionBoss::setAnimation();

	enegy = ui::Slider::create();
	enegy->loadBarTexture("Slider_Back.png");
	//enegy->loadSlidBallTextures("SliderNode_Normal.png", "SliderNode_Press.png", "SliderNode_Disable.png");
	enegy->loadProgressBarTexture("Slider_PressBar.png");
	enegy->setPosition(Vec2(this->getPositionX() + enegy->getContentSize().width / 3 * 0.25f, this->getPositionY() + this->getContentSize().height / 2.5 * 3.0f));
	enegy->setMaxPercent(10);
	enegy->setPercent(enegy->getMaxPercent());
	enegy->setScale(0.25f);

	this->addChild(enegy);
	enegy->setVisible(false);
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
	type = 2;
	//down
	Vector<SpriteFrame*>  animFrames;
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(0, 0, 100, 150)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(100, 0, 100, 150)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(200, 0, 100, 150)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(300, 0, 100, 150)));

	//default
	this->setSpriteFrame(animFrames.at(0));
	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f);

	Animate* animate = Animate::create(animation);
	Animates.pushBack(animate);
	animFrames.clear();

	//up
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(0, 450, 100, 150)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(100, 450, 100, 150)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(200, 450, 100, 150)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(300, 450, 100, 150)));

	animation = Animation::createWithSpriteFrames(animFrames, 0.1f);

	animate = Animate::create(animation);
	Animates.pushBack(animate);
	animFrames.clear();

	//left
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(0, 150, 100, 150)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(100, 150, 100, 150)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(200, 150, 100, 150)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(300, 150, 100, 150)));

	animation = Animation::createWithSpriteFrames(animFrames, 0.1f);

	animate = Animate::create(animation);
	Animates.pushBack(animate);
	animFrames.clear();

	//right 
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(0, 300, 100, 150)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(100, 300, 100, 150)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(200, 300, 100, 150)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(300, 300, 100, 150)));

	animation = Animation::createWithSpriteFrames(animFrames, 0.1f);

	animate = Animate::create(animation);
	Animates.pushBack(animate);
	animFrames.clear();
	goUp = true;

	// die
	std::string minionnamedie = "prefap/Minions/ShadowDie.png";
	animFrames.pushBack(SpriteFrame::create(minionnamedie, Rect(0, 0, 144, 152)));
	animFrames.pushBack(SpriteFrame::create(minionnamedie, Rect(144, 0, 144, 152)));
	animFrames.pushBack(SpriteFrame::create(minionnamedie, Rect(288, 0, 144, 152)));
	animFrames.pushBack(SpriteFrame::create(minionnamedie, Rect(432, 0, 144, 152)));

	animation = Animation::createWithSpriteFrames(animFrames, 0.1f);

	animate = Animate::create(animation);
	Animates.pushBack(animate);
	animFrames.clear();
}
void MinionBoss::reset()
{
	Minions::reset();
	this->setTexture("prefap/Minions/Shadow.png");
	this->setTextureRect(Rect(100, 0, 100, 150));
}
void MinionBoss::setStatus(bool checkdie)
{
	if (checkdie == true)
	{
		goUp = false;
		this->setTexture("prefap/Minions/ShadowDie.png");
		this->setTextureRect(Rect(432, 0, 144, 152));
	}
	else
	{
		goUp = true;
		this->setTexture("prefap/Minions/Shadow.png");
		this->setTextureRect(Rect(100, 0, 100, 150));
	}
}