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

#include "Minions.h"
#include "Definitions.h"
USING_NS_CC;
Minions::Minions(Player* playerScene):  Actor("prefap/Minions/bluebird-midflap.png")
{
	player = playerScene;

	auto EnemyBody = PhysicsBody::createBox(this->getContentSize());
	EnemyBody->setCollisionBitmask(ENEMY_COLISION_BITMASK);

	EnemyBody->setContactTestBitmask(true);
	EnemyBody->setDynamic(false);
	this->setPhysicsBody(EnemyBody);

	this->setPosition(Vec2(visibleSize.width/2 + visibleSize.height*0.2 + origin.x, visibleSize.height*0.8));
	this->schedule(CC_SCHEDULE_SELECTOR(Minions::findPlayer), 1.0f);
}	
void Minions::findPlayer(float dt)
{
	/*cocos2d::Vec2 point = this->getPosition();
	cocos2d::Vec2 pointup = Vec2(point.x, point.y + speed) - player->getPosition();
	cocos2d::Vec2 pointdow = Vec2(point.x, point.y - speed) - player->getPosition();
	cocos2d::Vec2 pointleft = Vec2(point.x - speed, point.y ) - player->getPosition();
	cocos2d::Vec2 pointright = Vec2(point.x + speed, point.y) - player->getPosition();
	
	if(abs(pointup.x+pointup.y)<abs(pointup.x + pointup.y))*/
}
