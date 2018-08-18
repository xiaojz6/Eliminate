#ifndef AELIMINATE_H
#define AELIMINATE_H

#pragma  comment(lib,"WinMM.Lib")
#define _CRT_SECURE_NO_WARNINGS

#include<windows.h>
#include<stdio.h>
#include <graphics.h>
#include <conio.h>
#include <time.h>
#include <process.h>
#include <thread>

#define WIDTH	600
#define HIGH    840
#define ZOOM	10
#define DIA		60	
#define RAD		30

typedef struct
{
	int x, y;
}COOR;

void InitGame();//初始化游戏
void InitImg();
void Welcom();
void GetSameColorAnimal(COOR coor, COLORREF cl);
void GameRun();//运行游戏
void DrawCursor(int x, int y, int flg = 0);
void DrawAnimal();
void DrawButton();
void AddScore();
bool IsExisted(COOR coor, COLORREF cl);
void Drawrectangle();
void FallAnimal();
void AddScore();
void DrawTime();
void GameOver();
void PlayMusic();

#endif //AELIMINATE_H