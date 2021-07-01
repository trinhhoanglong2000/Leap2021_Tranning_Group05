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
	//preload sound
	AudioEngine::preload(thrillingbackground_sound);
	AudioEngine::preload(HitTrap_sound);
	AudioEngine::preload(playerMove_sound);
	AudioEngine::preload(Roar_sound);
	AudioEngine::preload(softbackground_sound);
	AudioEngine::preload(surprisebackground_sound);




}

void SoundManager::PlayMusic(std::string name) {
	AudioEngine::play2d("music/softbackground.mp3", true, 1.0f, nullptr);
}
void SoundManager::PlayMusic(std::string name,bool loop,float volumn) {
	AudioEngine::play2d("music/softbackground.mp3", loop, volumn, nullptr);
}
SoundManager* SoundManager::mInstancePtr = new SoundManager();
