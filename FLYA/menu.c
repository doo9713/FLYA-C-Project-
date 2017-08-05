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
	printf("  ######      #      ##   ##  ######	\n");
	printf(" ##          ###     ### ###  ##  		\n");
	printf("##  ####    ## ##    #######  ######	\n");
	printf(" #######   #######   ## # ##  ##		\n");
	printf("  ### ##  ##     ##  ##   ##  ######	\n\n");

	printf("  ####	  ##     ##  ######   #####		\n");
	printf(" ##  ##	   ##   ##   ##	  ##  ##  ##	\n");
	printf("##    ##    ## ##    ######   #####		\n");
	printf(" ##  ##	     ###     ##	  ##  ## ##		\n");
	printf("  ####	      #      ######   ##  ##	\n\n");

	printf("            Your Score : %d\n", score);
	printf("            Input Name >> ");
	scanf("%s", name);
	printf("%s\n", name);
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
	for (int i = 1; i < 10; ++i) {
		char temp[BUFFSIZE];
		char column[BUFFSIZE];
		wsprintfA(column, "0%d", i);
		ReadColumString(Path, column, temp);
		printf("%d\n", GetScore(temp));
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
	char t[BUFFSIZE];
	itoa(score, t, 10);
	wsprintfA(rank, "%s(%d)", str, score);
	printf("%s", rank);
}

void WriteColumString(const char* FilePath, const char* Colum, const char* Write)
{
	static char FullPath[256];
	strcpy(FullPath, "./");
	strcat(FullPath, FilePath);
	WritePrivateProfileStringA("정보", Colum, Write, FullPath);
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
		strtok(Temp, "="); // 왼쪽에 있는 문자열들중에 오른쪽에 있는 문자열과 같은 문자열이 있는 위치
						   // 그곳을 널문자로 변경하는 함수
						   // Key\0ABC
						   // 문자열 -> 문자 배열 -> 주소
						   // "ABC" == "ABC" -> 주소비교
						   // "Key" == Colum
		if (strcmp(Temp, Colum) == 0) // 문자열 비교함수 1 == 1
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