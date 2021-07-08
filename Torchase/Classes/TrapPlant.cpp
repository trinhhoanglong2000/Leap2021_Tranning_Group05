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
TrapPlant::TrapPlant() {

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	//this->initWithFile("prefap/trap/Bear_Trap.png", Rect(0,0,32,32));
	this->initWithFile("prefap/trap/Plant.png", Rect(0, 0, 28, 32));
	auto PlayerBody = PhysicsBody::createBox(this->getContentSize());
	PlayerBody->setCollisionBitmask(TRAP_PLANT_COLISION_BITMASK);
	PlayerBody->setCategoryBitmask(TRAP_PLANT_CATEGORY_BITMASK);
	PlayerBody->setContactTestBitmask(TRAP_PLANT_COLISION_BITMASK);
	PlayerBody->setDynamic(false);
	this->setPhysicsBody(PlayerBody);
	this->setScale(3.0f);
	enegy = ui::Slider::create();
	enegy->loadBarTexture("Slider_Back.png"); // what the slider looks like
	//enegy->loadSlidBallTextures("SliderNode_Normal.png", "SliderNode_Press.png", "SliderNode_Disable.png");
	enegy->loadProgressBarTexture("Slider_PressBar.png");
	enegy->setPosition(this->getPosition()+this->getContentSize());
	enegy->setMaxPercent(10);
	enegy->setPercent(enegy->getMaxPercent());
	enegy->setScale(0.5f);
	enegy->setGlobalZOrder(50);
	this->addChild(enegy);
	enegy->setVisible(false);

	//animation
	//Vector<SpriteFrame*>  animFrames;
	//animFrames.pushBack(SpriteFrame::create("prefap/trap/Bear_Trap.png", Rect(0,0,32,32)));
	//animFrames.pushBack(SpriteFrame::create("prefap/trap/Bear_Trap.png", Rect(32, 0, 32, 32)));
	//animFrames.pushBack(SpriteFrame::create("prefap/trap/Bear_Trap.png", Rect(64, 0, 32, 32)));
	//animFrames.pushBack(SpriteFrame::create("prefap/trap/Bear_Trap.png", Rect(96, 0, 32, 32)));


	//
	Vector<SpriteFrame*>  animFrames;
	/*animFrames.pushBack(SpriteFrame::create("prefap/trap/Plant.png", Rect(165, 0, 28, 32)));
	animFrames.pushBack(SpriteFrame::create("prefap/trap/Plant.png", Rect(133, 0, 28, 32)));
	animFrames.pushBack(SpriteFrame::create("prefap/trap/Plant.png", Rect(101, 0, 28, 32)));
	animFrames.pushBack(SpriteFrame::create("prefap/trap/Plant.png", Rect(79, 0, 28, 32)));*/
	animFrames.pushBack(SpriteFrame::create("prefap/trap/Plant.png", Rect(0, 0, 28, 32)));
	animFrames.pushBack(SpriteFrame::create("prefap/trap/Plant.png", Rect(32, 0, 28, 32)));
	animFrames.pushBack(SpriteFrame::create("prefap/trap/Plant.png", Rect(79, 0, 28, 32)));
	animFrames.pushBack(SpriteFrame::create("prefap/trap/Plant.png", Rect(101, 0, 28, 32)));
	animFrames.pushBack(SpriteFrame::create("prefap/trap/Plant.png", Rect(133, 0, 28, 32)));
	animFrames.pushBack(SpriteFrame::create("prefap/trap/Plant.png", Rect(165, 0, 28, 32)));
	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
	Animate* animate = Animate::create(animation);
	_Animation.pushBack(animate);


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
	//add animation trap_plant
	enegy->setVisible(true);
}
void TrapPlant::HitPlayer()
{
	
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
		enegy->setVisible(false);
		enegy->setPercent(enegy->getMaxPercent());
	}
}