#include<stdio.h>
#include<stdlib.h>
#include"SqStack.h"
//基于数组的顺序栈
Status initStack(SqStack* s, int sizes)//初始化栈
{
	if (s) {
		s->elem = (ElemType*)malloc(sizes * sizeof(ElemType));
		s->size = sizes;
		s->top = 0;
	}
	else return SUCCESS;
}
Status isEmptyStack(SqStack* s)//判断栈是否为空
{
	if (s)
		if (s->top == 0)
			return SUCCESS;
		else return ERROR;
	else
	{
		printf("输入为空\n");
		return ERROR;
	}
}
Status getTopStack(SqStack* s, ElemType* e) //得到栈顶元素
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
Status clearStack(SqStack* s)//清空栈
{
	if (s)
	{/*改变头结点*/
		s->top = 0;
		return SUCCESS;
	}
	else return ERROR;
}
Status destroyStack(SqStack* s)//销毁栈
{
	if (s)
	{/*先清空在释放*/
		s->top = 0;
		s->size = 0;
		free(s->elem);
		return SUCCESS;
	}
	else return ERROR;
}
Status stackLength(SqStack* s, int* length)//检测栈长度
{
	if (s)
	{
		*length = s->top;
		return SUCCESS;
	}
	else return ERROR;
}
Status pushStack(SqStack* s, ElemType data)//入栈
{
	if (s)
	{
		if (s->top == s->size)
		{/*先检测是否满，满栈则扩张并且更新尺度*/
			s->elem= (ElemType*)realloc(s->elem, (s->size + ADDSIZE) * sizeof(ElemType));
			s->size = s->size + ADDSIZE;
		}
		s->elem[s->top] = data;
		s->top++;
		return SUCCESS;
	}
	else return ERROR;
}
Status popStack(SqStack* s, ElemType* data)//出栈
{
	if (s)
	{/*如果是空栈直接返回*/
		if (isEmptyStack(s))
			return ERROR;
		s->top--;
		*data = s->elem[s->top];
		return SUCCESS;
	}
	else return ERROR;
}