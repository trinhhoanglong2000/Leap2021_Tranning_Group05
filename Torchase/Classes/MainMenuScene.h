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

#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__

#include "cocos2d.h"
#include "Player.h"
#include "ui\CocosGUI.h"

USING_NS_CC;

class MainMenuScene : public cocos2d::Scene
{


public:
    static cocos2d::Scene* createScene();
    virtual bool init();
	CREATE_FUNC(MainMenuScene);
private:

	Menu* menu;
	Menu* menuPlay;
	Menu* menuLevelContinue;
	Menu* menuLevelNew;
	Menu* optionMenu;
	DrawNode* layout;
	MenuItemToggle* toggle1, *toggle2;
	UserDefault *def;
	bool continueGame;
	void PlayMenu(cocos2d::Ref* pSender);
	void Tutorial(cocos2d::Ref* pSender);
	void CloseTutorial(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType Type);
	void NextTutorial(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType Type);
	void PreviousTutorial(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType Type);
	void LevelMenuContinue(cocos2d::Ref* pSender);
	void LevelMenuNew(cocos2d::Ref* pSender);
	void MainMenu(cocos2d::Ref* pSender);
	void OptionMenu(cocos2d::Ref* pSender);

	void menuCloseCallback(cocos2d::Ref* pSender);
	void gotoPlayScreen(cocos2d::Ref* pSender);
	void gotoStoryScreen(cocos2d::Ref* pSender);
	void OnOFF(cocos2d::Ref* pSender);
	void setoption();
	cocos2d::Vector<cocos2d::Sprite*> all_Tutorial;

	cocos2d::ui::Layout *layout_tutorial;
	int mindTutorial;
};

#endif // __MAINMENU_SCENE_H__
