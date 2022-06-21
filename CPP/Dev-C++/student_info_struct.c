#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	struct student_info{
		int ID;
		char name[10];
		int birthday[3];
		enum {male,female} gender;
		int score[5];
		};
		
		struct student_info xiaoming = {10086,"xiaoming",{2000,12,3},male,{100,90,80,70,60}};
		
		printf("name: %s\n",xiaoming.name);
		if(xiaoming.gender==male)
		puts("gender: male");
		else
		puts("gender: female");
	//	printf("gender: %s\n",xiaoming.gender);
		printf("student ID: %d\n",xiaoming.ID);
		printf("birthday: %d,%d,%d\n",xiaoming.birthday[0],xiaoming.birthday[1],xiaoming.birthday[2]);
		printf("score: %d,%d,%d,%d,%d\n",xiaoming.score[0],xiaoming.score[1],xiaoming.score[2],xiaoming.score[3],xiaoming.score[4]);
			
  	return 0;
}
