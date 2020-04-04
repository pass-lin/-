#include<stdio.h>
#include<stdlib.h>
#define ok 1
#define no 0
#define BASESIZE 15
#define ADDSIZE 5
typedef union
{
	char c;
	int num;
}Elemtype;
typedef int status;
typedef struct/*定义一个栈*/
{
	Elemtype* base;
	Elemtype* top;
	int length;
}stack;
typedef int status;/*status表示返回值状态*/
void intstack(stack* p)
{
	p->base = p->top = (Elemtype*)malloc(BASESIZE * sizeof(Elemtype));
	if (!p->base)exit(-1);
	p->length = BASESIZE;
}
status push(stack* p, Elemtype a)/*压栈处理*/
{

	if ((p->top - p->base) == p->length)
	{
		p->base = (Elemtype*)realloc(p->base, (p->length + ADDSIZE) * sizeof(Elemtype));
		if (!p->base)exit(-1);
		p->top = p->base + p->length;
		p->length += ADDSIZE;
	}
	*(p->top) = a;
	p->top++;
	return ok;
}
status pop(stack* p, Elemtype* e)/*退栈*/
{
	if (p->base == p->top)return no;
	p->top--;
	*e = *p->top;
	return ok;
}
Elemtype getstack(stack* p)/*得到栈顶元素*/
{
	if (p->base == p->top)
	{
		printf("输入错误\n");
	}
	return *(p->top - 1);
}

int charnumber(char a)/*定义符号优先级*/
{
	switch (a)
	{
	case '*':
	case'/':return 3; break;
	case '+':
	case'-':return 2; break;
	case ')':
	case '(':return 1; break;
	case'#':return 0; break;
	}
}
char charcompare(char a, char b)/*算符优先级的比较*/
{
	if (a == ')')return '>';
	if (b == '(' || (a == '(' && b != ')'))return '<';
	if (a == '(' && b == ')' || a == b == '#')return '=';
	charnumber(a);
	charnumber(b);
	if (a >= b)
		return '>';
	else return'<';
}
status LN(char c)/*判断是否是符号*/
{
	switch (c)/*运算符返回1数字符返回2非法符返回0*/
	{
	case '*':
	case'/':
	case '+':
	case'-':
	case ')':
	case '(':
	case'#':return 1;
	}
	if (c >= '0' && c <= '9')
		return 2;
	return 0;
}
int compute(int a, char t, int b)/*计算*/
{
	switch (t)
	{
	case '*':return a * b;
	case'/':return a / b;
	case '+':return a + b;
	case'-':return a - b;
	}
}

int main()
{
	
	while (1)
	{
		int flag = 0;/*定义一个报错变量*/
		Elemtype n1, n2, temp;/*定义三个临时的工具人变量*/
		temp.c = 0;/*初始化变量*/		
		n1.num = n2.num = 0;
		stack charcter, number;/*定义运算符栈和数字栈*/
		intstack(&charcter);/*创建栈*/
		intstack(&number);
		Elemtype ch,prech;/*定义一个当前的输入字符，和他的前一个输入字符*/
		prech.c = 0;
		ch.c = '#';/*初始化变量*/
		push(&charcter, ch);/*第一个虚拟运算符先进栈*/
		while (LN(ch.c) != 2)/*采集桌面上的字符，第一个数字符前的字符全部无视*/
			ch.c = getchar();
		while (ch.c != '#' || getstack(&charcter).c != '#')
		{
			while ((LN(ch.c) == LN(prech.c))|| LN(ch.c)==0)
			{/*如果输入了非法字符，无视他继续采集，如果连续输入两个运算符只有前面一个有效*/
				prech.c = ch.c;
				ch.c = getchar();
			}
			if (LN(ch.c) == 2)
			{
				int i;
				char a[10] = { 0 };
				for (i = 0; LN(ch.c) == 2 && i < 9; i++)/*处理大于一位的字符*/
				{
					a[i] = ch.c;
					ch.c = 'a';
					while (!LN(ch.c))/*无视中间的非法字符*/
					{
						prech.c = ch.c;
						ch.c = getchar();
					}
				}
				if (i < 9)
				{
					a[i] = '\0';
					Elemtype n;
					n.num = atoi(a);/*将字符串变成整数*/
					push(&number, n);
				}
				else
					flag = 1;/*字符串太长的话则继续报错处理*/
			}
			else if (LN(ch.c)) {
				switch (charcompare(getstack(&charcter).c, ch.c))
				{
				case '<':push(&charcter, ch); prech.c = ch.c; ch.c = getchar(); break;/*如果优先级小压栈*/
				case'=':pop(&charcter, &n1); prech.c = ch.c;  ch.c = getchar(); break;/*如果等于拖去括号*/
				case'>':pop(&charcter, &temp); pop(&number, &n2); pop(&number, &n1);/*如果大于则进行计算*/
					temp.num = compute(n1.num, temp.c, n2.num); push(&number, temp);
					break;//最后当栈中仅有字符#与当前的ch为#时结束运算		
				}
			}
			if (flag)/*报错*/
			{
				printf("input number is too large.please resume load\n");
				break;
			}
		}
		if(!flag)/*清空*/
			printf("%d\n", getstack(&number).num);
		free(charcter.base);
		free(number.base);
	}
}