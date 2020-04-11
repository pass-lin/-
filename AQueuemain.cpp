#include"AQueue.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char type;
char datatype[MAXQUEUE];
void screen()
{/*显示菜单的函数*/
	printf("******************************************************************\n");
	printf("*****************//please input a number//************************\n");
	printf("****************  1:创建一个队列           ***********************\n");
	printf("****************  2:将一个数据加入队列     ***********************\n");
	printf("****************  3:判断队列是否为空       ***********************\n");
	printf("****************  4:得到队列头元素         ***********************\n");
	printf("****************  5:检测队列长度           ***********************\n");
	printf("****************  6:遍历队列               ***********************\n");
	printf("****************  7:清空队列               ***********************\n");
	printf("****************  8:销毁队列               ***********************\n");
	printf("****************  9:将前n个元素出队        ***********************\n");
	printf("****************  10:结束程序              ***********************\n");
	printf("******************************************************************\n");
}

int main()
{
	int flag = 0, endflag = 1;/*是否存在队列的标志flag和是否继续执行的endflag*/
	int i, j;//工具人变量ij
	void* t = malloc(MAXQUEUE);//工具人临时变量t
	AQueue p;
	void(*vist)(void*);//访问函数
	vist = APrint;
	screen();//输出屏幕
	while (endflag)
	{
		scanf_s("%d", &i);
		switch (i)
		{
		case 1://创建队列
			if (flag)
				printf("已经存在一个栈了\n");
			else
			{
				InitAQueue(&p);
				flag = 1;
				printf("创建成功\n");
			}
			break;
		case 2:
			if (!flag)
				printf("不存在该队列\n");
			else
			{
				printf("你要输入的数据类型是\n");
				int flag_2 = 1;
				while (flag_2)
				{//先询问用户的存储类型
					printf("1:浮点型 2：整形 3：字符 4：字符串 5:结束输入:");
					scanf_s("%d", &j);
					switch (j)
					{/*收集对应的存储类型然后将其入队*/
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
					default:printf("输入错误请重新输入\n"); break;
					}
				}
			}break;
		case 3:
			if (!flag)/*判断队列是否为空*/
				printf("不存在该队列\n");
			else
			{
				if (IsEmptyAQueue(&p))
					printf("空队列\n");
				else
					printf("非空队列\n");
			}break;
		case 4:
			if (!flag)/*得到头结点并输出*/
				printf("不存在该队列\n");
			else
			{
				GetHeadAQueue(&p, t);
				type = datatype[p.front];/*先表示对应的格式*/
				APrint(t);
				printf("\n");
			}break;
		case 5:
			if (!flag)
				printf("不存在该队列\n");
			else
				printf("队列长度是%d\n", LengthAQueue(&p));
			break;
		case 6:
			if (!flag)
				printf("不存在该队列\n");
			else
				if (!TraverseAQueue(&p, vist))
					printf("空队列\n");
			break;
		case 7:
			if (!flag)
				printf("不存在该队列\n");
			else
				ClearAQueue(&p);
			break;
		case 8:
			if (!flag)
				printf("不存在该队列\n");
			else
			{
				DestoryAQueue(&p);
				flag = 0;
			}break;
		case 9:
			if (!flag)
				printf("不存在该队列\n");
			else
			{
				printf("你想让前几个数出队:");
				scanf_s("%d", &j);/*询问用户输出的个数*/
				while (!IsEmptyAQueue(&p)&&j)
				{/*边出队边打印*/
					type = datatype[p.front];
					DeAQueue(&p, t);
					APrint(t);
					j--;
				}
				printf("\n");
				if (j != 0)
					printf("没有足够的元素出队\n");
			}break;
		case 10:endflag = 0; break;
		default:printf("输入错误请重新输入\n"); break;
		}
	}
}
