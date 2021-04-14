#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *ssu_thread(void *arg);
int main(){
	pthread_t tid;

	if(pthread_create(&tid, NULL, ssu_thread, NULL) != 0){ //새로운 쓰레드 생성 1
		fprintf(stderr, "pthread_create error\n");
		exit(1);
	}

	printf("%u\n", (unsigned int)tid); //현재 쓰레드 id

	if(pthread_create(&tid, NULL, ssu_thread, NULL) != 0){ //새로운 쓰레드 생성 2
		fprintf(stderr, "pthread_create error\n");
		exit(1);
	}

	printf("%u\n", (unsigned int)tid); //현재 쓰레드 id
	sleep(1);
	exit(0);
}

void *ssu_thread(void *arg){
	pthread_t tid;

	tid = pthread_self(); //현재 쓰레드의 id 리턴받고 출력
	printf("->%u\n", (unsigned int)tid); 
	return NULL;
}
