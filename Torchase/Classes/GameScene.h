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

#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "cocos2d.h"
#include "Player.h"
#include "Minions.h"
#include "ui\CocosGUI.h"
#include "GameMap.h"
#include "Canvas.h"
#include "Battery.h"
#include "SoundManager.h"
#include "TrapPlant.h"
#include "Trap.h"
#include "Door.h"

class GameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene(int Level_of_difficult_Scene, int controller_Scene);
	
    virtual bool init();
    CREATE_FUNC(GameScene);
	void shakeScreen(float dt);
	float rangeRandom(float min, float max);
	void Lighting(float dt);
	void Lightingstart(float dt);
	void Lightingbg(float dt);
	void setcheckLighting(float dt);
	cocos2d::Vector<Minions*> AllMinions;
	cocos2d::Vector<Trap*> AllTrap;
	cocos2d::Vector<Iteam*> AllIteam;
	void GoToGameOver(float dt);
	void GotoAgain(float dt);
	void SaveInGame(cocos2d::Node *item);
	void checkdie();
	//GameScene *Scene_layer;
private:
	UserDefault *def;
	int level = 0;
	void SetPhysicWorld(cocos2d::PhysicsWorld *world) { sceneWorld = world; };
	bool onContactBegin(cocos2d::PhysicsContact &contact);
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	Door *door;

	Player *player;
	Minions *minion;
	GameMap *gameMap;

	cocos2d::PhysicsWorld *sceneWorld;
	cocos2d::DrawNode* background_off;

	int thickness = 400;
	int width = 1000;
	int height = 1200;

	Canvas *canvas;
	Battery *battery;
	bool light;
	bool checkLighting;

	int SET_SHAKE_DURATION = 10;
	int SET_LIGHTING_DURATION = 3;
	int SET_LIGHTINGBG_DURATION = 5;

	int gameState;

	cocos2d::Sprite *effect;

	cocos2d::SEL_SCHEDULE Schedule_lighting;
	cocos2d::SEL_SCHEDULE Schedule_shake;

	
};

#endif // __GAMESCENE_H__
