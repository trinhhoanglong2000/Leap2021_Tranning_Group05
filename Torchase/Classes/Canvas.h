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

#ifndef __CANVAS_H__
#define __CANVAS_H__

#include "ui\CocosGUI.h"
#include"Player.h"
#include "Minions.h"
#include "Trap.h"
#include "TrapPlant.h"
#include "cocos2d.h"
#include "Son.h"

class Canvas : public cocos2d::ui::Layout
{
	
public:
	Canvas(Player *playerScene, cocos2d::DrawNode* background_offScene, int controller, cocos2d::Scene *sceneGame, int &_gameState, int levelGame);
	
	bool TouchMoveBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	bool TouchMoveEnd(cocos2d::Touch *touch, cocos2d::Event *event);
	bool TouchMoveMove(cocos2d::Touch *touch, cocos2d::Event *event);

	void MoveUp(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType Type);
	void MoveDow(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType Type);
	void MoveLeft(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType Type);
	void MoveRight(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType Type);
	void PauseScene(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType Type);
	void GotoMainMenu(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType Type);
	//void ResumeScene(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType Type);
	void OnOffLight(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType Type);
	void PutTrap(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType Type);
	void reduceenergy(float dt);
	void autoplusenergy(float dt);
	void plusenergy(int power);
	void AutoMove(float dt);
	void reducePlant();
	void Goagain(bool light);
	void goup(float dt);
	void meet();
	void actionmeet(float dt);
	void movemeet(float dt);
	void OnButtonController();
	void ontalk();
	void offtalk();
	cocos2d::Vector<Minions*> AllMinions;
	cocos2d::Vector<Trap*> AllTrap;
	cocos2d::DrawNode* background_off;
	bool endlight;
	cocos2d::ui::Slider *enegy;
	TrapPlant *plant;
	cocos2d::TMXLayer *_meta;
	int maxmap;
	Son *son;
	cocos2d::Vec2 playerNow;
	int level;
	int num_talk;
private:
	Player *player;	
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	cocos2d::SEL_SCHEDULE Schedule_ReduceEnegy;
	int int_move;
	int mind_move;
	bool BoolTouch;
	bool touchpause = false;
	bool talk = true;
	bool waittalk = false;
	int controller_canvas;
	cocos2d::ui::Button *ButtonUp, *ButtonDow, *ButtonLeft, *ButtonRight,
						*ButtonPause, *ButtonResume, *ButtonHome, *ButtonLight, *ButtonTrap, *ButtonConvert;
	cocos2d::ui::Text *TXT_Number;
	cocos2d::Scene *scene;
	
	int *gameState;
	cocos2d::Menu *pauseMenu;
	cocos2d::Sprite *pauseBackgr, *talkboxBachgr;
	cocos2d::Label *LableTalk;
	cocos2d::UserDefault *def;
	
	std::vector<std::string> talkbox;
};

#endif // __CANVAS_H__
