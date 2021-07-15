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

#include "TrapPlant.h"
#include "Definitions.h"
#include "ui\CocosGUI.h"

USING_NS_CC;
TrapPlant::TrapPlant() : Trap("prefap/trap/Plant.png", Rect(0, 0, 28, 32)) {

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	type = 1;
	this->setScale(3.0f);
	enegy = ui::Slider::create();
	enegy->loadBarTexture("Slider_Back.png"); 
	//enegy->loadSlidBallTextures("SliderNode_Normal.png", "SliderNode_Press.png", "SliderNode_Disable.png");
	enegy->loadProgressBarTexture("Slider_PressBar.png");
	enegy->setPosition(Vec2(this->getPositionX() + enegy->getContentSize().width/3 * 0.25f,this->getPositionY()+this->getContentSize().height/2.5 * 3.0f) );
	enegy->setMaxPercent(10);
	enegy->setPercent(enegy->getMaxPercent());
	enegy->setScale(0.25f);

	this->addChild(enegy);
	enegy->setVisible(false);

	Vector<SpriteFrame*>  animFrames;

	animFrames.pushBack(SpriteFrame::create("prefap/trap/Plant.png", Rect(0, 0, 28, 32)));
	animFrames.pushBack(SpriteFrame::create("prefap/trap/Plant.png", Rect(32, 0, 28, 32)));
	animFrames.pushBack(SpriteFrame::create("prefap/trap/Plant.png", Rect(79, 0, 28, 32)));
	animFrames.pushBack(SpriteFrame::create("prefap/trap/Plant.png", Rect(101, 0, 28, 32)));
	animFrames.pushBack(SpriteFrame::create("prefap/trap/Plant.png", Rect(133, 0, 28, 32)));
	animFrames.pushBack(SpriteFrame::create("prefap/trap/Plant.png", Rect(165, 0, 28, 32)));
	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
	Animate* animate = Animate::create(animation);
	_Animation.pushBack(animate);

	Vector<SpriteFrame*>  animFramesOut;
	animFramesOut.pushBack(SpriteFrame::create("prefap/trap/Plant.png", Rect(165, 0, 28, 32)));
	animFramesOut.pushBack(SpriteFrame::create("prefap/trap/Plant.png", Rect(133, 0, 28, 32)));
	animFramesOut.pushBack(SpriteFrame::create("prefap/trap/Plant.png", Rect(101, 0, 28, 32)));
	animFramesOut.pushBack(SpriteFrame::create("prefap/trap/Plant.png", Rect(79, 0, 28, 32)));
	animFramesOut.pushBack(SpriteFrame::create("prefap/trap/Plant.png", Rect(32, 0, 28, 32)));
	animFramesOut.pushBack(SpriteFrame::create("prefap/trap/Plant.png", Rect(0, 0, 28, 32)));
	Animation* animations = Animation::createWithSpriteFrames(animFramesOut, 0.2f);
	Animate* animates = Animate::create(animations);
	_AnimationOut.pushBack(animates);

}
TrapPlant::TrapPlant(std::string name) {

	this->initWithFile(name);
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
}
TrapPlant::TrapPlant(std::string filename, cocos2d::Rect rect)
{
	this->initWithFile(filename,rect);
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
}
void TrapPlant::AddSlider()
{
	enegy->setVisible(true);
}
void TrapPlant::HitPlayer()
{
	this->stopAllActions();
	TrapPlant::AddSlider();
	// chay animation
	this->setLocalZOrder(40);
	auto animationAction = RepeatForever::create(_Animation.at(0));
	this->runAction(_Animation.at(0));
}
void TrapPlant::ReduceSlider()
{
	enegy->setPercent(enegy->getPercent() - 1);
	if (enegy->getPercent() <= 0)
	{
		this->setLocalZOrder(20);
		this->stopAllActions();
		auto animationAction = RepeatForever::create(_AnimationOut.at(0));
		this->runAction(_AnimationOut.at(0));

		this->schedule(CC_SCHEDULE_SELECTOR(TrapPlant::PlusSlider), 1.0f);
	}
}
void TrapPlant::PlusSlider(float dt)
{
	enegy->setPercent(enegy->getPercent() + 2);
	if (enegy->getPercent() >= enegy->getMaxPercent())
	{
		enegy->setVisible(false);
		this->unschedule(CC_SCHEDULE_SELECTOR(TrapPlant::PlusSlider));
	}
}
void TrapPlant::reset()
{
	enegy->setPercent(enegy->getMaxPercent());
	enegy->setVisible(false);
}