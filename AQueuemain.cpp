#include"AQueue.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char type;
char datatype[MAXQUEUE];
void screen()
{/*��ʾ�˵��ĺ���*/
	printf("******************************************************************\n");
	printf("*****************//please input a number//************************\n");
	printf("****************  1:����һ������           ***********************\n");
	printf("****************  2:��һ�����ݼ������     ***********************\n");
	printf("****************  3:�ж϶����Ƿ�Ϊ��       ***********************\n");
	printf("****************  4:�õ�����ͷԪ��         ***********************\n");
	printf("****************  5:�����г���           ***********************\n");
	printf("****************  6:��������               ***********************\n");
	printf("****************  7:��ն���               ***********************\n");
	printf("****************  8:���ٶ���               ***********************\n");
	printf("****************  9:��ǰn��Ԫ�س���        ***********************\n");
	printf("****************  10:��������              ***********************\n");
	printf("******************************************************************\n");
}

int main()
{
	int flag = 0, endflag = 1;/*�Ƿ���ڶ��еı�־flag���Ƿ����ִ�е�endflag*/
	int i, j;//�����˱���ij
	void* t = malloc(MAXQUEUE);//��������ʱ����t
	AQueue p;
	void(*vist)(void*);//���ʺ���
	vist = APrint;
	screen();//�����Ļ
	while (endflag)
	{
		scanf_s("%d", &i);
		switch (i)
		{
		case 1://��������
			if (flag)
				printf("�Ѿ�����һ��ջ��\n");
			else
			{
				InitAQueue(&p);
				flag = 1;
				printf("�����ɹ�\n");
			}
			break;
		case 2:
			if (!flag)
				printf("�����ڸö���\n");
			else
			{
				printf("��Ҫ���������������\n");
				int flag_2 = 1;
				while (flag_2)
				{//��ѯ���û��Ĵ洢����
					printf("1:������ 2������ 3���ַ� 4���ַ��� 5:��������:");
					scanf_s("%d", &j);
					switch (j)
					{/*�ռ���Ӧ�Ĵ洢����Ȼ�������*/
					case 1:float t0; scanf_s("%f", &t0);
						memcpy(t, &t0, MAXQUEUE);
						datatype[p.rear] = 'f';
						EnAQueue(&p, t); break;
					case 2:int t1; scanf_s("%d", &t1);
						memcpy(t, &t1, MAXQUEUE);
						datatype[p.rear] = 'd';
						EnAQueue(&p, t); break;
					case 3:char t2[1];
						scanf_s("%s", t2, 2);
						memcpy(t, t2, MAXQUEUE);
						datatype[p.rear] = 'c';
						EnAQueue(&p, t); break;
					case 4:char t3[MAXQUEUE]; scanf_s("%s", t3, 10);
						memcpy(t, t3, MAXQUEUE);
						datatype[p.rear] = 's';
						EnAQueue(&p, t); break;
					case 5:flag_2 = 0; break;
					default:printf("�����������������\n"); break;
					}
				}
			}break;
		case 3:
			if (!flag)/*�ж϶����Ƿ�Ϊ��*/
				printf("�����ڸö���\n");
			else
			{
				if (IsEmptyAQueue(&p))
					printf("�ն���\n");
				else
					printf("�ǿն���\n");
			}break;
		case 4:
			if (!flag)/*�õ�ͷ��㲢���*/
				printf("�����ڸö���\n");
			else
			{
				GetHeadAQueue(&p, t);
				type = datatype[p.front];/*�ȱ�ʾ��Ӧ�ĸ�ʽ*/
				APrint(t);
				printf("\n");
			}break;
		case 5:
			if (!flag)
				printf("�����ڸö���\n");
			else
				printf("���г�����%d\n", LengthAQueue(&p));
			break;
		case 6:
			if (!flag)
				printf("�����ڸö���\n");
			else
				if (!TraverseAQueue(&p, vist))
					printf("�ն���\n");
			break;
		case 7:
			if (!flag)
				printf("�����ڸö���\n");
			else
				ClearAQueue(&p);
			break;
		case 8:
			if (!flag)
				printf("�����ڸö���\n");
			else
			{
				DestoryAQueue(&p);
				flag = 0;
			}break;
		case 9:
			if (!flag)
				printf("�����ڸö���\n");
			else
			{
				printf("������ǰ����������:");
				scanf_s("%d", &j);/*ѯ���û�����ĸ���*/
				while (!IsEmptyAQueue(&p)&&j)
				{/*�߳��ӱߴ�ӡ*/
					type = datatype[p.front];
					DeAQueue(&p, t);
					APrint(t);
					j--;
				}
				printf("\n");
				if (j != 0)
					printf("û���㹻��Ԫ�س���\n");
			}break;
		case 10:endflag = 0; break;
		default:printf("�����������������\n"); break;
		}
	}
}
