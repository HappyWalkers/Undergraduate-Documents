#include <stdio.h>
#include <stdlib.h>
#include "struct_student_info.h"
#include "print_get.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void swap(struct Student_Info* a,struct Student_Info* b);
int ave_score(int score[]);
void sort_score(struct Student_Info students[],int sum);

int main(int argc, char *argv[]) {
	printf("Enter the number of the classmates: ");
	int sum;
	scanf("%d",&sum);
	printf("\n");
	
	struct Student_Info students[sum+1];
	for(int i=1;i<=sum;i++)
	{
		students[i]=*GetInfo();
	}
	
	sort_score(students,sum);
	
	for(int i=1;i<=sum;i++)
	{
		PrintInfo(students[i]);
	}
	return 0;
}

void sort_score(struct Student_Info students[],int sum)
{	
	for(int i=1;i<=sum;i++)
	{
		for(int j=i;j<=sum;j++)
		{
			if(ave_score(students[i].score) < ave_score(students[j].score))
			{
				swap(&students[i],&students[j]);
			}
		}
	}
}

int ave_score(int score[])
{
	return (score[0]+score[1]+score[2]+score[3]+score[4])/5;
}

void swap(struct Student_Info* a,struct Student_Info* b)
{
	struct Student_Info temp=*a;
	*a=*b;
	*b=temp;
}
