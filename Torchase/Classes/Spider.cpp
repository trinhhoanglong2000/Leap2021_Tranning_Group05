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

#include "Spider.h"
#include "Definitions.h"

USING_NS_CC;




Spider::Spider(Player * playerScene, float mapspeed):	Minions( playerScene, mapspeed)
{
	Spider::setAnimation();

}
Spider::Spider() : Minions()
{
	Spider::setAnimation();
}
void Spider::Roar(float dt)
{
	Minions::Roar(1);
	Schedule_findPlayer = CC_SCHEDULE_SELECTOR(Spider::findPlayer);
	this->schedule(Schedule_findPlayer, 1.3f, 100, 1.0f);
}
void Spider::findPlayer(float dt)
{
	// add audio
	Minions::findPlayer(1);
}
void Spider::setAnimation()
{

	//down
	type = 0;
	Vector<SpriteFrame*>  animFrames;
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(100, 0, 100, 100)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(0, 0, 100, 100)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(100, 0, 100, 100)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(0, 0, 100, 100)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(100, 0, 100, 100)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(200, 0, 100, 100)));


	Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f);

	Animate* animate = Animate::create(animation);
	Animates.pushBack(animate);
	animFrames.clear();

	//up
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(100, 300, 100, 100)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(0, 300, 100, 100)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(100, 300, 100, 100)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(0, 300, 100, 100)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(100, 300, 100, 100)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(200, 300, 100, 100)));

	animation = Animation::createWithSpriteFrames(animFrames, 0.1f);

	animate = Animate::create(animation);
	Animates.pushBack(animate);
	animFrames.clear();

	//left
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(100, 100, 100, 100)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(0, 100, 100, 100)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(100, 100, 100, 100)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(0, 100, 100, 100)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(100, 100, 100, 100)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(200, 100, 100, 100)));

	animation = Animation::createWithSpriteFrames(animFrames, 0.1f);

	animate = Animate::create(animation);
	Animates.pushBack(animate);
	animFrames.clear();

	//right 
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(100, 200, 100, 100)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(0, 200, 100, 100)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(100, 200, 100, 100)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(0, 200, 100, 100)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(100, 200, 100, 100)));
	animFrames.pushBack(SpriteFrame::create(minionname, Rect(200, 200, 100, 100)));

	animation = Animation::createWithSpriteFrames(animFrames, 0.1f);

	animate = Animate::create(animation);
	Animates.pushBack(animate);
	animFrames.clear();
	goUp = true;


	// die
	std::string minionnamedie = "prefap/Minions/spiderDie.png";
	animFrames.pushBack(SpriteFrame::create(minionnamedie, Rect(0, 0, 100, 100)));
	animFrames.pushBack(SpriteFrame::create(minionnamedie, Rect(100, 0, 100, 100)));
	animFrames.pushBack(SpriteFrame::create(minionnamedie, Rect(200, 0, 100, 100)));

	animation = Animation::createWithSpriteFrames(animFrames, 0.1f);

	animate = Animate::create(animation);
	Animates.pushBack(animate);
	animFrames.clear();
}