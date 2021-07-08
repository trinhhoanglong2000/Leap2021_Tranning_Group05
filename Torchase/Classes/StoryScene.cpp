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

	auto Story = Label::createWithTTF("The story is about a father and his son named John and Tommy. The father\nworks as a night guard for a museum in the city.One day, Tommy's aunt was away and couldn't \nhelp his father taking care of him so the father took his son with him on duty.\nWith the curiosity of a child, Tommy accidentally activated an ancient treasure and was\nimprisoned in the building. You must help John find his way to Tommy's cell by collecting items\nthat are left somewhere in the rooms.\nBe careful of the monsters along the way and kill them by luring them into traps with your\nTourch. Note that the Torch's battery is limited and we don't have much time left to\nsave Tommy.", "fonts/Raven Song.ttf", 25);
	Story->setPosition(Point(visibleSize.width / 22, visibleSize.height * 4 / 5));
	Story->setAnchorPoint(Vec2(0, 1));
	this->addChild(Story,20);


	auto Label = Label::createWithTTF("Play", "fonts/Raven Song.ttf", visibleSize.height / 18);
	auto btn = MenuItemLabel::create(Label, CC_CALLBACK_1(StoryScene::gotoPlayScreen, this));
	btnSkip = Menu::create(btn,NULL);
	btnSkip->setPosition(visibleSize.width * 9 / 10, visibleSize.height / 8);

	this->addChild(btnSkip,50);


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
