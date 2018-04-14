#include "aeliminate.h"

int main(char argc, char* argv[])
{
	InitGame();
	GameRun();
	GameOver();
	_getch();
	closegraph();
	return 0;
}