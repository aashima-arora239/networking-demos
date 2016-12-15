#include "header.h"

#define PORT 30068

void* serveClient(void* connfd)
{
	char buf[SIZE];

	char recv[SIZE];

	char* strings[MAX];

	int connd = (int)connfd;
	
	memset(buf,0, SIZE);

        recvData(connd, buf);

        int count = tokenize(buf, strings);

        memset(recv, 0, SIZE);

       	reverse(recv, strings, count);

        sendData(connd, recv);

        shutdown(connd, SHUT_WR);

        close(connd);

	pthread_exit(NULL);

	
}
int main(int argc, char* argv[])
{
	struct sockaddr_in socketaddr,clientaddr;

	int sd,connd;

	pthread_t pth;

	memset(&socketaddr,0,sizeof(socketaddr));

	sd = socket(AF_INET, SOCK_STREAM, 0);

	if( sd < 0)
	{
		perror("socket");
		exit(FAILURE);
	}

	socketaddr.sin_family = AF_INET;

	socketaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	socketaddr.sin_port = htons(PORT);

	int b = bind(sd,(struct sockaddr*)&socketaddr,sizeof(socketaddr));
	
	if (-1 == b)	
		printf("Cannot bind to port");

	listen(sd,5);
	

	while(1)
	{
		socklen_t size = sizeof(clientaddr);	

		connd = accept(sd,(struct sockaddr*)&clientaddr,&size);
		
		printf("Connection from client");

		if(0 > connd)
			printf("No connection");

		pthread_create(&pth,NULL,&serveClient, (void*)connd);

	}
				
	

	close(sd);
}
	
	
	
	
