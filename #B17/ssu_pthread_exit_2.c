#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *ssu_thread(void *arg);

int main(void)
{
	pthread_t tid;

	if(pthread_create(&tid, NULL, ssu_thread, NULL) != 0){ //쓰레드 생성
		fprintf(stderr, "pthread_create error\n");
		exit(1);
	}
	sleep(1);
	printf("쓰레드가 완료되기 전 main함수가 먼저 종료되면 실행 중 쓰레드 소멸\n");
	printf("메인 종료\n");
	exit(0);
}

void *ssu_thread(void *arg){
	printf("쓰레드 시작\n");
	sleep(5); //이로 인해 생성한 쓰레드보다 메인 쓰레드가 먼저 종료됨
	printf("쓰레드 수행 완료\n");
	pthread_exit(NULL); //생성한 쓰레드 종료 
	return NULL;
}
