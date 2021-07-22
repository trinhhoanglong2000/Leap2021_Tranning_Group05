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

#include "StoryScene.h"
#include "GameScene.h"
#include "Definitions.h"
#include "AudioEngine.h"
#include "SoundManager.h"
USING_NS_CC;

int Level_of_difficult_temp;
int controller_temp;
Scene* StoryScene::createScene(int Level_of_difficult_Scene, int controller_Scene)
{
	Level_of_difficult_temp = Level_of_difficult_Scene;
	controller_temp = controller_Scene;
	return StoryScene::create();
	//return GameScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool StoryScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto BgSprite = Sprite::create("city_night.png");
	BgSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	BgSprite->setScale(visibleSize.width / BgSprite->getContentSize().width, visibleSize.height / BgSprite->getContentSize().height);
	this->addChild(BgSprite);

	LableStory = Label::createWithTTF("The story is about a father John and his son Tommy. The father works as \n\na night guard for a museum in the city. One day, Tommy's aunt was away \n\nand couldn't help his father taking care of him.", "fonts/Balsoon.ttf", visibleSize.height / 15);
	LableStory->setPosition(Point(visibleSize.width / 22, visibleSize.height * 3.5 / 5));
	LableStory->setAnchorPoint(Vec2(0, 1));
	this->addChild(LableStory,20);


	auto Label = Label::createWithTTF("Play", "fonts/Balsoon.ttf", visibleSize.height / 10);
	auto btn = MenuItemLabel::create(Label, CC_CALLBACK_1(StoryScene::gotoPlayScreen, this));
	btnSkip = Menu::create(btn,NULL);
	btnSkip->setPosition(visibleSize.width * 9 / 10, visibleSize.height / 7);
	btnSkip->setVisible(false);
	this->addChild(btnSkip,50);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(StoryScene::TouchMoveBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

	story.push_back("So the father took his son with him on duty. With the curiosity of a child, \n\nTommy accidentally activated an ancient treasure and was imprisoned in the \n\nbuilding. You must help John find his way to Tommy's cell by collecting items");
	story.push_back("that are left somewhere in the rooms. Be careful of the monsters along \n\nthe way and kill them by luring them into traps with your Tourch. Note that \n\nthe Torch's battery is limited and we don't have much time left to save Tommy.");
	num_story = 0;
	check = false;
    return true;
}
void StoryScene::gotoPlayScreen(Ref* pSender) {

	//auto node = dynamic_cast<Node*>(pSender);
	auto scene = GameScene::createScene(Level_of_difficult_temp, controller_temp);
	SoundManager::getInstance()->stopMusic(MAINMENU_SOUND);
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}


void StoryScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}
bool StoryScene::TouchMoveBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
	if (check == true)
		return true;
	if (num_story > 1 && check ==false)
	{
		check = true;
		auto scene = GameScene::createScene(Level_of_difficult_temp, controller_temp);
		SoundManager::getInstance()->stopMusic(MAINMENU_SOUND);
		Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
		return true;
	}
	
	LableStory->setString(story.at(num_story));
	if(num_story==1)
		btnSkip->setVisible(true);
	num_story++;
	return true;
}	
