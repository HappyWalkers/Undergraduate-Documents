#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void print(int* list,int length);
int insert(int* list,int position,int value,int length);

int main(int argc, char *argv[]) {
	//顺序表的定义，插入和删除
	//	数组实现
	int init_size=10;
	int *list=(int*)malloc(init_size*sizeof(int));//create
	if(list==NULL)
	{
		printf("malloc failed in initial");
		return;
	}
	int length=0;
	
	for(int i=0;i<10;i++)//initial
	{
		list[i]=i+1;
		length++;
		
	}
	printf("----initialize the sequence list----\n");
	print(list,length);
	
	printf("----insert 1234 in NO.5 postion----\n");
	length=insert(list,5,1234,length);
	print(list,length);
	
	printf("----delete the number of NO.5 position---\n");
	length=delete(list,5,length);
	print(list,length);
	
	return 0;
}

int insert(int* list,int position,int value,int length)
{
	length++;
	list=(int*)realloc(list,(length)*sizeof(int));
	for(int i=length;i>=position;i--)
	{
		list[i+1]=list[i];
	}
	list[position]=value;
	return length;
}

int delete(int* list,int position,int length)
{
	length--;
	list=(int*)realloc(list,(length)*sizeof(int));
	for(int i=position;i<length;i++)
	{
		list[i]=list[i+1];
	}
	return length;
}

void print(int* list,int length)
{
	for(int i=0;i<length;i++)
	{
		printf("the NO.%d value is:%d\n",i+1,list[i]);
	}
	printf("\n");
}
