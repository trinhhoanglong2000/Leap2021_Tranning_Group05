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
 #include "MinionManager.h"
 #include "Definitions.h"
 #include "AudioEngine.h"
#include "Shadow.h"
#include "Spider.h"
#include "MinionBoss.h"
#include "Minions.h"
USING_NS_CC;

MinionManager::MinionManager() {
	
}
void MinionManager::CreateAllMinion()
{
	for (int i = 0; i < 5; i++)
	{
		auto shadow = new Shadow();
		shadow->setVisible(false);

		auto spider = new Spider();
		spider->setVisible(false);

		auto minionBoss = new MinionBoss();
		minionBoss->setVisible(false);

		AllMinions.pushBack(minionBoss);
		AllMinions.pushBack(shadow);
		AllMinions.pushBack(spider);
	}
}
Minions *MinionManager::CreateMinion(int Type)
{
	for (int i = 0; i < AllMinions.size(); i++)
	{
		if (AllMinions.at(i)->type == Type && AllMinions.at(i)->isVisible() == false)
		{
			MinionManager::setfalseMinion(AllMinions.at(i));
			AllMinions.at(i)->setVisible(true);
				return AllMinions.at(i);
		}
	}
	switch (Type)
	{
	case 0:
	{
		auto spider = new Spider();
		spider->setVisible(true);
		AllMinions.pushBack(spider);
		return spider;
		break;
	}
	case 1:
	{
		
		auto shadow = new Shadow();
		shadow->setVisible(true);
		AllMinions.pushBack(shadow);
		return shadow;
		break;
	}
	case 2:
	{
		
		auto minionBoss = new MinionBoss();
		minionBoss->setVisible(true);
		AllMinions.pushBack(minionBoss);
		return minionBoss;
		break;
	}
	default:
		break;
	}
}
void MinionManager::SetFalseAllMinion()
{
	for (int i = 0; i < AllMinions.size(); i++)
	{
		MinionManager::setfalseMinion(AllMinions.at(i));
	}
}
void MinionManager::setfalseMinion(Minions *minion)
{
	minion->setVisible(false);
	minion->hit = false;
	if (minion->type == 0)
	{
		auto minions = dynamic_cast<Spider*>(minion);
		minions->reset();
	}
	if (minion->type == 1)
	{
		auto minions = dynamic_cast<Shadow*>(minion);
		minions->reset();
	}
	if (minion->type == 2)
	{
		auto minions = dynamic_cast<MinionBoss*>(minion);
		minions->reset();
	}
}
MinionManager* MinionManager::mInstancePtr = new MinionManager();
