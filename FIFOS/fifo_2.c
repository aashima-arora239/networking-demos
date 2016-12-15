#include <sys/wait.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

#define FIFO_1 "rdwr1"
#define FIFO_2 "rdwr2"
#define SIZE 50

int main(void)
{
	char* message = "Connection Established";
	char* term = "Terminate";
	char* ack = "Ack";
	char buf[SIZE];
	char buf2[SIZE];
	char filename[SIZE];
	int fp,fdr,fdw,readbytes,ctr1,ctr2;

	printf("Enter the name of the file : ");
	fgets(filename,SIZE,stdin);
	filename[strlen(filename) - 1] = '\0';	

	mknod(FIFO_1,S_IFIFO|0666,0);
	mknod(FIFO_2,S_IFIFO|0666,0);
	
	fdr = open(FIFO_1, O_RDWR);
	fdw = open(FIFO_2, O_RDWR);
	
	readbytes = read(fdr,buf,sizeof(buf));
	
	if(-1 == readbytes)
	{
		perror("read");
	}
	else
	{
		if(!strncmp(buf,"Connect",7))
		{
			printf("Received the %s message, Sending confirmation..\n",buf);
			write(fdw,message,strlen(message));	
		}
	}
	
	fp = open(filename, O_RDONLY,S_IRWXG);
	if (-1 == fp)
	{
		perror("fp:open");
	}	

	while (1)
	{
		memset(buf,'\0',SIZE);
		memset(buf2,'\0',SIZE);
		ctr2 = read(fp,buf2,sizeof(buf2));

                if(ctr2 <= 0)
                {
                        write(fdw,term,strlen(term));
                }
                else
                {
                        write(fdw,buf2,strlen(buf2));
                }
		
		ctr1 = read(fdr,buf,sizeof(buf));

                if(ctr1 > 0)
                {
                        puts(buf);
                        if (!strncmp(buf,term,strlen(term)))
                        {
				printf("\nReceived Terminate..\n");
                                write(fdw,ack,strlen(ack));
                                close(fp);
                                close(fdw);
                                break;
                         }
                         if (strstr(ack,buf))
                         {
				printf("\nReceived Ack..\n");
                                break;
                         }
                }
 
	}
	
}
