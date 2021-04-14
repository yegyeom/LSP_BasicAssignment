#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *ssu_thread(void *arg);

int main(void)
{
	pthread_t tid1, tid2;
	int thread1 = 1;
	int thread2 = 2;
	int status;

	if(pthread_create(&tid1, NULL, ssu_thread, (void*)&thread1) != 0){ //새로운 쓰레드 생성 1
		fprintf(stderr, "pthread_create error\n");
		exit(1);
	}

	if(pthread_create(&tid2, NULL, ssu_thread, (void*)&thread2) != 0){ //새로운 쓰레드 생성 2
		fprintf(stderr, "pthread_create error\n");
		exit(1);
	}
	//생성된 쓰레드가 종료될 때까지 기다림
	pthread_join(tid1, (void*)&status); 
	pthread_join(tid2, (void*)&status);
	exit(0);
}

void *ssu_thread(void *arg){
	int thread_index;
	int i;

	thread_index = *((int*)arg);
	
	for(i = 0 ; i < 5 ; i++){ //인자로 받은 값 출력
		printf("%d : %d\n", thread_index, i);
		sleep(1);
	}

	return NULL;
}	
