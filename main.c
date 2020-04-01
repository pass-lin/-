#include<stdio.h>
#include "../head/linkedList.h"
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
	int flag = 0,endflag=1,j,i;/*��ʱ����j��i���ж������Ƿ���ڵ�flag�����Ƿ���������endflag*/
	LinkedList p = NULL;/*���岢��ʼ���б�ͼ*/
	void(* g)(ElemType) = visit;/*���ʺ�����ָ��*/
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
				InitList(&p);
				flag = 1;
			}
			break;
		case 2:/*ɾ��һ�������Ǹ����ĺ���*/
			if(!flag)
				printf("no list\n");
			else
			{
				printf("please in put the number:");
				scanf_s("%d", &i);
				if (SearchList(p, i)&&p)/*���ж��Ǹ����ڲ���*/
				{
					LinkedList m = p;
					while (m->data != i)
						m = m->next;/*Ȼ���ҵ��Ǹ���*/
					if (DeleteList(p, &i))/*�����ǰ���*/
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
			{/*��������*/
				DestroyList(p);
				flag = 0;
			}
			break;
		case 4:
			if (!flag)
				printf("no list\n");
			else
			{
				printf("intput exsample:3 2 5 6#\n");/*���ʹ����*/
				printf("equal exsample:3a2c5e6#\n");
				printf("equal exsample:3,2,5,6#\n");
				printf("#as end\n");
				printf("please input the number(number is less than 10^9):");
				char ch;
				ch = getchar();/*�õ���Ļ�ϵ�һ���ַ���*/
				int n;
				while (1)
				{
					if (LN(ch))/*�ж��Ƿ�Ϊ�����ַ�*/
					{
						int k = 0;;
						char a[10] = { 0 };/*���ڴ洢��λ����*/
						for (k = 0; LN(ch)&&k<9; k++)/*�������һλ���ַ�*/
						{
							a[k] = ch;/*������յ��������ַ���������*/
							ch = getchar();
						}
						if (k < 9)
						{
							a[k] = '\0';/*��ӽ����ַ�*/
							n = atoi(a);/*���ַ����������*/
							LinkedList m;/*�����½ڵ㲢����*/
							m = (LNode*)malloc(sizeof(LNode));
							m->data = n, m->next = NULL;
							InsertList(p, m);
						}
						else
							printf("input number is too large\n");
					}
					if (ch == '#')break;/*û��#�žͼ���*/
					ch = getchar();
				}
			}
			break;
		case 5:
			if (!flag)
				printf("no list\n");
			else
				TraverseList(p->next, g);/*������������*/
			printf("\n");
			break;
		case 6:
			if (!flag)/*���ж��Ƿ��������ٽ�������*/
				printf("no list\n");
			else
				if (!ReverseList(&p))
					printf("error\n");
			break;
		case 7:/*ͬ��*/
			if (!flag)
				printf("no list\n");
			else
				p->next = ReverseEvenList(p->next);
			break;
		case 8:
			if (!flag)
				printf("no list\n");
			else/*�ҵ��м�Ľ�㲢�����ֵ*/
			{
				LNode *e = FindMidNode(&p);
				printf("the number  is %d\n", e->data);
			}
			break;
		case 9:
			if (!flag)
				printf("no list\n");
			else/*�ҵ�������Ȼ���жϸ������Ƿ����*/
			{
				printf("please in put the number:");
				scanf_s("%d", &i);
				if (SearchList(p, i))
					printf("the number is exit\n");
				else
					printf("no the number\n");
			}
			break;
		case 10:/*����*/
			endflag = 0;
			system("pause");
			break;
		default:
			printf("intput a false number\n");
			break;
		}
	}
}