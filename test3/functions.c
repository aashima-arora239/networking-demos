#include "header.h"

int sendData(int sd, char* buf)
{
	char buffer[SIZE];

	memset(buffer, 0 , SIZE);

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


int tokenize(char* buf, int numbers[])
{
	char* temp;

	int i = 1;

	temp = strtok(buf, "*");

	sscanf(temp,"%d", &numbers[0]);	

	while(NULL != (temp = strtok(NULL, "*")) && i < MAX)
	{
		sscanf(temp,"%d", &numbers[i]);	
		
		i++;
	
	}

	return i;
}

int reverse(char* buf, int numbers[], int count)
{
	int i = 0;

	int len = 0;

	for(i = count - 1; i >= 0 ; i--)
	{
		sprintf(buf+len, "%d%s", numbers[i], "*");

		len = strlen(buf);
	}

	return SUCCESS;
}	
		
			
		
	
