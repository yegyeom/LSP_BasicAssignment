#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *ssu_loop1(void *arg);
void *ssu_loop2(void *arg);

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; //뮤텍스 변수 초기화
int shared_value;

int main(void)
{
	pthread_t tid1, tid2;
	int status;

	shared_value = 0;

	if(pthread_create(&tid1, NULL, ssu_loop1, NULL) != 0){ //쓰레드 생성 1
		fprintf(stderr, "pthread_create error\n");
		exit(1);
	}

	sleep(1);

	if(pthread_create(&tid2, NULL, ssu_loop2, NULL) != 0){ //쓰레드 생성 2
		fprintf(stderr, "pthread_create error\n");
		exit(1);
	}

	if(pthread_join(tid1, (void*)&status) != 0){ //생성된 쓰레드 1이 종료될 때까지 기다림
		fprintf(stderr, "pthread_join error\n");
		exit(1);
	}

	if(pthread_join(tid2, (void*)&status) != 0){ //생성된 쓰레드 2가 종료될 때까지 기다림
		fprintf(stderr, "pthread_join error\n");
		exit(1);
	}

	status = pthread_mutex_destroy(&mutex); //사용이 끝난 뮤텍스 변수 해제
	printf("code = %d\n", status); //에러 확인
	printf("programming is end\n");
	exit(0);
}

void *ssu_loop1(void *arg){
	int i;

	for(i = 0 ; i < 10 ; i++){
		pthread_mutex_lock(&mutex); //lock 걸기
		printf("loop1 : %d\n", shared_value);
		shared_value++; //공유변수 변경

		if(i==10)
			return NULL;

		pthread_mutex_unlock(&mutex); //lock 해제
		sleep(1);
	}

	return NULL;
}

void *ssu_loop2(void *arg){
	int i;
	
	for(i = 0 ; i < 10 ; i++){
		pthread_mutex_lock(&mutex); //lock 설정
		printf("loop2 : %d\n", shared_value);
		shared_value++; //공유변수 변경
		pthread_mutex_unlock(&mutex); //lock 해제
		sleep(2);
	}

	return NULL;
}
