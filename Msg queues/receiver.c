#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <mqueue.h>


#define MQ_NAME "/mq001"
#define OPEN_FLAGS   O_RDWR|O_CREAT
#define OPEN_MODE    S_IRUSR|S_IWUSR
int main(void)
{
	int flags,opt;
	mqd_t msgq;
	struct mq_attr attr;
	attr.mq_maxmsg = 10;
	attr.mq_msgsize= 2048;
	attr.mq_curmsgs = 0;
	int ret;	
	char buf[30];
		
	if(-1 == (msgq = mq_open(MQ_NAME, OPEN_FLAGS, OPEN_MODE, &attr))) 	
	{
		perror("mq:open");
		exit(0);
	}
	
	for(;;)
	{
		
		if ((ret = mq_receive(msgq,buf,2048,NULL)) < 0)
		{
			perror("mq:receive");
			break;
		}
		else
		{
			buf[ret] = '\0';
			printf("Received : %s \n",buf);
		}
	}

	mq_close(msgq);
	mq_unlink(MQ_NAME);	
		
}
				
