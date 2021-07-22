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

#include "TrapCheckBoss.h"
#include "Definitions.h"
#include "ui\CocosGUI.h"
#include "TrapManager.h"
#include "TrapRock.h"
USING_NS_CC;
TrapCheckBoss::TrapCheckBoss() : Trap("prefap/trap/CheckBoss.png", Rect(0, 0, 128, 128)) {

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	type = 4;
	this->setScale(0.8f);
}
TrapCheckBoss::TrapCheckBoss(std::string name) {

	this->initWithFile(name);
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
}
TrapCheckBoss::TrapCheckBoss(std::string filename, cocos2d::Rect rect)
{
	this->initWithFile(filename,rect);
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
}
void TrapCheckBoss::hitplayer(cocos2d::Scene *sceneGame)
{
	AllTrap = TrapManager::getInstance()->AllTrap;
	/*if (taget == 1)
	{
		for (int i = 0; i < AllTrap.size(); i++)
		{
			if (AllTrap.at(i)->type == 3 && AllTrap.at(i)->isVisible() == true)
			{
				auto trap = dynamic_cast<TrapRock*>(AllTrap.at(i));
				trap->atack(1);
			}
		}
	}*/
	scene = sceneGame;
	//TrapCheckBoss::addtrap(0);
	this->schedule(CC_SCHEDULE_SELECTOR(TrapCheckBoss::addtrap), 0.5f);
}
void TrapCheckBoss::addtrap(float dt)
{
	auto trap = TrapManager::getInstance()->CreateTrap(0);
	trap->setPosition(this->getPosition());
	scene->addChild(trap, 25);
	this->setVisible(false);
	this->removeFromParent();
}