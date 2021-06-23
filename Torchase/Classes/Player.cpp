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

#include "Player.h"
#include "Definitions.h"
#include "ui\CocosGUI.h"
#include "GameScene.h"
USING_NS_CC;
Player::Player(cocos2d::Scene *scene)
{
	//cam = camera;
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	PlayerSprite = Sprite::create("prefap/Player/redbird-midflap.png");
	PlayerSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	PlayerSprite->setTag(1);
	scene->addChild(PlayerSprite,2);
	mainscene = scene;


}	
void Player::MoveUp()
{
	PlayerSprite->setPosition(Vec2(PlayerSprite->getPositionX(), PlayerSprite->getPositionY() + visibleSize.height*PLAYER_SPEED));
	auto cam = mainscene->getDefaultCamera();
	cam->setPosition(PlayerSprite->getPosition());
}
void Player::MoveDow()
{
	PlayerSprite->setPosition(Vec2(PlayerSprite->getPositionX(), PlayerSprite->getPositionY() - visibleSize.height*PLAYER_SPEED));
	auto cam = mainscene->getDefaultCamera();
	cam->setPosition(PlayerSprite->getPosition());
}
void Player::MoveLeft()
{
	PlayerSprite->setPosition(Vec2(PlayerSprite->getPositionX() - visibleSize.height*PLAYER_SPEED, PlayerSprite->getPositionY()));
	auto cam = mainscene->getDefaultCamera();
	cam->setPosition(PlayerSprite->getPosition());
}
void Player::MoveRight()
{
	PlayerSprite->setPosition(Vec2(PlayerSprite->getPositionX() + visibleSize.height*PLAYER_SPEED, PlayerSprite->getPositionY()));
	auto cam = mainscene->getDefaultCamera();
	cam->setPosition(PlayerSprite->getPosition());
}