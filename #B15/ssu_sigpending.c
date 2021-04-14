#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main(void)
{
	sigset_t pendingset;
	sigset_t sig_set;

	int count = 0;

	sigfillset(&sig_set); //모든 시그널을 sig_set에 추가
	sigprocmask(SIG_SETMASK, &sig_set, NULL); //시그널 집합에 포함된 모든 시그널을 블록

	while(1){
		printf("count : %d\n", count++);
		sleep(1);

		if(sigpending(&pendingset) == 0){ //현재 팬딩 중인 시그널 집합의 정보를 가져옴
			if(sigismember(&pendingset, SIGINT)){ //팬딩 중인 시그널 집합 중 그 안에 SIGINT 시그널 있는지 검사
				printf("SIGINT가 블록되어 대기 중. 무한 루프를 종료.\n");
				break; //무한루프 나옴
			}
		}
	}
	exit(0);
}
