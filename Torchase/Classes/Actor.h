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

#ifndef __Actor_H__
#define __Actor_H__

#include "cocos2d.h"

class Actor : public cocos2d::Sprite
{
public:
	Actor();
	Actor(std::string name);
	Actor(std::string filename, cocos2d::Rect rect);
	cocos2d::MoveTo * MoveUp();
	cocos2d::MoveTo * MoveDow();
	cocos2d::MoveTo * MoveLeft();
	cocos2d::MoveTo * MoveRight();
	void removeAction();
	float speed;
	cocos2d::Vec2 mindPositison;
protected:
	//static cocos2d::Camera *cam;
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	cocos2d::MoveTo *moveAction;
	cocos2d::Vector< cocos2d::Animate* > Animates;
};

#endif // __Actor_H__
