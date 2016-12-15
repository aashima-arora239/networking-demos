#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/wait.h>
#include<unistd.h>
#include<fcntl.h>

int main(int argc,char *argv[])
{
	int listenfd,connfd;
	struct sockaddr_in servaddr,cliaddr;
	socklen_t len;
	char buff[512];
	char *haddrp = NULL;
	int x;
	if(argc != 2)
		printf("a.out portno\n");
	listenfd = socket(AF_INET,SOCK_STREAM,0);
	if(listenfd ==-1)
	{
		perror("socket");
		exit(1);
	}
	else
	{
		printf("Socket created successfully\n");
	}

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(atoi(argv[1]));

	x = bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
	if(x ==-1)
	{
		perror("bind");
		exit(1);
	}
	else
	{
		printf("bind successfull\n");
	}

	x = listen(listenfd,10);
	if(x ==-1)
	{
		perror("listen");
		exit(1);
	}
	else
	{
		printf("Listen successfull\n");
	}	
	for(;;)
	{
		len = sizeof(cliaddr);
		memset(&cliaddr,0,sizeof(cliaddr));
		connfd = accept(listenfd,(struct sockaddr *)&cliaddr,&len);
		if(connfd ==-1)
		{	
			perror("accept");
			exit(1);
		}
		else
		{
			printf("accept successfull\n");
		}
		//haddrp = inet_ntoa(cliaddr.sin_addr);
		//printf("Connection request from %s\n",haddrp);
		read(connfd,buff,sizeof(buff));
		write(1,buff,strlen(buff));
		

		strcpy(buff,"Programming");
		write(connfd,buff,strlen(buff));
		close(connfd);
	}
close(listenfd);
shutdown(connfd,SHUT_RDWR);
shutdown(listenfd,SHUT_RDWR);
}

