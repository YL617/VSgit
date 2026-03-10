#define _CRT_SECURE_NO_WARNINGS
#include "work.h"


bool change_T()
{
	HWND hnd = GetHWnd();
	SetWindowText(hnd, L"退出");
	int hed = MessageBox(hnd, L"是否在原先系统基础上操作？", L"提示", MB_OKCANCEL);
	if (hed == IDOK)
	{
		return true;
	}
	else if (hed == IDCANCEL)
	{
		return false;
	}
}


void InitTable(Table* con)
{
	con->Now_person = 0;
	memset(con->person, 0, sizeof(con->person));
}


void write_text(Table* con)
{
	FILE* fpWrite;
	if ((fpWrite = fopen("E:\\计算机语言相关\\C\\VS\\项目\\text.txt", "w")) == NULL)
	{
		printf("无法打开文件text.txt");
		exit(0);              //退出并删除文件
	}
	for (int i = 0; i < con->Now_person; i++)
	{
		fprintf(fpWrite, "%-10d\t%-10s\t%-10.2f\t%-10.2f\t%-10.2f\t%-10.2f\n", con->person[i].Work_number,
			con->person[i].Name,
			con->person[i].Base_wage,
			con->person[i].Allowance,
			con->person[i].Tax,
			con->person[i].Real_wage);

	}
	fclose(fpWrite);
	fpWrite = NULL;
}

void read_text(Table* con)
{
	FILE* fpRead;
	if ((fpRead = fopen("E:\\计算机语言相关\\C\\VS\\项目\\text.txt", "r")) == NULL)
	{
		printf("无法打开文件text.txt");
		exit(0);
	}
	int i;
	for (i = 0; i < 500; i++)
	{
		int result = fscanf(fpRead, "%d %s %lf %lf %lf %lf", &con->person[i].Work_number,
			con->person[i].Name,
			&con->person[i].Base_wage,
			&con->person[i].Allowance,
			&con->person[i].Tax,
			&con->person[i].Real_wage);
		if (result != 6)
			break;
	}

	con->Now_person = i;

	fclose(fpRead);
	fpRead = NULL;
}

void set_work(Table* con)        //函数1：建立工资表
{
	if (con->Now_person == 500)    printf("职工人员已招满！");
	else
	{
		int a;
		wchar_t c[2];
		do
		{
			a = 0;
            wchar_t s[4][20];
			do
			{
				InputBox(s[0], 10, L"请输入职工工号：");
				con->person[con->Now_person].Work_number = _wtoi(s[0]);
			} while (Judge(con->person[con->Now_person].Work_number, con));
		
			InputBox(con->person[con->Now_person].Name, 10, L"请输入新职工姓名：");

			InputBox(s[1], 10, L"请输入新职工基本工资：");
			con->person[con->Now_person].Base_wage = _wtof(s[1]);

			InputBox(s[2], 10, L"请输入新职工津贴：");
			con->person[con->Now_person].Allowance = _wtof(s[2]);

			InputBox(c, 10, L"是否录入下一项：");
			

			if (c[0] == 'Y' || c[0] == 'y')    a = 1;
			else if (c[0] == 'N' || c[0] == 'n')  a = 0;
			con->Now_person += 1;
		} while (a);
	}
}

int Judge(int a, Table* con)
{
	if (a <= 0 || a >= 1000000000)
	{
		HWND hnd = GetHWnd();
		SetWindowText(hnd, L"退出");
		int isok = MessageBox(hnd, L"输入的工号形式错误！！！", L"提示", MB_OKCANCEL);
		return 1;
	}
	for (int i = 0; i < con->Now_person; i++)
	{
		if (a == con->person[i].Work_number)
		{
			HWND hed = GetHWnd();
			SetWindowText(hed, L"退出");
			int isok = MessageBox(hed, L"该工号已存在！！！", L"提示", MB_OKCANCEL);
			return 1;
		}
	}
	return 0;
}

void define_tax(Table* con)     //函数2：确定职工扣税和实际工资
{
	for (int i = 0; i < con->Now_person; i++)
	{
		if (con->person[i].Base_wage + con->person[i].Allowance < 3000)
		{
			con->person[i].Tax = 0;
		}
		else if (con->person[i].Base_wage + con->person[i].Allowance < 4000)
		{
			con->person[i].Tax = (con->person[i].Base_wage + con->person[i].Allowance - 3000) * 0.05;
		}
		else
		{
			con->person[i].Tax = (con->person[i].Base_wage + con->person[i].Allowance - 3000) * 0.05 + (con->person[i].Base_wage + con->person[i].Allowance - 4000) * 0.1;              //职工扣税金额
		}
		con->person[i].Real_wage = con->person[i].Base_wage + con->person[i].Allowance - con->person[i].Tax;       //职工实际工资
	}
}

void sort_worknumber(Table* con)                                             //对职工的顺序按工号自小到大排序
{
	for (int i = 0; i < con->Now_person; i++)                                                       
	{
		for (int j = i + 1; j < con->Now_person; j++)
		{
			if (con->person[j].Work_number < con->person[i].Work_number)
			{
				Work a = con->person[i];
				con->person[i] = con->person[j];
				con->person[j] = a;
			}
		}
	}
}

void printf_worktable(Table* con)                                           //输出明细工资表
{
	printf("%-10s\t%-10s\t%-12s\t%-12s\t%-12s\t%-12s\n", "工号", "姓名", "基础工资", "津贴", "税收", "实际工资");
	for (int i = 0; i < con->Now_person; i++)
	{
		printf("%-10d\t%-10s\t%-10.2f\t%-10.2f\t%-10.2f\t%-10.2f\n", con->person[i].Work_number,
			con->person[i].Name,
			con->person[i].Base_wage,
			con->person[i].Allowance,
			con->person[i].Tax,
			con->person[i].Real_wage);
	}
}

void sort_realwage(Table* con)    //函数3：实发工资从高到低排序
{
	for (int i = 0; i < con->Now_person; i++)             
	{
		for (int j = i + 1; j < con->Now_person; j++)
		{
			if (con->person[j].Real_wage > con->person[i].Real_wage)
			{
				Work a = con->person[i];
				con->person[i] = con->person[j];
				con->person[j] = a;
			}
		}
	}
}

void change_work(Table* con, int Work_number, double new_basewage, double new_allowance)   //函数4：修改职工的工作信息
{
	for (int i = 0; i < con->Now_person; i++)                                                    //遍历结构体
	{
		if (con->person[i].Work_number == Work_number)                                           //找到需修改的职工
		{
			con->person[i].Base_wage = new_basewage;                                             //修改基本工资
			con->person[i].Allowance = new_allowance;                                            //修改津贴
			if (con->person[i].Base_wage + con->person[i].Allowance < 3000)
			{
				con->person[i].Tax = 0;
			}
			else if (con->person[i].Base_wage + con->person[i].Allowance <= 4000)
			{
				con->person[i].Tax = (con->person[i].Base_wage + con->person[i].Allowance - 3000) * 0.05;
			}
			else

				con->person[i].Tax = (con->person[i].Base_wage + con->person[i].Allowance - 4000) * 0.1;              //修改后职工扣税金额

			con->person[i].Real_wage = con->person[i].Base_wage + con->person[i].Allowance - con->person[i].Tax;       //修改后职工实际工资
			break;
		}

	}

}

void printf_workimage(Table* con)
{
	printf("%-10s\t%-10s\t%-12s\t%-12s\n", "工号", "姓名", "基础工资", "津贴");
	for (int i = 0; i < con->Now_person; i++)
	{
		printf("%-10d\t%-10s\t%-10.2f\t%-10.2f\n", con->person[i].Work_number,
			con->person[i].Name,
			con->person[i].Base_wage,
			con->person[i].Allowance);
	}
}

int judge(int a, Table* con)
{
	for (int i = 0; i < con->Now_person; i++)
	{
		if (a == con->person[i].Work_number)
		{
			return 0;
		}
	}
	HWND hnd = GetHWnd();
	SetWindowText(hnd, L"退出");
	int isok = MessageBox(hnd, L"输入工号错误，无此工号！！！", L"提示", MB_OKCANCEL);
	return 1;
}


int seek_work(Table* con, int Work_number,int *i)    //函数5：查询职工工资信息
{
	for (* i = 0; *i < con->Now_person; *i+=1)                         //遍历结构体
	{
		if (con->person[*i].Work_number == Work_number)                //寻找查询的职工
		{
			return 0;
		}
	}
	HWND hnd = GetHWnd();
	SetWindowText(hnd, L"退出");
	int isok = MessageBox(hnd, L"输入错误，无此工号的职工！！！", L"提示", MB_OKCANCEL);
	return 1;
}

void printf_worknumber(Table* con)
{
	printf("%-10s\t%-10s\n", "工号", "姓名");
	for (int i = 0; i < con->Now_person; i++)
	{
		printf("%-10d\t%-10s\n", con->person[i].Work_number,
			con->person[i].Name);
	}
}

void analyze_work(Table* con, int a[], double b[])   //函数6：职工工资统计分析
{
	for (int i = 0; i < con->Now_person; i++)                              //遍历结构体
	{
		if (con->person[i].Real_wage < 3000)   a[0]++;                     //对实际工资小于3000的进行计数
		else if (con->person[i].Real_wage < 4000)    a[1]++;               //对实际工资大于3000并且小于4000的进行计数
		else     a[2]++;              //对实际工资大于4000的进行计数
	}
	b[0] = a[0] * 1.0 / con->Now_person * 100;                              //计数实际工资小于3000的比例
	b[1] = a[1] * 1.0 / con->Now_person * 100;                              //计算实际工资大于3000并且小于4000的比例
	b[2] = a[2] * 1.0 / con->Now_person * 100;                              //计算实际工资大于4000的比例
}