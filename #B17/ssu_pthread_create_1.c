#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

void *ssu_thread(void *arg);

int main(void)
{
	pthread_t tid;
	pid_t pid;

	if(pthread_create(&tid, NULL, ssu_thread, NULL) != 0){ //쓰레드 생성
		fprintf(stderr, "pthread_create error\n");
		exit(1);
	}

	pid = getpid(); //현재 프로세스 id
	tid = pthread_self(); //현재 쓰레드 id (메인 쓰레드)
	printf("Main Thread: pid %u tid %u \n", (unsigned int)pid, (unsigned int)tid);
	sleep(1);

	exit(0);
}

void *ssu_thread(void *arg){
	pthread_t tid;
	pid_t pid;

	pid = getpid(); //현재 프로세스 id
	tid = pthread_self(); //현재 쓰레드 id (생성한 쓰레드)
	printf("New Thread: pid %d tid %u \n", (int)pid, (unsigned int)tid);
	return NULL;
}
