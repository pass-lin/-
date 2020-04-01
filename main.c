#include<stdio.h>
#include "../head/linkedList.h"
#include<stdlib.h>
void visit(ElemType e)
{
	printf("-->%d", e);
}
int LN(char c)/*判断是否是符号*/
{
	if (c >= '0' && c <= '9')/*打印函数*/
		return 1;
	else return 0;
}
void screen()
{/*显示菜单的函数*/
	printf("******************************************************************\n");
	printf("*****************//please input a number//************************\n");
	printf("****************  1:input a new list       ***********************\n");
	printf("****************  2:delete the first node after a number *********\n");
	printf("****************  3:destory the list       ***********************\n");
	printf("****************  4:insert   number        ***********************\n");
	printf("****************  5:print the list         ***********************\n");
	printf("****************  6:reverse the list       ***********************\n");
	printf("****************  7:ReverseEvenList        ***********************\n");
	printf("****************  8:FindMidNode            ***********************\n");
	printf("****************  9:search a number        ***********************\n");
	printf("****************  10:end the software      ***********************\n");
	printf("******************************************************************\n");
}
int main()
{
	int flag = 0,endflag=1,j,i;/*临时变量j，i。判断链表是否存在的flag，和是否结束程序的endflag*/
	LinkedList p = NULL;/*定义并初始化列表图*/
	void(* g)(ElemType) = visit;/*访问函数的指针*/
	screen();/*展示菜单*/
	while (endflag)
	{
		scanf_s("%d", &j);/*输入选项*/
		switch (j)
		{
		case 1:
			if (flag)/*先判断链表是否存在*/
				printf("A linked list already exists\n");
			else
			{
				InitList(&p);
				flag = 1;
			}
			break;
		case 2:/*删除一个数后那个结点的函数*/
			if(!flag)
				printf("no list\n");
			else
			{
				printf("please in put the number:");
				scanf_s("%d", &i);
				if (SearchList(p, i)&&p)/*先判断那个数在不在*/
				{
					LinkedList m = p;
					while (m->data != i)
						m = m->next;/*然后找到那个数*/
					if (DeleteList(p, &i))/*输出当前情况*/
						printf("successfully delet it\n");
					else
						printf("unsuccessfully delet it\n");
				}
				else
					printf("no the number\n");
			}
			break;
		case 3:
			if (!flag)
				printf("no list\n");
			else
			{/*销毁链表*/
				DestroyList(p);
				flag = 0;
			}
			break;
		case 4:
			if (!flag)
				printf("no list\n");
			else
			{
				printf("intput exsample:3 2 5 6#\n");/*输出使用例*/
				printf("equal exsample:3a2c5e6#\n");
				printf("equal exsample:3,2,5,6#\n");
				printf("#as end\n");
				printf("please input the number(number is less than 10^9):");
				char ch;
				ch = getchar();/*得到屏幕上第一个字符串*/
				int n;
				while (1)
				{
					if (LN(ch))/*判断是否为数字字符*/
					{
						int k = 0;;
						char a[10] = { 0 };/*用于存储多位数字*/
						for (k = 0; LN(ch)&&k<9; k++)/*处理大于一位的字符*/
						{
							a[k] = ch;/*如果接收的数字是字符存入数组*/
							ch = getchar();
						}
						if (k < 9)
						{
							a[k] = '\0';/*添加结束字符*/
							n = atoi(a);/*将字符串变成整数*/
							LinkedList m;/*生成新节点并插入*/
							m = (LNode*)malloc(sizeof(LNode));
							m->data = n, m->next = NULL;
							InsertList(p, m);
						}
						else
							printf("input number is too large\n");
					}
					if (ch == '#')break;/*没到#号就继续*/
					ch = getchar();
				}
			}
			break;
		case 5:
			if (!flag)
				printf("no list\n");
			else
				TraverseList(p->next, g);/*启动遍历函数*/
			printf("\n");
			break;
		case 6:
			if (!flag)/*先判断是否有链表再进行运算*/
				printf("no list\n");
			else
				if (!ReverseList(&p))
					printf("error\n");
			break;
		case 7:/*同上*/
			if (!flag)
				printf("no list\n");
			else
				p->next = ReverseEvenList(p->next);
			break;
		case 8:
			if (!flag)
				printf("no list\n");
			else/*找到中间的结点并且输出值*/
			{
				LNode *e = FindMidNode(&p);
				printf("the number  is %d\n", e->data);
			}
			break;
		case 9:
			if (!flag)
				printf("no list\n");
			else/*找到该数字然后判断该数字是否存在*/
			{
				printf("please in put the number:");
				scanf_s("%d", &i);
				if (SearchList(p, i))
					printf("the number is exit\n");
				else
					printf("no the number\n");
			}
			break;
		case 10:/*结束*/
			endflag = 0;
			system("pause");
			break;
		default:
			printf("intput a false number\n");
			break;
		}
	}
}