#include"BinaryTree.h"
#include<stdlib.h>
#include<stdio.h>
int compute(int a, char b, int c)
{
    /*���㺯��*/
	if (b == '/' && c == 0)//����ǳ�������
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
//�������������ն�����T
void DestroyBiTree(BiTree T)
{
	if (T != NULL)
	{/*��������ݹ�����*/
		DestroyBiTree(T->lchild);
		DestroyBiTree(T->rchild);
		free(T);
	}
}
//��ʼ������������T����
//����������ݻٶ�����T
int record;//���ڶ�λ��ǰ���ַ�
BiTNode* CreateBiTree(BiTree T, char* definition)
{//ͨ���ҵ������������и���
	if (definition != NULL)
	{
		if (T == NULL)
			InitBiTree(&T);
		if (definition[record] >= '0' && definition[record] <= '9')
		{		//�����������ΪҶ�ӽ��	
			T->data = definition[record];
			return T;
		}
		T->data = definition[record];
		record++;//�����ֱ������������
		T->lchild = CreateBiTree(T->lchild, definition);
		record++;
		T->rchild = CreateBiTree(T->rchild, definition);
		return	T;
	}
	
	return NULL;
	
}
//��ʼ������ definition�����������Ķ���
//�����������definition���������T


//���²��ֺ�������δָ����������
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
//��ʼ������������T���ڣ�visitΪ�Խ��Ĳ�����Ӧ�ú���
//����������������T����ÿ��������visit����һ���ҽ�һ�Σ�һ��visitʧ�ܣ������ʧ��
Status InOrderTraverse(BiTree T, void(*visit)(TElemType e))
{//�ǵݹ�
	if (T!=NULL)
	{//�Ƚ���һ��ջ
		BiTree statck[30];
		int  front = 0;
		BiTree p = T;
		/*���ⲿ�Ƚ���һ�β���*/
		statck[front] = p;
		front++;
		p = p->lchild;
		while (front != 0)
		{
			while (p)
			{//һֱ�������ջ��ֱ��pΪ��
				statck[front] = p;
				front++;
				p = p->lchild;				
			}
			if (front!=0)
			{//ֻҪջ���գ��Ǿͳ�ջ����������ǰ��
				p = statck[--front];
				visit(p->data);
				p = p->rchild;
				if (p)
				{
					//�Ƚ����������ĵ�һ����ջ����
					statck[front] = p;
					front++;
					p = p->lchild;
				}

			}
		}
	}
	return ERROR;
}//�������
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
}//�������
Status LevelOrderTraverse(BiTree T, void(*visit)(TElemType e))
{
	if (T)
	{
		BiTree quene[30];//����һ������
		int rear, front;//��ͷ�Ͷ�βָ��
		rear = 0, front = 1;//��ʼ��
		quene[front] = T;
		while (rear != front)
		{
			BiTree temp = quene[front];
			front = (front - 1 + 30) % 30;
			/*ֻҪ ��ǰ��������������Ϊ�㣬���������*/
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
			/*���ʵ�ǰ���*/
			visit(temp->data);
		}
		return SUCEESS;
	}
	return ERROR;
}//�������
Status isleaf(BiTree p)
{
	if (p->lchild == NULL && p->rchild == NULL)
		return SUCEESS;
	return ERROR;
}
int Value(BiTree T)
{
	if (isleaf(T))
		return atoi(&T->data);//�����Ҷ�ӽڵ㷵�ص�ǰ����
	int left = Value(T->lchild);/*�ֱ��������������ֵ*/
	int right = Value(T->rchild);
	if (left == errornumber || right == errornumber)
		return errornumber;/*�������1/0������ȫ��1/0�Ĵ�����*/
	return compute(left, T->data, right);/*�������ҵ������㵱ǰ��ֵ*/
}//������Ķ�������ֵ
/*
��ʾ�����ڽ��ṹ�������ø�Tagֵ��־������������������������
�ɸ�����Ҫ�������Ӳ���.
*/
