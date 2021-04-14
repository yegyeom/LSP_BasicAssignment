#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main(void){
	sigset_t set;

	sigemptyset(&set); //시그널 집합을 초기화
	sigaddset(&set, SIGINT); //시그널 집합에 SIGINT 시그널을 추가

	switch(sigismember(&set, SIGINT)) //시그널 집합에 SIGINT 있는지 확인
	{
		case 1 : //시그널 집합 존재
			printf("SIGINT is included. \n");
			break;
		case 0 : //시그널 집합 존재하지 않음
			printf("SIGINT is not included. \n");
			break;
		default :
			printf("failed to call sigismember() \n");
	}

	switch(sigismember(&set, SIGSYS)) //시그널 집합에 SIGSYS있는지 확인
	{
		case 1 :
			printf("SIGSYS is included. \n");
			break;
		case 0 :
			printf("SIGSYS is not included\n");
			break;
		default :
			printf("failed to call sigismember() \n");
	}

	exit(0);
}
