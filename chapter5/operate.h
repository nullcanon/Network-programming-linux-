/*************************************************************************
	> File Name: operate.h
	> Author: jack
	> Mail: hansheng.jiayou@qq.com 
	> Created Time: 2018-03-21 12:34:40
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#define STACKMAX 100
#define STACKADD 10

/****************符号栈******************/
typedef struct StackChar
{
    char *base;
    char *top;
    int stacksize;
}SC;

void InitStackSC(SC *S);
void PushSC(SC *S,char e);
int StackEmptySC(SC* S);
void PopSC(SC *S,char *e);
char GetTopSC(SC *S);

/****************数字栈*******************/
typedef struct StackData
{
    double *base;
    double *top;
    int stacksize;
}SD;
void InitStackSD(SD *S);
int StackEmptySD(SD* S);
void PushSD(SD *S,double e);
void PopSD(SD *S,double *e);
double GetTopSD(SD *S);

/************计算函数******************/
char Precede(char x,char y);//判断操两个操作符优先度
double Operate(double a,char op,double b);//计算函数
int In(char c);//检查是否为符号,是返回1,否则返回0
double EvaluateExpression(char* ch);//主要逻辑

