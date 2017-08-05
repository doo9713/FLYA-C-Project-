#include "game.h"

/* ������ �⺻ �� ���� */
void MakeBoard(char(*GameWorld)[SIZE_Y]) {
	for (int i = 0; i < SIZE_X; ++i)
		for (int j = 0; j < SIZE_Y; ++j)
			GameWorld[i][j] = EMPTY;

	for (int i = 0; i < SIZE_X; ++i) {
		GameWorld[i][0] = WALL;
		GameWorld[i][SIZE_Y - 1] = WALL;
	}
}

/* ������ �� ��� */
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

/* �÷��̾� �ʱ���ġ ���� */
void MakePlayer(char(*GameWorld)[SIZE_Y], PPlayerPos MyPos) {
	MyPos->xpos = SIZE_X - 1;
	MyPos->ypos = SIZE_Y / 2;
	GameWorld[MyPos->xpos][MyPos->ypos] = PLAYER;
}

/* ����Ű�� ���� �÷��̾� ��ġ �缳�� */
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

/* �� ���� */
PNode MakeEnemy(char(*GameWorld)[SIZE_Y], PNode Enemy) {
	int ypos = (rand() % SIZE_Y - 3) + 2;

	/* ��ũ�� ����Ʈ�� ���� �߰� */
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

/* ���� ���������� ��Ʈ�� */
void ControlEnemy(char(*GameWorld)[SIZE_Y], PNode Enemy) {
	PNode temp = Enemy->next;
	while (temp->next != NULL) {
		GameWorld[temp->xpos][temp->ypos] = EMPTY;
		temp->xpos += 1;
		GameWorld[temp->xpos][temp->ypos] = ENEMY;
		temp = temp->next;
	}
}

/* ���� */
void DeleteNode(PNode Enemy) {
	PNode Del = Enemy->next;
	Enemy->next = Enemy->next->next;
	free(Del);
}

/* ������ �� Ȯ�� */
void CheckEnemy(PNode Enemy) {
	PNode t_Enemy = Enemy;
	if (t_Enemy->next == NULL)
		return; // ���� �ϳ��� ���°��
	while (t_Enemy->next != NULL) {
		if (t_Enemy->next->xpos >= SIZE_X)
			DeleteNode(t_Enemy);
		t_Enemy = t_Enemy->next;
	}
}

/* �Ѿ� ���� */
PNode MakeBullet(char(*GameWorld)[SIZE_Y], PPlayerPos MyPos, PNode Bullet) {
	int xpos = MyPos->xpos - 1;
	int ypos = MyPos->ypos;

	/* ��ũ�� ����Ʈ�� �Ѿ��� �߰� */
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

/* �Ѿ��� �ö󰡵��� ��Ʈ�� */
void ControlBullet(char(*GameWorld)[SIZE_Y], PNode Bullet) {
	PNode temp = Bullet->next;
	while (temp->next != NULL) {
		GameWorld[temp->xpos][temp->ypos] = EMPTY;
		if (temp->xpos > 0) {
			temp->xpos -= 1;
			GameWorld[temp->xpos][temp->ypos] = BULLET;
		}
		temp = temp->next;
	}
}

/* ������ �Ѿ� Ȯ�� */
void CheckBullet(PNode Bullet) {
	PNode t_Bullet = Bullet;
	if (t_Bullet->next == NULL)
		return; // �Ѿ��� �ϳ��� ���°��
	while (t_Bullet->next != NULL) {
		if (t_Bullet->next->xpos <= 0)
			DeleteNode(t_Bullet);
		t_Bullet = t_Bullet->next;
	}
}

/* �Ѿ� Ŭ���� */
void ClearBullet(char(*GameWorld)[SIZE_Y]) {
	for (int i = 1; i < SIZE_Y - 1; ++i)
		if (GameWorld[0][i] == BULLET)
			GameWorld[0][i] = EMPTY;
}

/* �浹 �˻� */
void CheckTrigger(PNode Enemy, PNode Bullet) {
	PNode t_Enemy = Enemy;
	PNode t_Bullet = Bullet;
	if (t_Enemy->next == NULL)
		return; // ���� �ϳ��� ���°��
	if (t_Bullet->next == NULL)
		return; // �Ѿ��� �ϳ��� ���°��

	while (t_Enemy->next != NULL) {
		while (t_Bullet->next != NULL) {
			if (t_Bullet->next->xpos == t_Enemy->next->xpos &&
				t_Bullet->next->ypos == t_Enemy->next->ypos) {
				DeleteNode(t_Bullet);
				DeleteNode(t_Enemy);
			}
			t_Bullet = t_Bullet->next;
		}
		t_Enemy = t_Enemy->next;
	}
}