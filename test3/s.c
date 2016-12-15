#include "header.h"

#define PORT 30062

int main(int argc, char* argv[])
{
	struct sockaddr_in socketaddr,clientaddr;
	int sd,connd;
	char buf[SIZE];
	char recv[SIZE];
	int numbers[MAX];
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
		int size = sizeof(clientaddr);	

		connd = accept(sd,(struct sockaddr*)&clientaddr,&size);
		
		printf("Connection from client");

		if(0 > connd)
			printf("No connection");

		memset(buf,0, SIZE);
		
 		recvData(connd, buf);
		
		int count = tokenize(buf, numbers);

		memset(recv, 0, SIZE);

		reverse(recv, numbers, count);
		
		sendData(connd, recv);	
		
		shutdown(connd, SHUT_WR);
	
		close(connd);
	}
				
	

	close(sd);
}
	
	
	
	
