#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <easyx.h>
#include <stdlib.h>
#include <time.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

IMAGE img_bk[2];
IMAGE img_me[2];

void loadimg()
{
	loadimage(img_bk + 0, L"E:\\计算机语言相关\\C\\VS\\表白\\welcome.png",getwidth(),getheight());
	loadimage(img_bk + 1, L"E:\\计算机语言相关\\C\\VS\\表白\\bk.png",getwidth(),getheight());

	loadimage(img_me + 0, L"E:\\计算机语言相关\\C\\VS\\表白\\1.jpg",40,40);
	loadimage(img_me + 1, L"E:\\计算机语言相关\\C\\VS\\表白\\2.jpg",40,40);
}

void welcome()
{
	mciSendString(L"open E:\\计算机语言相关\\C\\VS\\表白\\浪漫空气.mp3", NULL, 0, NULL);
	mciSendString(L"play E:\\计算机语言相关\\C\\VS\\表白\\浪漫空气.mp3", NULL, 0, NULL);

	srand(time(NULL));    //时间种子
	setbkmode(TRANSPARENT);

	settextstyle(48, 0, L"宋体");          //字体大小，字体

	while (true)
	{
		putimage(0, 0, img_bk + 0);



		settextcolor(RGB(rand()%256,rand()%256,rand()%256));       //颜色
		outtextxy(450, 20, L"XXXXX");        //标题

		outtextxy(200, 100, L"我想拉着你的手");
		outtextxy(200, 150, L"直到海的尽头");
		outtextxy(200, 200, L"我们就在这个路口");
		outtextxy(200, 250, L"各自相流");
		outtextxy(200, 300, L"直到");
		outtextxy(200, 350, L"海的尽头");
		outtextxy(200, 400, L"");
		outtextxy(200, 450, L"");
		outtextxy(200, 500, L"今朝胜旧年，有你胜所有");
		outtextxy(200, 550, L"");

		for (int i = 0; i < 10; i++)
		{
			settextcolor(RGB(rand() % 256, rand() %256 , rand() % 256));
		outtextxy(rand()%getwidth(), rand()%getheight(), L"♥");
		}


		Sleep(500);

		static clock_t start = 0;
		if (clock() - start > 5000)
		{
			break;
		}
	}

}

struct Meteor
{
	int x;
	int y;
	int speed;     //速度
};

void meteor_init(Meteor* pthis, int x, int y, int speed)
{
	pthis->x = x;
	pthis->y = y;
	pthis->speed = speed;
}

void meteor_draw(Meteor* pthis)
{
	putimage(pthis->x, pthis->y, img_me + rand()%2, SRCPAINT);
}

void meteor_update(Meteor* pthis)
{
	pthis->x += pthis->speed;
	pthis->y += pthis->speed;

	if (pthis->y > 500)
	{
		pthis->x = rand() % 1100 - 300;
		pthis->y = rand() % 840-300;
	}
}
#define METEOE_NUM 100
int main()
{
	initgraph(1200, 800, 1 | 8);
	setbkcolor(WHITE);
	cleardevice();
	loadimg();
	welcome();

	Meteor meteors[METEOE_NUM];
	for (int i = 0; i < METEOE_NUM; i++)
	{
		int x = rand()%1100-300;
		int y = rand()%840-300;
		meteor_init(meteors + i, x,y, rand()%2+1);
	}
	while (true)
	{	
		BeginBatchDraw();
		putimage(0, 0, img_bk + 1);

		for (int i = 0; i < METEOE_NUM; i++)
		{

		meteor_draw(meteors+i);
		meteor_update(meteors+i);
		}
		EndBatchDraw();
		Sleep(10);
	}

	getchar();
	return 0;
}