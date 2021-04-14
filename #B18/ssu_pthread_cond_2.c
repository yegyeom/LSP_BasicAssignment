#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <sys/time.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER; //뮤텍스 변수 초기화
pthread_cond_t cond = PTHREAD_COND_INITIALIZER; //cond 변수 초기화

int glo_val1 = 1, glo_val2 = 2;

void *ssu_thread1(void *arg);
void *ssu_thread2(void *arg);

int main(void){
	pthread_t tid1, tid2;

	pthread_create(&tid1, NULL, ssu_thread1, NULL); //쓰레드1 생성
	pthread_create(&tid2, NULL, ssu_thread2, NULL); //쓰레드2 생성
	pthread_join(tid1, NULL); //생성된 쓰레드 1 종료될 때까지 기다림
	pthread_join(tid2, NULL); //생성된 쓰레드 2 종료될 때까지 기다림
	pthread_mutex_destroy(&lock); //사용 끝난 뮤텍스 변수 해제
	pthread_cond_destroy(&cond); //사용 끝난 cond 변수 해제

	exit(0);
}

void *ssu_thread1(void *arg){
	sleep(1); //대기로 인해 ssu_pthread2 먼저 호출
	glo_val1 = 2;
	glo_val2 = 1;
//대기 풀리고
	if(glo_val1 > glo_val2)
		pthread_cond_broadcast(&cond); //pthread_cond_wait 중인 모든 변수 깨움

	printf("ssu_thread1 end\n");
	return NULL;
}

void *ssu_thread2(void *arg){
	struct timespec timeout;
	struct timeval now;

	pthread_mutex_lock(&lock); //뮤텍스 lock 설정
	gettimeofday(&now, NULL); //현재 시각 측정

	timeout.tv_sec = now.tv_sec + 5;
	timeout.tv_nsec = now.tv_usec * 1000;

	if(glo_val1 <= glo_val2){
		printf("ssu_thread2 sleep\n");
		if(pthread_cond_timedwait(&cond, &lock, &timeout) == ETIMEDOUT) //대기 상태로 변경
			printf("timeout\n");
		else
			printf("glo_val1 = %d, glo_val2 = %d\n", glo_val1, glo_val2);
	}

	pthread_mutex_unlock(&lock); //뮤텍스 lock 해제
	printf("ssu_thread2 end\n");
	return NULL;
}
