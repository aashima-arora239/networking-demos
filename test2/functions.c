#include "header.h"

int sendData(int sd, char* buf)
{
	char buffer[SIZE];
	
	memset(buffer, 0, SIZE);

	strncpy(buffer, buf, strlen(buf));

	int n = 0;

	int pointer = 0;

	int bytes_written = SIZE;

	while((n = write(sd, buffer+pointer, bytes_written)) > 0)
	{
		pointer = pointer + n;

		bytes_written = bytes_written -  n;
	}
	
	return SUCCESS;
}

int recvData(int sd, char* buf)
{
	int pointer = 0;

	int n = 0;

	while((n = read(sd, buf+pointer, SIZE)) > 0)
	{
		
		pointer = pointer + n;
	}

	buf[pointer] = '\0';

	return SUCCESS;
}


int tokenize(char* buf, char* strings[])
{
	char* temp;

	int i = 1;

	strings[0] = malloc(S_SIZE);
	
	temp = strtok(buf, "*");
	
	strcpy(strings[0],temp);

	while(NULL != (temp = strtok(NULL, "*")) && i < MAX)
	{
		strings[i] = malloc(S_SIZE);
		
		strcpy(strings[i],temp);

		i++;
	
	}

	return i;
}

int reverse(char* buf, char* strings[], int count)
{
	int i = 0;
	
	for(i = count - 1; i >= 0 ; i--)
	{
		strcat(buf,strings[i]);
		strncat(buf,"*",1);
	}

	return SUCCESS;
}	
		
			
		
	
