#include<stdio.h>
#include<stdlib.h>
#include"LinkStack.h"
void screen()
{/*显示菜单的函数*/
	printf("******************************************************************\n");
	printf("*****************//please input a number//************************\n");
	printf("****************  1:创建一个栈             ***********************\n");
	printf("****************  2:将一组数入栈           ***********************\n");
	printf("****************  3:判断栈是否为空         ***********************\n");
	printf("****************  4:得到栈顶元素           ***********************\n");
	printf("****************  5:检测栈长度             ***********************\n");
	printf("****************  6:将前n个数出栈          ***********************\n");
	printf("****************  7:清空栈                 ***********************\n");
	printf("****************  8:销毁栈                 ***********************\n");
	printf("****************  9:结束程序               ***********************\n");
	printf("******************************************************************\n");
}
int LN(char c)/*判断是否是符号*/
{
	if (c >= '0' && c <= '9')
		return 1;
	else return 0;
}
int main()
{
	int flag = 0, endflag = 1, j, i;/*临时变量j，i。判断链表是否存在的flag，和是否结束程序的endflag*/
	LinkStack *p=NULL;/*定义并初始化列表图*/
	screen();/*展示菜单*/
	while (endflag)
	{
		scanf_s("%d", &j);/*输入选项*/
		switch (j)
		{
		case 1:
			if (flag)
				printf("已经存在一个栈了\n");
			else
			{
				initLStack(&p);
				flag = 1;
				printf("创建成功\n");
			}
			break;
		case 2:
			if (!flag)
				printf("no list\n");
			else
			{
				printf("输入例:3 2 5 6#\n");/*输出使用例*/
				printf("输入例:3a2c5e6#\n");
				printf("输入例:3,2,5,6#\n");
				printf("#作为结尾\n");
				printf("请输入数据(数应小于 10^9):");
				char ch;
				ch = getchar();/*得到屏幕上第一个字符串*/
				int n;
				while (1)
				{
					if (LN(ch))/*判断是否为数字字符*/
					{
						int k = 0;;
						char a[10] = { 0 };/*用于存储多位数字*/
						for (k = 0; LN(ch) && k < 9; k++)/*处理大于一位的字符*/
						{
							a[k] = ch;/*如果接收的数字是字符存入数组*/
							ch = getchar();
						}
						if (k < 9)
						{
							a[k] = '\0';/*添加结束字符*/
							n = atoi(a);/*将字符串变成整数*/
							pushLStack(p, n);
						}
						else
							printf("输入的数据太大了\n");
					}
					if (ch == '#')break;/*没到#号就继续*/
					ch = getchar();
				}
			}
			break;
		case 3:
			if (!flag)
				printf("no list\n");
			else
			{
				if (isEmptyLStack(p))
					printf("空\n");
				else
					printf("不空\n");
			}
			break;
		case 4:
			if (!flag)
				printf("no list\n");
			else
			{
				ElemType e;
				getTopLStack(p, &e);
				printf("栈顶元素是%d\n", e);
			}
			break;
		case 5:
			if (!flag)
				printf("no list\n");
			else
			{
				int e;
				LStackLength(p, &e);
				printf("长度是%d\n", e);
			}
			break;
		case 6:
			if (!flag)
				printf("no list\n");
			else
			{
				printf("要出栈的个数:");
				scanf_s("%d", &i);
				while (i && !isEmptyLStack(p))
				{
					ElemType e;
					popLStack(p, &e);
					printf("-->%d", e);
					i--;
				}
				printf("\n");
				if (i)
					printf("栈中元素不足\n");
			}
			break;
		case 7:
			if (!flag)
				printf("no list\n");
			else
				clearLStack(p);
			break;
		case 8:
			if (!flag)
				printf("no list\n");
			else
			{
				destroyLStack(p);
				flag = 0;
			}
			break;
		case 9:
			endflag = 0;
			break;
		default:
			printf("输入错误，请重新输入\n");
			break;
		}
	}
}
