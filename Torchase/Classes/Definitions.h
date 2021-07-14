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

#ifndef __DEFINITIONS_H__
#define __DEFINITIONS_H__

#define DISPLAY_TIME_SPLASH_SCENE 2
#define DISPLAY_TIME_STORY_SCENE 30
#define TRANSITION_TIME 0.5

#define ACTOR_SPEED 0.6
#define BUTTON_SCALE 0.35
#define MININON_SPEED 1
#define AUTO_SPEED 0.2
#define ROCK_SPEED 1

#define TIME_REDUCE_ENERGY 1
#define PERCENT_REDUCE 1
#define MAX_PERCENT 60

#define ITEM_CATEGORY_BITMASK 1
#define PLAYER_CATEGORY_BITMASK 2
#define WALL_CATEGORY_BITMASK 4
#define TRAP_CATEGORY_BITMASK 8
#define ENEMY_CATEGORY_BITMASK 16
#define PLAYER_BG_CATEGORY_BITMASK 32
#define PLAYER_EDGE_CATEGORY_BITMASK 64
#define DOOR_CATEGORY_BITMASK 128


#define ITEM_COLISION_BITMASK 2
#define PLAYER_COLISION_BITMASK 157	// 1+4+8+16+128
#define WALL_COLISION_BITMASK 26	// 2+16 + 8
#define TRAP_COLISION_BITMASK 22	// 2+16+ 4
#define ENEMY_COLISION_BITMASK 110	// 2+4+8+32 + 64
#define PLAYER_BG_COLISION_BITMASK 16 
#define PLAYER_EDGE_COLISION_BITMASK 16
#define DOOR_COLISION_BITMASK 2

#define MAP_SCALE 5

#define AUTOPLUSHENEGY 2




//========================MUSIC LOCATION==============
#define thrillingbackground_sound "music/thrillingbackground.mp3"
#define HitTrap_sound "music/playerHitTrap.mp3"
#define playerMove_sound "music/playerMove.mp3"
#define Roar_sound "music/roar.mp3"

#define softbackground_sound "music/backgroundmusic.mp3"

#define surprisebackground_sound "music/surprisebackground.mp3"
#define LIGHTING "music/lighting.mp3"
#define MAINMENU_SOUND "music/Mainmenu.mp3"

#endif // __DEFINITIONS_H__
