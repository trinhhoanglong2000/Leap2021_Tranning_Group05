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

#include "Canvas.h"
#include "Definitions.h"
#include "ui\CocosGUI.h"
#include "GameScene.h"
USING_NS_CC;
Canvas::Canvas(Player *playerScene, cocos2d::DrawNode* background_offScene)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	player = playerScene;
	background_off = background_offScene;
	auto ButtonUp = ui::Button::create("prefap/Gui/Play-8.png");
	auto ButtonDow = ui::Button::create("prefap/Gui/Play-8.png");
	auto ButtonLeft = ui::Button::create("prefap/Gui/Play-8.png");
	auto ButtonRight = ui::Button::create("prefap/Gui/Play-8.png");
	auto ButtonLight = ui::Button::create("prefap/Gui/Play-8.png");

	ButtonUp->setScale(BUTTON_SCALE);
	ButtonDow->setScale(BUTTON_SCALE);
	ButtonLeft->setScale(BUTTON_SCALE);
	ButtonRight->setScale(BUTTON_SCALE);
	ButtonLight->setScale(BUTTON_SCALE);

	ButtonLight->setPosition(Vec2(visibleSize.width / 2.5 + origin.x, -visibleSize.height / 4 + origin.y));
	ButtonLight->addTouchEventListener(CC_CALLBACK_2(Canvas::OnOffLight, this));

	ButtonUp->setPosition(Vec2(-visibleSize.width / 3 + origin.x, -visibleSize.height / 4 + origin.y + ButtonUp->getContentSize().height*BUTTON_SCALE));
	ButtonUp->addTouchEventListener(CC_CALLBACK_2(Canvas::MoveUp, this));

	ButtonDow->setPosition(Vec2(-visibleSize.width / 3 + origin.x, -visibleSize.height / 4 + origin.y - ButtonUp->getContentSize().height*BUTTON_SCALE));
	ButtonDow->addTouchEventListener(CC_CALLBACK_2(Canvas::MoveDow, this));

	ButtonLeft->setPosition(Vec2(-visibleSize.width / 3 + origin.x - ButtonLeft->getContentSize().width*BUTTON_SCALE, -visibleSize.height / 4 + origin.y));
	ButtonLeft->addTouchEventListener(CC_CALLBACK_2(Canvas::MoveLeft, this));

	ButtonRight->setPosition(Vec2(-visibleSize.width / 3 + origin.x + ButtonLeft->getContentSize().width*BUTTON_SCALE, -visibleSize.height / 4 + origin.y));
	ButtonRight->addTouchEventListener(CC_CALLBACK_2(Canvas::MoveRight, this));

	this->addChild(ButtonUp);
	this->addChild(ButtonDow);
	this->addChild(ButtonLeft);
	this->addChild(ButtonRight);
	this->addChild(ButtonLight);

	enegy = ui::Slider::create();
	enegy->loadBarTexture("Slider_Back.png"); // what the slider looks like
	//enegy->loadSlidBallTextures("SliderNode_Normal.png", "SliderNode_Press.png", "SliderNode_Disable.png");
	enegy->loadProgressBarTexture("Slider_PressBar.png");
	enegy->setPosition(Vec2(-visibleSize.width /3 + origin.x, visibleSize.height /2.5 + origin.y));
	enegy->setMaxPercent(MAX_PERCENT);
	enegy->setPercent(enegy->getMaxPercent());
	enegy->setScale(1.5f);
	this->addChild(enegy);
	this->schedule(CC_SCHEDULE_SELECTOR(Canvas::reduceenergy), TIME_REDUCE_ENERGY);
}
void Canvas::MoveUp(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType Type)
{
	if (Type == ui::Widget::TouchEventType::BEGAN)
	{
		player->MoveUp();
	}
}
void Canvas::MoveDow(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType Type)
{
	if (Type == ui::Widget::TouchEventType::BEGAN)
	{
		player->MoveDow();
	}

}
void Canvas::MoveLeft(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType Type)
{
	if (Type == ui::Widget::TouchEventType::BEGAN)
	{
		player->MoveLeft();
	}
}
void Canvas::MoveRight(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType Type)
{
	if (Type == ui::Widget::TouchEventType::BEGAN)
	{
		player->MoveRight();
	}
}
void Canvas::OnOffLight(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType Type)
{
	if (Type == ui::Widget::TouchEventType::BEGAN)
	{
		if (background_off->isVisible())
		{
			background_off->setVisible(false);
		}
		else
		{
			background_off->setVisible(true);
		}
	}
}
void Canvas::reduceenergy(float dt)
{
	enegy->setPercent(enegy->getPercent() - PERCENT_REDUCE);
}