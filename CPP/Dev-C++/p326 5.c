#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
//first:read_line word to a array[20].............bingo
//second:save the word to a *[100]
//third:sort the array
//fourth:print the array

char read_line(char word[],int max_word)
{
	char y;
	if((y=getchar())=='\n')
	{
		return y;
	}
	word[0]=y;
	for(int i=1;(y=getchar())!='\n' && i<max_word;i++)
   	{
    	word[i]=y;
    }
    return 'a';
}

void sort(char* words[],int num)
{
	for(int i=0;i<num;i++)
	{
		for(int j=i;j<num;j++)
		{
			if(strcmp(words[i],words[j])>0)
			{
				swap(words[i],words[j]);
			}
		}
	}
}

void swap(char* a,char*b)
{
	char* c=malloc(strlen(a)+1);
	if(c==NULL)
	{
		printf("fail in swap");
		return NULL;
	}
	strcpy(c,a);
	strcpy(a,b);
	strcpy(b,c);
}

int main(int argc, char *argv[]) {
	const int max_word=20;
	const int max_num=100;
	int count=0;
	char word[20]={0};
	char* words[100]={NULL};
	char flag;
	while(count<=max_num)
	{
		printf("Enter word: ");
		flag=read_line(word,max_word);
	    if(flag=='\n')break;
	//    printf("%s",word);
	    
	    words[count]=malloc(strlen(word)+1);
	    if(words[count]==NULL)
	    {
	    	printf("fail in main");
	    	break;
		}
		strcpy(words[count],word);
	//	printf("%s",word[count]);
		count++;
	}
	
	sort(words,count);
	
	printf("In sorted order: ");
	for(int i=0;i<count;i++)
	{
		printf("%s ",words[i]);
	}
	
	return 0;
}
