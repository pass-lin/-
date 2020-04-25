#include"BinaryTree.h"
#include<stdlib.h>
#include<stdio.h>
#include<string>
void visit(TElemType e)
{
	printf("%c", e); 
}
int main()
{
	void(* a)(TElemType e);
	a= visit;
    char s[30];
	printf("输入例:1+1\n");
	while (1)
	{
		BiTree p;
		InitBiTree(&p);
		printf("请输入计算式:");
		scanf_s("%s", s, 30);
		CreateBiTree(p, s, 0, strlen(s) - 1);
		printf("前缀表达式为:\n");
		PreOrderTraverse(p, a);
		printf("\n");
		printf("中缀表达式为:\n");
		InOrderTraverse(p, a);
		printf("\n");
		printf("后缀表达式为:\n");
		PostOrderTraverse(p, a);
		printf("\n");
		printf("层序表达式为:\n");
		LevelOrderTraverse(p, a);
		printf("\n");
		int m = Value(p);
		if (m != errornumber)
		{
			printf("计算结果%s=", s);
			printf("%d\n", m);
		}
		else
		{
			printf("计算结果%s=", s);
			printf("inf\n");
		}
		DestroyBiTree(p);
	}
}