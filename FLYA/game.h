#pragma once

#include "main.h"

/* �������� ���� �Լ� */
void MakeBoard(char(*GameWorld)[SIZE_Y]);
void PrintBoard(char(*GameWorld)[SIZE_Y], int score);

/* �÷��̾ ���� �Լ�*/
void MakePlayer(char(*GameWorld)[SIZE_Y], PPlayerPos MyPos);
void ControlPlayer(char(*GameWorld)[SIZE_Y], PPlayerPos MyPos);

/* ���� ���� �Լ�*/
PNode MakeEnemy(char(*GameWorld)[SIZE_Y], PNode Enemy);
void ControlEnemy(char(*GameWorld)[SIZE_Y], PNode Enemy);
int CheckEnemy(PNode Enemy);

/* �Ѿ��� ���� �Լ� */
PNode MakeBullet(char(*GameWorld)[SIZE_Y], PPlayerPos MyPos, PNode Bullet);
void ControlBullet(char(*GameWorld)[SIZE_Y], PNode Bullet);
void CheckBullet(PNode Bullet);
void ClearBullet(char(*GameWorld)[SIZE_Y]);

/* ���ӿ�����Ʈ ���� */
void CheckTrigger(char(*GameWorld)[SIZE_Y], PNode Enemy, PNode Bullet, int * score);
void DeleteNode(PNode Enemy);
void AllNodeDelete(PNode node);
