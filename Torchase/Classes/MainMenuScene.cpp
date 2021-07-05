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

#include "MainMenuScene.h"
#include "Definitions.h"
#include "GameScene.h"
#include "SoundManager.h"
USING_NS_CC;


Scene* MainMenuScene::createScene()
{
	return MainMenuScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object



	auto BgSprite = Sprite::create("dungeon.jpg");
	BgSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	float scale = MAX(visibleSize.width / BgSprite->getContentSize().width, visibleSize.height / BgSprite->getContentSize().height);

	BgSprite->setScale(scale);
	this->addChild(BgSprite);



	auto myLabel = Label::createWithTTF("Torchase", "fonts/Raven Song.ttf", visibleSize.height/9);
	myLabel->setAnchorPoint(Vec2(0,0));
	myLabel->setPosition(visibleSize.width/20, visibleSize.height-myLabel->getBoundingBox().size.height*3/2);
	this->addChild(myLabel);
	//========================Menu
	Vector<MenuItem*> menuArr;
	auto Label = Label::createWithTTF("Play", "fonts/Raven Song.ttf", visibleSize.height / 18);
	auto btn = MenuItemLabel::create(Label, CC_CALLBACK_1(MainMenuScene::PlayMenu, this));
	btn->setAnchorPoint(Vec2(0, 1));

	menuArr.pushBack(btn);

	Label = Label::createWithTTF("Option", "fonts/Raven Song.ttf", visibleSize.height / 18);
	btn = MenuItemLabel::create(Label, CC_CALLBACK_1(MainMenuScene::OptionMenu, this));
	btn->setAnchorPoint(Vec2(0, 1));

	menuArr.pushBack(btn);

	Label = Label::createWithTTF("Exit", "fonts/Raven Song.ttf", visibleSize.height / 18);
	btn = MenuItemLabel::create(Label, CC_CALLBACK_1(MainMenuScene::menuCloseCallback, this));
	btn->setAnchorPoint(Vec2(0, 1));

	menuArr.pushBack(btn);

	menu = Menu::createWithArray(menuArr);
	menu->setPosition(Vec2(myLabel->getPositionX(), myLabel->getPositionY()-myLabel->getContentSize().height));
	menu->alignItemsVerticallyWithPadding(10);

	menu->setAnchorPoint(Vec2(0, 0));

	this->addChild(menu);


	//=================PlayLevel
	menuArr.clear();
	Label = Label::createWithTTF("Continue", "fonts/Raven Song.ttf", visibleSize.height / 18);
	btn = MenuItemLabel::create(Label, CC_CALLBACK_1(MainMenuScene::LevelMenu, this));
	btn->setAnchorPoint(Vec2(0, 1));

	menuArr.pushBack(btn);

	Label = Label::createWithTTF("New Game", "fonts/Raven Song.ttf", visibleSize.height / 18);
	btn = MenuItemLabel::create(Label, CC_CALLBACK_1(MainMenuScene::LevelMenu, this));
	btn->setAnchorPoint(Vec2(0, 1));

	menuArr.pushBack(btn);

	Label = Label::createWithTTF("Back", "fonts/Raven Song.ttf", visibleSize.height / 18);
	btn = MenuItemLabel::create(Label, CC_CALLBACK_1(MainMenuScene::MainMenu, this));
	btn->setAnchorPoint(Vec2(0, 1));

	menuArr.pushBack(btn);

	menuPlay = Menu::createWithArray(menuArr);
	menuPlay->setPosition(Vec2(myLabel->getPositionX(), myLabel->getPositionY() - myLabel->getContentSize().height));
	menuPlay->alignItemsVerticallyWithPadding(10);
		
	menuPlay->setAnchorPoint(Vec2(0, 0));
	menuPlay->setVisible(false);
	this->addChild(menuPlay);

	//=================LevelMenu
	menuArr.clear();
	Label = Label::createWithTTF("Easy", "fonts/Raven Song.ttf", visibleSize.height / 18);
	btn = MenuItemLabel::create(Label, CC_CALLBACK_1(MainMenuScene::gotoPlayScreen, this));
	btn->setAnchorPoint(Vec2(0, 1));
	btn->setTag(0);
	menuArr.pushBack(btn);

	Label = Label::createWithTTF("Normal", "fonts/Raven Song.ttf", visibleSize.height / 18);
	btn = MenuItemLabel::create(Label, CC_CALLBACK_1(MainMenuScene::gotoPlayScreen, this));
	btn->setAnchorPoint(Vec2(0, 1));
	btn->setTag(1);

	menuArr.pushBack(btn);

	Label = Label::createWithTTF("Hard", "fonts/Raven Song.ttf", visibleSize.height / 18);
	btn = MenuItemLabel::create(Label, CC_CALLBACK_1(MainMenuScene::gotoPlayScreen, this));
	btn->setAnchorPoint(Vec2(0, 1));
	btn->setTag(2);

	menuArr.pushBack(btn);

	Label = Label::createWithTTF("Back", "fonts/Raven Song.ttf", visibleSize.height / 18);
	btn = MenuItemLabel::create(Label, CC_CALLBACK_1(MainMenuScene::MainMenu, this));
	btn->setAnchorPoint(Vec2(0, 1));

	menuArr.pushBack(btn);

	menuLevel = Menu::createWithArray(menuArr);
	menuLevel->setPosition(Vec2(myLabel->getPositionX(), myLabel->getPositionY() - myLabel->getContentSize().height));
	menuLevel->alignItemsVerticallyWithPadding(10);
		
	menuLevel->setAnchorPoint(Vec2(0, 0));
	menuLevel->setVisible(false);
	this->addChild(menuLevel);
	
	//==============================
	return true;

}
void MainMenuScene::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}
void MainMenuScene::PlayMenu(Ref* pSender) {
	menu->setVisible(false);
	menuPlay->setVisible(true);
	menuLevel->setVisible(false);
}
void  MainMenuScene::LevelMenu(cocos2d::Ref* pSender) {
	menu->setVisible(false);
	menuPlay->setVisible(false);
	menuLevel->setVisible(true);
}
void MainMenuScene ::MainMenu(cocos2d::Ref* pSender) {
	menu->setVisible(true);
	menuPlay->setVisible(false);
	menuLevel->setVisible(false);
}
void MainMenuScene::gotoPlayScreen(cocos2d::Ref* pSender) {
	
	auto node = dynamic_cast<Node*>(pSender);
	

	auto scene = GameScene::createScene();

	log("%d", node->getTag());
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}
void  MainMenuScene::OptionMenu(cocos2d::Ref* pSender) {
}


