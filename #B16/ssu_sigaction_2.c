#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void ssu_check_pending(int signo, char *signame);
void ssu_signal_handler(int signo);

int main(void){
	struct sigaction sig_act;
	sigset_t sig_set;

	sigemptyset(&sig_act.sa_mask); //sig act의 sa_mask 초기화
	sig_act.sa_flags = 0; //sa_flag 0으로 초기화
	sig_act.sa_handler = ssu_signal_handler; //sa_handler는 ssu_signal_handler 주소를 가짐

	if(sigaction(SIGUSR1, &sig_act, NULL) != 0){ //sig_act를 인자로 주어 SIGUSR1이 발생했을 때 액션에 대한 정보를 전달
		fprintf(stderr, "sigaction() error\n");
		exit(1);
	}
	else{
		sigemptyset(&sig_set); //sig_set 집합 초기화
		sigaddset(&sig_set, SIGUSR1); //SIGUSR1 시그널 추가

		if(sigprocmask(SIG_SETMASK, &sig_set, NULL) != 0){ //시그널 집합에 있는 시그널 블록시킴
			fprintf(stderr, "sigprocmask() error\n");
			exit(1);
		}
		else{
			printf("SIGUSR1 signals are now blocked\n");
			kill(getpid(), SIGUSR1); //현재 프로세스에 SIGUSR1 시그널 발생
			printf("after kill()\n");
			ssu_check_pending(SIGUSR1, "SIGUSR1");
			sigemptyset(&sig_set); //sig_set 집합을 초기화
			sigprocmask(SIG_SETMASK, &sig_set, NULL); //SIGUSR1 시그널 블록
			printf("SIGUSR1 signals are no loger blocked\n");
			ssu_check_pending(SIGUSR1, "SIGUSR1");
		}
	}
	exit(0);
}

void ssu_check_pending(int signo, char *signame){
	sigset_t sig_set;

	if(sigpending(&sig_set) != 0) //블록되어 있는 도중 그때 온 시그널 집합 가져옴
		printf("sigpending() error\n");
	else if(sigismember(&sig_set, signo)) //SIGUSR1이 시그널 집합에 포함되어 있다면
		printf("a %s signal is pending\n", signame);
	else
		printf("%s signals are not pending\n", signame);
}

void ssu_signal_handler(int signo){
	printf("in ssu_signal_handler function\n");
}
