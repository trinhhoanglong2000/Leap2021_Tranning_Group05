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

#include "GameScene.h"
#include "Definitions.h"
#include "AudioEngine.h"
USING_NS_CC;
Scene* GameScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	//scene->getPhysicsWorld()->setGravity(Vec2(0, 0));

	auto Scene_layer = GameScene::create();
	Scene_layer->SetPhysicWorld(scene->getPhysicsWorld());
	Scene_layer->removeChild(Scene_layer->getDefaultCamera());

	scene->addChild(Scene_layer);

	return scene;
	//return GameScene::create();
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

	// ui move
	Layout = ui::Layout::create();

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
	ButtonLight->addTouchEventListener(CC_CALLBACK_2(GameScene::OnOffLight, this));

	ButtonUp->setPosition(Vec2(-visibleSize.width / 3 + origin.x, -visibleSize.height / 4 + origin.y + ButtonUp->getContentSize().height*BUTTON_SCALE));
	ButtonUp->addTouchEventListener(CC_CALLBACK_2(GameScene::MoveUp, this));

	ButtonDow->setPosition(Vec2(-visibleSize.width / 3 + origin.x, -visibleSize.height / 4 + origin.y - ButtonUp->getContentSize().height*BUTTON_SCALE));
	ButtonDow->addTouchEventListener(CC_CALLBACK_2(GameScene::MoveDow, this));

	ButtonLeft->setPosition(Vec2(-visibleSize.width / 3 + origin.x - ButtonLeft->getContentSize().width*BUTTON_SCALE, -visibleSize.height / 4 + origin.y));
	ButtonLeft->addTouchEventListener(CC_CALLBACK_2(GameScene::MoveLeft, this));

	ButtonRight->setPosition(Vec2(-visibleSize.width / 3 + origin.x + ButtonLeft->getContentSize().width*BUTTON_SCALE, -visibleSize.height / 4 + origin.y));
	ButtonRight->addTouchEventListener(CC_CALLBACK_2(GameScene::MoveRight, this));

	Layout->addChild(ButtonUp);
	Layout->addChild(ButtonDow);
	Layout->addChild(ButtonLeft);
	Layout->addChild(ButtonRight);
	Layout->addChild(ButtonLight);

	player = new Player();	
	this->addChild(player,10);
	player->addChild(Layout, 30);
	Layout->setPosition(Vec2(0, 0));

	auto cam = Camera::getDefaultCamera();
	this->runAction(Follow::create(player));
	
	minion = new Minions(); // add enemy
	this->addChild(minion, 5);

	gameMap = new GameMap(this); // add gamemap

	this->schedule(CC_SCHEDULE_SELECTOR(GameScene::enemyFind), 1.0f);
	return true;
}
void GameScene::enemyFind(float dt)
{
	minion->findPlayer(player);
}
void GameScene::MoveUp(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType Type)
{
	if (Type == ui::Widget::TouchEventType::BEGAN)
	{
		player->MoveUp();
	}
}
void GameScene::MoveDow(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType Type)
{
	if(Type== ui::Widget::TouchEventType::BEGAN)
	{
		player->MoveDow(); 
	}
	
}
void GameScene::MoveLeft(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType Type)
{
	if (Type == ui::Widget::TouchEventType::BEGAN)
	{
		player->MoveLeft();
	}
}
void GameScene::MoveRight(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType Type)
{
	if (Type == ui::Widget::TouchEventType::BEGAN)
	{
		player->MoveRight();
	}
}
void GameScene::OnOffLight(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType Type)
{
	if (Type == ui::Widget::TouchEventType::BEGAN)
	{
		player->OnOffLight();
	}
}
