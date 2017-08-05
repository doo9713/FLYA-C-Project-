#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <malloc.h>
#include <time.h>

#define BUFFSIZE 256

#pragma region MenuSet
#define START 1
#define RANKING 2
#define EXIT 3
#pragma endregion

#pragma region MapSize
#define SIZE_X 20
#define SIZE_Y 30
#pragma endregion

#pragma region MapOBJ
#define WALL '|'
#define PLAYER 'A'
#define EMPTY ' '
#define ENEMY 'O'
#define BULLET '.'
#pragma endregion

#pragma region KeyCode
#define ARROWCODE 224
#define UPARROW  72
#define LEFTARROW 75
#define RIGHTARROW 77
#define DOWNARROW 80
#pragma endregion

/* 플레이어의 위치정보 구조체 */
typedef struct PlayerPos {
	int xpos;
	int ypos;
} PlayerPos, *PPlayerPos;

/* 총알과 적의 자료를 관리할 노드 구조체 */
typedef struct Node {
	int xpos;
	int ypos;
	struct Node * next;
} Node, *PNode;

/* 랭킹정보를 저장할 구조체 */
typedef struct Ranking {
	char str[BUFFSIZE];
	int score;
} Ranking;