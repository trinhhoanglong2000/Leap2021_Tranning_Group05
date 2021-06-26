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
Player::Player() : Actor("prefap/Player/redbird-midflap.png")
{
	auto PlayerBody = PhysicsBody::createBox(this->getContentSize());
	PlayerBody->setCollisionBitmask(PLAYER_COLISION_BITMASK);
	PlayerBody->setContactTestBitmask(true);
	PlayerBody->setDynamic(false);
	this->setPhysicsBody(PlayerBody);
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

	this->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->setTag(1);

	this->addChild(background);


	mind = 1;
}
void Player::MoveUp()
{
	if (mind == 1)
		Actor::MoveUp();
	else
	{
		background->setPosition(+this->getBoundingBox().size.width / 2, +this->getBoundingBox().size.height / 2 + (height - thickness * 2) / 4);

		mind = 1;
		background->setRotation(0);
	}
}
void Player::MoveDow()
{
	if (mind == 2)
		Actor::MoveDow();
	else
	{
		background->setPosition(+this->getBoundingBox().size.width / 2, +this->getBoundingBox().size.height / 2 - (height - thickness * 2) / 4);

		mind = 2;
		background->setRotation(180);
	}
}
void Player::MoveLeft()
{
	if (mind == 3)
		Actor::MoveLeft();
	else
	{
		background->setPosition(+this->getBoundingBox().size.width / 2 - (width - thickness * 2) / 2, +this->getBoundingBox().size.height / 4);

		mind = 3;

		background->setRotation(-90);
	}
}
void Player::MoveRight()
{
	if (mind == 4)
		Actor::MoveRight();
	else
	{
		background->setPosition(+this->getBoundingBox().size.width / 2 + (width - thickness * 2) / 2, +this->getBoundingBox().size.height / 2);

		mind = 4;
		background->setRotation(90);
	}
}
void Player::OnOffLight()
{
	/*if (background->isVisible())
	{
		
		background->setVisible(false);
	
	}
	else
	{
		background->setVisible(true);
		
	}*/
}