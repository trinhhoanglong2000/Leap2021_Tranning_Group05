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

#include "Actor.h"
#include "Definitions.h"

USING_NS_CC;

Actor::Actor(std::string name) {

	this->initWithFile(name);
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
}
void Actor::MoveUp()
{
	 moveAction = MoveTo::create(ACTOR_SPEED,Vec2(this->getPositionX(), this->getPositionY() + speed));
	this->runAction(moveAction);
	//this->setPosition(Vec2(this->getPositionX(), this->getPositionY() + visibleSize.height * PLAYER_SPEED));

}
void Actor::MoveDow()
{
	 moveAction = MoveTo::create(ACTOR_SPEED, Vec2(this->getPositionX(), this->getPositionY() - speed));
	this->runAction(moveAction);
	//this->setPosition(Vec2(this->getPositionX(), this->getPositionY() - visibleSize.height * PLAYER_SPEED));
}
void Actor::MoveLeft()
{
	 moveAction = MoveTo::create(ACTOR_SPEED, Vec2(this->getPositionX()  - speed, this->getPositionY()));
	this->runAction(moveAction);
	//this->setPosition(Vec2(this->getPositionX() - visibleSize.height * PLAYER_SPEED, this->getPositionY()));
}
void Actor::MoveRight()
{
	 moveAction = MoveTo::create(ACTOR_SPEED, Vec2(this->getPositionX() + speed, this->getPositionY()));
	this->runAction(moveAction);
	//this->setPosition(Vec2(this->getPositionX() + visibleSize.height * PLAYER_SPEED, this->getPositionY()));
}
void Actor::removeAction(cocos2d::Vec2 here)
{
	this->stopAction(moveAction);
	auto reverAction = MoveTo::create(ACTOR_SPEED/2, here);
	this->runAction(reverAction);
}