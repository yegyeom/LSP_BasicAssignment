#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void ssu_signal_handler(int signo){
	printf("ssu_signal_handler control\n");
}

int main(void){
	struct sigaction sig_act;
	sigset_t sig_set;

	sigemptyset(&sig_act.sa_mask); //mask할 대상을 모두 초기화
	sig_act.sa_flags = 0; //sa_flag 0으로 초기화
	sig_act.sa_handler = ssu_signal_handler; //sa_handler는 ssu_signal_handler 주소를 가짐
	sigaction(SIGUSR1, &sig_act, NULL); //sig_act를 인자로 주어 SIGUSR1이 발생했을 때 액션에 대한 정보를 전달
	printf("before first kill()\n");
	kill(getpid(), SIGUSR1); //현재 프로세스에 SIGUSR1 시그널 발생
	sigemptyset(&sig_set); //sig_set 집합을 초기화
	sigaddset(&sig_set, SIGUSR1); //SIGUSR1 시그널 추가
	sigprocmask(SIG_SETMASK, &sig_set, NULL); //시그널 집합에 있는 시그널을 블록 시킴
	printf("before second kill()\n");
	kill(getpid(), SIGUSR1); //현재 프로세스에 SIGUSR1 시그널 발생
	printf("after second kill()\n");
	exit(0);
}
