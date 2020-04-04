#include<stdio.h>
#include<stdlib.h>
#include"SqStack.h"
//���������˳��ջ
Status initStack(SqStack* s, int sizes)//��ʼ��ջ
{
	if (s) {
		s->elem = (ElemType*)malloc(sizes * sizeof(ElemType));
		s->size = sizes;
		s->top = 0;
	}
	else return SUCCESS;
}
Status isEmptyStack(SqStack* s)//�ж�ջ�Ƿ�Ϊ��
{
	if (s)
		if (s->top == 0)
			return SUCCESS;
		else return ERROR;
	else
	{
		printf("����Ϊ��\n");
		return ERROR;
	}
}
Status getTopStack(SqStack* s, ElemType* e) //�õ�ջ��Ԫ��
{
	if (s)
	{
		if (isEmptyStack(s))
			return ERROR;
		*e = s->elem[s->top - 1];
		return SUCCESS;
	}
	else return ERROR;
}
Status clearStack(SqStack* s)//���ջ
{
	if (s)
	{/*�ı�ͷ���*/
		s->top = 0;
		return SUCCESS;
	}
	else return ERROR;
}
Status destroyStack(SqStack* s)//����ջ
{
	if (s)
	{/*��������ͷ�*/
		s->top = 0;
		s->size = 0;
		free(s->elem);
		return SUCCESS;
	}
	else return ERROR;
}
Status stackLength(SqStack* s, int* length)//���ջ����
{
	if (s)
	{
		*length = s->top;
		return SUCCESS;
	}
	else return ERROR;
}
Status pushStack(SqStack* s, ElemType data)//��ջ
{
	if (s)
	{
		if (s->top == s->size)
		{/*�ȼ���Ƿ�������ջ�����Ų��Ҹ��³߶�*/
			s->elem= (ElemType*)realloc(s->elem, (s->size + ADDSIZE) * sizeof(ElemType));
			s->size = s->size + ADDSIZE;
		}
		s->elem[s->top] = data;
		s->top++;
		return SUCCESS;
	}
	else return ERROR;
}
Status popStack(SqStack* s, ElemType* data)//��ջ
{
	if (s)
	{/*����ǿ�ջֱ�ӷ���*/
		if (isEmptyStack(s))
			return ERROR;
		s->top--;
		*data = s->elem[s->top];
		return SUCCESS;
	}
	else return ERROR;
}