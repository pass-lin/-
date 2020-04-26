#include"BinaryTree.h"
#include<stdlib.h>
#include<stdio.h>
int compute(int a, char b, int c)
{
    /*计算函数*/
	if (b == '/' && c == 0)//如果是除零特判
		return errornumber;
	switch (b)
	{
	case '+':return a + c; break;
	case '-':return a - c; break;
	case '/':return a / c; break;
	case '*':return a * c; break;
	}
}
Status InitBiTree(BiTree* T)
{
	if (T != NULL)
	{
		*T = (BiTNode*)malloc(sizeof(BiTNode));
		(*T)->lchild = (*T)->rchild = NULL;
		return SUCEESS;
	}
	return ERROR;	
}
//操作结果：构造空二叉树T
void DestroyBiTree(BiTree T)
{
	if (T != NULL)
	{/*后序遍历递归销毁*/
		DestroyBiTree(T->lchild);
		DestroyBiTree(T->rchild);
		free(T);
	}
}
//初始条件：二叉树T存在
//操作结果：摧毁二叉树T
int record;//用于定位当前的字符
BiTNode* CreateBiTree(BiTree T, char* definition)
{//通过找到最后运算符来切割树
	if (definition != NULL)
	{
		if (T == NULL)
			InitBiTree(&T);
		if (definition[record] >= '0' && definition[record] <= '9')
		{		//如果是数字则为叶子结点	
			T->data = definition[record];
			return T;
		}
		T->data = definition[record];
		record++;//其他分别计算左右子树
		T->lchild = CreateBiTree(T->lchild, definition);
		record++;
		T->rchild = CreateBiTree(T->rchild, definition);
		return	T;
	}
	
	return NULL;
	
}
//初始条件： definition给出二叉树的定义
//操作结果：按definition构造二叉树T


//以下部分函数定义未指定参数类型
Status PreOrderTraverse(BiTree T, void(*visit)(TElemType e))
{
	if (T != NULL)
	{
		visit(T->data);
		PreOrderTraverse(T->lchild, visit);
		PreOrderTraverse(T->rchild, visit);
		return SUCEESS;
	}
	return ERROR;
}
//初始条件：二叉树T存在，visit为对结点的操作的应用函数
//操作结果：先序遍历T，对每个结点调用visit函数一次且仅一次，一旦visit失败，则操作失败
Status InOrderTraverse(BiTree T, void(*visit)(TElemType e))
{//非递归
	if (T!=NULL)
	{//先建立一个栈
		BiTree statck[30];
		int  front = 0;
		BiTree p = T;
		/*在外部先进行一次操作*/
		statck[front] = p;
		front++;
		p = p->lchild;
		while (front != 0)
		{
			while (p)
			{//一直向左边入栈，直到p为空
				statck[front] = p;
				front++;
				p = p->lchild;				
			}
			if (front!=0)
			{//只要栈不空，那就出栈并向右子树前进
				p = statck[--front];
				visit(p->data);
				p = p->rchild;
				if (p)
				{
					//先进行右子树的第一次入栈操作
					statck[front] = p;
					front++;
					p = p->lchild;
				}

			}
		}
	}
	return ERROR;
}//中序遍历
Status PostOrderTraverse(BiTree T, void(*visit)(TElemType e))
{
	if (T != NULL)
	{
		
		PostOrderTraverse(T->lchild, visit);
		PostOrderTraverse(T->rchild, visit);
		visit(T->data);
		return SUCEESS;
	}
	return ERROR;
}//后序遍历
Status LevelOrderTraverse(BiTree T, void(*visit)(TElemType e))
{
	if (T)
	{
		BiTree quene[30];//定义一个队列
		int rear, front;//队头和队尾指针
		rear = 0, front = 1;//初始化
		quene[front] = T;
		while (rear != front)
		{
			BiTree temp = quene[front];
			front = (front - 1 + 30) % 30;
			/*只要 当前结点的左右子树不为零，将他们入队*/
			if (temp->lchild != NULL)
			{
				quene[rear] = temp->lchild;
				rear = (rear - 1 + 30) % 30;
			}
			if (temp->rchild != NULL)
			{
				quene[rear] = temp->rchild;
				rear = (rear - 1 + 30) % 30;
			}
			/*访问当前结点*/
			visit(temp->data);
		}
		return SUCEESS;
	}
	return ERROR;
}//层序遍历
Status isleaf(BiTree p)
{
	if (p->lchild == NULL && p->rchild == NULL)
		return SUCEESS;
	return ERROR;
}
int Value(BiTree T)
{
	if (isleaf(T))
		return atoi(&T->data);//如果是叶子节点返回当前的数
	int left = Value(T->lchild);/*分别计算左右子树的值*/
	int right = Value(T->rchild);
	if (left == errornumber || right == errornumber)
		return errornumber;/*如果出现1/0接下来全是1/0的错误数*/
	return compute(left, T->data, right);/*利用左右的数计算当前的值*/
}//构造出的二叉树求值
/*
提示：可在结点结构体中设置个Tag值标志数字与操作符来构造二叉树，
可根据需要自行增加操作.
*/
