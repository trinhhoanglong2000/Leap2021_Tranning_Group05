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

#include "SoundManager.h"
#include "Definitions.h"
#include "AudioEngine.h"

USING_NS_CC;

SoundManager::SoundManager() {

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	thrilling = false;
}
void SoundManager::getsoftbackground()
{
	idsoftbg = AudioEngine::play2d("music/softbackground.mp3", true, 1.0f, nullptr);
}
void SoundManager::getthrillingbackground()
{
	if (thrilling == false)
	{
		thrilling = true;
		//AudioEngine::resume(idthrillingbg);
		idthrillingbg = AudioEngine::play2d("music/thrillingbackground.mp3", true, 1.0f, nullptr);
	}
}
void SoundManager::getMinionRoar()
{
	roar = AudioEngine::play2d("music/roar.mp3", false, 1.0f, nullptr);
}
void SoundManager::getPlayerMove()
{
	int i = AudioEngine::play2d("music/playerMove.mp3", false, 0.5f, nullptr);
}
void SoundManager::getPlayerHitTrap()
{
	int i = AudioEngine::play2d("music/playerHitTrap.mp3", false, 1.0f, nullptr);
}
void SoundManager::getPlayerHitminion()
{
	int i = AudioEngine::play2d("music/playerHitTrap.mp3", false, 1.0f, nullptr);
}