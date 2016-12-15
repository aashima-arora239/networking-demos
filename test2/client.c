#include "header.h"

int main(int argc, char* argv[])
{
	struct sockaddr_in server_addr;
	int sd,i;
	char buffer[SIZE];
	char* strings[MAX];

	sd = socket(AF_INET, SOCK_STREAM, 0);

	if( sd < 0)
	{
		perror("socket");
		exit(FAILURE);
	}

	memset(&server_addr, 0, sizeof(server_addr));

	server_addr.sin_family = AF_INET;

	server_addr.sin_addr.s_addr = inet_addr(argv[1]);

	server_addr.sin_port = htons(atoi(argv[2]));

	printf("Sendingg strings to the server");

	memset(buffer, 0, sizeof(buffer));
		
	for(i = 3 ; i < argc; i++)
	{
		strncat(buffer, argv[i], strlen(argv[i]));
		strncat(buffer,"*",1);
	}

	if(-1 == connect(sd, (struct sockaddr*)&server_addr, sizeof(server_addr)))
	{
		perror("Cannot connect to server");
		exit(FAILURE);
	}
	
	sendData(sd, buffer);

	shutdown(sd, SHUT_WR);

	memset(buffer, 0, sizeof(buffer));

	recvData(sd, buffer);

	int count = tokenize(buffer, strings);

	printf("Reversing display order...\n");
	
	for(i = 0; i < count; i++)
	{
		printf("%s \n",strings[i]);
	}
		
}
	
	
