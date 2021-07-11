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

#include "TrapBear.h"
#include "Definitions.h"
#include "ui\CocosGUI.h"

USING_NS_CC;
TrapBear::TrapBear() : Trap("prefap/trap/Bear_Trap.png", Rect(0, 0, 32, 32)) {

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	type = 2;
	this->setScale(4.0f);

	Vector<SpriteFrame*>  animFrames;

	animFrames.pushBack(SpriteFrame::create(name, Rect(0, 0, 32, 32)));
	animFrames.pushBack(SpriteFrame::create(name, Rect(32, 0, 32, 32)));
	animFrames.pushBack(SpriteFrame::create(name, Rect(64, 0, 32, 32)));
	animFrames.pushBack(SpriteFrame::create(name, Rect(96, 0, 32, 32)));
	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
	Animate* animate = Animate::create(animation);
	_Animation.pushBack(animate);

	Vector<SpriteFrame*>  animFramesOut;
	animFramesOut.pushBack(SpriteFrame::create(name, Rect(165, 0, 28, 32)));
	animFramesOut.pushBack(SpriteFrame::create(name, Rect(133, 0, 28, 32)));
	animFramesOut.pushBack(SpriteFrame::create(name, Rect(101, 0, 28, 32)));
	animFramesOut.pushBack(SpriteFrame::create(name, Rect(79, 0, 28, 32)));
	animFramesOut.pushBack(SpriteFrame::create(name, Rect(32, 0, 28, 32)));
	animFramesOut.pushBack(SpriteFrame::create(name, Rect(0, 0, 28, 32)));
	Animation* animations = Animation::createWithSpriteFrames(animFramesOut, 0.2f);
	Animate* animates = Animate::create(animations);
	_AnimationOut.pushBack(animates);

}
TrapBear::TrapBear(std::string name) {

	this->initWithFile(name);
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
}
TrapBear::TrapBear(std::string filename, cocos2d::Rect rect)
{
	this->initWithFile(filename,rect);
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
}
void TrapBear::HitPlayer()
{
	// chay animation
	this->setLocalZOrder(40);
	auto animationAction = RepeatForever::create(_Animation.at(0));
	this->runAction(_Animation.at(0));
	work = false;
}
