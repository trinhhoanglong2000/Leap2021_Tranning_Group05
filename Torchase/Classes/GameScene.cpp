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
static GameScene *Scene_layer;
Scene* GameScene::createScene()
{
	/*auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	//scene->getPhysicsWorld()->setGravity(Vec2(0, 0));

	Scene_layer = GameScene::create();
	Scene_layer->SetPhysicWorld(scene->getPhysicsWorld());

	scene->addChild(Scene_layer);
	return scene;*/
	return GameScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

	auto bg = Sprite::create("Background.png");
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(bg);

	// ui move
	Layout = ui::Layout::create();

	ButtonUp = ui::Button::create("prefap/Gui/Play-8.png");
	auto ButtonDow = ui::Button::create("prefap/Gui/Play-8.png");
	auto ButtonLeft = ui::Button::create("prefap/Gui/Play-8.png");
	auto ButtonRight = ui::Button::create("prefap/Gui/Play-8.png");

	ButtonUp->setScale(BUTTON_SCALE);
	ButtonDow->setScale(BUTTON_SCALE);
	ButtonLeft->setScale(BUTTON_SCALE);
	ButtonRight->setScale(BUTTON_SCALE);

	ButtonUp->setPosition(Vec2(visibleSize.width / 5 + origin.x, visibleSize.height / 5 + origin.y + ButtonUp->getContentSize().height*BUTTON_SCALE));
	ButtonUp->addTouchEventListener(CC_CALLBACK_2(GameScene::MoveUp, this));

	ButtonDow->setPosition(Vec2(visibleSize.width / 5 + origin.x, visibleSize.height / 5 + origin.y - ButtonUp->getContentSize().height*BUTTON_SCALE));
	ButtonDow->addTouchEventListener(CC_CALLBACK_2(GameScene::MoveDow, this));

	ButtonLeft->setPosition(Vec2(visibleSize.width / 5 + origin.x - ButtonLeft->getContentSize().width*BUTTON_SCALE, visibleSize.height / 5 + origin.y));
	ButtonLeft->addTouchEventListener(CC_CALLBACK_2(GameScene::MoveLeft, this));

	ButtonRight->setPosition(Vec2(visibleSize.width / 5 + origin.x + ButtonLeft->getContentSize().width*BUTTON_SCALE, visibleSize.height / 5 + origin.y));
	ButtonRight->addTouchEventListener(CC_CALLBACK_2(GameScene::MoveRight, this));

	Layout->addChild(ButtonUp);
	Layout->addChild(ButtonDow);
	Layout->addChild(ButtonLeft);
	Layout->addChild(ButtonRight);
	this->addChild(Layout, 5);

	player = new Player(this); // add player

	return true;
}
void GameScene::MoveUp(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType Type)
{
	if (Type == ui::Widget::TouchEventType::BEGAN)
	{
		Layout->setPosition(Vec2(Layout->getPositionX(), Layout->getPositionY() + visibleSize.height*PLAYER_SPEED));
		player->MoveUp();
	}
}
void GameScene::MoveDow(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType Type)
{
	if(Type== ui::Widget::TouchEventType::BEGAN)
	{
		Layout->setPosition(Vec2(Layout->getPositionX(), Layout->getPositionY() - visibleSize.height*PLAYER_SPEED));
		player->MoveDow(); 
	}
	
}
void GameScene::MoveLeft(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType Type)
{
	if (Type == ui::Widget::TouchEventType::BEGAN)
	{
		Layout->setPosition(Vec2(Layout->getPositionX() - visibleSize.height*PLAYER_SPEED, Layout->getPositionY()));
		player->MoveLeft();
	}
}
void GameScene::MoveRight(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType Type)
{
	if (Type == ui::Widget::TouchEventType::BEGAN)
	{
		Layout->setPosition(Vec2(Layout->getPositionX() + visibleSize.height*PLAYER_SPEED, Layout->getPositionY()));
		player->MoveRight();
	}
}

