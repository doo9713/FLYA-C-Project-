#include "main.h"
#include "game.h"
#include "menu.h"

void setCursor(int x, int y) {
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void main() {
	char GameWorld[SIZE_X][SIZE_Y];
	PlayerPos MyPos;
	Node EnemyHead = { -1, -1, 0 };
	Node BulletHead = { -1, -1, 0 };
	int count = 0;
	int score = 0;

	while (1) {
		system("cls");
		int Select = PrintMainMenu();;

		switch (Select)
		{
			/* ���� ���� */
		case START:
			if (EnemyHead.next != NULL)
				AllNodeDelete(&EnemyHead);
			if (BulletHead.next != NULL)
				AllNodeDelete(&BulletHead);

			system("cls");
			srand((unsigned)time(NULL));

			MakeBoard(GameWorld);
			MakePlayer(GameWorld, &MyPos);
			MakeEnemy(GameWorld, &EnemyHead);
			MakeBullet(GameWorld, &MyPos, &BulletHead);
			PrintBoard(GameWorld, score);

			while (1) {
				setCursor(0, 0);
				count += 1;
				PrintBoard(GameWorld, score);
				ControlPlayer(GameWorld, &MyPos);
				/* �� ��Ʈ�� */
				if (count % 5 == 0) {
					if (count % 10 == 0)
						MakeEnemy(GameWorld, &EnemyHead);
					ControlEnemy(GameWorld, &EnemyHead);
					ClearBullet(GameWorld);
				}
				/* �Ѿ� ��Ʈ�� */
				if (count % 2 == 0) {
					MakeBullet(GameWorld, &MyPos, &BulletHead);
					ControlBullet(GameWorld, &BulletHead);
				}
				if (count % 3 == 0)
					ClearBullet(GameWorld);
				if (CheckEnemy(&EnemyHead))
					break;
				CheckBullet(&BulletHead);
				CheckTrigger(GameWorld, &EnemyHead, &BulletHead, &score);
				if (count == 10)
					count = 0;
				Sleep(100);
			}
			PrintGameOver(score);
			score = 0;
			/* ��ŷ Ȯ�� */
		case RANKING:
			PrintRanking();
			break;
			/* �׳� ���� */
		case EXIT:
			return;
		default:
			break;
		}
	}
}