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
Minions::Minions(cocos2d::Scene *scene)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	MinionSprite = Sprite::create("prefap/Minions/bluebird-midflap.png");
	MinionSprite->setPosition(Vec2(visibleSize.width/2 + visibleSize.height*0.2 + origin.x, visibleSize.height*0.8));
	scene->addChild(MinionSprite,2);

	player = scene->getChildByTag(1);
	//scene->schedule(CC_SCHEDULE_SELECTOR(Minions::findPlayer), 2.0f);
}	
void Minions::findPlayer()
{
	if (MinionSprite->getPositionX() < player->getPositionX())
	{
		
		Minions::MinionsMoveRight();
		return;
	}
	if (MinionSprite->getPositionX() > player->getPositionX())
	{
		Minions::MinionsMoveLeft();
		return;
	}
	if (MinionSprite->getPositionY() < player->getPositionY())
	{
		Minions::MinionsMoveUp();
		return;
	}
	if (MinionSprite->getPositionY() > player->getPositionY())
	{
		Minions::MinionsMoveDow();
	}
}
void Minions::MinionsMoveUp()
{
	MinionSprite->setPosition(Vec2(MinionSprite->getPositionX(), MinionSprite->getPositionY() + visibleSize.height*PLAYER_SPEED));
}
void Minions::MinionsMoveDow()
{
	MinionSprite->setPosition(Vec2(MinionSprite->getPositionX(), MinionSprite->getPositionY() - visibleSize.height*PLAYER_SPEED));
}
void Minions::MinionsMoveLeft()
{
	MinionSprite->setPosition(Vec2(MinionSprite->getPositionX() - visibleSize.height*PLAYER_SPEED, MinionSprite->getPositionY()));
}
void Minions::MinionsMoveRight()
{
	MinionSprite->setPosition(Vec2(MinionSprite->getPositionX() + visibleSize.height*PLAYER_SPEED, MinionSprite->getPositionY()));
}