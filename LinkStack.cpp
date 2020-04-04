#include<stdio.h>
#include<stdlib.h>
#include"LinkStack.h"
//��ջ
Status initLStack(LinkStack** s)//��ʼ��ջ
{
	if (s)
	{
		*s = (LinkStack*)malloc(sizeof(LinkStack));
		(*s)->count = 0;
		(*s)->top = NULL;
		return SUCCESS;
	}
	else
		return ERROR;
}
Status isEmptyLStack(LinkStack* s)//�ж�ջ�Ƿ�Ϊ��
{
	if (s)
		if (s->count == 0)
			return SUCCESS;
		else
			return ERROR;
	else
	{
		printf("������Ϊ��\n");
		return ERROR;
	}
}
Status getTopLStack(LinkStack* s, ElemType* e)//�õ�ջ��Ԫ��
{
	if (s && !isEmptyLStack(s))
	{
		*e = s->top->data;
		return SUCCESS;
	}
	else return ERROR;
}
Status clearLStack(LinkStack* s)//���ջ
{
	if (s)
	{
		LinkStackPtr m, p;
		p = s->top;
		s->top = NULL;
		while (s->count)/*��count�������ͷ��ڴ�*/
		{
			m = p;
			p = p->next; 
			s->count--;
			free(m);
		}
		return SUCCESS;
	}
	else
		return ERROR;
}
Status destroyLStack(LinkStack* s)//����ջ
{
	if (s)
	{
		clearLStack(s);/*��������ͷŵ�ǰ�ڵ�*/
		free(s);
		return SUCCESS;
	}
	else
		return ERROR;
}
Status LStackLength(LinkStack* s, int* length)//���ջ����
{
	if (s)
	{
		*length = s->count;
		return SUCCESS;
	}
	else return ERROR;
}
Status pushLStack(LinkStack* s, ElemType data)//��ջ
{
	if (s)
	{
			LinkStackPtr  q;/*����һ���µĽ�������topǰ*/
			q = (StackNode*)malloc(sizeof(StackNode));
			q->data = data;
			q->next = s->top;
			s->top = q;
			s->count++;
			return SUCCESS;
	}
	else return ERROR;
}
Status popLStack(LinkStack* s, ElemType* data)//��ջ
{
	if (s)/*����һ����ջ�������ͷ��ڴ�*/
	{
		LinkStackPtr p, q;
		p= s->top;
		q = p->next;
		*data = p->data;
		free(p);
		s->top = q;
		s->count--;/*���ټ�¼*/
		return SUCCESS;
	}
	else return ERROR;
}
