#include "main.h"
#include "game.h"
#include "menu.h"

void main() {
	char GameWorld[SIZE_X][SIZE_Y];
	PlayerPos MyPos;
	Node EnemyHead = { -1, -1, 0 };
	Node BulletHead = { -1, -1, 0 };
	int count = 0;

	while (1) {
		system("cls");
		int Select = PrintMainMenu();;

		switch (Select)
		{
			/* 게임 시작 */
		case START:
			system("cls");
			srand((unsigned)time(NULL));

			MakeBoard(GameWorld);
			MakePlayer(GameWorld, &MyPos);
			MakeEnemy(GameWorld, &EnemyHead);
			MakeBullet(GameWorld, &MyPos, &BulletHead);
			PrintBoard(GameWorld);

			while (1) {
				system("cls");
				count += 1;
				PrintBoard(GameWorld);
				ControlPlayer(GameWorld, &MyPos);
				/* 적 컨트롤 */
				if (count % 5 == 0) {
					if (count % 10 == 0)
						MakeEnemy(GameWorld, &EnemyHead);
					ControlEnemy(GameWorld, &EnemyHead);
					ClearBullet(GameWorld);
				}
				/* 총알 컨트롤 */
				if (count % 2 == 0) {
					MakeBullet(GameWorld, &MyPos, &BulletHead);
					ControlBullet(GameWorld, &BulletHead);
				}
				if (count % 3 == 0)
					ClearBullet(GameWorld);
				CheckEnemy(&EnemyHead);
				CheckBullet(&BulletHead);
				CheckTrigger(&EnemyHead, &BulletHead);
				if (count == 10)
					count = 0;
				Sleep(100);
			}
			/* 랭킹 확인 */
		case RANKING:
			break;
			/* 그냥 종료 */
		case EXIT:
			return;
		default:
			break;
		}
	}
}