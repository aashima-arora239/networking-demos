#include <stdio.h> 
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h> 
#include <netdb.h> 
#include <string.h>
int main(int argc,char *argv[])
{
	int sd, fromlen, tolen;
	int addrlen;
	struct sockaddr_in sin;
	struct sockaddr_in cin;
	int recvd;
	int structlength;
	char buf[100];

	if(argc != 2)
	{
		printf("a.out Portno\n");
		exit(1);
	}
/* get an internet domain socket */
	if ((sd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) 
	{
		perror("socket");
		exit(1);
	}
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(atoi(argv[1]));

	/* bind the socket to the port number */
	if (bind(sd, (struct sockaddr *) &sin, sizeof(sin)) == -1) 
	{
		perror("bind");
		exit(1);
	}; 
	printf("After bind.\n");

	structlength = sizeof(cin);
	recvd = recvfrom(sd, buf, sizeof(buf), 0,(struct sockaddr *) &cin, &structlength);
	write(1,buf,strlen(buf));
	
	/* close up both sockets */
	close(sd);
	/* give client a chance to properly shutdown */
	sleep(1);
	} /* main*/
