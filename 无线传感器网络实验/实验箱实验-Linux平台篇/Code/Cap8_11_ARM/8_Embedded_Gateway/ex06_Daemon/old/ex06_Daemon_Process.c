#include<stdio.h>
#include<unistd.h>
#include<syslog.h>

int main()
{
	daemon(0, 0);
	openlog("daemon_log", LOG_PID, LOG_USER);
	while(1)
	{
		//printf("this is daemon process\n");
		syslog(LOG_INFO, "this is daemon process\n");
		sleep(1);
	}
	closelog();
	return 0;
}
