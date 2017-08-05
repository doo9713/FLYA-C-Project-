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

char * PrintGameOver(int Score) {
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

	printf("            Your Score : %d\n", Score);
	printf("            Input Name >> ");
	scanf("%s", name);
	return name;
}