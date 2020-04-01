#include<stdio.h>
#include "../head/duLinkedList.h"
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
	printf("********************************************************************************\n");
	printf("*****************//please input a number//**************************************\n");
	printf("****************  1:input a new list                       *********************\n");
	printf("****************  2:destory the list                       *********************\n");
	printf("****************  3:insert number a group number           *********************\n");
	printf("****************  4:insert number a before number b        *********************\n");
	printf("****************  5:insert number a after number b         *********************\n");
	printf("****************  6:delete the first node after the node p *********************\n");
	printf("****************  7:print the list                         *********************\n");
	printf("****************  8:end the software                       *********************\n");
	printf("********************************************************************************\n");
}
int main()
{
	int flag = 0, endflag = 1, j, i;/*临时变量j，i。判断链表是否存在的flag，和是否结束程序的endflag*/
	DuLinkedList p = NULL;/*定义并初始化列表图*/
	void(*g)(ElemType) = visit;/*访问函数的指针*/
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
				InitList_DuL(&p);
				flag = 1;
			}
			break;
		case 2:
			if (!flag)
				printf("no list\n");
			else
			{/*销毁链表*/
				DestroyList(p);
				flag = 0;
			}
			break;
		case 3:
			if (!flag)
				printf("no list\n");
			else
			{
				printf("intput exsample:3 2 5 6#\n");/*输出使用例*/
				printf("equal exsample:3a2c5e6#\n");
				printf("equal exsample:3,2,5,6#\n");
				printf("#as end\n");
				printf("please input the number:");
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
							DuLinkedList m;/*生成新节点并插入*/
							m = (DuLNode*)malloc(sizeof(DuLNode));
							m->data = n, m->next = NULL;
							InsertAfterList_DuL(p, m);
						}
						else
							printf("input number is too large\n");
					
					}
					if (ch == '#')break;/*没到#号就继续*/
					ch = getchar();
				}
			}
			break;
		case 4:
			if (!flag)
				printf("no list\n");
			else
			{
				printf("please in put the number b:");
				scanf_s("%d", &i);
				DuLinkedList m = p;
				while (m->data != i && m != NULL)
					m = m->next;/*然后找到那个数*/
				if (m == NULL)/*输出当前情况*/
					printf("no the number\n");
				else
				{
					printf("please in put the number a:");
					scanf_s("%d", &i);
					DuLinkedList n;/*生成新节点并插入*/
					n = (DuLNode*)malloc(sizeof(DuLNode));
					n->data = i, n->next = NULL;
					InsertBeforeList_DuL(m, n);
				}
			}
			break;
		case 5:
			if (!flag)
				printf("no list\n");
			else
			{
				printf("please in put the number b:");
				scanf_s("%d", &i);
				DuLinkedList m = p;
				while (m->data != i && m != NULL)
					m = m->next;/*然后找到那个数*/
				if (m == NULL)/*输出当前情况*/
					printf("no the number\n");
				else
				{
					printf("please in put the number a:");
					scanf_s("%d", &i);
					DuLinkedList n;/*生成新节点并插入*/
					n = (DuLNode*)malloc(sizeof(DuLNode));
					n->data = i, n->next = NULL;
					InsertAfterList_DuL(m, n);
				}
			}
			break;
		case 6:
			if (!flag)
				printf("no list\n");
			else
			{
				printf("please in put the number b:");
				scanf_s("%d", &i);
				DuLinkedList m = p;
				while (m->data != i && m != NULL)
					m = m->next;/*然后找到那个数*/
				if (m == NULL)/*输出当前情况*/
					printf("no the number\n");
				else
				{
					ElemType e = 0;/*找到数则删除并输出*/
					DeleteList_DuL(m, &e);
					printf("deleted number is %d\n", e);
				}
			}
			break;
		case 7:
			if (!flag)
				printf("no list\n");
			else
				TraverseList_DuL(p->next, g);/*启动遍历函数*/
			printf("\n");
			break;
		case 8:
			endflag = 0;
			system("pause");
			break;
		default:
			printf("intput a false number\n");
			break;
		}
	}
}