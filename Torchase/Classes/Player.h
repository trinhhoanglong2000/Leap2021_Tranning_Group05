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

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include"Actor.h"
#include "SoundManager.h"

class Player : public Actor
{
public:
	Player();
	void MoveUp();
	void MoveDow();
	void MoveLeft();
	void MoveRight();
	void OnOffLight();
	void removeAction();
	void GoToAgain(float dt);
	int mind;
	void setFalseMove();
	void setTrueMove(float dt);
	void setActionDie(float dt);
	void setBlackVisionBG(cocos2d::Size size);
	void Playerdie();
	bool checkMove;
	//void  GoToGameOver(float dt);
	void createHeal();
	bool stop;
	void changeTravelTime(float value);
	void resetTravelTime(float dt);
	void changeHeal();
	cocos2d::DrawNode *background;
	bool die;
	int NumHeal;
private:
	cocos2d::UserDefault *def;
	int thickness = 400;
	int width = 1000;
	int height = 1200;
	cocos2d::Vector<cocos2d::SpriteFrame*> stand;
	cocos2d::SEL_SCHEDULE Schedule_reverse;
	cocos2d::Vector<cocos2d::Sprite*> vecHeal;
	
};

#endif // __PLAYER_H__
