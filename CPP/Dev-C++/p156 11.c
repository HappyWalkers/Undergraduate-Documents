#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define stack_size 100

int contents[stack_size];
int top=0;

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
	                                                                        
}
