#pragma once

#include "main.h"

/* �������� ���� �Լ� */
void MakeBoard(char(*GameWorld)[SIZE_Y]);
void PrintBoard(char(*GameWorld)[SIZE_Y]);

/* �÷��̾ ���� �Լ�*/
void MakePlayer(char(*GameWorld)[SIZE_Y], PPlayerPos MyPos);
void ControlPlayer(char(*GameWorld)[SIZE_Y], PPlayerPos MyPos);

/* ���� ���� �Լ�*/
PNode MakeEnemy(char(*GameWorld)[SIZE_Y], PNode Enemy);
void ControlEnemy(char(*GameWorld)[SIZE_Y], PNode Enemy);
void DeleteEnemy(PNode Enemy);
void CheckEnemy(PNode Enemy, PNode Bullet);

/* �Ѿ��� ���� �Լ� */
PNode MakeBullet(char(*GameWorld)[SIZE_Y], PPlayerPos MyPos, PNode Bullet);
void ControlBullet(char(*GameWorld)[SIZE_Y], PNode Bullet);
