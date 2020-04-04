#include<stdio.h>
#include<stdlib.h>
#include"LinkStack.h"
//链栈
Status initLStack(LinkStack** s)//初始化栈
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
Status isEmptyLStack(LinkStack* s)//判断栈是否为空
{
	if (s)
		if (s->count == 0)
			return SUCCESS;
		else
			return ERROR;
	else
	{
		printf("输入结点为空\n");
		return ERROR;
	}
}
Status getTopLStack(LinkStack* s, ElemType* e)//得到栈顶元素
{
	if (s && !isEmptyLStack(s))
	{
		*e = s->top->data;
		return SUCCESS;
	}
	else return ERROR;
}
Status clearLStack(LinkStack* s)//清空栈
{
	if (s)
	{
		LinkStackPtr m, p;
		p = s->top;
		s->top = NULL;
		while (s->count)/*将count清零且释放内存*/
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
Status destroyLStack(LinkStack* s)//销毁栈
{
	if (s)
	{
		clearLStack(s);/*先清空在释放当前节点*/
		free(s);
		return SUCCESS;
	}
	else
		return ERROR;
}
Status LStackLength(LinkStack* s, int* length)//检测栈长度
{
	if (s)
	{
		*length = s->count;
		return SUCCESS;
	}
	else return ERROR;
}
Status pushLStack(LinkStack* s, ElemType data)//入栈
{
	if (s)
	{
			LinkStackPtr  q;/*建立一个新的结点插入在top前*/
			q = (StackNode*)malloc(sizeof(StackNode));
			q->data = data;
			q->next = s->top;
			s->top = q;
			s->count++;
			return SUCCESS;
	}
	else return ERROR;
}
Status popLStack(LinkStack* s, ElemType* data)//出栈
{
	if (s)/*将第一个出栈，并且释放内存*/
	{
		LinkStackPtr p, q;
		p= s->top;
		q = p->next;
		*data = p->data;
		free(p);
		s->top = q;
		s->count--;/*减少记录*/
		return SUCCESS;
	}
	else return ERROR;
}
