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
#include "TrapBear.h"
#include "MinionManager.h"
#include "TrapManager.h"
#include "MainMenuScene.h"

USING_NS_CC;
using namespace cocos2d::ui;//ui namespace

Canvas::Canvas(Player *playerScene, cocos2d::DrawNode* background_offScene, int controller_Scene, cocos2d::Scene *sceneGame, int &_gameState, int levelGame)
{
	def = UserDefault::getInstance();
	scene = sceneGame;
	this->gameState = &_gameState;
	level = levelGame;
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	player = playerScene;
	endlight = true;
	plant = nullptr;
	controller_canvas = controller_Scene;
	background_off = background_offScene;
	ButtonUp = ui::Button::create("prefap/Gui/up.png");
	ButtonDow = ui::Button::create("prefap/Gui/down.png");
	ButtonLeft = ui::Button::create("prefap/Gui/left.png");
	ButtonRight = ui::Button::create("prefap/Gui/rights.png");
	ButtonLight = ui::Button::create("prefap/Gui/light.png");
	ButtonTrap = ui::Button::create("prefap/Gui/Trap.png");
	ButtonConvert = ui::Button::create("prefap/Gui/right.png");

	ButtonPause = ui::Button::create("prefap/Gui/pausebtn.png");
	ButtonResume = ui::Button::create("prefap/Gui/play.png");
	ButtonHome = ui::Button::create("prefap/Gui/homebtn.png");
	

	pauseBackgr = Sprite::create("prefap/Gui/table.png");
	pauseBackgr->setScale(1.2f);
	pauseBackgr->setPosition(Vec2(origin.x,origin.y));
	pauseBackgr->setOpacity(0);
	this->addChild(pauseBackgr);

	
	talkboxBachgr = Sprite::create("prefap/Gui/blackboxx.png");
	talkboxBachgr->setScale(3.0f,2.0f);
	talkboxBachgr->setPosition(Vec2(0,-visibleSize.height/2+ talkboxBachgr->getContentSize().height));
	this->addChild(talkboxBachgr,100);

	ButtonConvert->setScale(BUTTON_SCALE);
	ButtonUp->setScale(BUTTON_SCALE);
	ButtonDow->setScale(BUTTON_SCALE);
	ButtonLeft->setScale(BUTTON_SCALE);
	ButtonRight->setScale(BUTTON_SCALE);
	ButtonPause->setScale(BUTTON_SCALE*2.5f);
	ButtonResume->setScale(BUTTON_SCALE*2.5f);

	ButtonLight->setScale(BUTTON_SCALE*1.3f);
	ButtonTrap->setScale(BUTTON_SCALE*1.3f);

	ButtonHome->setScale(BUTTON_SCALE*2.5f);

	ButtonConvert->setPosition(Vec2(visibleSize.width / 2.2 + origin.x, -visibleSize.height / 10 + origin.y));
	ButtonConvert->addTouchEventListener(CC_CALLBACK_2(Canvas::PutTrap, this));

	ButtonTrap->setPosition(Vec2(visibleSize.width / 2.7 + origin.x, -visibleSize.height / 4 + origin.y));
	ButtonTrap->addTouchEventListener(CC_CALLBACK_2(Canvas::PutTrap, this));
	  
	ButtonLight->setPosition(Vec2(visibleSize.width / 2.2 + origin.x, -visibleSize.height / 4 + origin.y));
	ButtonLight->addTouchEventListener(CC_CALLBACK_2(Canvas::OnOffLight, this));

	ButtonUp->setPosition(Vec2(-visibleSize.width / 3 + origin.x, -visibleSize.height / 4 + origin.y + ButtonUp->getContentSize().height*BUTTON_SCALE*0.75f));
	ButtonUp->addTouchEventListener(CC_CALLBACK_2(Canvas::MoveUp, this));

	ButtonDow->setPosition(Vec2(-visibleSize.width / 3 + origin.x, -visibleSize.height / 4 + origin.y - ButtonUp->getContentSize().height*BUTTON_SCALE*0.75f));
	ButtonDow->addTouchEventListener(CC_CALLBACK_2(Canvas::MoveDow, this));

	ButtonLeft->setPosition(Vec2(-visibleSize.width / 3 + origin.x - ButtonLeft->getContentSize().width*BUTTON_SCALE*0.75f, -visibleSize.height / 4 + origin.y));
	ButtonLeft->addTouchEventListener(CC_CALLBACK_2(Canvas::MoveLeft, this));

	ButtonRight->setPosition(Vec2(-visibleSize.width / 3 + origin.x + ButtonLeft->getContentSize().width*BUTTON_SCALE*0.75f, -visibleSize.height / 4 + origin.y));
	ButtonRight->addTouchEventListener(CC_CALLBACK_2(Canvas::MoveRight, this));

	ButtonPause->setPosition(Vec2(visibleSize.width /2.3 , visibleSize.height /2.5 ));
	ButtonPause->addTouchEventListener(CC_CALLBACK_2(Canvas::PauseScene, this));

	ButtonResume->setPosition(Vec2(pauseBackgr->getPosition().x+ pauseBackgr->getContentSize().width/4,origin.y));
	ButtonResume->addTouchEventListener(CC_CALLBACK_2(Canvas::PauseScene, this));

	ButtonHome->setPosition(Vec2(pauseBackgr->getPosition().x - pauseBackgr->getContentSize().width / 4, origin.y));
	ButtonHome->addTouchEventListener(CC_CALLBACK_2(Canvas::GotoMainMenu, this));

	this->addChild(ButtonUp);
	this->addChild(ButtonDow);
	this->addChild(ButtonLeft);
	this->addChild(ButtonRight);
	//this->addChild(ButtonConvert);
	this->addChild(ButtonPause);
	this->addChild(ButtonResume);
	this->addChild(ButtonLight);
	this->addChild(ButtonTrap);
	this->addChild(ButtonHome);

	NumTrap = Sprite::create("prefap/Gui/NumTrap.png");
	NumTrap->setScale(0.4f);
	NumTrap->setPosition(Vec2(ButtonTrap->getContentSize().width/1.2f,ButtonTrap->getContentSize().height / 1.2f));
	ButtonTrap->addChild(NumTrap, 100);

	LableNumTrap = Label::createWithTTF("100", "fonts/horroroid.ttf", visibleSize.height/10);
	LableNumTrap->setPosition(Vec2(ButtonTrap->getContentSize().width / 1.2f, ButtonTrap->getContentSize().height / 1.2f));
	LableNumTrap->setColor(Color3B::BLACK);
	ButtonTrap->addChild(LableNumTrap, 101);

	erroTrap = Label::createWithTTF("out of Trap", "fonts/horroroid.ttf", visibleSize.height / 18);
	erroTrap->setPosition(Vec2(visibleSize.width / 2.7 + origin.x, -visibleSize.height / 7 + origin.y));
	erroTrap->setColor(Color3B::WHITE);
	this->addChild(erroTrap, 101);
	erroTrap->setVisible(false);
	// add slider enegy
	enegy = ui::Slider::create();
	enegy->loadBarTexture("Slider_Backs.png"); 
	//enegy->loadSlidBallTextures("SliderNode_Normal.png", "SliderNode_Press.png", "SliderNode_Disable.png");
	enegy->loadProgressBarTexture("Slider_PressBars.png");
	enegy->setPosition(Vec2(-visibleSize.width /2.8 + origin.x, player->vecHeal.at(0)->getPositionY()- player->vecHeal.at(0)->getContentSize().height*0.2f));
	enegy->setMaxPercent(MAX_PERCENT);
	enegy->setPercent(enegy->getMaxPercent());
	enegy->setScale(1.3f);
	this->addChild(enegy);
	
	int_move = 0;
	mind_move = 1;
	BoolTouch = false;
	
	LableTalk = Label::createWithTTF("John:\nAlright, Where are we now???", "fonts/Balsoon.ttf", visibleSize.height / 15);
	LableTalk->setPosition(Point(talkboxBachgr->getPosition().x -talkboxBachgr->getContentSize().width * 1.3f, talkboxBachgr->getPosition().y+ talkboxBachgr->getContentSize().height/3));
	LableTalk->setAnchorPoint(Vec2(0, 1));
	this->addChild(LableTalk, 100);

	LableTalkContent = Label::createWithTTF("John:\nAlright, Where are we now???", "fonts/Balsoon.ttf", visibleSize.height / 15);
	LableTalkContent->setPosition(Point(talkboxBachgr->getPosition().x - talkboxBachgr->getContentSize().width * 1.3f, talkboxBachgr->getPosition().y + talkboxBachgr->getContentSize().height / 9));
	LableTalkContent->setAnchorPoint(Vec2(0, 1));
	LableTalkContent->setMaxLineWidth(talkboxBachgr->getContentSize().width *2.7f);
	LableTalkContent->setLineHeight(talkboxBachgr->getContentSize().height/6);
	this->addChild(LableTalkContent, 100);

	//First talk - instruction
	std::string file = StringUtils::format("story/level_%d.txt", level);
	auto s = FileUtils::getInstance()->getStringFromFile(file);
	int count = s.find("\n");
	while(count!=-1)
	{
		auto temp = s.substr(0, count);
		talkbox.push_back(temp);
		s = s.substr(count + 1, s.length());
		count = s.find("\n");
		
	}

	// add touch move
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(Canvas::TouchMoveBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(Canvas::TouchMoveEnd, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(Canvas::TouchMoveMove, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
	Schedule_ReduceEnegy = CC_SCHEDULE_SELECTOR(Canvas::reduceenergy);
	if (controller_Scene == 1)
	{
		ButtonUp->setVisible(false);
		ButtonDow->setVisible(false);
		ButtonRight->setVisible(false);
		ButtonLeft->setVisible(false);
	}

}
void Canvas::MoveUp(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType Type)
{
	if (Type == ui::Widget::TouchEventType::BEGAN && int_move == 0 )
	{
		player->MoveUp();
		int_move = 1;
		mind_move = 1;
		this->schedule(CC_SCHEDULE_SELECTOR(Canvas::AutoMove), AUTO_SPEED / 1.5f);
	}
	if (Type == ui::Widget::TouchEventType::ENDED && int_move == 1)
	{
		
		int_move = 0;
		this->unschedule(CC_SCHEDULE_SELECTOR(Canvas::AutoMove));
		Canvas::reducePlant();
	}
	if (Type == ui::Widget::TouchEventType::MOVED && int_move == 1)
	{
		Vec2 *pointGoc = new Vec2(ButtonUp->getPositionX() + 600, ButtonUp->getPositionY() + 315);
		float x = (ButtonUp->getTouchMovePosition().x - pointGoc->x) * (ButtonUp->getTouchMovePosition().x - pointGoc->x);
		float y = (ButtonUp->getTouchMovePosition().y - pointGoc->y) * (ButtonUp->getTouchMovePosition().y - pointGoc->y);
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
		mind_move = 2;
		this->schedule(CC_SCHEDULE_SELECTOR(Canvas::AutoMove), AUTO_SPEED / 1.5f);
	}
	if (Type == ui::Widget::TouchEventType::ENDED && int_move == 2)
	{
		int_move = 0;
		this->unschedule(CC_SCHEDULE_SELECTOR(Canvas::AutoMove));
		Canvas::reducePlant();
	}
	if (Type == ui::Widget::TouchEventType::MOVED && int_move == 2)
	{
		Vec2 *pointGoc = new Vec2(ButtonDow->getPositionX() + 600, ButtonDow->getPositionY() + 315);
		float x = (ButtonDow->getTouchMovePosition().x - pointGoc->x) * (ButtonDow->getTouchMovePosition().x - pointGoc->x);
		float y = (ButtonDow->getTouchMovePosition().y - pointGoc->y) * (ButtonDow->getTouchMovePosition().y - pointGoc->y);
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
		mind_move = 3;
		this->schedule(CC_SCHEDULE_SELECTOR(Canvas::AutoMove), AUTO_SPEED / 1.5f);
	}
	if (Type == ui::Widget::TouchEventType::ENDED && int_move == 3)
	{
		int_move = 0;
		this->unschedule(CC_SCHEDULE_SELECTOR(Canvas::AutoMove));
		Canvas::reducePlant();
	}
	if (Type == ui::Widget::TouchEventType::MOVED && int_move == 3)
	{
		Vec2 *pointGoc = new Vec2(ButtonLeft->getPositionX() + 600, ButtonLeft->getPositionY() + 315);
		float x = (ButtonLeft->getTouchMovePosition().x - pointGoc->x) * (ButtonLeft->getTouchMovePosition().x - pointGoc->x);
		float y = (ButtonLeft->getTouchMovePosition().y - pointGoc->y) * (ButtonLeft->getTouchMovePosition().y - pointGoc->y);
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
		mind_move = 4;
		this->schedule(CC_SCHEDULE_SELECTOR(Canvas::AutoMove), AUTO_SPEED / 1.5f);
	}
	if (Type == ui::Widget::TouchEventType::ENDED && int_move == 4)
	{
		int_move = 0;
		this->unschedule(CC_SCHEDULE_SELECTOR(Canvas::AutoMove));
		Canvas::reducePlant();
	}
	if (Type == ui::Widget::TouchEventType::MOVED && int_move == 4)
	{
		Vec2 *pointGoc = new Vec2(ButtonRight->getPositionX() + 600, ButtonRight->getPositionY() + 315);
		float x = (ButtonRight->getTouchMovePosition().x - pointGoc->x) * (ButtonRight->getTouchMovePosition().x - pointGoc->x);
		float y = (ButtonRight->getTouchMovePosition().y - pointGoc->y) * (ButtonRight->getTouchMovePosition().y - pointGoc->y);
		float pos = sqrt(x + y);
		if (pos - (ButtonRight->getContentSize().width / 2 * BUTTON_SCALE) > 0)
		{
			int_move = 0;
			this->unschedule(CC_SCHEDULE_SELECTOR(Canvas::AutoMove));
		}
	}
}
void Canvas::PauseScene(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType Type)
{
	if (Type == ui::Widget::TouchEventType::BEGAN)
	{
		if (STATE_PLAYING == *gameState)
		{
			auto callback = CallFunc::create([&]() {
				Director::getInstance()->pause();
			});
			*gameState = STATE_PAUSE;
			CCLOG("pause %d", *gameState);
			auto moveAction = FadeIn::create(PAUSE_BACKGROUND_FADE_IN_TIME);
			auto sequence = Sequence::create(moveAction, callback, nullptr);
			pauseBackgr->runAction(sequence);
			ButtonDow->setVisible(false);
			ButtonUp->setVisible(false);
			ButtonLeft->setVisible(false);
			ButtonRight->setVisible(false);
			ButtonLight->setVisible(false);
			ButtonTrap->setVisible(false);
			ButtonPause->setVisible(false);
			ButtonResume->setVisible(true);
			ButtonHome->setVisible(true);
			//EaseBounceOut *menuActionEase = EaseBounceOut::create(MoveTo::create(EASE_BOUNCE_IN_TIME, Vec2(origin.x, origin.y)));
		}
		else if (STATE_PAUSE == *gameState)
		{
			*gameState = STATE_PLAYING;
			Director::getInstance()->resume();
			CCLOG("resume %d", *gameState);
			pauseBackgr->runAction(FadeOut::create(PAUSE_BACKGROUND_FADE_IN_TIME));
			//EaseBounceOut *menuActionEase = EaseBounceOut::create(MoveTo::create(EASE_BOUNCE_IN_TIME, Vec2(origin.x, origin.y + visibleSize.height)));
			
			Canvas::OnButtonController();
			ButtonPause->setVisible(true);
			ButtonResume->setVisible(false);
			ButtonHome->setVisible(false);
		}
	}
}
void Canvas::GotoMainMenu(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType Type)
{
	if (Type == ui::Widget::TouchEventType::BEGAN)
	{
		Director::getInstance()->resume();
		auto scene = MainMenuScene::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
	}
}
void Canvas::OnOffLight(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType Type)
{
	AllMinions = MinionManager::getInstance()->AllMinions;
	if (Type == ui::Widget::TouchEventType::BEGAN && endlight ==true && enegy->getPercent()>0)
	{
		if (enegy->getPercent() <= 0)
		{
			Canvas::reduceenergy(1);
			return;
		}
		if (background_off->isVisible())
		{
			player->background->getPhysicsBody()->setEnabled(true);
			player->background->setVisible(true);
			background_off->setVisible(false);
			for (int i = 0; i < AllMinions.size(); i++)
			{
				if (AllMinions.at(i)->boolFind == true && AllMinions.at(i)->isVisible()==true && AllMinions.at(i)->Booldie==false)
				{
					if (AllMinions.at(i)->type == 1);
					AllMinions.at(i)->lighton(1);
				}
			}
			Schedule_ReduceEnegy = CC_SCHEDULE_SELECTOR(Canvas::reduceenergy);
			this->schedule(Schedule_ReduceEnegy, TIME_REDUCE_ENERGY);
			this->unschedule(CC_SCHEDULE_SELECTOR(Canvas::autoplusenergy));
		}
		else
		{
			player->background->getPhysicsBody()->setEnabled(false);
			player->background->setVisible(false);
			background_off->setVisible(true);
			for (int i = 0; i < AllMinions.size(); i++)
			{
				if (AllMinions.at(i)->boolFind == true && AllMinions.at(i)->isVisible() == true && AllMinions.at(i)->Booldie == false)
				{
					if (AllMinions.at(i)->type == 1);
					{
						AllMinions.at(i)->lightoff();
					}
				}
			}
			this->unschedule(Schedule_ReduceEnegy);
			this->schedule(CC_SCHEDULE_SELECTOR(Canvas::autoplusenergy), 1.0f);
		}
	}
}
void Canvas::reduceenergy(float dt)
{
	if (player->die == true)
	{
		return;
	}
	enegy->setPercent(enegy->getPercent() - PERCENT_REDUCE);
	if (enegy->getPercent() <= 0)
	{
		AllMinions = MinionManager::getInstance()->AllMinions;
		player->background->getPhysicsBody()->setEnabled(false);
		player->background->setVisible(false);
		background_off->setVisible(true);
		for (int i = 0; i < AllMinions.size(); i++)
		{
			if (AllMinions.at(i)->boolFind == true && AllMinions.at(i)->isVisible() == true && AllMinions.at(i)->Booldie == false)
			{
				if (AllMinions.at(i)->type == 1);
				{
					AllMinions.at(i)->lightoff();
				}
			}
		}
		this->schedule(CC_SCHEDULE_SELECTOR(Canvas::autoplusenergy), 1.0f);
		this->unschedule(Schedule_ReduceEnegy);	
	}
}
void Canvas::autoplusenergy(float dt)
{
	if (enegy->getPercent() + AUTOPLUSHENEGY < enegy->getMaxPercent())
		enegy->setPercent(enegy->getPercent() + AUTOPLUSHENEGY);
	else
		enegy->setPercent(enegy->getMaxPercent());
}
void Canvas::plusenergy(int power)
{
	if(enegy->getPercent() + power<enegy->getMaxPercent())
		enegy->setPercent(enegy->getPercent() + power);
	else
		enegy->setPercent(enegy->getMaxPercent());
}
void Canvas::AutoMove(float dt)
{
	if(mind_move ==1)
		player->MoveUp();
	if (mind_move == 2)
		player->MoveDow();
	if (mind_move == 3)
		player->MoveLeft();
	if (mind_move == 4)
		player->MoveRight();
}
bool Canvas::TouchMoveBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
	if (talk && !waittalk)
	{
		num_talk=num_talk+2;
		LableTalk->setString(talkbox.at(num_talk));
		LableTalkContent->setString(talkbox.at(num_talk+1));
		int countwait = talkbox.at(num_talk + 1).find("let me...");
		int countTalk = talkbox.at(num_talk + 1).find("Good luck!!!");
		if (countwait >=0 )
		{ 
			CCLOG("%d", talkbox.at(num_talk + 1).find("let me..."));
			waittalk = true;
			this->schedule(CC_SCHEDULE_SELECTOR(Canvas::actionmeet), 1.0f, 0, 0);
		}
		if (countTalk >=0 )
		{
			talk = false;
		}	
	}
	else if (!talk && !waittalk)
	{
		def->setIntegerForKey("INGAME_NumTalk", num_talk);
		Canvas::offtalk();
	}
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
	if (controller_canvas == 0 || talk ==true)
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
	if (controller_canvas == 0 || talk == true)
		return true;
	if(int_move==0)
		this->schedule(CC_SCHEDULE_SELECTOR(Canvas::AutoMove), AUTO_SPEED/1.5f);
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
	mind_move = int_move;
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
			plant = nullptr;
		}
	}
}
void Canvas::PutTrap(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType Type)
{
	if (amountTrap <= 0)
	{
		if (checkTouchPutTrap == false)
		{
			checkTouchPutTrap = true;
			auto fadeOut = FadeTo::create(1, 10);
			auto callback = CallFunc::create([&]() {
				erroTrap->setVisible(false);
				checkTouchPutTrap = false;
			});
			auto sequenceout = Sequence::create(fadeOut, callback, nullptr);
			auto fadeIn = FadeTo::create(1, 255);
			Sequence* sequence = Sequence::create(fadeIn, sequenceout, NULL);
			erroTrap->setVisible(true);
			erroTrap->runAction(sequence);
		}
		return;
	}
	if (Type == ui::Widget::TouchEventType::BEGAN && player->die==false)
	{
		switch (mind_move)
		{
		case 1:
		{
			auto tileSprite = _meta->getTileAt(Vec2((int)((player->getPositionX() / player->speed)-0.5), (int)(maxmap -0.5- (player->getPositionY() + player->speed)/ player->speed)));
			if (tileSprite)
				return;
			auto trap = TrapManager::getInstance()->CreateTrap(2);
			trap->setPosition(Vec2(player->getPositionX(), player->getPositionY() + player->speed));
			scene->addChild(trap, 20);
			amountTrap--;
			Canvas::changeNumtrap();
			break;
		}
		case 2:
		{
			auto tileSprite = _meta->getTileAt(Vec2((int)((player->getPositionX() / player->speed) - 0.5), (int)(maxmap - 0.5 - (player->getPositionY() - player->speed) / player->speed)));
			if (tileSprite)
				return;
			auto trap = TrapManager::getInstance()->CreateTrap(2);
			trap->setPosition(Vec2(player->getPositionX(), player->getPositionY() - player->speed));
			scene->addChild(trap, 20);
			amountTrap--;
			Canvas::changeNumtrap();
			break;
		}
		case 3:
		{
			auto tileSprite = _meta->getTileAt(Vec2((int)(((player->getPositionX() - player->speed) / player->speed) - 0.5), (int)(maxmap - 0.5 - player->getPositionY() / player->speed)));
			if (tileSprite)
				return;
			auto trap = TrapManager::getInstance()->CreateTrap(2);
			trap->setPosition(Vec2(player->getPositionX() - player->speed, player->getPositionY()));
			scene->addChild(trap, 20);
			amountTrap--;
			Canvas::changeNumtrap();
			break;
		}
		case 4:
		{
			auto tileSprite = _meta->getTileAt(Vec2((int)(((player->getPositionX() + player->speed) / player->speed) - 0.5), (int)(maxmap - 0.5 - player->getPositionY() / player->speed)));
			if (tileSprite)
				return;
			auto trap = TrapManager::getInstance()->CreateTrap(2);
			trap->setPosition(Vec2(player->getPositionX() + player->speed, player->getPositionY()));
			scene->addChild(trap,20);
			amountTrap--;
			Canvas::changeNumtrap();
			break;
		}
		default:
			break;
		}
	}
}
void Canvas::goup(float dt)
{
	int_move = 5;
	BoolTouch = false;
	this->unschedule(CC_SCHEDULE_SELECTOR(Canvas::AutoMove));
	this->unschedule(Schedule_ReduceEnegy);	
	this->unschedule(Schedule_ReduceEnegy);
	this->unschedule(CC_SCHEDULE_SELECTOR(Canvas::autoplusenergy));
	if (player->checkMove == true)
	{
		player->background->getPhysicsBody()->setEnabled(false);
		player->background->setVisible(false);
		background_off->setVisible(false);
		endlight = false;
		Canvas::AutoMove(1);
		int_move = 0;
		return;
	}
	this->schedule(CC_SCHEDULE_SELECTOR(Canvas::goup), 0.1f, 0, 0);
}
void Canvas::Goagain(bool light)
{
	int_move = 0;
	endlight = true;
	if (light == false)
	{
		player->background->getPhysicsBody()->setEnabled(true);
		player->background->setVisible(true);
		background_off->setVisible(false);
	}
	else
	{
		player->background->getPhysicsBody()->setEnabled(false);
		player->background->setVisible(false);
		background_off->setVisible(true);
	}
}
void Canvas::meet()
{
	//player->checkMove = false;
	//player->background->setVisible(false);
	//player->background->getPhysicsBody()->setEnabled(false);
	//player->getPhysicsBody()->setEnabled(false);
	endlight = true;
	//player->setTextureRect(Rect(360, 359, 80, 95));
	//this->schedule(CC_SCHEDULE_SELECTOR(Canvas::actionmeet), 2.0f, 0, 0);
}
void Canvas::actionmeet(float dt)
{
	son->MoveUp();
	this->schedule(CC_SCHEDULE_SELECTOR(Canvas::movemeet), 1.0f, 0, 0);
}
void Canvas::movemeet(float dt)
{
	auto move = MoveTo::create(1.0f, playerNow);
	player->background->setVisible(true);
	auto callback = CallFunc::create([&]() {
		this->stopAllActions();
		player->checkMove = true;
		player->background->getPhysicsBody()->setEnabled(true);
		player->getPhysicsBody()->setEnabled(true);
		endlight = true;
		player->setTextureRect(Rect(360, 1, 80, 95));
		this->removeChild(son);
	});
	auto sequence = Sequence::create(move, callback, nullptr);
	player->runAction(sequence);
	waittalk = false;
}
void Canvas::OnButtonController()
{
	Director::getInstance()->resume();
	if (controller_canvas != 1)
	{
		ButtonUp->setVisible(true);
		ButtonDow->setVisible(true);
		ButtonRight->setVisible(true);
		ButtonLeft->setVisible(true);
	}
	ButtonLight->setVisible(true);
	ButtonTrap->setVisible(true);
}
void Canvas::ontalk()
{
	ButtonResume->setVisible(false);
	ButtonPause->setVisible(false);
	ButtonHome->setVisible(false);
	ButtonUp->setVisible(false);
	ButtonDow->setVisible(false);
	ButtonLeft->setVisible(false);
	ButtonRight->setVisible(false);
	ButtonLight->setVisible(false);
	ButtonTrap->setVisible(false);
	waittalk = false;
	talk = true;

	talkboxBachgr->setVisible(true);
	LableTalk->setVisible(true);
	LableTalkContent->setVisible(true);
	num_talk+=2;
	LableTalk->setString(talkbox.at(num_talk));
	LableTalkContent->setString(talkbox.at(num_talk+1));
	this->unschedule(Schedule_ReduceEnegy);
	this->unschedule(CC_SCHEDULE_SELECTOR(Canvas::AutoMove));
}
void Canvas::offtalk()
{
	ButtonPause->setVisible(true);
	ButtonPause->setVisible(true);
	ButtonResume->setVisible(false);
	ButtonHome->setVisible(false);
	Canvas::OnButtonController();

	talkboxBachgr->setVisible(false);
	LableTalk->setVisible(false);
	LableTalkContent->setVisible(false);
	waittalk = true;

	this->schedule(Schedule_ReduceEnegy, TIME_REDUCE_ENERGY);
}
void Canvas::changeNumtrap()
{
	auto s = StringUtils::format("%d", amountTrap);
	LableNumTrap->setString(s);
}