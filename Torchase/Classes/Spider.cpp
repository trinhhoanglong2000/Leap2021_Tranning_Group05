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

#include "Spider.h"
#include "Definitions.h"

USING_NS_CC;




Spider::Spider(Player * playerScene, float mapspeed):	Minions( playerScene, mapspeed)
{
	Spider::setAnimation();

}
Spider::Spider() : Minions()
{
	Spider::setAnimation();
	
}
void Spider::Roar(float dt)
{
	this->setLocalZOrder(35);
	lazer->setVisible(true);
	boolFind = true;
	//Minions::findPlayer(1);
	this->schedule(CC_SCHEDULE_SELECTOR(Spider::stare), 0.1f);
}
void Spider::stare(float dt)
{
	if (numstare <= 0)
	{
		numstare = 20;
		this->schedule(CC_SCHEDULE_SELECTOR(Spider::actionLazer), 0.1f);
		this->unschedule(CC_SCHEDULE_SELECTOR(Spider::stare));
	}
	else
	{
		
		numstare--;
		cocos2d::Vec2 *pointX = new Vec2(0, -30);
		cocos2d::Vec2 *pointY = new Vec2(player->getPositionX() - this->getPositionX(), player->getPositionY() - this->getPositionY());
		mindPlayer = Vec2(pointY->x,pointY->y);
		float s = (pointX->x * pointY->x + pointX->y * pointY->y) / (sqrt(pointX->x*pointX->x + pointX->y*pointX->y)*sqrt(pointY->x*pointY->x + pointY->y*pointY->y));
		//s = 90 * (s+1);
		/*if (player->getPositionX() > this->getPositionX())
			s = -s;*/
		auto radian = acos(s);
		radian = radian * 180 / 3.141592;
		this->setRotation(radian);
	}
	
}
void Spider::actionLazer(float dt)
{
	if (numlazer <= 0)
	{
		lazer->setVisible(false);
		numlazer = 15;
		Schedule_findPlayer = CC_SCHEDULE_SELECTOR(Minions::findPlayerType0);
		this->schedule(Schedule_findPlayer, 0.2f, 0, 0);
		this->unschedule(CC_SCHEDULE_SELECTOR(Spider::actionLazer));
	}
	else
	{
		numlazer--;
		if (lazer->isVisible() == true)
			lazer->setVisible(false);
		else
			lazer->setVisible(true);
	}
}
void Spider::setAnimation()
{
	lazer = Sprite::create("prefap/Minions/lazer.png");
	lazer->setScale(0.6f);
	lazer->setPosition(this->getContentSize().width / 2, -this->getContentSize().height*2.0f);
	this->addChild(lazer);
	//down
	type = 0;
	Vector<SpriteFrame*>  animFrames;
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(100, 0, 100, 100)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(0, 0, 100, 100)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(100, 0, 100, 100)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(0, 0, 100, 100)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(100, 0, 100, 100)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(200, 0, 100, 100)));


	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f);

	Animate* animate = Animate::create(animation);
	Animates.pushBack(animate);
	animFrames.clear();

	//up
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(100, 300, 100, 100)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(0, 300, 100, 100)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(100, 300, 100, 100)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(0, 300, 100, 100)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(100, 300, 100, 100)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(200, 300, 100, 100)));

	animation = Animation::createWithSpriteFrames(animFrames, 0.1f);

	animate = Animate::create(animation);
	Animates.pushBack(animate);
	animFrames.clear();

	//left
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(100, 100, 100, 100)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(0, 100, 100, 100)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(100, 100, 100, 100)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(0, 100, 100, 100)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(100, 100, 100, 100)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(200, 100, 100, 100)));

	animation = Animation::createWithSpriteFrames(animFrames, 0.1f);

	animate = Animate::create(animation);
	Animates.pushBack(animate);
	animFrames.clear();

	//right 
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(100, 200, 100, 100)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(0, 200, 100, 100)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(100, 200, 100, 100)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(0, 200, 100, 100)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(100, 200, 100, 100)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(200, 200, 100, 100)));

	animation = Animation::createWithSpriteFrames(animFrames, 0.1f);

	animate = Animate::create(animation);
	Animates.pushBack(animate);
	animFrames.clear();
	goUp = true;

	
	// die
	std::string minionnamedie = "prefap/Minions/spiderDie.png";
	animFrames.pushBack(SpriteFrame::create(minionnamedie, Rect(0, 0, 100, 100)));
	animFrames.pushBack(SpriteFrame::create(minionnamedie, Rect(100, 0, 100, 100)));
	animFrames.pushBack(SpriteFrame::create(minionnamedie, Rect(200, 0, 100, 100)));

	animation = Animation::createWithSpriteFrames(animFrames, 0.1f);

	animate = Animate::create(animation);
	Animates.pushBack(animate);
	animFrames.clear();
}
void Spider::reset()
{
	Minions::reset();
	lazer->setVisible(false);
	this->setTexture("prefap/Minions/spider.png");
	this->setTextureRect(Rect(100, 0, 100, 100));
}
void Spider::setStatus(bool checkdie)
{
	if (checkdie == true)
	{
		goUp = false;
		this->setTexture("prefap/Minions/spiderDie.png");
		this->setTextureRect(Rect(200, 0, 100, 100));
	}
	else
	{
		goUp = true;
		this->setTexture("prefap/Minions/spider.png");
		this->setTextureRect(Rect(100, 0, 100, 100));
	}
}