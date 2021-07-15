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
 #include "TrapManager.h"
 #include "Definitions.h"
 #include "AudioEngine.h"
#include "Trap.h"
#include "TrapBear.h"
#include "TrapPlant.h"
#include "Trapthorn.h"
#include "TrapRock.h"
#include "TrapCheckBoss.h"
USING_NS_CC;

TrapManager::TrapManager() {
	
}
void TrapManager::CreateAllTrap()
{
	for (int i = 0; i < 5; i++)
	{
		auto trapBear = new TrapBear();
		trapBear->setVisible(false);

		auto trapPlant = new TrapPlant();
		trapPlant->setVisible(false);

		auto trapthorn = new Trapthorn();
		trapthorn->setVisible(false);

		auto traprock = new TrapRock();
		traprock->setVisible(false);

		auto trapCheckBoss = new TrapCheckBoss();
		trapCheckBoss->setVisible(false);

		AllTrap.pushBack(trapBear);
		AllTrap.pushBack(trapPlant);
		AllTrap.pushBack(trapthorn);
		AllTrap.pushBack(traprock);
		AllTrap.pushBack(trapCheckBoss);

	}
}
Trap *TrapManager::CreateTrap(int Type)
{
	for (int i = 0; i < AllTrap.size(); i++)
	{
		if (AllTrap.at(i)->type == Type && AllTrap.at(i)->isVisible() == false)
		{
			AllTrap.at(i)->setVisible(true);
				return AllTrap.at(i);
		}
	}
	switch (Type)
	{
	case 0:
	{
		auto trapthorn = new Trapthorn();
		trapthorn->setVisible(true);
		AllTrap.pushBack(trapthorn);
		return trapthorn;
		break;
	}
	case 1:
	{
		auto trapPlant = new TrapPlant();
		trapPlant->setVisible(true);
		AllTrap.pushBack(trapPlant);
		return trapPlant;
		break;
	}
	case 2:
	{
		auto trapBear = new TrapBear();
		trapBear->setVisible(true);
		AllTrap.pushBack(trapBear);
		return trapBear;
		break;
	}
	case 3:
	{

		auto traprock = new TrapRock();
		traprock->setVisible(true);
		AllTrap.pushBack(traprock);
		return traprock;
		break;
	}
	case 4:
	{
		auto trapCheckBoss = new TrapCheckBoss();
		trapCheckBoss->setVisible(true);
		AllTrap.pushBack(trapCheckBoss);
		return trapCheckBoss;
		break;
	}
	default:
		break;
	}
}
void TrapManager::SetFalseAllTrap()
{
	for (int i = 0; i < AllTrap.size(); i++)
	{
		AllTrap.at(i)->setVisible(false);
	}
}
TrapManager* TrapManager::mInstancePtr = new TrapManager();
