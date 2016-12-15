#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

float balance = 1000;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void error(char* message)
{
	fprintf(stdout,"%s : %s \n",message,strerror(errno));
	exit(1);
}

void* deposit()
{
	int i = 0;
	for(i = 0; i < 50; i++)
	{
		pthread_mutex_lock(&lock);
		balance += 50;
		pthread_mutex_unlock(&lock);
	}
	printf("The balance is : %f\n",balance);
}	

void* withdraw()
{
	int i = 0;
	
	for(i = 0; i < 20; i++)
	{
		
		pthread_mutex_lock(&lock);
		balance -= 20;
		pthread_mutex_unlock(&lock);
	}

	printf("The balance is : %f\n",balance);
}

int main(void)
{
	pthread_t d;
	pthread_t w;
	long i = 0;
	void* result;
	
	if(pthread_create(&d, NULL, deposit, NULL) == -1)
		error("Can't create thread");

	if(pthread_create(&w, NULL, withdraw, NULL) == -1)
		error("Can't create thread");

	if(pthread_join(d,&result) == -1)
		error("Can't join thread");

	if(pthread_join(w,&result) == -1)
		error("Can't join thread");
}
