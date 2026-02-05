#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <easyx.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#include <conio.h>
#include <math.h>

//宏定义
#define table_x   1200
#define table_y   640

//敌方小球攻击速度
int space_x = 5;
int space_y = 5;
int space_itx = 5;
int space_ity = 5;
//己方小球的初始速度
int space_me = 2;
//关卡结束条件
int end = 0;
//加载背景图片
IMAGE img_qq[3];
//定义鼠标
ExMessage msg = { 0 };

//结构体——我
struct Me {
	int x;
	int y;
	int r;
	bool survival;
}Me;

struct You {
	int x;
	int y;
	int r;
}You;

struct it {
	int x;
	int y;
	int r;
}it;
//初始化——定义数值
void DefineCircle_me();
void DefineCircle_you();
void DefineCircle_it();
//画圆
void DrawCircle_me(DWORD color);
void DrawCircle_you(DWORD color);
void DrawCircle_it(DWORD color);
//改变圆形的位置
void ChangePlace();
//圆形瞬移技能
void QuickRemove();
//敌人的球开始移动
void remove_you();
void remove_it();
//小球被敌方球攻击后死亡
void if_survival() {                                                               
	if ((int)sqrt((Me.x - You.x) * (Me.x - You.x) + (Me.y - You.y) * (Me.y - You.y)) < Me.r + You.r) {
		Me.survival = false;
	}
	if ((int)sqrt((Me.x - it.x) * (Me.x - it.x) + (Me.y - it.y) * (Me.y - it.y)) < Me.r + it.r) {
		Me.survival = false;
	}
}
//第一关   
//特点：你是一个小球，只需躲避一个小球的撞击，坚持30s(此时圆心不能碰墙，否者将封禁行动能力)
void fist_bk();
void fist();
//第二关
//特点：
void second_bk();
void second();

//第三关
//特点：敌方的小球分裂成两个球，且速度有所增加，你的小球速度不变但大小变小一点，好消息是你领悟了技能：瞬移
void last_bk();
void last();
int main() {
	initgraph(table_x,table_y,1|8);
	loadimage(&img_qq[0], "E:\\Computer_language\\C\\VS\\寒假小项目\\图片\\球球作战\\background.png", 1200, 640);
	loadimage(&img_qq[1],"E:\\Computer_language\\C\\VS\\寒假小项目\\图片\\球球作战\\bb255d73-4db8-469a-807d-a9125f3b6216.png",1200,640);
	loadimage(&img_qq[2], "E:\\Computer_language\\C\\VS\\寒假小项目\\图片\\球球作战\\ee2ebefb-7e0c-43a6-af5b-d250362df20f.png",1200,640);
	putimage(0, 0, &img_qq[0]);
	DefineCircle_me();
	DefineCircle_you();
	DefineCircle_it();
	while (1) {
		//书写标题
		setbkmode(TRANSPARENT);
		settextstyle(150, 0, "楷体");
		settextcolor(YELLOW);
		outtextxy(300, 30, "球球大战");
		settextstyle(40, 0, "宋体");
		settextcolor(BLACK);
		outtextxy(450, 520, "开始游戏（左击鼠标）");
		if (peekmessage(&msg, EX_MOUSE)) {
			if (msg.message == WM_LBUTTONDOWN) {
				break;
			}
		}
	}
	//消除鼠标状态
	msg.message = 0;
	//第一关   
	//特点：你是一个小球，只需躲避一个小球的撞击，坚持30s(此时圆心不能碰墙，否者将封禁行动能力)
	fist_bk();
	fist();
	while (Me.survival==false) {
		cleardevice();
		BeginBatchDraw();
		putimage(0, 0, &img_qq[2]);
		EndBatchDraw();
	}
	//重置鼠标状态
	msg.message = 0;
	//重置撞击次数
	end = 0;
	Sleep(500);
	//第二关
	//特点：敌方小球的大小变大、移动速度变快,己方小球的大小变大
	second_bk();
	second();
	while (Me.survival==false) {
		cleardevice();
		BeginBatchDraw();
		putimage(0, 0, &img_qq[2]);
		EndBatchDraw();
	}
	//重置鼠标状态
	msg.message = 0;
	//重置撞击次数
	end = 0;
	Sleep(500);
	//第三关
	//特点：敌方的小球分裂成两个球，且速度有所增加，你的小球速度不变但大小变小一点，好消息是你领悟了技能：瞬移
	last_bk();
	last();
	while(Me.survival) {
		cleardevice();
		BeginBatchDraw();
		putimage(0,0,&img_qq[1]);
		EndBatchDraw();
	}
	while (Me.survival == false) {
		cleardevice();
		BeginBatchDraw();
		putimage(0, 0, &img_qq[2]);
		EndBatchDraw();
	}
}

//初始化——定义数值
void DefineCircle_me() {
	Me.x = 200;
	Me.y = 500;
	Me.r = 20;
	Me.survival = true;
}
void DefineCircle_you() {
	You.x = 100;
	You.y = 100;
	You.r = 50;
}
void DefineCircle_it() {
	it.x = 0;
	it.y = 0;
	it.r = 0;
}

//初始化——画圆
void DrawCircle_me(DWORD color) {
	setfillcolor(color);
	solidcircle(Me.x, Me.y, Me.r);
}
void DrawCircle_you(DWORD color) {
	setfillcolor(color);
	solidcircle(You.x, You.y, You.r);
}
void DrawCircle_it(DWORD color) {
	setfillcolor(color);
	solidcircle(it.x, it.y, it.r);
}

//改变圆形的位置
void ChangePlace() {
	if (Me.x >= 0 && Me.x <= table_x && Me.y >= 0 && Me.y <= table_y)
	{
		if (GetAsyncKeyState(VK_UP)) {
			Me.y -= space_me;
		}
		if (GetAsyncKeyState(VK_DOWN)) {
			Me.y += space_me;
		}
		if (GetAsyncKeyState(VK_RIGHT)) {
			Me.x += space_me;
		}
		if (GetAsyncKeyState(VK_LEFT)) {
			Me.x -= space_me;
		}
	}
}

//圆形瞬移技能
void QuickRemove() {
	if (Me.y > table_y)
	{
		Me.y = 0;
	}
	if (Me.y < 0) {
		Me.y = table_y;
	}
	if (Me.x > table_x) {
		Me.x = 0;
	}
	if (Me.x < 0) {
		Me.x = table_x;
	}
}

//敌人的球开始移动
void remove_you() {
	You.x += space_x;
	You.y += space_y;
	if (You.x > table_x-You.r ) {
		You.x = table_x - You.r;
		space_x = ~space_x;
		end++;

	}
	if ( You.x < You.r) {
		You.x = You.r;
		space_x = ~space_x;
		end++;

	}
	if (You.y > table_y-You.r) {
		You.y = table_y - You.r;
		space_y = ~space_y;
		end++;
	}
	if ( You.y <You.r) {
		You.y = You.r;
		space_y = ~space_y;
		end++;
	}
}

void remove_it() {
	it.x += space_itx+rand()%5;
	it.y += space_ity+rand()%4;
	if (it.x > table_x - it.r) {
		it.x = table_x - it.r;
		space_itx = ~space_itx;
	}
	if (it.x < it.r) {
		it.x = it.r;
		space_itx = ~space_itx;

	}
	if (it.y > table_y - it.r) {
		it.y = table_y - it.r;
		space_ity = ~space_ity;
	}
	if (it.y < it.r) {
		it.y = it.r;
		space_ity = ~space_ity;
	}
}
//第一关   
//特点：你是一个小球，只需躲避一个小球的撞击，坚持30s(此时圆心不能碰墙，否者将封禁行动能力)
void fist_bk() {
	cleardevice();
	putimage(0, 0, &img_qq[0]);
	settextstyle(100, 0, "楷体");
	settextcolor(YELLOW);
	outtextxy(410, 20, "第一关");
	settextstyle(30, 0, "宋体");
	settextcolor(BLACK);
	outtextxy(20,150,"关卡介绍：");
	outtextxy(170, 150, "你是一个小白球，只需利用键盘躲避一个小红球的撞击，坚持到敌方小球的20");
	outtextxy(170,200,"次撞击结束，即可通关。");
	outtextxy(20,300,"注意事项：");
	outtextxy(170,300,"不要让你的圆心碰到边界，否者你将失去移动能力!!!（合理利用此条件）");
	Sleep(2000);
	while (1) {
		if (peekmessage(&msg, EX_MOUSE)) {
			if (msg.message == WM_LBUTTONDOWN) {
				break;
			}
		}
		outtextxy(450, 600, "(点击左键：继续)");
	}

}

void fist() {
	while (Me.survival &&end<=20)
	{
		//双缓区
		BeginBatchDraw();
		//清屏
		cleardevice();
 		//加载背景
		putimage(0, 0, &img_qq[0]);
		DrawCircle_me(WHITE);
		DrawCircle_you(RED);
		// fillcircle(Me.x, Me.y, Me.r);
		ChangePlace();
		//瞬移技能
	//	QuickRemove();
		//敌方小球移动撞击
		remove_you();
		//判断你是否被撞击
		if_survival();
		EndBatchDraw();
		Sleep(1);
	}
}

//第二关   
//特点：敌方小球的大小变大、移动速度变快，己方小球的大小变大
void second_bk() {	
	Me.r = 50;
	You.r += 20;
	space_x += 3;
	space_y += 3;
	space_me += 2;
	cleardevice();
	putimage(0, 0, &img_qq[0]);
	settextstyle(100, 0, "楷体");
	settextcolor(YELLOW);
	outtextxy(410, 20, "第二关");
	settextstyle(30, 0, "宋体");
	settextcolor(BLACK);
	outtextxy(20, 150, "关卡介绍：");
	outtextxy(170, 150, "依然只有一个小红球撞击你，但是敌方小球的大小变大、移动速度变快，己方");
	outtextxy(170, 200, "小球的大小变大、移动速度也变快");
	outtextxy(20, 300, "注意事项：");
	outtextxy(170, 300, "此时你的小球无法藏在角落");
	Sleep(2000);
	while (1) {
		if (peekmessage(&msg, EX_MOUSE)) {
			if (msg.message == WM_LBUTTONDOWN) {
				break;
			}
		}
		outtextxy(450, 600, "(点击左键：继续)");
	}
}
void second() {
	while (Me.survival && end <= 30)
	{
		if (Me.x < Me.r) {
			Me.x = Me.r;
		}
		if (Me.x + Me.r > table_x) {
			Me.x = table_x - Me.r;
		}
		if (Me.y < Me.r) {
			Me.y = Me.r;
		}
		if (Me.y + Me.r > table_y) {
			Me.y = table_y - Me.r;
		}
		//双缓区
		BeginBatchDraw();
		//清屏
		cleardevice();
		putimage(0,0,&img_qq[0]);
		DrawCircle_me(WHITE);
		DrawCircle_you(RED);
		// fillcircle(Me.x, Me.y, Me.r);
		ChangePlace();
		//瞬移技能
	//	QuickRemove();
		//敌方小球移动撞击
		remove_you();
		//判断你是否被撞击
		if_survival();
		EndBatchDraw();
		Sleep(1);
	}
}

//第三关
//特点：敌方的小球分裂成两个球，且速度有所增加，你的小球速度不变但大小变小一点，好消息是你领悟了技能：瞬移
void last_bk() {
	Me.r = 30;
	You.r += 20;
	space_x += 2;
	space_y += 2;
	cleardevice();
	putimage(0, 0, &img_qq[0]);
	settextstyle(100, 0, "楷体");
	settextcolor(YELLOW);
	outtextxy(410, 20, "第三关");
	settextstyle(30, 0, "宋体");
	settextcolor(BLACK);
	outtextxy(20, 150, "关卡介绍：");
	outtextxy(170, 150, "敌方的小球分裂成两个球，且速度有所增加，你的小球速度不变但大小变小一");
	outtextxy(170, 200, "点");
	outtextxy(20, 300, "限时技能：");
	outtextxy(170, 300, "瞬移技能（自行体会）");
	Sleep(2000);
	while (1) {
		if (peekmessage(&msg, EX_MOUSE)) {
			if (msg.message == WM_LBUTTONDOWN) {
				break;
			}
		}
		outtextxy(450, 600, "(点击左键：继续)");
	}
	it.x = You.x;
	it.y = You.y;
	it.r = You.r;
}
void last() {
	while (Me.survival && end <= 40)
	{
		//双缓区
		BeginBatchDraw();
		//清屏
		cleardevice();
		//加载背景
		putimage(0, 0, &img_qq[0]);
		DrawCircle_me(WHITE);
		DrawCircle_you(RED);
		DrawCircle_it(RED);
		ChangePlace();
		//瞬移技能
		QuickRemove();
		//敌方小球移动撞击
		remove_you();
		remove_it();
		//判断你是否被撞击
		if_survival();
		EndBatchDraw();
		Sleep(1);
	}
}
