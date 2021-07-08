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

#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include"Player.h"
#include "Minions.h"
#include "TrapPlant.h"

class Canvas : public cocos2d::ui::Layout
{
public:
	Canvas(Player *playerScene, cocos2d::DrawNode* background_offScene, int controller);
	
	bool TouchMoveBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	bool TouchMoveEnd(cocos2d::Touch *touch, cocos2d::Event *event);
	bool TouchMoveMove(cocos2d::Touch *touch, cocos2d::Event *event);

	void MoveUp(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType Type);
	void MoveDow(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType Type);
	void MoveLeft(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType Type);
	void MoveRight(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType Type);
	void OnOffLight(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType Type);
	void reduceenergy(float dt);
	void plusenergy(int power);
	void AutoMove(float dt);
	void reducePlant();
	cocos2d::Vector<Minions*> AllMinions;
	cocos2d::DrawNode* background_off;
	bool endlight;
	cocos2d::ui::Slider *enegy;
	TrapPlant *plant;
private:
	Player *player;
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	
	cocos2d::SEL_SCHEDULE Schedule_ReduceEnegy;
	int int_move;
	bool BoolTouch;
	int controller_canvas;
	cocos2d::ui::Button *ButtonUp, *ButtonDow, *ButtonLeft, *ButtonRight;
};

#endif // __CANVAS_H__
