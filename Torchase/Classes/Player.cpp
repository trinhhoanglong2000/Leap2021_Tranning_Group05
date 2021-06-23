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
USING_NS_CC;

Player::Player(cocos2d::Scene *scene)
{

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	PlayerSprite = Sprite::create("prefap/Player/redbird-midflap.png");
	PlayerSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	scene->addChild(PlayerSprite);

	auto ButtonUp = ui::Button::create("prefap/Gui/Play-8.png");
	auto ButtonDow = ui::Button::create("prefap/Gui/Play-8.png");
	auto ButtonLeft = ui::Button::create("prefap/Gui/Play-8.png");
	auto ButtonRight = ui::Button::create("prefap/Gui/Play-8.png");

	ButtonUp->setScale(BUTTON_SCALE);
	ButtonDow->setScale(BUTTON_SCALE);
	ButtonLeft->setScale(BUTTON_SCALE);
	ButtonRight->setScale(BUTTON_SCALE);

	ButtonUp->setPosition(Vec2(visibleSize.width / 5 + origin.x, visibleSize.height / 5 + origin.y + ButtonUp->getContentSize().height*BUTTON_SCALE));
	ButtonUp->addTouchEventListener(CC_CALLBACK_2(Player::MoveUp, this));
	scene->addChild(ButtonUp);

	ButtonDow->setPosition(Vec2(visibleSize.width / 5 + origin.x, visibleSize.height / 5 + origin.y - ButtonUp->getContentSize().height*BUTTON_SCALE));
	ButtonDow->addTouchEventListener(CC_CALLBACK_2(Player::MoveDow, this));
	scene->addChild(ButtonDow);

	ButtonLeft->setPosition(Vec2(visibleSize.width / 5+ origin.x - ButtonLeft->getContentSize().width*BUTTON_SCALE, visibleSize.height / 5 + origin.y));
	ButtonLeft->addTouchEventListener(CC_CALLBACK_2(Player::MoveLeft, this));
	scene->addChild(ButtonLeft);

	ButtonRight->setPosition(Vec2(visibleSize.width / 5 + origin.x + ButtonLeft->getContentSize().width*BUTTON_SCALE, visibleSize.height / 5 + origin.y));
	ButtonRight->addTouchEventListener(CC_CALLBACK_2(Player::MoveRight, this));
	scene->addChild(ButtonRight);
}	
void Player::MoveUp(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType Type)
{
	switch (Type)
	{
	case ui::Widget::TouchEventType::ENDED:
	{
		PlayerSprite->setPosition(Vec2(PlayerSprite->getPositionX(), PlayerSprite->getPositionY() + visibleSize.height*PLAYER_SPEED));
		break;
	}
	default:
		break;
	}
}
void Player::MoveDow(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType Type)
{
	switch (Type)
	{
	case ui::Widget::TouchEventType::ENDED:
	{
		PlayerSprite->setPosition(Vec2(PlayerSprite->getPositionX(), PlayerSprite->getPositionY() - visibleSize.height*PLAYER_SPEED));
		break;
	}
	default:
		break;
	}
}
void Player::MoveLeft(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType Type)
{
	switch (Type)
	{
	case ui::Widget::TouchEventType::ENDED:
	{
		PlayerSprite->setPosition(Vec2(PlayerSprite->getPositionX() - visibleSize.height*PLAYER_SPEED, PlayerSprite->getPositionY()));
		break;
	}
	default:
		break;
	}
}
void Player::MoveRight(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType Type)
{
	switch (Type)
	{
	case ui::Widget::TouchEventType::ENDED:
	{
		PlayerSprite->setPosition(Vec2(PlayerSprite->getPositionX() + visibleSize.height*PLAYER_SPEED, PlayerSprite->getPositionY()));
		break;
	}
	default:
		break;
	}
}