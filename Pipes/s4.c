#include <sys/types.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
	int fd[2];
	pid_t pid;
	
	pipe(fd);
	pid = fork();

	if(0 == pid)
	{
		close(1);
		dup(fd[1]);
		close(fd[0]);
		execlp("ls","ls","-al",NULL);
	}
	else
	{	
		close(0);
		dup(fd[0]);
		close(fd[1]);
		execlp("sort","sort",NULL);
		
	}

}
