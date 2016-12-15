#include <sys/socket.h>
#include <arpa/inet.h>
#include <time.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <pthread.h>
#include <unistd.h>

#define SUCCESS 1
#define FAILURE 0
#define SIZE 1024
#define MAX 10
#define S_SIZE 10


int sendData(int sd, char* buf);
int recvData(int sd, char* buf);
int tokenize(char* buf, char* strings[]);
int reverse(char* buf, char* strings[], int count);









