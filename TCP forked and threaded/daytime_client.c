#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
int main(int argc,char *argv[])
{
	unsigned int len,sockfd,n;
	struct sockaddr_in servaddr,cliaddr;
	char buff[512];

	if(argc!=3)
	printf("a.out ipaddress portno\n");

	if((sockfd =socket(AF_INET,SOCK_STREAM,0))<0)
	perror("socket connection failed");

	bzero(&servaddr,sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port =htons(atoi(argv[2]));
	if((connect(sockfd,(struct sockadd *)& servaddr,sizeof(servaddr)))<0)
		perror("connect");
	strcpy(buff,"System");
        write(sockfd,buff,strlen(buff));
	sleep(1);
	read(sockfd,buff,sizeof(buff));
	write(1,buff,strlen(buff));
	shutdown(sockfd,SHUT_RDWR);
	close(sockfd);
	exit(0);
}


