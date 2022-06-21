#include <stdio.h>
#include <stdlib.h>
int main()
{
	printf("Enter a date (mm/dd/yyyy): ");
	int day;
	int year;
	int month;
	char* m[]={"January","Frbruary","March","April","May","june","july","August","September","October","November","December"};
	scanf("%d/%d/%d",&month,&day,&year);
	printf("You enter the date %s %d, %d",m[month-1],day,year);
}
