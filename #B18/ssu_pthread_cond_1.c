#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *ssu_thread1(void *arg);
void *ssu_thread2(void *arg);

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER; //뮤텍스 변수 1 초기화
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER; //뮤텍스 변수 2 초기화
pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER; //cond 변수 1 초기화
pthread_cond_t cond2 = PTHREAD_COND_INITIALIZER; //cond 변수 2 초기화

int count = 0;
int input = 0;
int t1 = 0, t2 = 0;

int main(){
	pthread_t tid1, tid2;
	int status;

	if(pthread_create(&tid1, NULL, ssu_thread1, NULL) != 0){ //쓰레드1 생성
		fprintf(stderr, "pthread_create error\n");
		exit(1);
	}

	if(pthread_create(&tid2, NULL, ssu_thread2, NULL) != 0){ //쓰레드2 생성
		fprintf(stderr, "pthread_create error\n");
		exit(1);
	}

	while(1){
		printf("2개 이상의 개수 입력 : ");
		scanf("%d", &input);

		if(input >= 2){ //2개 이상 입력
			pthread_cond_signal(&cond1); //cond1로 시그널을 보냄
			break;
		}
	}

	pthread_join(tid1, (void*)&status); //생성된 쓰레드1이 종료될 때까지 기다림
	pthread_join(tid2, (void*)&status); //생성된 쓰레드2가 종료될 때까지 기다림

	printf("complete \n");
	exit(0);
}

void *ssu_thread1(void *arg){
	while(1){
		pthread_mutex_lock(&mutex1); //뮤텍스1 lock 설정

		if(input < 2)
			pthread_cond_wait(&cond1, &mutex1); //cond를 기다리고 있음

		if(input == count){
			pthread_cond_signal(&cond2); //cond2로 시그널을 보냄
			break;
		}

		if(count == 0){
			t2++;
			count++;
			printf("Thread 1 : %d\n", t1);
		}
		else if(count % 2 == 0){
			t1 += t2;
			count++;
			printf("Thread 1 : %d\n", t1);
		}

		pthread_cond_signal(&cond2); //cond2로 시그널을 보냄 
		pthread_cond_wait(&cond1, &mutex1); //cond1 으로 시그널 전달되기를 기다리고 있음
		pthread_mutex_unlock(&mutex1); //뮤텍스 lock 해제
	}

	return NULL;
}

void *ssu_thread2(void *arg){
	while(1){
		pthread_mutex_lock(&mutex2); //뮤텍스 lock 설정

		if(input < 2)
			pthread_cond_wait(&cond2, &mutex2); //cond2로 시그널 전달되기를 기다리고 있음

		if(input == count){
			pthread_cond_signal(&cond1); //cond1으로 시그널 보냄
			break;
		}

		if(count == 1){
			count++;
			printf("Thread 2 : %d\n", t2);
		}
		else if(count % 2 == 1){
			t2 += t1;
			count++;
			printf("Thread 2 : %d\n", t2);
		}

		pthread_cond_signal(&cond1); //cond1으로 시그널 보냄
		pthread_cond_wait(&cond2, &mutex2); //cond2로 시그널 전달되기를 기다리고 있음
		pthread_mutex_unlock(&mutex2); //뮤텍스 lock 해제
	}
	return NULL;
}
