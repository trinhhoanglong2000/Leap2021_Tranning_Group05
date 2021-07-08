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
Canvas::Canvas(Player *playerScene, cocos2d::DrawNode* background_offScene, int controller_Scene)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	player = playerScene;
	endlight = true;
	plant = nullptr;
	controller_canvas = controller_Scene;
	background_off = background_offScene;
	ButtonUp = ui::Button::create("prefap/Gui/Play-8.png");
	ButtonDow = ui::Button::create("prefap/Gui/Play-8.png");
	ButtonLeft = ui::Button::create("prefap/Gui/Play-8.png");
	ButtonRight = ui::Button::create("prefap/Gui/Play-8.png");
	auto ButtonLight = ui::Button::create("prefap/Gui/Play-8.png");
	
	ButtonUp->setScale(BUTTON_SCALE);
	ButtonDow->setScale(BUTTON_SCALE);
	ButtonLeft->setScale(BUTTON_SCALE);
	ButtonRight->setScale(BUTTON_SCALE);
	ButtonLight->setScale(BUTTON_SCALE);

	ButtonLight->setPosition(Vec2(visibleSize.width / 2.5 + origin.x, -visibleSize.height / 4 + origin.y));
	ButtonLight->addTouchEventListener(CC_CALLBACK_2(Canvas::OnOffLight, this));

	ButtonUp->setPosition(Vec2(-visibleSize.width / 3 + origin.x, -visibleSize.height / 4 + origin.y + ButtonUp->getContentSize().height*BUTTON_SCALE/1.3));
	ButtonUp->addTouchEventListener(CC_CALLBACK_2(Canvas::MoveUp, this));

	ButtonDow->setPosition(Vec2(-visibleSize.width / 3 + origin.x, -visibleSize.height / 4 + origin.y - ButtonUp->getContentSize().height*BUTTON_SCALE/1.3));
	ButtonDow->addTouchEventListener(CC_CALLBACK_2(Canvas::MoveDow, this));

	ButtonLeft->setPosition(Vec2(-visibleSize.width / 3 + origin.x - ButtonLeft->getContentSize().width*BUTTON_SCALE/1.3, -visibleSize.height / 4 + origin.y));
	ButtonLeft->addTouchEventListener(CC_CALLBACK_2(Canvas::MoveLeft, this));

	ButtonRight->setPosition(Vec2(-visibleSize.width / 3 + origin.x + ButtonLeft->getContentSize().width*BUTTON_SCALE/1.3, -visibleSize.height / 4 + origin.y));
	ButtonRight->addTouchEventListener(CC_CALLBACK_2(Canvas::MoveRight, this));
	
	this->addChild(ButtonUp);
	this->addChild(ButtonDow);
	this->addChild(ButtonLeft);
	this->addChild(ButtonRight);
	this->addChild(ButtonLight);
	if (controller_Scene == 1)
	{
		ButtonUp->setVisible(false);
		ButtonDow->setVisible(false);
		ButtonRight->setVisible(false);
		ButtonLeft->setVisible(false);
	}
	// add slider enegy
	enegy = ui::Slider::create();
	enegy->loadBarTexture("Slider_Back.png"); // what the slider looks like
	//enegy->loadSlidBallTextures("SliderNode_Normal.png", "SliderNode_Press.png", "SliderNode_Disable.png");
	enegy->loadProgressBarTexture("Slider_PressBar.png");
	enegy->setPosition(Vec2(-visibleSize.width /3 + origin.x, visibleSize.height /2.5 + origin.y));
	enegy->setMaxPercent(MAX_PERCENT);
	enegy->setPercent(enegy->getMaxPercent());
	enegy->setScale(1.5f);
	this->addChild(enegy);
	Schedule_ReduceEnegy = CC_SCHEDULE_SELECTOR(Canvas::reduceenergy);

	this->schedule(Schedule_ReduceEnegy, TIME_REDUCE_ENERGY);
	int_move = 0;
	BoolTouch = false;
	
	// add touch move
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(Canvas::TouchMoveBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(Canvas::TouchMoveEnd, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(Canvas::TouchMoveMove, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
	
}
void Canvas::MoveUp(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType Type)
{
	if (Type == ui::Widget::TouchEventType::BEGAN && int_move == 0 )
	{
		
		
		player->MoveUp();
		int_move = 1;
		this->schedule(CC_SCHEDULE_SELECTOR(Canvas::AutoMove), AUTO_SPEED);
	}
	if (Type == ui::Widget::TouchEventType::ENDED && int_move == 1)
	{
		
		int_move = 0;
		this->unschedule(CC_SCHEDULE_SELECTOR(Canvas::AutoMove));
		Canvas::reducePlant();
	}
	if (Type == ui::Widget::TouchEventType::MOVED && int_move == 1)
	{
		float x = (ButtonUp->getTouchMovePosition().x - ButtonUp->getTouchBeganPosition().x) * (ButtonUp->getTouchMovePosition().x - ButtonUp->getTouchBeganPosition().x);
		float y = (ButtonUp->getTouchMovePosition().y - ButtonUp->getTouchBeganPosition().y) * (ButtonUp->getTouchMovePosition().y - ButtonUp->getTouchBeganPosition().y);
		float pos = sqrt(x + y);
		if (pos - (ButtonUp->getContentSize().width/2 * BUTTON_SCALE ) > 0)
		{	
			int_move = 0;
			this->unschedule(CC_SCHEDULE_SELECTOR(Canvas::AutoMove));
		}
	}
	
}
void Canvas::MoveDow(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType Type)
{
	if (Type == ui::Widget::TouchEventType::BEGAN && int_move == 0)
	{
		player->MoveDow();
		int_move = 2;
		this->schedule(CC_SCHEDULE_SELECTOR(Canvas::AutoMove), AUTO_SPEED);
	}
	if (Type == ui::Widget::TouchEventType::ENDED && int_move == 2)
	{
		int_move = 0;
		this->unschedule(CC_SCHEDULE_SELECTOR(Canvas::AutoMove));
		Canvas::reducePlant();
	}
	if (Type == ui::Widget::TouchEventType::MOVED && int_move == 2)
	{
		float x = (ButtonDow->getTouchMovePosition().x - ButtonDow->getTouchBeganPosition().x) * (ButtonDow->getTouchMovePosition().x - ButtonDow->getTouchBeganPosition().x);
		float y = (ButtonDow->getTouchMovePosition().y - ButtonDow->getTouchBeganPosition().y) * (ButtonDow->getTouchMovePosition().y - ButtonDow->getTouchBeganPosition().y);
		float pos = sqrt(x + y);
		if (pos - (ButtonDow->getContentSize().width / 2 * BUTTON_SCALE) > 0)
		{
			int_move = 0;
			this->unschedule(CC_SCHEDULE_SELECTOR(Canvas::AutoMove));
		}
	}
}
void Canvas::MoveLeft(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType Type)
{
	if (Type == ui::Widget::TouchEventType::BEGAN && int_move == 0)
	{
		player->MoveLeft();
		int_move = 3;
		this->schedule(CC_SCHEDULE_SELECTOR(Canvas::AutoMove), AUTO_SPEED);
	}
	if (Type == ui::Widget::TouchEventType::ENDED && int_move == 3)
	{
		int_move = 0;
		this->unschedule(CC_SCHEDULE_SELECTOR(Canvas::AutoMove));
		Canvas::reducePlant();
	}
	if (Type == ui::Widget::TouchEventType::MOVED && int_move == 3)
	{
		float x = (ButtonLeft->getTouchMovePosition().x - ButtonLeft->getTouchBeganPosition().x) * (ButtonLeft->getTouchMovePosition().x - ButtonLeft->getTouchBeganPosition().x);
		float y = (ButtonLeft->getTouchMovePosition().y - ButtonLeft->getTouchBeganPosition().y) * (ButtonLeft->getTouchMovePosition().y - ButtonLeft->getTouchBeganPosition().y);
		float pos = sqrt(x + y);
		if (pos - (ButtonLeft->getContentSize().width / 2 * BUTTON_SCALE) > 0)
		{
			int_move = 0;
			this->unschedule(CC_SCHEDULE_SELECTOR(Canvas::AutoMove));
		}
	}
}
void Canvas::MoveRight(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType Type)
{
	if (Type == ui::Widget::TouchEventType::BEGAN && int_move == 0)
	{
		player->MoveRight();
		int_move = 4;
		this->schedule(CC_SCHEDULE_SELECTOR(Canvas::AutoMove), AUTO_SPEED);
	}
	if (Type == ui::Widget::TouchEventType::ENDED && int_move == 4)
	{
		
		int_move = 0;
		this->unschedule(CC_SCHEDULE_SELECTOR(Canvas::AutoMove));
		Canvas::reducePlant();
	}
	if (Type == ui::Widget::TouchEventType::MOVED && int_move == 4)
	{
		float x = (ButtonRight->getTouchMovePosition().x - ButtonRight->getTouchBeganPosition().x) * (ButtonRight->getTouchMovePosition().x - ButtonRight->getTouchBeganPosition().x);
		float y = (ButtonRight->getTouchMovePosition().y - ButtonRight->getTouchBeganPosition().y) * (ButtonRight->getTouchMovePosition().y - ButtonRight->getTouchBeganPosition().y);
		float pos = sqrt(x + y);
		if (pos - (ButtonRight->getContentSize().width / 2 * BUTTON_SCALE) > 0)
		{
			int_move = 0;
			this->unschedule(CC_SCHEDULE_SELECTOR(Canvas::AutoMove));
		}
	}
}
void Canvas::OnOffLight(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType Type)
{
	
	if (Type == ui::Widget::TouchEventType::BEGAN && endlight ==true)
	{
		if (background_off->isVisible())
		{
			player->background->getPhysicsBody()->setEnabled(true);
			player->background->setVisible(true);
			background_off->setVisible(false);
			for (int i = 0; i < AllMinions.size(); i++)
			{
				AllMinions.at(i)->lighton();
			}
			Schedule_ReduceEnegy = CC_SCHEDULE_SELECTOR(Canvas::reduceenergy);
			this->schedule(Schedule_ReduceEnegy, TIME_REDUCE_ENERGY);
			
		}
		else
		{
			player->background->getPhysicsBody()->setEnabled(false);
			player->background->setVisible(false);
			background_off->setVisible(true);
			for (int i = 0; i < AllMinions.size(); i++)
			{
				AllMinions.at(i)->lightoff();
			}
			this->unschedule(Schedule_ReduceEnegy);
		}
	}
}
void Canvas::reduceenergy(float dt)
{
	enegy->setPercent(enegy->getPercent() - PERCENT_REDUCE);
	if (player->die == true)
	{
		this->pause();
		return;
	}
	if (enegy->getPercent() <= 0)
	{
		
		endlight = false;
		player->background->getPhysicsBody()->setEnabled(false);
		player->background->setVisible(false);
		background_off->setVisible(true);
		for (int i = 0; i < AllMinions.size(); i++)
		{
			AllMinions.at(i)->lightoff();
		}
		this->unschedule(Schedule_ReduceEnegy);
	}
}
void Canvas::plusenergy(int power)
{
	if(enegy->getPercent() + power<enegy->getMaxPercent())
		enegy->setPercent(enegy->getPercent() + power);
	else
		enegy->setPercent(enegy->getMaxPercent());
	endlight = true;
}
void Canvas::AutoMove(float dt)
{
	if(int_move==1)
		player->MoveUp();
	if (int_move == 2)
		player->MoveDow();
	if (int_move == 3)
		player->MoveLeft();
	if (int_move == 4)
		player->MoveRight();
}
bool Canvas::TouchMoveBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
	if (controller_canvas == 0)
		return true;
	if (BoolTouch == false)
	{
		BoolTouch = true;
	}
	return true;
}
bool Canvas::TouchMoveEnd(cocos2d::Touch *touch, cocos2d::Event *event)
{
	if (controller_canvas == 0)
	{
		return true;
	}
	int_move = 0;
	this->unschedule(CC_SCHEDULE_SELECTOR(Canvas::AutoMove));
	BoolTouch = false;
	Canvas::reducePlant();
	return true;
}
bool Canvas::TouchMoveMove(cocos2d::Touch *touch, cocos2d::Event *event)
{ 
	if (controller_canvas == 0)
		return true;
	if(int_move==0)
		this->schedule(CC_SCHEDULE_SELECTOR(Canvas::AutoMove), AUTO_SPEED);
	cocos2d::Vec2 pointgoc = Vec2(touch->getStartLocation().x, touch->getStartLocation().y + 20) - touch->getStartLocation();
	cocos2d::Vec2 point = touch->getLocation() - touch->getStartLocation();
	float radian = (pointgoc.x * point.x + pointgoc.y * point.y) / (sqrt(point.x*point.x + point.y*point.y)*sqrt(pointgoc.x*pointgoc.x + pointgoc.y*pointgoc.y));
	if (radian > 0.5 || radian < -0.5)
	{
		if (point.y < 0)
			int_move = 2;
		else
			int_move = 1;
	}
	else
	{
		if (point.x < 0)
			int_move = 3;
		else
			int_move = 4;
	}
	
	return true;
}
void Canvas::reducePlant()
{
	if (plant != nullptr)
	{
		plant->ReduceSlider();
		if (plant->enegy->getPercent() <= 0)
		{
			player->stop = true;
			plant == nullptr;
		}
	}
}