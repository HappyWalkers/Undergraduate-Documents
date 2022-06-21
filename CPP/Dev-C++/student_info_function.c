#include <stdio.h>
#include <stdlib.h>
#include "struct_student_info.h"
#include "print_get.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */


struct Student_Info * GetInfo();
void PrintInfo(struct Student_Info a);

int main(int argc, char *argv[]) {
	struct Student_Info xiaoming=*GetInfo();
	PrintInfo(xiaoming);
	return 0;
}

