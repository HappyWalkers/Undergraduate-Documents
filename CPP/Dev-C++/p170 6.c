#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define stack_size 100

int contents[stack_size];
int top=0;

void stack_overflow(void)
{
	printf("Expression is too complex");
}

void stack_underflow(void)
{
	printf("Not enough operands in expression");
}

void make_empty(void)
{
	top=0;
}

bool is_empty(void)
{
	return top==0;
}

bool is_full(void)
{
	return top==stack_size;
}

void push(int i)
{
	if(is_full())
	stack_overflow();
	else
	contents[top++]=i;
}

int pop(void)
{
	if(is_empty())
	stack_underflow();
	else
	return contents[--top];
}

void main()
{
	char input;
	
	while(1)
	{
		printf("Enter an RPN expression: ");
		while(1)
		{
			scanf(" %c",&input);
		//	printf("%c",input);
			if(input>='0' && input<='9')
			{
				push(input-48);
		//		printf("%d\n",contents[0]);
			}
			else if(input=='+')
			{
				push(pop()+pop());
			}
			else if(input=='-')
			{
				int first=pop();
				int second=pop();
				push(second-first);
			}
			else if(input=='*')
			{
				push(pop()*pop());
			}
			else if(input=='/')
			{
				int first=pop();
				int second=pop();
				push(second/first);
			}
			else if(input=='=')
			{
				printf("Value of expression: ");
				printf("%d",pop());
				printf("\n");
				break;
			}
			else
			{
				return;
			}
		}
	}
}
