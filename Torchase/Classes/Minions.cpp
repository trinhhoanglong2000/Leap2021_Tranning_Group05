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
Minions::Minions(Player* playerScene) : Actor("prefap/Minions/spider.jpg", Rect(100, 0, 100, 100))
{
	player = playerScene;

	auto EnemyBody = PhysicsBody::createBox(this->getContentSize());
	EnemyBody->setCollisionBitmask(ENEMY_COLISION_BITMASK);
	EnemyBody->setCategoryBitmask(ENEMY_CATEGORY_BITMASK);
	EnemyBody->setContactTestBitmask(ENEMY_COLISION_BITMASK);
	EnemyBody->setDynamic(false);
	this->setPhysicsBody(EnemyBody);

	this->setPosition(Vec2(visibleSize.width / 2 + visibleSize.height*0.2 + origin.x, visibleSize.height*0.8));

	boolFind = false;

	//animation
	if (type == 0) {

		//down
		Vector<SpriteFrame*>  animFrames;
		animFrames.pushBack(SpriteFrame::create("prefap/Minions/spider.jpg", Rect(100, 0, 100, 100)));
		animFrames.pushBack(SpriteFrame::create("prefap/Minions/spider.jpg", Rect(0, 0, 100, 100)));
		animFrames.pushBack(SpriteFrame::create("prefap/Minions/spider.jpg", Rect(100, 0, 100, 100)));
		animFrames.pushBack(SpriteFrame::create("prefap/Minions/spider.jpg", Rect(0, 0, 100, 100)));
		animFrames.pushBack(SpriteFrame::create("prefap/Minions/spider.jpg", Rect(100, 0, 100, 100)));
		animFrames.pushBack(SpriteFrame::create("prefap/Minions/spider.jpg", Rect(200, 0, 100, 100)));

		
		Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f);

		Animate* animate = Animate::create(animation);
		Animates.pushBack(animate);
		//up
		animFrames.pushBack(SpriteFrame::create("prefap/Minions/spider.jpg", Rect(100, 300, 100, 100)));
		animFrames.pushBack(SpriteFrame::create("prefap/Minions/spider.jpg", Rect(0,   300, 100, 100)));
		animFrames.pushBack(SpriteFrame::create("prefap/Minions/spider.jpg", Rect(100, 300, 100, 100)));
		animFrames.pushBack(SpriteFrame::create("prefap/Minions/spider.jpg", Rect(0,   300, 100, 100)));
		animFrames.pushBack(SpriteFrame::create("prefap/Minions/spider.jpg", Rect(100, 300, 100, 100)));
		animFrames.pushBack(SpriteFrame::create("prefap/Minions/spider.jpg", Rect(200, 300, 100, 100)));


		animation = Animation::createWithSpriteFrames(animFrames, 0.1f);

		animate = Animate::create(animation);
		Animates.pushBack(animate);
		//left
		animFrames.pushBack(SpriteFrame::create("prefap/Minions/spider.jpg", Rect(100, 100, 100, 100)));
		animFrames.pushBack(SpriteFrame::create("prefap/Minions/spider.jpg", Rect(0,   100, 100, 100)));
		animFrames.pushBack(SpriteFrame::create("prefap/Minions/spider.jpg", Rect(100, 100, 100, 100)));
		animFrames.pushBack(SpriteFrame::create("prefap/Minions/spider.jpg", Rect(0,   100, 100, 100)));
		animFrames.pushBack(SpriteFrame::create("prefap/Minions/spider.jpg", Rect(100, 100, 100, 100)));
		animFrames.pushBack(SpriteFrame::create("prefap/Minions/spider.jpg", Rect(200, 100, 100, 100)));


		animation = Animation::createWithSpriteFrames(animFrames, 0.1f);

		animate = Animate::create(animation);
		Animates.pushBack(animate);
		//right 
		animFrames.pushBack(SpriteFrame::create("prefap/Minions/spider.jpg", Rect(100, 200, 100, 100)));
		animFrames.pushBack(SpriteFrame::create("prefap/Minions/spider.jpg", Rect(0, 200, 100, 100)));
		animFrames.pushBack(SpriteFrame::create("prefap/Minions/spider.jpg", Rect(100, 200, 100, 100)));
		animFrames.pushBack(SpriteFrame::create("prefap/Minions/spider.jpg", Rect(0, 200, 100, 100)));
		animFrames.pushBack(SpriteFrame::create("prefap/Minions/spider.jpg", Rect(100, 200, 100, 100)));
		animFrames.pushBack(SpriteFrame::create("prefap/Minions/spider.jpg", Rect(200, 200, 100, 100)));


		animation = Animation::createWithSpriteFrames(animFrames, 0.1f);

		animate = Animate::create(animation);
		Animates.pushBack(animate);

	}
}	
void Minions::findPlayer(float dt)
{
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
	}
	if ((abs(pointup.x) + abs(pointup.y)) > (abs(pointdow.x) + abs(pointdow.y)) && booldow)
	{
		pointup = pointdow;
		booltro = &booldow;
	}
	if ((abs(pointup.x) + abs(pointup.y)) > (abs(pointleft.x) + abs(pointleft.y)) && boolleft)
	{
		pointup = pointleft;
		booltro = &boolleft;
	}
	if ((abs(pointup.x) + abs(pointup.y)) > (abs(pointright.x) + abs(pointright.y)) && boolright)
	{
		pointup = pointright;
		booltro = &boolright;
	}
	booltop = true;
	booldow = true;
	boolleft = true;
	boolright = true;
	
	auto moveAction = MoveTo::create(MININON_SPEED, pointup + player->getPosition());
	this->runAction(moveAction);
}
void Minions::removeAction()
{
	Actor::removeAction();
	*booltro = false;
}
void Minions::checkfindPlayer(float dt)
{
	cocos2d::Vec2 pointup = this->getPosition() - player->getPosition();
	if (abs(pointup.x) + abs(pointup.y) <= speed + speed / 3 && boolFind == false)
	{
		pointup = Vec2(pointup.x - 20, pointup.y - 20);
		if (pointup.x < 0 && pointup.y >0 && player->background->getRotation() == 0)
		{
			Minions::setfindtrue();
		}
		if (pointup.x < 0 && pointup.y < 0 && player->background->getRotation() == 180)
		{
			Minions::setfindtrue();
		}
		if (pointup.x > 0 && pointup.y < 0 && player->background->getRotation() == 90)
		{
			Minions::setfindtrue();
		}
		if (pointup.x > 0 && pointup.y > 0 && player->background->getRotation() == 270)
		{
			Minions::setfindtrue();
		}
	}
}
void Minions::setfindtrue()
{
	//this->unschedule(Schedule_CheckfindPlayer);
	Minions::findPlayer(1);
	Schedule_findPlayer = CC_SCHEDULE_SELECTOR(Minions::findPlayer);
	this->schedule(Schedule_findPlayer, 1.0f);
	boolFind = true;
}