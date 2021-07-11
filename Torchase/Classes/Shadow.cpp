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

#include "Shadow.h"
#include "Definitions.h"

USING_NS_CC;




Shadow::Shadow(Player * playerScene, float mapspeed):	Minions( playerScene, mapspeed)
{
	
	type = 1;
	//down
	Vector<SpriteFrame*>  animFrames;
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(0, 0, 100, 150)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(100, 0, 100, 150)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(200, 0, 100, 150)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(300, 0, 100, 150)));

	//default
	this->setSpriteFrame(animFrames.at(0));
	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f);

	Animate* animate = Animate::create(animation);
	Animates.pushBack(animate);
	animFrames.clear();

	//up
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(0, 450, 100, 150)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(100, 450, 100, 150)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(200, 450, 100, 150)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(300, 450, 100, 150)));

	animation = Animation::createWithSpriteFrames(animFrames, 0.1f);

	animate = Animate::create(animation);
	Animates.pushBack(animate);
	animFrames.clear();

	//left
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(0, 150, 100, 150)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(100, 150, 100, 150)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(200, 150, 100, 150)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(300, 150, 100, 150)));

	animation = Animation::createWithSpriteFrames(animFrames, 0.1f);

	animate = Animate::create(animation);
	Animates.pushBack(animate);
	animFrames.clear();

	//right 
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(0, 300, 100, 150)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(100, 300, 100, 150)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(200, 300, 100, 150)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(300, 300, 100, 150)));

	animation = Animation::createWithSpriteFrames(animFrames, 0.1f);

	animate = Animate::create(animation);
	Animates.pushBack(animate);
	animFrames.clear();
	goUp = true;

	// die
	std::string minionnamedie = "prefap/Minions/ShadowDie.png";
	animFrames.pushBack(SpriteFrame::create(minionnamedie, Rect(0, 0, 144, 152)));
	animFrames.pushBack(SpriteFrame::create(minionnamedie, Rect(144, 0, 144, 152)));
	animFrames.pushBack(SpriteFrame::create(minionnamedie, Rect(288, 0, 144, 152)));
	animFrames.pushBack(SpriteFrame::create(minionnamedie, Rect(432, 0, 144, 152)));

	animation = Animation::createWithSpriteFrames(animFrames, 0.1f);

	animate = Animate::create(animation);
	Animates.pushBack(animate);
	animFrames.clear();

}
void Shadow::Roar(float dt)
{
	Minions::Roar(1);
	this->setLocalZOrder(30);
	Schedule_findPlayer = CC_SCHEDULE_SELECTOR(Minions::findPlayer);
	this->schedule(Schedule_findPlayer, 1.3f, 100, 1.0f);
}