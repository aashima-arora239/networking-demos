#include <sys/types.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>


int main(void)
{
	char data[20];
	char buf[20];
	int fd[2];
	memset(data,'\0',20);
	memset(buf,'\0',20);
	pid_t pid;
	
	pipe(fd);
	pid = fork();

	if(0 == pid)
	{
		sleep(3);
		close(fd[1]);
		memset(buf,'\0',20);
		printf("In child..");
		while(read(fd[0],buf,sizeof(buf)) > 0)
		{		
			printf("\nData read : %s \n", buf);
			
			if(!strncmp(buf,"exit",4))
			{
				close(fd[0]);
				printf("Exiting from child process! \n");
				exit(0);
			}
		}
	}
	else
	{
		close(fd[0]);
	
		while(1)
		{
			if(!strncmp(data,"exit",4))
			{
				write(fd[1],"exit",strlen("exit"));
				close(fd[1]);
				printf("Exiting from parent process! \n");
				exit(0);
			}
			printf("In Parent...\n");
			printf("\nEnter data to be read by the child process :");
			memset(data,'\0',20);
			fgets(data,20,stdin);
			write(fd[1],data,strlen(data)+ 1);
		}
		
	}

}
