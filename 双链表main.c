#include<stdio.h>
#include "../head/duLinkedList.h"
#include<stdlib.h>
void visit(ElemType e)
{
	printf("-->%d", e);
}
int LN(char c)/*�ж��Ƿ��Ƿ���*/
{
	if (c >= '0' && c <= '9')/*��ӡ����*/
		return 1;
	else return 0;
}
void screen()
{/*��ʾ�˵��ĺ���*/
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
	int flag = 0, endflag = 1, j, i;/*��ʱ����j��i���ж������Ƿ���ڵ�flag�����Ƿ���������endflag*/
	DuLinkedList p = NULL;/*���岢��ʼ���б�ͼ*/
	void(*g)(ElemType) = visit;/*���ʺ�����ָ��*/
	screen();/*չʾ�˵�*/
	while (endflag)
	{
		scanf_s("%d", &j);/*����ѡ��*/
		switch (j)
		{
		case 1:
			if (flag)/*���ж������Ƿ����*/
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
			{/*��������*/
				DestroyList(p);
				flag = 0;
			}
			break;
		case 3:
			if (!flag)
				printf("no list\n");
			else
			{
				printf("intput exsample:3 2 5 6#\n");/*���ʹ����*/
				printf("equal exsample:3a2c5e6#\n");
				printf("equal exsample:3,2,5,6#\n");
				printf("#as end\n");
				printf("please input the number:");
				char ch;
				ch = getchar();/*�õ���Ļ�ϵ�һ���ַ���*/
				int n;
				while (1)
				{
					if (LN(ch))/*�ж��Ƿ�Ϊ�����ַ�*/
					{
						int k = 0;;
						char a[10] = { 0 };/*���ڴ洢��λ����*/
						for (k = 0; LN(ch) && k < 9; k++)/*�������һλ���ַ�*/
						{
							a[k] = ch;/*������յ��������ַ���������*/
							ch = getchar();
						}
						if (k < 9)
						{
							a[k] = '\0';/*��ӽ����ַ�*/
							n = atoi(a);/*���ַ����������*/
							DuLinkedList m;/*�����½ڵ㲢����*/
							m = (DuLNode*)malloc(sizeof(DuLNode));
							m->data = n, m->next = NULL;
							InsertAfterList_DuL(p, m);
						}
						else
							printf("input number is too large\n");
					
					}
					if (ch == '#')break;/*û��#�žͼ���*/
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
					m = m->next;/*Ȼ���ҵ��Ǹ���*/
				if (m == NULL)/*�����ǰ���*/
					printf("no the number\n");
				else
				{
					printf("please in put the number a:");
					scanf_s("%d", &i);
					DuLinkedList n;/*�����½ڵ㲢����*/
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
					m = m->next;/*Ȼ���ҵ��Ǹ���*/
				if (m == NULL)/*�����ǰ���*/
					printf("no the number\n");
				else
				{
					printf("please in put the number a:");
					scanf_s("%d", &i);
					DuLinkedList n;/*�����½ڵ㲢����*/
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
					m = m->next;/*Ȼ���ҵ��Ǹ���*/
				if (m == NULL)/*�����ǰ���*/
					printf("no the number\n");
				else
				{
					ElemType e = 0;/*�ҵ�����ɾ�������*/
					DeleteList_DuL(m, &e);
					printf("deleted number is %d\n", e);
				}
			}
			break;
		case 7:
			if (!flag)
				printf("no list\n");
			else
				TraverseList_DuL(p->next, g);/*������������*/
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