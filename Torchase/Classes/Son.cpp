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

#include "Son.h"
#include "Definitions.h"
#include "ui\CocosGUI.h"
#include "GameScene.h"
#include "GameOver.h"
USING_NS_CC;
Son::Son() : Actor("prefap/Player/george.png", Rect(0, 0, 48, 48))
{
	this->setScale(1.5f);
	traveltime = ACTOR_SPEED;
	auto PlayerBody = PhysicsBody::createBox(Size(this->getContentSize().width/2,this->getContentSize().height));
	PlayerBody->setCollisionBitmask(PLAYER_COLISION_BITMASK);
	PlayerBody->setCategoryBitmask(PLAYER_CATEGORY_BITMASK);
	PlayerBody->setContactTestBitmask(PLAYER_COLISION_BITMASK);
	PlayerBody->setDynamic(false);
	this->setPhysicsBody(PlayerBody);
	this->setTag(1);

	//push frame
	//Look up
	Vector<SpriteFrame*>  animFrames;
	animFrames.pushBack(SpriteFrame::create("prefap/Player/george.png", Rect(0, 0, 48, 48)));
	animFrames.pushBack(SpriteFrame::create("prefap/Player/george.png", Rect(0, 48, 48, 48)));
	animFrames.pushBack(SpriteFrame::create("prefap/Player/george.png", Rect(0, 96, 48, 48)));
	animFrames.pushBack(SpriteFrame::create("prefap/Player/george.png", Rect(0, 144, 48, 48)));
	animFrames.pushBack(SpriteFrame::create("prefap/Player/george.png", Rect(0, 0, 0, 0)));
	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
	
	Animate* animate = Animate::create(animation);
	Animates.pushBack(animate);

}
void Son::MoveUp()
{
	this->runAction(Animates.at(0));

}
