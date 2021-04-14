#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main(void)
{
	sigset_t sig_set;
	sigset_t old_set;
	sigset_t new_set;

	sigemptyset(&sig_set); //시그널 집합 sig_set 초기화
	sigaddset(&sig_set, SIGINT); //SIGINT 시그널을 sig_set에 추가
	sigprocmask(SIG_BLOCK, &sig_set, &old_set); //sig_set인자 블록, 기존의 시그널 집합 old_set에 저장
	sigsuspend(&old_set); //SIGINT 발생할 때까지 프로세스 일시 정지 => 발생하면 시그널 핸들러 실행하고 종료
	exit(0);
}

