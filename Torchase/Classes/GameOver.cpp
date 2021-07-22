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

#include "GameOver.h"
#include "Definitions.h"
#include "MainMenuScene.h"
#include "GameScene.h"
USING_NS_CC;

int controll;
int finish;
Scene* GameOver::createScene(int controller_Scene, bool finish_Scene)
{
	controll = controller_Scene;
	finish = finish_Scene;
    return GameOver::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameOver::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	def = UserDefault::getInstance();
	def->setBoolForKey("INGAME_OverGame", true);
	level = def->getIntegerForKey("INGAME_Level", 1);
	Level_of_difficult = def->getIntegerForKey("INGAME_CONTINUE_LEVEL", 0);
	std::string win = "You Lose!!!";
	if (finish == true)
	{
		level++;
		def->setIntegerForKey("INGAME_Level", level);
		win = "You Win!!!";
	}

	SoundManager::getInstance()->stopALLMusic();
	SoundManager::getInstance()->PlayMusics(EVIL_LAUGH, false, 1);
	SoundManager::getInstance()->PlayMusics(GAME_OVER_SOUND, true, 1.0f);

	auto BgSprite = Sprite::create("coco2d.png");
	BgSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(BgSprite);

	auto myLabel = Label::createWithTTF(win, "fonts/Raven Song.ttf", visibleSize.height / 9);
	myLabel->setAnchorPoint(Vec2(0.5, 0));
	myLabel->setPosition(visibleSize.width / 2, visibleSize.height - myLabel->getBoundingBox().size.height * 3 / 2);
	this->addChild(myLabel);
	//========================Menu
	Vector<MenuItem*> menuArr;
	if (finish == true)
	{
		auto Labelnext = Label::createWithTTF("Next Game", "fonts/Raven Song.ttf", visibleSize.height / 18);
		auto btnnext = MenuItemLabel::create(Labelnext, CC_CALLBACK_1(GameOver::GoToGameSceneNext, this));
		btnnext->setAnchorPoint(Vec2(0, 1));

		menuArr.pushBack(btnnext);
	}

	auto Label = Label::createWithTTF("Replay", "fonts/Raven Song.ttf", visibleSize.height / 18);
	auto btn = MenuItemLabel::create(Label, CC_CALLBACK_1(GameOver::GoToGameScene, this));
	btn->setAnchorPoint(Vec2(0, 1));

	menuArr.pushBack(btn);

	Label = Label::createWithTTF("Home", "fonts/Raven Song.ttf", visibleSize.height / 18);
	btn = MenuItemLabel::create(Label, CC_CALLBACK_1(GameOver::GoToMainMenu, this));
	btn->setAnchorPoint(Vec2(0, 1));

	menuArr.pushBack(btn);

	menu = Menu::createWithArray(menuArr);
	menu->setPosition(Vec2(visibleSize.width / 20, myLabel->getPositionY() - myLabel->getContentSize().height));
	menu->alignItemsVerticallyWithPadding(30);

	menu->setAnchorPoint(Vec2(0, 0));


	this->addChild(menu);


    return true;
}
void GameOver::GoToMainMenu(cocos2d::Ref* pSender)
{
	SoundManager::getInstance()->stopMusic(EVIL_LAUGH);
	auto scene = MainMenuScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

void GameOver::GoToGameScene(cocos2d::Ref* pSender)
{
	if (finish == true)
	{
		level--;
		def->setIntegerForKey("INGAME_Level", level);
	}

	SoundManager::getInstance()->stopMusic(EVIL_LAUGH);
	auto scene = GameScene::createScene(4, controll);
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}
void GameOver::GoToGameSceneNext(cocos2d::Ref* pSender)
{
	SoundManager::getInstance()->stopMusic(EVIL_LAUGH);
	auto scene = GameScene::createScene(3, controll);
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}
void GameOver::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
