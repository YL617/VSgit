//#define _CRT_SECURE_NO_WARNINGS
//#include "work.h"
//#include <mmsystem.h>
//#pragma comment(lib,"winmm.lib")
//ExMessage msg = { 0 };
//
//void clear();              //清屏函数
//void returnbutton(IMAGE img_mm);
//bool InArea(int msgx, int msgy, int rx1, int ry1, int rx2, int ry2);
//void button(int x1, int y1, int x2, int y2, const wchar_t* table);
//int centerText_button(int a);
//bool judge_message(int x1, int y1, int x2, int y2);
//int change();
//int draw_table(int* a);
//void draw_base(Table con);     //绘制基础的信息
//void draw_BASE();              //绘制“工号、工资”等
//
////宏定义
//#define headline_w 400      //“职工工资管理系统”宽位
//#define headline_h 10       //“职工工资管理系统”高位
//#define headline_s 50       //“职工工资管理系统”字体大小 
//
//#define title_h  100         //"工号、姓名"等的高位
//#define data_h   140          //“工号、姓名”等的数据高位
//#define line_x   200          //表格线的宽位
//#define line_w   1000         //表格线的末尾
//#define line_h   135          //表格线的高位
//
//
//int main()
//{
//	mciSendString(L"open E:\\计算机语言相关\\C\\VS\\表白\\浪漫空气.mp3", NULL, 0, NULL);
//	mciSendString(L"play E:\\计算机语言相关\\C\\VS\\表白\\浪漫空气.mp3", NULL, 0, NULL);
//
//	Table  con = { 0 };
//	InitTable(&con);
//
//
//	initgraph(1200, 600, 1 | 8);      //创建一个（1200，600）大小的窗口
//	setbkcolor(BLACK);
//	cleardevice();
//	IMAGE img_mm;
//	loadimage(&img_mm, L"C:\\Users\\杨乐\\Desktop\\0a5098aaaa2fe83680afb73fc43c1334.png", 1200, 600);   //加载图片（不覆盖）
//
//	int new_button = centerText_button(1);         //保存鼠标的按键情况
//	int n1 = 0, n2 = 0, n3 = 0;
//	cleardevice();
//	putimage(0, 0, &img_mm);   //用图片覆盖背景
//
//	if (change_T())         //判断是否在原先系统数据基础上操作
//	{
//		read_text(&con);
//	}
//	while (1)
//	{
//
//		int work_number = 0, a[3] = { 0 };                        //计算比例
//		double new_basewage = 0, new_allowance = 0, b[3] = { 0.0 };   //计算比例
//
//		//获取消息
//
//		if (peekmessage(&msg, EX_MOUSE))
//		{
//
//		}
//		//双缓冲
//		BeginBatchDraw();
//		if (new_button == 0)              //当未点击任何按钮，按钮参数为0时，输出背景图片和按钮
//		{
//			putimage(0, 0, &img_mm);
//			centerText_button(0);
//			settextstyle(headline_s, 0, L"楷体");
//			outtextxy(headline_w, headline_h, L"职工工资管理系统");
//
//		}
//		EndBatchDraw();
//
//		if (judge_message(1000, 10, 1100, 60))               //当点击“首页”按钮时，按钮参数归零，并清屏
//		{
//			new_button = 0;
//			n1 = 0;
//			n2 = 0;
//			n3 = 0;
//			cleardevice();
//		}
//
//		if (centerText_button(1) > 0)                         //当按钮被按下时
//		{
//			new_button = centerText_button(1);                   //按钮参数等于被按下的按钮
//			returnbutton(img_mm);                                //背景清屏后，输出图片，并显示“首页”按钮
//		}
//
//		BeginBatchDraw();
//		switch (new_button)                                     //判断按钮参数
//		{
//		case 1:                                                  //情况：按钮1被按下
//			set_work(&con);
//			define_tax(&con);
//			write_text(&con);
//			new_button = 0;
//			break;
//		case 2:
//			sort_worknumber(&con);
//			write_text(&con);
//
//			settextstyle(30, 0, L"楷体");
//			draw_BASE();
//
//			settextstyle(20, 0, L"宋体");
//			draw_base(con);
//
//			break;
//		case 3:
//			sort_realwage(&con);
//			write_text(&con);
//
//			settextstyle(30, 0, L"楷体");
//			draw_BASE();
//
//			settextstyle(20, 0, L"宋体");
//			draw_base(con);
//
//			break;
//		case 4:
//			settextstyle(30, 0, L"楷体");
//			draw_BASE();
//			BeginBatchDraw();
//			settextstyle(20, 0, L"宋体");
//			for (int i = 0; i < con.Now_person; i++)
//			{
//				wchar_t str[6][100];
//				swprintf(str[0], 100, L" % -10d", con.person[i].Work_number);
//				swprintf(str[1], 100, L" % s", con.person[i].Name);
//				swprintf(str[2], 100, L" % -10.2f", con.person[i].Base_wage);
//				swprintf(str[3], 100, L" % -10.2f", con.person[i].Allowance);
//				swprintf(str[4], 100, L" % -10.2f", con.person[i].Tax);
//				swprintf(str[5], 100, L" % -10.2f", con.person[i].Real_wage);
//
//				outtextxy(290, data_h + i * 30, str[0]);
//				outtextxy(410, data_h + i * 30, str[1]);
//				outtextxy(500, data_h + i * 30, str[2]);
//				outtextxy(620, data_h + i * 30, str[3]);
//				outtextxy(735, data_h + i * 30, str[4]);
//				outtextxy(840, data_h + i * 30, str[5]);
//
//
//				setlinestyle(PS_DASH);
//				setlinecolor(BLACK);
//				line(line_x, line_h + i * 30, line_w, line_h + i * 30);
//			}
//			EndBatchDraw();
//
//			wchar_t m[3][100];
//
//			if (!n1)
//			{
//
//				do
//				{
//
//					InputBox(m[0], 100, L"请输入职工工号：");
//					work_number = _wtoi(m[0]);
//				} while (judge(work_number, &con));
//
//				InputBox(m[1], 100, L"请输入修改职工的新基础工资：");
//				new_basewage = _wtof(m[1]);
//
//				InputBox(m[2], 100, L"请输入修改职工的新津贴：");
//				new_allowance = _wtof(m[2]);
//			}
//			n1 = 1;
//			change_work(&con, work_number, new_basewage, new_allowance);
//			write_text(&con);
//
//			BeginBatchDraw();
//			cleardevice();
//			putimage(0, 0, &img_mm);
//			settextstyle(30, 0, L"楷体");
//			draw_BASE();
//			settextstyle(headline_s, 0, L"楷体");
//			outtextxy(headline_w, headline_h, L"职工工资管理系统");
//			settextstyle(20, 0, L"宋体");
//			draw_base(con);
//			EndBatchDraw();
//			if (draw_table(&n1))
//			{
//				new_button = 0;
//			}
//
//			break;
//
//		case 5:
//			BeginBatchDraw();
//			returnbutton(img_mm);
//			putimage(0, 0, &img_mm);
//			settextstyle(headline_s, 0, L"楷体");
//			outtextxy(headline_w, headline_h, L"职工工资管理系统");
//			settextstyle(30, 0, L"楷体");
//			draw_BASE();
//			EndBatchDraw();
//
//
//			if (!n2)
//			{
//
//				do
//				{
//					InputBox(m[0], 20, L"请输入查询职工的工号：");
//					work_number = _wtoi(m[0]);
//				} while (seek_work(&con, work_number, &n3));
//
//
//			}
//			n2 = 1;
//			wchar_t str[6][100];
//
//			swprintf(str[0], 100, L" % -10d", con.person[n3].Work_number);
//			swprintf(str[1], 100, L" % s", con.person[n3].Name);
//			swprintf(str[2], 100, L" % -10.2f", con.person[n3].Base_wage);
//			swprintf(str[3], 100, L" % -10.2f", con.person[n3].Allowance);
//			swprintf(str[4], 100, L" % -10.2f", con.person[n3].Tax);
//			swprintf(str[5], 100, L" % -10.2f", con.person[n3].Real_wage);
//
//			BeginBatchDraw();
//
//			settextstyle(20, 0, L"宋体");
//			outtextxy(290, 140, str[0]);
//			outtextxy(410, 140, str[1]);
//			outtextxy(500, 140, str[2]);
//			outtextxy(620, 140, str[3]);
//			outtextxy(735, 140, str[4]);
//			outtextxy(840, 140, str[5]);
//			EndBatchDraw();
//			break;
//		case 6:
//			analyze_work(&con, a, b);
//			wchar_t str1[100];
//			wchar_t str2[100];
//			wchar_t str3[100];
//			swprintf(str1, 100, L"实发工资小于3000的人数为：%-3d                     比例为：%f%%", a[0], b[0]);
//			swprintf(str2, 100, L"实发工资大于3000并且小于4000的人数为：%-3d   比例为：%f%%", a[1], b[1]);
//			swprintf(str3, 100, L"实发工资大于等于4000的人数为：%-3d                 比例为：%f%%", a[2], b[2]);
//			settextstyle(20, 0, L"宋体");
//			outtextxy(200, 150, str1);
//			outtextxy(200, 210, str2);
//			outtextxy(200, 270, str3);
//			break;
//		case 7:
//			if (change())
//			{
//				return 0;
//			}
//			else
//			{
//				new_button = 0;
//			}
//
//			break;
//		}
//		EndBatchDraw();
//		msg.message = 0;
//
//	}
//
//	return 0;
//}
//
//void returnbutton(IMAGE img_mm)             //绘制返回菜单版的按钮
//{
//	cleardevice();
//	putimage(0, 0, &img_mm);
//	settextstyle(headline_s, 0, L"楷体");
//	outtextxy(headline_w, headline_h, L"职工工资管理系统");
//	int x = 1000;
//	int y = 10;
//	int w = 100;
//	int h = 50;
//
//	if (InArea(msg.x, msg.y, x, y, x + w, y + h))
//	{
//		setfillcolor(RGB(108, 108, 108));             //设置按钮悬浮状态
//		settextcolor(RED);
//	}
//	else
//	{
//		setfillcolor(WHITE);
//		settextcolor(BLACK);
//	}
//	int hspace = (w - textwidth(L"首页")) / 2;
//	int wspace = (h - textheight(L"首页")) / 2;
//
//
//	setbkmode(TRANSPARENT);
//
//	outtextxy(x + hspace, y + wspace, L"首页");
//
//}
//
//void clear()
//{
//	printf("\n按回车键，清屏！！！");
//	getchar();                 //读取缓冲区的回车键
//	system("cls");          //清屏
//}
////建立菜单表
//const wchar_t* table[] =
//{
//	L"1、建立职工工资表",
//	L"2. 职工扣税和实发工资",
//	L"3. 实发工资从高到低排序",
//	L"4. 修改职工工资信息",
//	L"5. 查询职工工资信息",
//	L"6. 职工工资统计分析",
//	L"0. 退出系统"
//};
//
//bool InArea(int msgx, int msgy, int rx1, int ry1, int rx2, int ry2)     //判段鼠标是否在按钮上
//{
//
//	if (msgx<rx2 && msgx>rx1 && msgy<ry2 && msgy>ry1)
//	{
//		return true;
//	}
//	return false;
//}
//
//void button(int x1, int y1, int x2, int y2, const wchar_t* table)      //绘制按钮
//{
//	if (InArea(msg.x, msg.y, x1, y1, x2, y2))                    //设置按钮悬浮状态
//	{
//		setfillcolor(RGB(108, 108, 108));
//		settextcolor(RED);
//	}
//	else
//	{
//		setbkmode(TRANSPARENT);
//		settextcolor(BLACK);
//	}
//
//	//绘制按钮文本
//	int hspace = (x2 - x1 - textwidth(table)) / 2;
//	int wspace = (y2 - y1 - textheight(table)) / 2;
//
//
//	setbkmode(TRANSPARENT);  //背景模式设置为透明
//
//	outtextxy(x1 + hspace, y1 + wspace, table);
//
//}
//
//bool judge_message(int x1, int y1, int x2, int y2)               //判断按钮是否被点击
//{
//	//判断按钮是否被点击
//	if (msg.message == WM_LBUTTONDOWN && InArea(msg.x, msg.y, x1, y1, x2, y2))
//	{
//		return true;
//
//	}
//	return false;
//}
//
//int centerText_button(int a)       //centerText_button（0）输出按钮     centerText_button（1）记录鼠标点击按钮情况
//{
//	int rx = 350;
//	int ry = 100;
//	int rw = 500;
//	int rh = 50;
//	int spacing = 22;
//
//	settextstyle(30, 0, L"微软雅黑");
//	int i;
//	for (i = 0; i < 7; i++)
//	{
//		if (a == 0)
//		{
//			button(rx, ry, rx + rw, ry + rh, table[i]);
//		}
//		else if (a == 1)
//		{
//			if (judge_message(rx, ry, rx + rw, ry + rh))
//			{
//				return i + 1;                                  //返回第几个按钮
//			}
//		}
//		ry += rh + spacing;                                     //改变按钮的高度
//	}
//	return 0;
//}
//
//int change()                         //跳出窗口，判断是否退出系统
//{
//	HWND hnd = GetHWnd();
//	SetWindowText(hnd, L"退出");
//	int isok = MessageBox(hnd, L"是否退出系统？", L"提示", MB_OKCANCEL);
//	if (isok == IDOK)                //点击确定，返回1
//	{
//		return 1;
//	}
//	else if (isok == IDCANCEL)         //点击取消，返回0
//	{
//		return 0;
//	}
//}
//
//int draw_table(int* a)
//{
//	HWND hnd = GetHWnd();
//	SetWindowText(hnd, L"退出");
//	int isok = MessageBox(hnd, L"是否要继续修改或查询？", L"提示", MB_OKCANCEL);
//	if (isok == IDOK)                //点击确定，返回1
//	{
//		*a = 0;
//		return 0;
//	}
//	else if (isok == IDCANCEL)         //点击取消，返回0
//	{
//		return 1;
//	}
//
//}
//
//void draw_base(Table con)
//{
//	for (int i = 0; i < con.Now_person; i++)
//	{
//		wchar_t str[6][100];
//		swprintf(str[0], 100, L" % -10d", con.person[i].Work_number);
//		swprintf(str[1], 100, L" % s", con.person[i].Name);
//		swprintf(str[2], 100, L" % -10.2f", con.person[i].Base_wage);
//		swprintf(str[3], 100, L" % -10.2f", con.person[i].Allowance);
//		swprintf(str[4], 100, L" % -10.2f", con.person[i].Tax);
//		swprintf(str[5], 100, L" % -10.2f", con.person[i].Real_wage);
//
//		outtextxy(290, data_h + i * 30, str[0]);
//		outtextxy(410, data_h + i * 30, str[1]);
//		outtextxy(500, data_h + i * 30, str[2]);
//		outtextxy(620, data_h + i * 30, str[3]);
//		outtextxy(735, data_h + i * 30, str[4]);
//		outtextxy(840, data_h + i * 30, str[5]);
//
//
//		setlinestyle(PS_DASH);
//		setlinecolor(BLACK);
//		line(line_x, line_h + i * 30, line_w, line_h + i * 30);
//	}
//}
//
//void draw_BASE()
//{
//	outtextxy(290, title_h, L"工号");
//	outtextxy(400, title_h, L"姓名");
//	outtextxy(500, title_h, L"基础工资");
//	outtextxy(645, title_h, L"津贴");
//	outtextxy(750, title_h, L"税收");
//	outtextxy(840, title_h, L"真实工资");
//}