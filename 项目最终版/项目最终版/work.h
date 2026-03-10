#pragma once
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "easyx.h"

#ifndef __WORK__H
#define __WORK__H
typedef struct
{
	int Work_number;      //工号
	TCHAR Name[50];      //姓名
	double  Base_wage;       //基本工资
	double  Allowance;       //津贴
	double  Tax;             //扣税
	double  Real_wage;       //实际工资
}Work;

typedef struct
{
	Work person[500];      //工资表
	int Now_person;        //当前人数
}Table;

bool change_T();                    //启示判断
void InitTable(Table* con);
void write_text(Table* con);        //将数据写入文件
void read_text(Table* con);         //从文件里读取数据

void set_work(Table* con);//函数1：建立工资表
int Judge(int a, Table* con);

void define_tax(Table* con);     //函数2：确定职工扣税和实际工资

void sort_worknumber(Table* con);                                             //对职工的顺序按工号自小到大排序

void printf_worktable(Table* con);                                           //输出明细工资表

void sort_realwage(Table* con);    //函数3：实发工资从高到低排序

void change_work(Table* con, int Work_number, double new_basewage, double new_allowance);   //函数4：修改职工的工作信息
void printf_workimage(Table* con);
int judge(int a, Table* con);

int seek_work(Table* con, int Work_number,int*i);    //函数5：查询职工工资信息
void printf_worknumber(Table* con);

void analyze_work(Table* con, int a[], double b[]);   //函数6：职工工资统计分析


#endif