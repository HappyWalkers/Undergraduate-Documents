//time_struct

#include <stdio.h>
#include <stdlib.h>


int ct(int a,int b);

struct TIME{
		int start_time;
		int arrival_time;
	}time[8]={ {ct(8,0),ct(10,16)}, {ct(9,43),ct(11,52)},{ct(11,19),ct(13,31)},{ct(12,47),ct(15,0)},{ct(14,0),ct(16,8)},{ct(15,45),ct(17,55)},{ct(19,0),ct(21,20)},{ct(21,45),ct(23,58)}};
	
int ct(int a,int b)
{
	return a*60+b;
}

int min_dis(int timeg,struct TIME time[])
{
	;
}
