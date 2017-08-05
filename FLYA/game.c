#include "game.h"

/* 게임의 기본 판 생성 */
void MakeBoard(char(*GameWorld)[SIZE_Y]) {
	for (int i = 0; i < SIZE_X; ++i)
		for (int j = 0; j < SIZE_Y; ++j)
			GameWorld[i][j] = EMPTY;

	for (int i = 0; i < SIZE_X; ++i) {
		GameWorld[i][0] = WALL;
		GameWorld[i][SIZE_Y - 1] = WALL;
	}
}

/* 게임의 판 출력 */
void PrintBoard(char(*GameWorld)[SIZE_Y]) {
	for (int i = 0; i < SIZE_Y; ++i)
		printf("-");
	printf("\n");

	for (int i = 0; i < SIZE_X; ++i) {
		GameWorld[i][0] = WALL;
		GameWorld[i][SIZE_Y - 1] = WALL;
		for (int j = 0; j < SIZE_Y; ++j)
			printf("%c", GameWorld[i][j]);
		printf("\n");
	}

	for (int i = 0; i < SIZE_Y; ++i)
		printf("-");
	printf("\n");
	printf("  Score : %d\n", 0);
	printf(" Escape : %d\n", 0);
}

/* 플레이어 초기위치 설정 */
void MakePlayer(char(*GameWorld)[SIZE_Y], PPlayerPos MyPos) {
	MyPos->xpos = SIZE_X - 1;
	MyPos->ypos = SIZE_Y / 2;
	GameWorld[MyPos->xpos][MyPos->ypos] = PLAYER;
}

/* 방향키에 따른 플레이어 위치 재설정 */
void ControlPlayer(char(*GameWorld)[SIZE_Y], PPlayerPos MyPos) {
	int Key;
	if (kbhit()) {
		Key = getch();
		if (Key == ARROWCODE) {
			Key = getch();
			switch (Key)
			{
			case UPARROW:
				break;
			case LEFTARROW:
				GameWorld[MyPos->xpos][MyPos->ypos] = EMPTY;
				MyPos->ypos -= 1;
				if (MyPos->ypos == 0)
					MyPos->ypos += 1;
				GameWorld[MyPos->xpos][MyPos->ypos] = PLAYER;
				break;
			case RIGHTARROW:
				GameWorld[MyPos->xpos][MyPos->ypos] = EMPTY;
				MyPos->ypos += 1;
				if (MyPos->ypos == SIZE_Y - 1)
					MyPos->ypos -= 1;
				GameWorld[MyPos->xpos][MyPos->ypos] = PLAYER;
				break;
			case DOWNARROW:
				break;
			default:
				break;
			}
		}
		Key = 0;
	}
}

/* 적 생성 */
PNode MakeEnemy(char(*GameWorld)[SIZE_Y], PNode Enemy) {
	int ypos = (rand() % SIZE_Y - 3) + 2;

	/* 링크드 리스트에 적을 추가 */
	PNode temp = Enemy->next;
	PNode NewEnemy = (PNode)malloc(sizeof(Node));
	NewEnemy->xpos = 0;
	NewEnemy->ypos = ypos;
	NewEnemy->next = NULL;

	if (temp == NULL)
		Enemy->next = NewEnemy;
	else {
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = NewEnemy;
	}
	GameWorld[0][ypos] = ENEMY;
	return NewEnemy;
}

/* 적이 내려오도록 컨트롤 */
void ControlEnemy(char(*GameWorld)[SIZE_Y], PNode Enemy) {
	PNode temp = Enemy->next;
	while (temp->next != NULL) {
		GameWorld[temp->xpos][temp->ypos] = EMPTY;
		temp->xpos += 1;
		GameWorld[temp->xpos][temp->ypos] = ENEMY;
		temp = temp->next;
	}
}

/* 적 제거 */
void DeleteEnemy(PNode Enemy) {
	PNode Del = Enemy->next;
	Enemy->next = Enemy->next->next;
	free(Del);
}

/* 제거할 적 확인 */
void CheckEnemy(PNode Enemy, PNode Bullet) {
	PNode t_Enemy = Enemy;
	if (t_Enemy->next == NULL)
		return; // 적이 하나도 없는경우
	while (t_Enemy->next != NULL) {
		if (t_Enemy->next->xpos >= SIZE_X)
			DeleteEnemy(t_Enemy);
		t_Enemy = t_Enemy->next;
	}
}

/* 총알 생성 */
PNode MakeBullet(char(*GameWorld)[SIZE_Y], PPlayerPos MyPos, PNode Bullet) {
	int xpos = MyPos->xpos - 1;
	int ypos = MyPos->ypos;

	/* 링크드 리스트에 총알을 추가 */
	PNode temp = Bullet->next;
	PNode NewBullet = (PNode)malloc(sizeof(Node));
	NewBullet->xpos = xpos;
	NewBullet->ypos = ypos;
	NewBullet->next = NULL;

	if (temp == NULL)
		Bullet->next = NewBullet;
	else {
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = NewBullet;
	}
	GameWorld[xpos][ypos] = BULLET;
	return NewBullet;
}

/* 총알이 올라가도록 컨트롤 */
void ControlBullet(char(*GameWorld)[SIZE_Y], PNode Bullet) {
	PNode temp = Bullet->next;
	while (temp->next != NULL) {
		GameWorld[temp->xpos][temp->ypos] = EMPTY;
		if (temp->xpos > 0)
			temp->xpos -= 1;
		GameWorld[temp->xpos][temp->ypos] = BULLET;
		temp = temp->next;
	}
}