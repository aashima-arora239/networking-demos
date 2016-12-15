#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

#define SIZE 50

static char message[] = " Writing between children ";

/*
	0 - Reading
	1 - Writing
*/

int main(void)
{
	pid_t pid;
	int fds[2];
	char buf[SIZE];

	pipe(fds);
	pid = fork();

	if(0 == pid)	
	{
		close(fds[1]);
		read(fds[0],buf,strlen(message));
		puts(buf);
	}
	else
	{
		close(fds[0]);
		sleep(10);
		write(fds[1],message,strlen(message));	
		wait(NULL);
	}

}	
