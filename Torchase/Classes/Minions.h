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

#ifndef __MINIONS_H__
#define __MINIONS_H__

#include "cocos2d.h"
#include"Actor.h"
#include "Player.h"

class Minions : public Actor
{
public:
	Minions();
	Minions(Player* playerScene, float mapspeed);
	void findPlayer(float dt);
	void findPlayerType0(float dt);
	void removeAction();
	void Roar(float dt);
	void lightoff();
	void lighton(float dt);
	bool boolFind;
	void die();
	void actiondie(float dt);
	void setplayer(Player* playerScene, float mapspeed);
	void changeTravelTime(float value);
	void resetTravelTime(float dt);
	void reset();
	int type;
	bool Booldie;
	float traveltime;
	bool hit;

protected:
	Player *player;
	bool booltop;
	bool boolright;
	bool boolleft;
	bool booldow;
	bool *booltro;
	bool goUp; 
	cocos2d::Vec2 mindPlayer;
	cocos2d::SEL_SCHEDULE Schedule_Roar;
	cocos2d::SEL_SCHEDULE Schedule_findPlayer;
	cocos2d::SEL_SCHEDULE Schedule_CheckfindPlayer;
	// type of enemy
};

#endif // __MINIONS_H__
