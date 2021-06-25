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

class GameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GameScene);
	//GameScene *Scene_layer;
private:
	void enemyFind(float dt);
	void SetPhysicWorld(cocos2d::PhysicsWorld *world) { sceneWorld = world; };
	void MoveUp(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType Type);
	void MoveDow(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType Type);
	void MoveLeft(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType Type);
	void MoveRight(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType Type);
	void OnOffLight(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType Type);
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	cocos2d::ui::Layout *Layout;
	Player *player;
	Minions *minion;
	GameMap *gameMap;
	cocos2d::PhysicsWorld *sceneWorld;
};

#endif // __GAMESCENE_H__
