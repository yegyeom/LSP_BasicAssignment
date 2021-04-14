#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

void ssu_signal_handler(int signo);
void ssu_timestamp(char *str);

int main(void)
{
	struct sigaction sig_act;
	sigset_t blk_set;

	sigfillset(&blk_set); //모든 시그널을 blk_set에 추가
	sigdelset(&blk_set, SIGALRM); //blk_set이 가르키는 시그널 집합에서 SIGALRM 삭제
	sigemptyset(&sig_act.sa_mask); //sa_mask 초기화
	sig_act.sa_flags = 0; //sa flag 0으로 초기화
	sig_act.sa_handler = ssu_signal_handler; //sa_handler는 ssu_signal_handler의 주소를 가짐
	sigaction(SIGALRM, &sig_act, NULL); //SIGALRM이 발생했을 때의 액션에 대한 정보 전달
	ssu_timestamp("before sigsuspend()");
	alarm(5); //5초후 SIGALRM 발생
	sigsuspend(&blk_set); //기존의 시그널 집합을 가지고 시그널이 발생할 때까지 잠시 팬딩하다가 SIGALRM 시그널이 발생하면 시그널 핸들러 실행
	ssu_timestamp("after sigsuspend()");
	exit(0);
}

void ssu_signal_handler(int signo){
	printf("in ssu_signal_handler() function\n");
}

void ssu_timestamp(char *str){
	time_t time_val;

	time(&time_val);
	printf("%s the time is %s\n", str, ctime(&time_val)); //시간 문자열로 변환해서 출력
}
