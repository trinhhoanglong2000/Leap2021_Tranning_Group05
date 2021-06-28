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

#include "Player.h"
#include "Definitions.h"
#include "ui\CocosGUI.h"
#include "GameScene.h"
USING_NS_CC;
Player::Player() : Actor("prefap/Player/Player.png", Rect(360, 1, 80, 95))
{
	//auto PlayerBody = PhysicsBody::createBox(Size(25,25)*MAP_SCALE);//this->getContentSize());
	auto PlayerBody = PhysicsBody::createBox(this->getContentSize());//this->getContentSize());
	PlayerBody->setCollisionBitmask(PLAYER_COLISION_BITMASK);
	PlayerBody->setCategoryBitmask(PLAYER_CATEGORY_BITMASK);
	PlayerBody->setContactTestBitmask(PLAYER_COLISION_BITMASK);
	PlayerBody->setDynamic(false);
	this->setPhysicsBody(PlayerBody);
<<<<<<< HEAD
	
=======

	background = DrawNode::create();
	background->setVisible(false);
	Vec2 vertices[] =
	{
		Vec2(0,height),
		Vec2(width,height),
		Vec2(width,0),
		Vec2(0,0)
	};
	background->setContentSize(Size(width, height));
	background->drawPolygon(vertices, 4, Color4F(Color3B::WHITE, 0), thickness, Color4F(Color3B::BLACK, 1));
	background->setAnchorPoint(Vec2(0.5f, 0.5f));
	background->setPosition(+this->getBoundingBox().size.width / 2, +this->getBoundingBox().size.height / 2 + (height - thickness * 2) / 4);
>>>>>>> 3b8eb98cc834f7f4a283f6fd0057e7301eaeb868

	this->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->setTag(1);

	//push frame
	//Look up
	Vector<SpriteFrame*>  animFrames;
	animFrames.pushBack(SpriteFrame::create("prefap/Player/Player.png", Rect(360, 1, 80, 95)));
	animFrames.pushBack(SpriteFrame::create("prefap/Player/Player.png", Rect(480, 1, 80, 95)));
	animFrames.pushBack(SpriteFrame::create("prefap/Player/Player.png", Rect(1, 1, 80, 95)));
	animFrames.pushBack(SpriteFrame::create("prefap/Player/Player.png", Rect(120, 1, 80, 95)));
	animFrames.pushBack(SpriteFrame::create("prefap/Player/Player.png", Rect(240, 1, 80, 95)));
	stand.pushBack(animFrames.at(0));
	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
	
	Animate* animate = Animate::create(animation);
	Animates.pushBack(animate);
	//Look down
	animFrames.clear();
	animFrames.pushBack(SpriteFrame::create("prefap/Player/Player.png", Rect(360, 242, 80, 95)));
	animFrames.pushBack(SpriteFrame::create("prefap/Player/Player.png", Rect(480, 242, 80, 95)));
	animFrames.pushBack(SpriteFrame::create("prefap/Player/Player.png", Rect(1, 242, 80, 95)));
	animFrames.pushBack(SpriteFrame::create("prefap/Player/Player.png", Rect(120, 242, 80, 95)));
	animFrames.pushBack(SpriteFrame::create("prefap/Player/Player.png", Rect(240, 242, 80, 95)));
	stand.pushBack(animFrames.at(0));
	animation = Animation::createWithSpriteFrames(animFrames, 0.1f);

	animate = Animate::create(animation);
	Animates.pushBack(animate);
	//Left
	animFrames.clear();
	animFrames.pushBack(SpriteFrame::create("prefap/Player/Player.png", Rect(360, 119, 80, 95)));
	animFrames.pushBack(SpriteFrame::create("prefap/Player/Player.png", Rect(480, 119, 80, 95)));
	animFrames.pushBack(SpriteFrame::create("prefap/Player/Player.png", Rect(1, 119, 80, 95)));
	animFrames.pushBack(SpriteFrame::create("prefap/Player/Player.png", Rect(120, 119, 80, 95)));
	animFrames.pushBack(SpriteFrame::create("prefap/Player/Player.png", Rect(240, 119, 80, 95)));
	stand.pushBack(animFrames.at(0));
	animation = Animation::createWithSpriteFrames(animFrames, 0.1f);

	animate = Animate::create(animation);
	Animates.pushBack(animate);

	//right
	animFrames.clear();
	animFrames.pushBack(SpriteFrame::create("prefap/Player/Player.png", Rect(360, 359, 80, 95)));
	animFrames.pushBack(SpriteFrame::create("prefap/Player/Player.png", Rect(480, 359, 80, 95)));
	animFrames.pushBack(SpriteFrame::create("prefap/Player/Player.png", Rect(1, 359, 80, 95)));
	animFrames.pushBack(SpriteFrame::create("prefap/Player/Player.png", Rect(120, 359, 80, 95)));
	animFrames.pushBack(SpriteFrame::create("prefap/Player/Player.png", Rect(240, 359, 80, 95)));
	stand.pushBack(animFrames.at(0));
	animation = Animation::createWithSpriteFrames(animFrames, 0.1f);

	animate = Animate::create(animation);
	Animates.pushBack(animate);
	mind = 1;
	checkMove = true;
}
void Player::setBlackVisionBG(cocos2d::Size size) {
	int max = MAX(size.width, size.height);
	thickness = (max - speed)/2;
	log("%f %d %d", speed, max, thickness);

	width = max;
	height = max + (int)speed;
	
	background = DrawNode::create();
	background->setVisible(true);
	Vec2 vertices[] =
	{
		Vec2(0,height),
		Vec2(width,height),
		Vec2(width,0),
		Vec2(0,0)
	};
	background->setContentSize(Size(width, height));
	background->drawPolygon(vertices, 4, Color4F(Color3B::WHITE, 0), thickness, Color4F(Color3B::BLACK, 1));
	background->setAnchorPoint(Vec2(0.5f, 0.5f));
	background->setPosition(+this->getBoundingBox().size.width / 2, (+this->getContentSize().height +speed)/2);
	this->addChild(background);

}
void Player::MoveUp()
{
	if(checkMove)
	if (mind == 1) {
		auto moveAction = Actor::MoveUp();
		auto animationAction = RepeatForever::create(Animates.at(mind-1));
		auto callback = CallFunc::create([&]() {
			this->stopAllActions();
			this->setSpriteFrame(stand.at(mind - 1));	
		});
		auto sequence = Sequence::create(moveAction, callback,nullptr);
		this->runAction(animationAction);
		this->runAction(sequence);
		Player::setFalseMove();
	}
	else
	{
		background->setPosition(+this->getBoundingBox().size.width / 2,  +this->getBoundingBox().size.height / 2 + speed / 2);
		mind = 1;
		this->setSpriteFrame(stand.at(mind - 1));
		background->setRotation(0);
	}
}
void Player::MoveDow()
{
	if (checkMove)
	if (mind == 2) {
		auto moveAction = Actor::MoveDow();	
		auto animationAction = RepeatForever::create(Animates.at(mind - 1));
		auto callback = CallFunc::create([&]() {
			this->stopAllActions();
			this->setSpriteFrame(stand.at(mind - 1));
		});
		auto sequence = Sequence::create(moveAction, callback, nullptr);
		this->runAction(animationAction);
		this->runAction(sequence);
		Player::setFalseMove();
	}
	else
	{
		background->setPosition(+this->getBoundingBox().size.width / 2, +this->getBoundingBox().size.height / 2 - speed/2);
		mind = 2;
		this->setSpriteFrame(stand.at(mind - 1));
		background->setRotation(180);
	}
}
void Player::MoveLeft()
{
	if (checkMove)
	if (mind == 3) {
		auto moveAction = Actor::MoveLeft();
		auto animationAction = RepeatForever::create(Animates.at(mind - 1));
		auto callback = CallFunc::create([&]() {
			this->stopAllActions();
			this->setSpriteFrame(stand.at(mind - 1));
		});
		auto sequence = Sequence::create(moveAction, callback, nullptr);
		this->runAction(animationAction);
		this->runAction(sequence);
		Player::setFalseMove();
	}
	else
	{
		background->setPosition(+this->getBoundingBox().size.width / 2 - speed / 2, +this->getBoundingBox().size.height / 2);
		mind = 3;
		this->setSpriteFrame(stand.at(mind - 1));
		background->setRotation(-90);
	}
}
void Player::MoveRight()
{
	if (checkMove)
	if (mind == 4) {
		auto moveAction = Actor::MoveRight();
		auto animationAction = RepeatForever::create(Animates.at(mind - 1));
		auto callback = CallFunc::create([&]() {
			this->stopAllActions();
			this->setSpriteFrame(stand.at(mind - 1));
		});
		auto sequence = Sequence::create(moveAction, callback, nullptr);
		this->runAction(animationAction);
		this->runAction(sequence);
		Player::setFalseMove();
	}
	else
	{
		background->setPosition(+this->getBoundingBox().size.width / 2 + speed / 2, +this->getBoundingBox().size.height / 2);
		mind = 4;
		this->setSpriteFrame(stand.at(mind - 1));
		background->setRotation(90);
	}
}
void Player::OnOffLight()
{

}
void Player::setTrueMove(float dt)
{
	this->unschedule(Schedule_reverse);
	checkMove = true;
}
void Player::setFalseMove()
{
	checkMove = false;
	Schedule_reverse = CC_SCHEDULE_SELECTOR(Player::setTrueMove);
	this->schedule(Schedule_reverse, ACTOR_SPEED);
}
