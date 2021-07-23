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

#include "TrapRock.h"
#include "Definitions.h"
#include "ui\CocosGUI.h"
#include "Actor.h"
#include "Trap.h"

USING_NS_CC;
TrapRock::TrapRock() : Trap("prefap/trap/Trap_Rock.png", Rect(0, 0, 51, 51)) {

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	type = 3;
	this->setScale(2.0f);
	checkmove = 3;
	Vector<SpriteFrame*>  animFrames;

	animFrames.pushBack(SpriteFrame::create("prefap/trap/Trap_Rock.png", Rect(0, 0, 51, 51)));
	animFrames.pushBack(SpriteFrame::create("prefap/trap/Trap_Rock.png", Rect(51, 0, 51, 51)));
	animFrames.pushBack(SpriteFrame::create("prefap/trap/Trap_Rock.png", Rect(102, 0, 51, 51)));
	animFrames.pushBack(SpriteFrame::create("prefap/trap/Trap_Rock.png", Rect(153, 0, 51, 51)));
	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
	Animate* animate = Animate::create(animation);
	_Animation.pushBack(animate);

	Vector<SpriteFrame*>  animFramesOut;
	animFramesOut.pushBack(SpriteFrame::create("prefap/trap/Trap_Rock.png", Rect(153, 0, 51, 51)));
	animFramesOut.pushBack(SpriteFrame::create("prefap/trap/Trap_Rock.png", Rect(102, 0, 51, 51)));
	animFramesOut.pushBack(SpriteFrame::create("prefap/trap/Trap_Rock.png", Rect(51, 0, 51, 51)));
	animFramesOut.pushBack(SpriteFrame::create("prefap/trap/Trap_Rock.png", Rect(0, 0, 51, 51)));
	Animation* animations = Animation::createWithSpriteFrames(animFramesOut, 0.2f);
	Animate* animates = Animate::create(animations);
	_AnimationOut.pushBack(animates);
	this->schedule(CC_SCHEDULE_SELECTOR(TrapRock::atack), 1.5f,0,0);
	//TrapRock::atack(1);
}
TrapRock::TrapRock(std::string name) {

	this->initWithFile(name);
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
}
TrapRock::TrapRock(std::string filename, cocos2d::Rect rect)
{
	this->initWithFile(filename,rect);
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
}
void TrapRock::atack(float dt)
{
	if (checkmove == 1)
	{
		auto moveAction = Actor::MoveRight();
		auto animationAction = RepeatForever::create(_Animation.at(0));
		auto callback = CallFunc::create([&]() {
			this->stopAllActions();
			TrapRock::atack(1);
		});
		auto sequence = Sequence::create(moveAction, callback, nullptr);
		this->runAction(animationAction);
		this->runAction(sequence);

	}
	if (checkmove == 2)
	{
		auto moveAction = Actor::MoveLeft();
		auto animationAction = RepeatForever::create(_AnimationOut.at(0));
		auto callback = CallFunc::create([&]() {
			this->stopAllActions();
			TrapRock::atack(1);
		});
		auto sequence = Sequence::create(moveAction, callback, nullptr);
		this->runAction(animationAction);
		this->runAction(sequence);

	}
	if (checkmove == 3)
	{
		auto moveAction = Actor::MoveUp();
		auto animationAction = RepeatForever::create(_Animation.at(0));
		auto callback = CallFunc::create([&]() {
			this->stopAllActions();
			TrapRock::atack(1);
		});
		auto sequence = Sequence::create(moveAction, callback, nullptr);
		this->runAction(animationAction);
		this->runAction(sequence);
			
	}
	if (checkmove == 4)
	{
		auto moveAction = Actor::MoveDow();
		auto animationAction = RepeatForever::create(_AnimationOut.at(0));
		auto callback = CallFunc::create([&]() {
			this->stopAllActions();
			TrapRock::atack(1);
		});
		auto sequence = Sequence::create(moveAction, callback, nullptr);
		this->runAction(animationAction);
		this->runAction(sequence);
	}
	
}
void TrapRock::setspeed(float speedScene)
{
	traveltime = ACTOR_SPEED;
	speed = speedScene;
	//TrapRock::atack(1);
}
void TrapRock::removeTrap()
{
	this->stopAllActions();
	switch (checkmove)
	{
	case 1:
	{
		checkmove = 2;
		break;
	}
	case 2:
	{
		checkmove = 1;
		break;
	}
	case 3:
	{
		checkmove = 4;
		break;
	}
	case 4:
	{
		checkmove = 3;
		break;
	}
	default:
		break;
	}
	TrapRock::atack(1);
}