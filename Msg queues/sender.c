#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <mqueue.h>


#define MQ_NAME "/mq001"

int main(void)
{
	int flags,opt;
	mqd_t msgq;
	struct mq_attr attr;
	attr.mq_maxmsg = 10;
	attr.mq_msgsize= 2048;
	int readchars;	
	char buf[30];
	int priority = 1;
		
	if (-1 == (msgq = mq_open(MQ_NAME,O_RDWR)))
	{
		perror("mq:open");
		exit(-1);
	}
	
	for(;;)
	{
		printf("Type a message to send : ");
		readchars = read(0,buf,sizeof(buf));
		
		if (mq_send(msgq,buf,readchars - 1,priority++) < 0)
		{
			perror("mq:send");
			break;
		}
		
	}
	mq_close(msgq);
				
}	
	
