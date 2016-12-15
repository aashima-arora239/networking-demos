#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h> 
#include<netdb.h> 
#include<string.h>

int main(int argc, char *argv[])
{
	char hostname[100];
	int port_no, sd, i, j, x;
	struct sockaddr_in pin;
	char buff[20]="System Program";

	if ((sd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) 
	{
		perror("socket");
		exit(1);
	}

	printf("After socket.\n");
	memset(&pin, 0, sizeof(pin));
	pin.sin_family = AF_INET;
	pin.sin_addr.s_addr = INADDR_ANY;
	pin.sin_port = htons(atoi(argv[1]));
	//bind(sd,(struct sockaddr *)&pin,sizeof(pin));
	printf("After fill in the socket struct.\n");
	
	/* grab an Internet domain socket */
	sendto(sd,buff, sizeof(buff), 0, (struct sockaddr *) &pin, sizeof(pin));
	close(sd);
	} /* main*/


