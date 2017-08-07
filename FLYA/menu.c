#include "menu.h"

int PrintMainMenu() {
	int Select;
	printf("\n\n\n");
	printf("##########  ##          ###      ###       ##  \n");
	printf("##          ##           ###   ###        ####  \n");
	printf("##########  ##             ######        ##  ##  \n");
	printf("##          ##               ##         ######## \n");
	printf("##          ##               ##        ##      ## \n");
	printf("##          ##########       ##       ##        ## \n\n");

	printf("               1. Start Game\n");
	printf("               2. Ranking\n");
	printf("               3. Exit Game\n\n");

	printf("               Input >> ");
	scanf("%d", &Select);
	return Select;
}

void PrintGameOver(int score) {
	char name[BUFFSIZE];
	system("cls");
	printf("\n\n\n");
	printf("  ######      #      ##   ##  ####### \n");
	printf(" ##          ###     ### ###  ##      \n");
	printf("##  ####    ## ##    #######  ####### \n");
	printf(" #######   #######   ## # ##  ##      \n");
	printf("  ### ##  ##     ##  ##   ##  ####### \n\n");

	printf("  ####    ##     ##  #######  ######  \n");
	printf(" ##  ##    ##   ##   ##       ##  ### \n");
	printf("##    ##    ## ##    #######  ######  \n");
	printf(" ##  ##      ###     ##       ##  ##  \n");
	printf("  ####        #      #######  ##   ## \n\n");

	printf("            Your Score : %d\n", score);
	printf("            Input Name >> ");
	scanf("%s", name);
	SaveRanking(name, score);
}


void PrintRanking() {
	char Path[BUFFSIZE];
	wsprintfA(Path, "./Rank/Rank.txt");

	system("cls");
	for (int i = 1; i < 10; ++i) {
		char temp[BUFFSIZE];
		char column[BUFFSIZE];
		wsprintfA(column, "0%d", i);
		ReadColumString(Path, column, temp);
		printf("%d : %s\n", i, temp);
	}

	printf("Press Any Key..\n");
	getch();
}

int GetScore(char * str) {
	char s_score[BUFFSIZE];
	int score = 0;
	int start = 0;
	int end = 0;

	for (int i = 0; i < strlen(str); ++i) {
		if (str[i] == '(')
			start = i;
		if (str[i] == ')')
			end = i;
	}

	int count = 0;
	for (int i = start + 1; i < end; ++i)
		s_score[count++] = str[i];

	score = atoi(s_score);
	return score;
}

void SaveRanking(char * str, int score) {
	char * rank = (char*)malloc(sizeof(char)*BUFFSIZE);
	wsprintfA(rank, "%s(%d)", str, score);
	SortRanking(rank);
}

void SortRanking(char * mystr) {
	Ranking rank[9];
	Ranking myRank;
	strcpy(myRank.str, mystr);
	myRank.score = GetScore(mystr);

	int saveIndex = 0;
	char Path[BUFFSIZE];
	wsprintfA(Path, "./Rank/Rank.txt");

	/* ��ŷ�� ������ ����ü�� ���� */
	for (int i = 1; i < 10; ++i) {
		char column[BUFFSIZE];
		wsprintfA(column, "0%d", i);
		ReadColumString(Path, column, rank[i-1].str);
		rank[i-1].score = GetScore(rank[i-1].str);
	}

	/* ���� �ش� ��ġ�� ���� */
	for (int i = 0; i < 9; ++i) {
		if (myRank.score > rank[i].score) {
			saveIndex = i;
			if (i == 8) {
				strcpy(rank[i].str, myRank.str);
				rank[i].score = myRank.score;
			}
			else {
				for (int j = 8; j > saveIndex; --j) {
					strcpy(rank[j].str, rank[j - 1].str);
					rank[j].score = rank[j - 1].score;
				}
				strcpy(rank[i].str, myRank.str);
				rank[i].score = myRank.score;
			}
			break;
		}
	}
	
	/* ��ŷ�� ������ �޸��忡 ���� */
	for (int i = 1; i < 10; ++i) {
		char column[BUFFSIZE];
		wsprintfA(column, "0%d", i);
		WriteColumString(Path, column, rank[i - 1].str);
	}
}

void WriteColumString(const char* FilePath, const char* Colum, const char* Write)
{
	static char FullPath[256];
	strcpy(FullPath, "./");
	strcat(FullPath, FilePath);
	WritePrivateProfileStringA("����", Colum, Write, FullPath);
}

void ReadColumString(const char* FilePath, const char* Colum, char* Read)
{
	FILE* fp = fopen(FilePath, "rt");
	if (fp == 0)
	{
		strcpy(Read, "");
		return;
	}

	static char Temp[1024];

	while (!feof(fp)) // End of File
	{
		fgets(Temp, 1023, fp); // file get string
		strtok(Temp, "="); // ���ʿ� �ִ� ���ڿ����߿� �����ʿ� �ִ� ���ڿ��� ���� ���ڿ��� �ִ� ��ġ
						   // �װ��� �ι��ڷ� �����ϴ� �Լ�
						   // Key\0ABC
						   // ���ڿ� -> ���� �迭 -> �ּ�
						   // "ABC" == "ABC" -> �ּҺ�
						   // "Key" == Colum
		if (strcmp(Temp, Colum) == 0) // ���ڿ� ���Լ� 1 == 1
		{
			// Key\0ABC
			strtok(Temp + strlen(Colum) + 1, "\n");
			strcpy(Read, Temp + strlen(Colum) + 1);
			fclose(fp);
			return;
		}
	}
	strcpy(Read, "");
	fclose(fp);
}