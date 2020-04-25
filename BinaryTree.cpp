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
BiTNode* CreateBiTree(BiTree T, char* definition,int begin, int end)
{//ͨ���ҵ������������и���
	if (definition != NULL)
	{
		if (T == NULL)//���ȸ���ǰ�ڵ㸳��ռ�
			InitBiTree(&T);
		if (begin==end)
		{//�����Ҷ�ӽڵ��򷵻�
			T->data = definition[begin];
			return T;
		}
		/*c1����Ѱ��+-��λ�ã�c2����Ѱ��* /��λ�ã�p������¼�Ƿ��������ڣ���ʾ�������*/
		int c1, c2, p; 
		c1 = c2 = -1, p = 0; 
		for (int i = begin; i<=end; i++)
			switch (definition[i])
			{
			case '(':p++; break;//����������p�ͼ�һ
			case ')':p--; break;//�����ż�һ
			case '+'://ֻ�в����������ٶ�λ
			case'-':if (!p)c1 = i; break;
			case '*':
			case '/':if (!p)c2 = i; break;
			}
		if (c1 < 0)c1 = c2;/*���û��+-��* /�Ŷ���*/
		if (c1 < 0)/*���* /��Ҳû�����ж��������ڣ��ѿ�����*/ 
			return CreateBiTree(T, definition, begin + 1, end - 1);
		T->data = definition[c1]; //����ǰ��㸳ֵ
		T->lchild = CreateBiTree(T->lchild, definition, begin, c1 - 1); //����������ߵ���Ϊ������
		T->rchild= CreateBiTree(T->rchild, definition, c1 + 1, end );//�ұ���Ϊ������
		return T;
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
