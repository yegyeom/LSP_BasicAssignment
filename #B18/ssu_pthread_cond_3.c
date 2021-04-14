#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define VALUE_DONE 10
#define VALUE_STOP1 3
#define VALUE_STOP2 6

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER; //뮤텍스 변수 초기화
pthread_cond_t cond = PTHREAD_COND_INITIALIZER; //cond 변수 초기화

void *ssu_thread1(void *arg);
void *ssu_thread2(void *arg);

int glo_val = 0;

int main(void){
	printf("test");
	pthread_t tid1, tid2;

	pthread_create(&tid1, NULL, &ssu_thread1, NULL); //쓰레드 1 생성
	pthread_create(&tid2, NULL, &ssu_thread2, NULL); //쓰레드 2 생성
	pthread_join(tid1, NULL); //생성한 쓰레드1 종료될 때까지 기다림
	pthread_join(tid2, NULL); //생성한 쓰레드2 종료될 때까지 기다림
	pthread_mutex_destroy(&lock); //사용이 끝난 뮤텍스 변수 해제
	pthread_cond_destroy(&cond); //사용이 끝난 cond변수 해제
	printf("final value: %d\n", glo_val);
	exit(0);
}

void *ssu_thread1(void *arg){
	while(1){
		pthread_mutex_lock(&lock); //뮤텍스 lock 설정
		pthread_cond_wait(&cond, &lock); //시그널이 오기 전까지 블록 상태
		glo_val++; 
		printf("global value ssu_thread1: %d\n", glo_val);
		pthread_mutex_unlock(&lock); //뮤텍스 lock 해제

		if(glo_val >= VALUE_DONE)
			return NULL;
		}
}

void *ssu_thread2(void *arg){
	while(1){
		pthread_mutex_lock(&lock);
		if(glo_val < VALUE_STOP1 || glo_val > VALUE_STOP2)
			pthread_cond_signal(&cond); //cond로 시그널 보냄 => ssu_thread1 실행 가능 
		else{
			glo_val++;
			printf("global value ssu_thread2: %d\n", glo_val); //변수 증가시키고 출력
		}

		pthread_mutex_unlock(&lock); //뮤텍스 lock 해제

		if(glo_val >= VALUE_DONE)
			return NULL;
	}
}
