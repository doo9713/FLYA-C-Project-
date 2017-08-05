#pragma once

#include "main.h"

/* 게임판을 위한 함수 */
void MakeBoard(char(*GameWorld)[SIZE_Y]);
void PrintBoard(char(*GameWorld)[SIZE_Y]);

/* 플레이어를 위한 함수*/
void MakePlayer(char(*GameWorld)[SIZE_Y], PPlayerPos MyPos);
void ControlPlayer(char(*GameWorld)[SIZE_Y], PPlayerPos MyPos);

/* 적을 위한 함수*/
PNode MakeEnemy(char(*GameWorld)[SIZE_Y], PNode Enemy);
void ControlEnemy(char(*GameWorld)[SIZE_Y], PNode Enemy);
void DeleteEnemy(PNode Enemy);
void CheckEnemy(PNode Enemy, PNode Bullet);

/* 총알을 위한 함수 */
PNode MakeBullet(char(*GameWorld)[SIZE_Y], PPlayerPos MyPos, PNode Bullet);
void ControlBullet(char(*GameWorld)[SIZE_Y], PNode Bullet);
