#include "aeliminate.h"

IMAGE img[6] = {};//角色数组

COOR cur = { 4, 7 };//光标坐标
COOR samecolor[140];
int index = 0;
int score = 0;
int gm_time = 60;//游戏时间
int rfrstm = 1;	//刷新次数

void InitImg()
{
	loadimage(&img[0], _T(".\\res\\xxl_hl.bmp"));
	loadimage(&img[1], _T(".\\res\\xxl_xj.bmp"));
	loadimage(&img[2], _T(".\\res\\xxl_xx.bmp"));
	loadimage(&img[3], _T(".\\res\\xxl_hm.bmp"));
	loadimage(&img[4], _T(".\\res\\xxl_mty.bmp"));
	loadimage(&img[5], _T(".\\res\\xxl_qw.bmp"));
}

void Welcom()
{
	LOGFONT f;
	gettextstyle(&f);                     // 获取当前字体设置
	f.lfHeight = 100;                      // 设置字体高度为 80
	_tcscpy(f.lfFaceName, _T("仿宋"));    // 设置字体为“仿宋”(高版本 VC 推荐使用 _tcscpy_s 函数)
	f.lfQuality = ANTIALIASED_QUALITY;    // 设置输出效果为抗锯齿  
	settextstyle(&f);                     // 设置字体样式
	settextcolor(LIGHTRED);
	outtextxy(250, 300, _T("消消乐"));
	Sleep(5000);
	setbkcolor(BLACK);
	cleardevice();
}

void DrawAnimal()
{
	setfillcolor(RGB(204, 255, 255));
	for (int i = 10; i <= WIDTH + 10; i += 5)
	{
		solidrectangle(10, 10, i, 850);
		Sleep(1);
	}

	srand((unsigned)time(NULL));
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 14; ++j)
		{
			putimage(i*DIA + 10, j*DIA + 10, &img[rand() % 6]);
			Sleep(10);
		}
	}
}


void DrawCursor(int x, int y, int flg /*= 0*/)
{
	setlinestyle(PS_SOLID, 1);
	setbkmode(OPAQUE);
	if (flg == 1)
	{
		setlinecolor(RGB(204, 255, 255));
	}
	else
		setlinecolor(LIGHTRED);
	rectangle(x*DIA + 10, y*DIA + 10, (x + 1)*DIA + 9, (y + 1)*DIA + 9);
}


void DrawScore()
{
	TCHAR s[10];
	_stprintf(s, _T("%d"), score);
	LOGFONT f;
	gettextstyle(&f);                     // 获取当前字体设置
	f.lfHeight = 50;                      // 设置字体高度为 50
	_tcscpy(f.lfFaceName, _T("仿宋"));    // 设置字体为“黑体”(高版本 VC 推荐使用 _tcscpy_s 函数)
	f.lfQuality = ANTIALIASED_QUALITY;    // 设置输出效果为抗锯齿  
	settextcolor(LIGHTRED);

	settextstyle(&f);
	outtextxy(700, 610, s);
}


void DrawRfrsTimes()
{
	TCHAR s[10];
	LOGFONT f;
	gettextstyle(&f);                     // 获取当前字体设置
	f.lfHeight = 80;
	settextstyle(&f);
	settextcolor(LIGHTGREEN);
	_stprintf(s, _T("%d"), rfrstm);
	outtextxy(700, 330, s);	//绘制刷新次数
}


void DrawButton()
{
	LOGFONT f;
	gettextstyle(&f);
	setlinestyle(PS_SOLID, 4);
	setfillcolor(RGB(252, 157, 154));
	fillrectangle(680, 430, 760, 480);
	f.lfHeight = 35;
	f.lfWeight = 5000;
	settextstyle(&f);
	setbkmode(TRANSPARENT);
	settextcolor(RGB(131, 175, 155));
	outtextxy(684, 437, _T("刷新"));
}


//初始化游戏界面
void InitGame()
{
	initgraph(WIDTH + 20 + 200, HIGH + 20);
	std::thread t2(PlayMusic);
	t2.detach();
	Welcom();
	setlinestyle(PS_SOLID, 10);
	setlinecolor(RGB(100, 100, 100));
	rectangle(5, 5, WIDTH + 15, HIGH + 15);	//绘制边界
	setlinestyle(PS_SOLID, 1);




	//绘制游戏字体元素
	LOGFONT f;
	gettextstyle(&f);                     // 获取当前字体设置
	f.lfHeight = 25;                      // 设置字体高度为 25
	_tcscpy(f.lfFaceName, _T("仿宋"));    // 设置字体为“黑体”(高版本 VC 推荐使用 _tcscpy_s 函数)
	f.lfQuality = ANTIALIASED_QUALITY;    // 设置输出效果为抗锯齿  
	settextstyle(&f);                     // 设置字体样式
	settextcolor(CYAN);
	outtextxy(640, 100, _T("剩余时间："));
	outtextxy(640, 300, _T("剩余刷新次数："));
	outtextxy(640, 580, _T("得分："));

	DrawRfrsTimes();

	DrawScore();

	//绘制刷新按钮
	DrawButton();

	InitImg();
	DrawAnimal();

	DrawCursor(cur.x, cur.y);

	std::thread t1(DrawTime);

	t1.detach();

}


void DrawTime()
{
	LOGFONT f;
	gettextstyle(&f);                     // 获取当前字体设置
	f.lfHeight = 80;                      // 设置字体高度为 80
	_tcscpy(f.lfFaceName, _T("仿宋"));    // 设置字体为“仿宋”(高版本 VC 推荐使用 _tcscpy_s 函数)
	f.lfQuality = ANTIALIASED_QUALITY;    // 设置输出效果为抗锯齿  
	settextstyle(&f);                     // 设置字体样式
	settextcolor(LIGHTGREEN);
	TCHAR s[10];

	while (gm_time >= 0)
	{
		_stprintf(s, _T("%d"), gm_time);
		setfillcolor(BLACK);
		solidrectangle(680, 130, 758, 250);
		outtextxy(680, 130, s);
		outtextxy(760, 130, _T("s"));	//绘制时间单位
		gm_time--;
		Sleep(1000);
	}
}


void GameRun()
{
	MOUSEMSG m;
	COOR t_cur;

	while (1)
	{
		if (gm_time < 0)
		{
			break;
		}
		else
		{
			m = GetMouseMsg();
			t_cur.x = (int)((m.x - 10) / 60);
			t_cur.y = (int)((m.y - 10) / 60);
			if (m.uMsg == WM_LBUTTONDOWN)
			{
				if (t_cur.x < 10 && t_cur.y < 14)
				{
					index = 0;
					DrawCursor(cur.x, cur.y, 1);
					DrawCursor(t_cur.x, t_cur.y);
					cur.x = t_cur.x;
					cur.y = t_cur.y;
					GetSameColorAnimal(cur, getpixel(cur.x*DIA + 10 + RAD, cur.y*DIA + 10 + RAD));
					if (index > 2)
					{
						Drawrectangle();
						FallAnimal();
						DrawCursor(t_cur.x, t_cur.y);
						AddScore();
						DrawRfrsTimes();
					}
				}
				if (m.x > 680 && m.x < 760 && m.y>430 && m.y < 480 && rfrstm>0)
				{
					DrawAnimal();
					rfrstm--;
					DrawRfrsTimes();
				}
			}
		}
	}
}


void AddScore()
{
	switch (index)
	{
	case 3:score += 3; break;
	case 4:score += 5; break;
	case 5:score += 8;  break;
	case 6:score += 11; gm_time += 5; break;
	default:score += 16; gm_time += 10; rfrstm++; break;
	}

	DrawScore();
}

void Drawrectangle()
{
	setfillcolor(RGB(204, 255, 255));
	setlinecolor(RGB(204, 255, 255));
	for (int i = 0; i < index; ++i)
	{
		fillrectangle(samecolor[i].x*DIA + 10, samecolor[i].y*DIA + 10, samecolor[i].x*DIA + 10 + DIA, samecolor[i].y*DIA + 10 + DIA);
	}
}

void GetSameColorAnimal(COOR coor, COLORREF cl)
{
	samecolor[index] = coor;
	index++;

	COOR tmpcoor;
	for (int i = 0; i < 4; ++i)
	{
		switch (i)
		{
		case 0:tmpcoor.x = coor.x; tmpcoor.y = coor.y - 1; break;//up
		case 1:tmpcoor.x = coor.x; tmpcoor.y = coor.y + 1; break;//down
		case 2:tmpcoor.x = coor.x - 1; tmpcoor.y = coor.y; break;//left
		case 3:tmpcoor.x = coor.x + 1; tmpcoor.y = coor.y; break;//right
		}

		if (IsExisted(tmpcoor, cl))
		{
			GetSameColorAnimal(tmpcoor, cl);
		}
	}
}


void FallAnimal()
{
	IMAGE tmpimg;
	int flg = 0;
	srand((unsigned)time(NULL));

	//排序
	for (int i = 0; i < index; ++i)
	{
		for (int j = index - 1; j > i; --j)
		{
			if (samecolor[j].y < samecolor[j - 1].y)
			{
				flg = 1;
				samecolor[index] = samecolor[j];
				samecolor[j] = samecolor[j - 1];
				samecolor[j - 1] = samecolor[index];
			}
		}
		if (!flg) break;
	}

	//向下移动上方小球
	for (int i = 0; i < index; ++i)
	{
		for (int j = samecolor[i].y; j >= 0; --j)
		{
			getimage(&tmpimg, samecolor[i].x*DIA + 10, (j - 1)*DIA + 10, 59, 59);//获取上方图像
			setfillcolor(RGB(204, 255, 255));
			setlinecolor(RGB(204, 255, 255));
			if (j != 0)
			{
				fillrectangle(samecolor[i].x*DIA + 10, (j - 1)*DIA + 10, samecolor[i].x*DIA + 10 + 59, (j - 1)*DIA + 10 + 59);//涂黑原彩色块
			}
			putimage(samecolor[i].x*DIA + 10, j*DIA + 10, &tmpimg);//原彩色块下方画
			Sleep(10);

			//添加新动物
			if (j == 0)
			{
				tmpimg = img[rand() % 6];
				putimage(samecolor[i].x*DIA + 10, j*DIA + 10, &tmpimg);
				Sleep(10);
			}
		}
	}
}


bool IsExisted(COOR coor, COLORREF cl)
{
	if (getpixel(coor.x*DIA + 10 + RAD, coor.y*DIA + 10 + RAD) != cl)
	{
		return false;
	}
	else
	{
		for (int i = 0; i < index; ++i)
		{
			if (coor.x == samecolor[i].x && coor.y == samecolor[i].y)
			{
				return false;
			}
		}
		return true;
	}
}

void GameOver()
{
	setbkcolor(BLACK);
	cleardevice();

	LOGFONT f;
	gettextstyle(&f);                     // 获取当前字体设置
	f.lfHeight = 100;                      // 设置字体高度为 80
	_tcscpy(f.lfFaceName, _T("仿宋"));    // 设置字体为“仿宋”(高版本 VC 推荐使用 _tcscpy_s 函数)
	f.lfQuality = ANTIALIASED_QUALITY;    // 设置输出效果为抗锯齿  
	settextstyle(&f);                     // 设置字体样式
	settextcolor(LIGHTRED);
	outtextxy(200, 350, _T("GameOver"));

	TCHAR s[10];
	_stprintf(s, _T("%d"), score);
	f.lfHeight = 40;
	settextstyle(&f);                     // 设置字体样式
	settextcolor(LIGHTBLUE);
	outtextxy(500, 580, _T("分数"));
	outtextxy(600, 580, s);

}

void PlayMusic()
{
	PlaySound(_T(".\\res\\bgm.wav"), NULL, SND_FILENAME | SND_ASYNC);
}