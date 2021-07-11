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

#include "Trap.h"
#include "Definitions.h"

USING_NS_CC;
Trap::Trap() {
}
Trap::Trap(std::string name) {

	this->initWithFile(name);
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	auto PlayerBody = PhysicsBody::createBox(this->getContentSize()/2);
	PlayerBody->setCollisionBitmask(TRAP_COLISION_BITMASK);
	PlayerBody->setCategoryBitmask(TRAP_CATEGORY_BITMASK);
	PlayerBody->setContactTestBitmask(TRAP_COLISION_BITMASK);
	PlayerBody->setDynamic(false);
	this->setPhysicsBody(PlayerBody);

}
Trap::Trap(std::string filename, cocos2d::Rect rect)
{
	this->initWithFile(filename,rect);
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	auto PlayerBody = PhysicsBody::createBox(this->getContentSize()/2);
	PlayerBody->setCollisionBitmask(TRAP_COLISION_BITMASK);
	PlayerBody->setCategoryBitmask(TRAP_CATEGORY_BITMASK);
	PlayerBody->setContactTestBitmask(TRAP_COLISION_BITMASK);
	PlayerBody->setDynamic(false);
	this->setPhysicsBody(PlayerBody);
}
