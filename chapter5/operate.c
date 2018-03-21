/*************************************************************************
  > File Name: operate.c
  > Author: jack
  > Mail: hansheng.jiayou@qq.com 
  > Created Time: 2018-03-21 12:43:56
 ************************************************************************/

#include "operate.h"


/**********************************符号栈****************************/

void InitStackSC(SC *S)
{
    S->base = (char*)malloc(STACKMAX*sizeof(char));
    S->top = S->base;
    S->stacksize = STACKMAX;

}

void PushSC(SC *S,char e)
{
    if(S->top - S->base >= S->stacksize)
    {
        S->base = (char*)realloc(S->base,(S->stacksize+STACKADD)*sizeof(char));
        if(!S->base)
            return;
        S->top = S->base + S->stacksize;
        S->stacksize += STACKADD;

    }
    *S->top++ = e;

}
int StackEmptySC(SC* S)
{
    if(S->base == S->top)
        return 1;
    return 0;

}
void PopSC(SC *S,char *e)
{
    *e = *--S->top;

}

char GetTopSC(SC *S)
{
    if(StackEmptySC(S))
        return 0;
    return *(S->top-1);

}

/**************************************数字栈******************/
void InitStackSD(SD *S)
{
    S->base = (double*)malloc(STACKMAX*sizeof(double));
    S->top = S->base;
    S->stacksize = STACKMAX;

}
int StackEmptySD(SD* S)
{
    if(S->base == S->top)
        return 1;
    return 0;

}
void PushSD(SD *S,double e)
{
    if(S->top - S->base >= S->stacksize)
    {
        S->base = (double*)realloc(S->base,(S->stacksize+STACKADD)*sizeof(double));
        if(!S->base)
            return;
        S->top = S->base + S->stacksize;
        S->stacksize += STACKADD;

    }
    *S->top++ = e;

}

void PopSD(SD *S,double *e)
{
    *e = *--S->top;

}

double GetTopSD(SD *S)
{
    if(StackEmptySD(S))
        return 0;
    return *(S->top-1);

}

/*******************************************/

char Precede(char x,char y)//判断操两个操作符优先度
{
    int i,j;
    char ch[7] = {'+','-','*','/','(',')','\0'};
    char cmp[7][7] = {
        //+   -   *   /   (   )   \n
        {'>','>','<','<','<','>','>',},// +
        {'>','>','<','<','<','>','>',},// -
        {'>','>','>','>','<','>','>',},// *
        {'>','>','>','>','<','>','>',},// /
        {'<','<','<','<','<','=',' ',},// (
        {'>','>','>','>',' ','>','>',},// )
        {'<','<','<','<','<',' ','=',} //\n
    };

    for(i=0; i<7; i++)
    {
        if(ch[i] == x) break;

    }
    for(j=0; j<7; j++)
    {
        if(ch[j] == y) break;

    }
    return cmp[i][j];

}

double Operate(double a,char op,double b)//计算函数
{
    switch(op)
    {
    case'+':
        return a+b;
        break;
    case'-':
        return a-b;
        break;
    case'*':
        return a*b;
        break;
    case'/':
        return a/b;
        break;
    default:
        return 0;

    }

}

int In(char c)//检查是否为符号,是返回1,否则返回0
{
    if(c=='+' || c=='-' || c=='*' || c=='/' || c=='(' || c==')' || c=='\0')
        return 1;
    return 0;

}
double EvaluateExpression(char* ch)
{
    SC C;//运算符
    SD D;//操作数
    SD *OPND = &D;
    SC *OPTR = &C;
    double a,b;
    char c,oper,tmp;
    int i = 1;
    InitStackSC(OPTR);//运算符
    PushSC(OPTR,'\0');
    InitStackSD(OPND);//操作数
    c = ch[0]; 
    while(c!='\0' || GetTopSC(OPTR)!='\0')
    {
        if(!In(c))//不是运算符,进栈
        {
            c -= '0';//将字符转化为数字
            PushSD(OPND,c);
            c = ch[i++];

        }
        else
        {
            switch(Precede(GetTopSC(OPTR),c))
            {
            case'>'://栈顶元素优先权大,退栈并将运算结果入栈
                PopSC(OPTR,&oper);
                PopSD(OPND,&b);
                PopSD(OPND,&a);
                PushSD(OPND,Operate(a,oper,b));
                break;
            case'='://脱括号并且接受下一个字符
                PopSC(OPTR,&tmp);
                c = ch[i++];
                break;
            case'<'://入符号栈并接收下一个字符
                PushSC(OPTR,c);
                c = ch[i++];
                break;

            }

        }

    }
    return GetTopSD(OPND);

}
