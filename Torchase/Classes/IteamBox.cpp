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

#include "IteamBox.h"
#include "Definitions.h"

USING_NS_CC;

IteamBox::IteamBox() :Iteam("prefap/Iteam/RandomBox.png", Rect(256, 0, 32, 32)) {
	name = "prefap/Iteam/RandomBox.png";
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	type = 3;
	this->setScale(3.5f);
	IteamBox::setAnimation();
}
void IteamBox::setAnimation()
{
	Vector<SpriteFrame*>  animFrames;
	animFrames.pushBack(SpriteFrame::create(name, Rect(0, 0, 32, 32)));
	animFrames.pushBack(SpriteFrame::create(name, Rect(0, 0, 32, 32)));
	animFrames.pushBack(SpriteFrame::create(name, Rect(0, 0, 32, 32)));
	animFrames.pushBack(SpriteFrame::create(name, Rect(0, 0, 32, 32)));
	animFrames.pushBack(SpriteFrame::create(name, Rect(32, 0, 32, 32)));
	animFrames.pushBack(SpriteFrame::create(name, Rect(64, 0, 32, 32)));
	animFrames.pushBack(SpriteFrame::create(name, Rect(96, 0, 32, 32)));
	animFrames.pushBack(SpriteFrame::create(name, Rect(128, 0, 32, 32)));
	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
	Animate* animate = Animate::create(animation);
	_Animation.pushBack(animate);

	animFrames.clear();
	animFrames.pushBack(SpriteFrame::create(name, Rect(256, 0, 32, 32)));
	animFrames.pushBack(SpriteFrame::create(name, Rect(288, 0, 32, 32)));
	animFrames.pushBack(SpriteFrame::create(name, Rect(320, 0, 32, 32)));
	animFrames.pushBack(SpriteFrame::create(name, Rect(352, 0, 32, 32)));
	animFrames.pushBack(SpriteFrame::create(name, Rect(384, 0, 32, 32)));
	animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
	animate = Animate::create(animation);
	_Animation.pushBack(animate);

	auto animationAction = RepeatForever::create(_Animation.at(0));
	this->runAction(animationAction);
}
void IteamBox::HitPlater()
{
	check = true;
	this->stopAllActions();
	auto callback = CallFunc::create([&]() {
		this->stopAllActions();
		this->removeFromParent();
	});
	auto sequence = Sequence::create(_Animation.at(1), callback, nullptr);
	this->runAction(sequence);
}