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
 #include "IteamManager.h"
 #include "Definitions.h"
 #include "AudioEngine.h"
#include "Battery.h"
#include "Key.h"
#include "Iteam.h"
#include "IteamBox.h"
#include "IteamSaveGame.h"

USING_NS_CC;

IteamManager::IteamManager() {
	
}
void IteamManager::CreateAllIteam()
{
	for (int i = 0; i < 3; i++)
	{

		auto battery = new Battery();
		battery->setVisible(false);

		auto key = new Key();
		key->setVisible(false);

		auto iteamBox = new IteamBox();
		iteamBox->setVisible(false);

		auto iteamSaveGame = new IteamSaveGame();
		iteamSaveGame->setVisible(false);


		AllIteam.pushBack(battery);
		AllIteam.pushBack(key);
		AllIteam.pushBack(iteamBox);
		AllIteam.pushBack(iteamSaveGame);

	}
}
Iteam *IteamManager::CreateIteam(int Type)
{
	for (int i = 0; i < AllIteam.size(); i++)
	{
		if (AllIteam.at(i)->type == Type && AllIteam.at(i)->isVisible() == false)
		{
			AllIteam.at(i)->setVisible(true);
				return AllIteam.at(i);
		}
	}
	switch (Type)
	{
	case 1:
	{
		auto battery = new Battery();
		battery->setVisible(true);
		AllIteam.pushBack(battery);
		return battery;
		break;
	}
	case 2:
	{
		
		auto key = new Key();
		key->setVisible(true);
		AllIteam.pushBack(key);
		return key;
		break;
	}
	case 3:
	{

		auto iteamBox = new IteamBox();
		iteamBox->setVisible(true);
		AllIteam.pushBack(iteamBox);
		return iteamBox;
		break;
	}
	case 4:
	{

		auto iteamSaveGame = new IteamSaveGame();
		iteamSaveGame->setVisible(false);
		AllIteam.pushBack(iteamSaveGame);
		return iteamSaveGame;
		break;
	}
	default:
		break;
	}
}
void IteamManager::SetFalseAllIteam()
{
	for (int i = 0; i < AllIteam.size(); i++)
	{
		AllIteam.at(i)->setVisible(false);
		AllIteam.at(i)->hit = false;
	}
}
IteamManager* IteamManager::mInstancePtr = new IteamManager();
