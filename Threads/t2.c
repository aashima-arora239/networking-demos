#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define SIZE 30
#define NUM 3

typedef struct{
	long emp_id;
	int hall_no;
	char name[SIZE];
	char branch[SIZE];
}emp;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
int id = 0;

void error(char* message)
{
	fprintf(stdout,"%s : %s \n",message,strerror(errno));
	exit(1);
}

void* display(void* empptr)
{
	emp* ptr = (emp*)empptr;
	while(id < NUM)
	{
		pthread_mutex_lock(&lock);
		printf("Executed By Thread : %lu\n", pthread_self());
		printf("Employee id : %ld\n", ptr[id].emp_id);
		printf("Employee name : %s\n", ptr[id].name);
		printf("Employee hall no : %d\n", ptr[id].hall_no);
		printf("Employee branch : %s\n", ptr[id].branch);
		id++;
		pthread_mutex_unlock(&lock);
		sleep(2);
		printf("Thread ID : %lu", pthread_self());
	}
	return (void*)(ptr[id].emp_id);
}	
	
int main(void)
{
	emp employees[NUM];
	pthread_t t0;
	pthread_t t1;
	long i = 0;
	void* result;
	
	for(i = 0; i < NUM; i++)
	{
		printf("\n\nEnter employee id : ");
		scanf("%ld",&employees[i].emp_id);
		getchar();

		printf("Enter employee hall no : ");
		scanf("%d",&employees[i].hall_no);
		getchar();

		printf("Enter employee name : ");
		fgets(employees[i].name,SIZE,stdin);
		
		printf("Enter employee branch : ");
		fgets(employees[i].branch,SIZE,stdin);
	}	

	if(pthread_create(&t0,NULL,display, (void*)&employees) == -1)
		error("Can't create thread");

	if(pthread_create(&t1,NULL,display, (void*)&employees) == -1)
		error("Can't create thread");

	if(pthread_join(t0,&result) == -1)
		error("Can't join thread");
	else
		printf("Thread returned with : %ld \n",(long)result);

	if(pthread_join(t1,&result) == -1)
		error("Can't join thread");
	else
		printf("Thread returned with : %ld \n",(long)result);
}
