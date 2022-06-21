#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
extern char **environ;



int main(int argc,char* argv[])
{
	pid_t pid;
	int stat_loc;

	printf("mian start\n");
        pid=fork();
        if (pid < 0)
                printf("error in fork!");	
        else if (pid == 0)
	{ 
               printf("i am the child process, my process id is %d\n",getpid());
 	       execve("pp",argv,environ);
	}
        else
                printf("i am the parent process, my process id is %d\n",getpid());
	wait(&stat_loc);

}
