#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

void error(char* message)
{
	fprintf(stdout,"%s : %s \n",message,strerror(errno));
	exit(1);
}

void* display(void* a)
{
	long id = (long)a;
	printf("Thread %ld executing..\n",id);
	return (void*)id;
}	
	
int main(void)
{
	pthread_t threads[5];
	long i = 0;
	void* result;
	
	for(i = 0; i < 5; i++)
	{
		if(pthread_create(&threads[i],NULL,display, (void*)i) == -1)
			error("Can't create thread");
	}

	for(i = 0; i < 5; i++)
	{
		if(pthread_join(threads[i],&result) == -1)
			error("Can't join thread");
	}

}
