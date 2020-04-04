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
{/*运算符返回1，数字符返回2，非法返回0*/
	switch (c)
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
	printf("输入以#为结尾的计算式\n");
	while (1)
	{
		Elemtype n1, n2, temp;/*定义三个临时变量*/
		temp.c = 0;
		int flag = 0;
		n1.num = n2.num = 0;
		stack charcter, number;
		intstack(&charcter);/*创建栈*/
		intstack(&number);
		Elemtype ch,prech;/*定义prech防止重复输入运算符*/
		prech.c = 0;
		ch.c = '#';
		push(&charcter, ch);/*将#入栈*/
		while (LN(ch.c) != 2)
			ch.c = getchar();
		while (ch.c != '#' || getstack(&charcter).c != '#')
		{
			int sign = 1;/*用来处理负号的机制*/
			while ((LN(ch.c) == LN(prech.c))|| LN(ch.c)==0)
			{
				if (ch.c = '-')/*碰见重复的-当做负号处理，其他输入作为无效处理*/
					sign *= -1;
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
					while (!LN(ch.c))
					{/*无视无效字符*/
						prech.c = ch.c;
						ch.c = getchar();
					}
				}
				if (i < 9)/*运算位数合法时入栈*/
				{
					a[i] = '\0';
					Elemtype n;
					n.num = sign *= atoi(a);/*将字符串变成整数*/
					push(&number, n);
				}
				else/*不合法更改标志*/
					flag = 1;
			}
			else if (LN(ch.c)) {
				switch (charcompare(getstack(&charcter).c, ch.c))
				{
				case '<':push(&charcter, ch); prech.c = ch.c; ch.c = getchar(); break;/*如果优先级小压栈*/
				case'=':pop(&charcter, &n1); prech.c = ch.c;  ch.c = getchar(); break;/*如果等于拖去括号*/
				case'>':pop(&charcter, &temp); pop(&number, &n2); pop(&number, &n1);/*如果大于则进行计算*/
					temp.num = compute(n1.num, temp.c, n2.num); push(&number, temp);
					break;
				}
			}
			if (flag)
			{/*输入数过大时输出报错*/
				printf("input number is too large.please resume load\n");
				break;
			}
		}/*当ch.c为#且栈中仅有#时结束运算*/
		if(!flag)/*没问题时输出运算结果*/
			printf("%d\n", getstack(&number).num);
		free(charcter.base);
		free(number.base);
	}
}