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
#include "StoryScene.h"
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

	SoundManager::getInstance()->PlayMusics(MAINMENU_SOUND, true, 1);

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
	btn = MenuItemLabel::create(Label, CC_CALLBACK_1(MainMenuScene::LevelMenuContinue, this));
	btn->setAnchorPoint(Vec2(0, 1));

	menuArr.pushBack(btn);

	Label = Label::createWithTTF("New Game", "fonts/Raven Song.ttf", visibleSize.height / 18);
	btn = MenuItemLabel::create(Label, CC_CALLBACK_1(MainMenuScene::LevelMenuNew, this));
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

	//=================LevelMenu for Continue
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

	menuLevelContinue = Menu::createWithArray(menuArr);
	menuLevelContinue->setPosition(Vec2(myLabel->getPositionX(), myLabel->getPositionY() - myLabel->getContentSize().height));
	menuLevelContinue->alignItemsVerticallyWithPadding(10);
		
	menuLevelContinue->setAnchorPoint(Vec2(0, 0));
	menuLevelContinue->setVisible(false);
	this->addChild(menuLevelContinue);
	
	//=================LevelMenu for New
	menuArr.clear();
	Label = Label::createWithTTF("Easyy", "fonts/Raven Song.ttf", visibleSize.height / 18);
	btn = MenuItemLabel::create(Label, CC_CALLBACK_1(MainMenuScene::gotoStoryScreen, this));
	btn->setAnchorPoint(Vec2(0, 1));
	btn->setTag(3);
	menuArr.pushBack(btn);

	Label = Label::createWithTTF("Normall", "fonts/Raven Song.ttf", visibleSize.height / 18);
	btn = MenuItemLabel::create(Label, CC_CALLBACK_1(MainMenuScene::gotoStoryScreen, this));
	btn->setAnchorPoint(Vec2(0, 1));
	btn->setTag(4);

	menuArr.pushBack(btn);

	Label = Label::createWithTTF("Hardd", "fonts/Raven Song.ttf", visibleSize.height / 18);
	btn = MenuItemLabel::create(Label, CC_CALLBACK_1(MainMenuScene::gotoStoryScreen, this));
	btn->setAnchorPoint(Vec2(0, 1));
	btn->setTag(5);

	menuArr.pushBack(btn);

	Label = Label::createWithTTF("Back", "fonts/Raven Song.ttf", visibleSize.height / 18);
	btn = MenuItemLabel::create(Label, CC_CALLBACK_1(MainMenuScene::MainMenu, this));
	btn->setAnchorPoint(Vec2(0, 1));

	menuArr.pushBack(btn);

	menuLevelNew = Menu::createWithArray(menuArr);
	menuLevelNew->setPosition(Vec2(myLabel->getPositionX(), myLabel->getPositionY() - myLabel->getContentSize().height));
	menuLevelNew->alignItemsVerticallyWithPadding(10);

	menuLevelNew->setAnchorPoint(Vec2(0, 0));
	menuLevelNew->setVisible(false);
	this->addChild(menuLevelNew);

	//==============================Option
	menuArr.clear();
	//auto layout = ui::Layout::create();
	//layout->setPosition(400, 400);
	//layout->setBackGroundColor()
	layout = DrawNode::create();

	int width = (menu->getPositionX() + myLabel->getBoundingBox().size.width*1.5);
	int height = menu->getPositionY()*3/4;
	Vec2 vertices[] =
	{
		Vec2(0,height),
		Vec2(width,height),
		Vec2(width,0),
		Vec2(0,0)
	};

	layout->setContentSize(Size(width, height));
	layout->drawPolygon(vertices, 4, Color4F(Color3B::GRAY, 0.1f), 2, Color4F(Color3B::GRAY, 0.5));
	layout->setAnchorPoint(Vec2(0, 0));
	layout->setPosition(menu->getPositionX()+ myLabel->getBoundingBox().size.width/2,menu->getPositionY()/2);
	
	this->addChild(layout);
	auto start = MenuItemImage::create("On.png", "On.png");
	auto off = MenuItemImage::create("OFF.png", "OFF.png");
	auto start1 = MenuItemImage::create("On.png", "On.png");
	auto off1 = MenuItemImage::create("OFF.png", "OFF.png");
	
	auto title1 = MenuItemFont::create("Swipe Gesture");
	auto title2 = MenuItemFont::create("Controller");
	start->setColor(Color3B::WHITE);
	toggle1 = MenuItemToggle::createWithCallback(
		CC_CALLBACK_1(MainMenuScene::OnOFF, this),
		off, start, NULL);
	toggle1->setTag(1);
	toggle1->setScale(0.5f);
	toggle2 = MenuItemToggle::createWithCallback(
		CC_CALLBACK_1(MainMenuScene::OnOFF, this),
		off1, start1, NULL);
	toggle2->setTag(2);
	toggle2->setScale(0.5f);
	toggle1->setSelectedIndex(1);

	
	
	menuArr.pushBack(title1);
	menuArr.pushBack(title2);

	menuArr.pushBack(toggle1);
	

	menuArr.pushBack(toggle2);
	
	optionMenu = Menu::createWithArray(menuArr);
	optionMenu->setContentSize(layout->getContentSize()*1.5f);

	layout->addChild(optionMenu);
	optionMenu->setPosition(layout->getPositionX()+layout->getContentSize().width/9, layout->getPositionY());
	optionMenu->alignItemsInColumns(2,2);
	
	
	toggle1->setPositionX(title1->getPositionX());
	
	toggle2->setPositionX(title2->getPositionX());


	layout->setVisible(false);
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
	menuLevelContinue->setVisible(false);
	menuLevelNew->setVisible(false);
	layout->setVisible(false);
}
void MainMenuScene::LevelMenuContinue(cocos2d::Ref* pSender) {
	menu->setVisible(false);
	menuPlay->setVisible(false);
	menuLevelContinue->setVisible(true);
	menuLevelNew->setVisible(false);
	layout->setVisible(false);
}
void MainMenuScene::LevelMenuNew(cocos2d::Ref* pSender) {
	menu->setVisible(false);
	menuPlay->setVisible(false);
	menuLevelContinue->setVisible(false);
	menuLevelNew->setVisible(true);
	layout->setVisible(false);
}
void MainMenuScene ::MainMenu(cocos2d::Ref* pSender) {
	menu->setVisible(true);
	menuPlay->setVisible(false);
	menuLevelContinue->setVisible(false);
	menuLevelNew->setVisible(false);
	layout->setVisible(false);
}
void MainMenuScene::gotoPlayScreen(cocos2d::Ref* pSender) {
	
	auto node = dynamic_cast<Node*>(pSender);
	auto scene = GameScene::createScene(node->getTag(), toggle1->getSelectedIndex());
	SoundManager::getInstance()->stopMusic(MAINMENU_SOUND);
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}
void MainMenuScene::gotoStoryScreen(cocos2d::Ref* pSender) {

	auto node = dynamic_cast<Node*>(pSender);
	auto scene = StoryScene::createScene(node->getTag(), toggle1->getSelectedIndex());
	SoundManager::getInstance()->stopMusic(MAINMENU_SOUND);
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}
void  MainMenuScene::OptionMenu(cocos2d::Ref* pSender) {
	layout->setVisible(true);
}
void MainMenuScene::OnOFF(cocos2d::Ref* pSender) {
	auto node = dynamic_cast<Node*>(pSender);
	int i = toggle1->getSelectedIndex();
	if (node->getTag() == 1 && i == 0)
	{
		toggle1->setSelectedIndex(1);
		toggle2->setSelectedIndex(0);
		return;
	}
	if (node->getTag() == 2 && i == 0)
	{
		toggle1->setSelectedIndex(0);
		toggle2->setSelectedIndex(1);
		return;
	}
	if (node->getTag() == 1)
	{
		toggle2->setSelectedIndex((i+1)%2);
	}
	else
	{
		toggle1->setSelectedIndex((i + 1) % 2);
	}
	
	
}


