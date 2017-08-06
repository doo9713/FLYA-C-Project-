#pragma once

#include "main.h"

int PrintMainMenu();
void PrintGameOver(int score);
void PrintRanking();
int GetScore(char * str);
void SaveRanking(char * str, int score);
void SortRanking(char * mystr);

/* Write Colum Function */
void WriteColumString(const char* FilePath, const char* Colum, const char* Write);

/* Read Colum Function */
void  ReadColumString(const char* FilePath, const char* Colum, char* Read);
