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

#include "WallCrake.h"
#include "Definitions.h"

USING_NS_CC;

WallCrake::WallCrake() :Iteam("prefap/Iteam/Wall1.png", Rect(0, 0, 128, 104)) {
	name = "prefap/Iteam/RandomBox.png";
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	type = 5;
	//this->setScale(3.5f);
	WallCrake::setAnimation();
}
void WallCrake::setAnimation()
{
	Vector<SpriteFrame*>  animFrames;
	animFrames.pushBack(SpriteFrame::create("prefap/Iteam/Wall1.png", Rect(0, 0, 128, 104)));
	animFrames.pushBack(SpriteFrame::create("prefap/Iteam/Wall2.png", Rect(0, 0, 128, 104)));
	animFrames.pushBack(SpriteFrame::create("prefap/Iteam/Wall3.png", Rect(0, 0, 128, 129)));
	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
	Animate* animate = Animate::create(animation);
	_Animation.pushBack(animate);

}
void WallCrake::HitMinion()
{
	check = true;
	this->stopAllActions();
	auto callback = CallFunc::create([&]() {
		check = false;
		this->stopAllActions();
		this->removeFromParent();
		this->setVisible(false);
		this->setLocalZOrder(20);
		this->setTexture("prefap/Iteam/Wall1.png");
		this->setTextureRect(Rect(0, 0, 128, 104));
	});
	auto sequence = Sequence::create(_Animation.at(0), callback, nullptr);
	this->runAction(sequence);
}