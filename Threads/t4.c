#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <semaphore.h>
int amount = 300;

sem_t s;

void error(char* message)
{
	fprintf(stdout,"%s : %d \n",message,strerror(errno));
	exit(1);
}

int deposit(int value)
{
	sem_wait(&s);
	printf(" In thread :  %lu\n", pthread_self());
	amount += value;
	printf("The amount after deposit is %d\n", amount);
	sem_post(&s);
}

int withdraw(int value)
{
	int ret = 0;
	sem_wait(&s);
	printf(" In thread :  %lu\n", pthread_self());
	if (amount > 300)
	{
		amount -= value;
		ret = 1;
		printf("The amount after withdrawing is %d\n", amount);
	}
	sem_post(&s);
	return ret;
}

void* callDeposit(void* val)
{
	int dep = (int)val;
	int i = 0;
	while (i < 30)	
	{
		deposit(dep);
		printf(" i in deposit : %d\n",i);
		i++;
	}
	return NULL;
}	

void* callWithdraw(void* val)
{
	int with = (int)val;
	int i = 0;
	while (i < 30)
	{
		withdraw(with);
		printf(" i in withdraw : %d\n",i);
		i++;
	}
	return NULL;
}

int main(void)
{
	pthread_t d;
	pthread_t w;

	sem_init(&s,0,1);	
	
	int dep = 50;
	int with = 70;

	if(pthread_create(&d, NULL, callDeposit, (void*)dep) == -1)
		error("Can't create thread");

	if(pthread_create(&w, NULL, callWithdraw, (void*)with) == -1)
		error("Can't create thread");

	if(pthread_join(d,NULL) == -1)
		error("Can't join thread");

	if(pthread_join(w,NULL) == -1)
		error("Can't join thread");
}
