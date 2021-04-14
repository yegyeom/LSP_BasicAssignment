#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void ssu_signal_handler1(int signo);
void ssu_signal_handler2(int signo);

int main(void)
{
	if(signal(SIGINT, ssu_signal_handler1) == SIG_ERR){ //SIGINT에 대한 시그널 핸들러로 ssu_signal_handler1 등록
		fprintf(stderr, "cannot hadle SIGINT\n");
		exit(EXIT_FAILURE);
	}

	if(signal(SIGUSR1, ssu_signal_handler2) == SIG_ERR){ //SIGUSR1에 대한 시그널 핸들러로 ssu_signal_handler2 등록
		fprintf(stderr, "cannot handle SIGUSR1\n");
		exit(EXIT_FAILURE);
	}

	raise(SIGINT); //자기 자신에게 SIGINT 보냄 => SIGINT의 시그널 핸들러 호출
	raise(SIGUSR1); //자기 자신에게 SIGUSR1 보냄 => SIGUSR1의 시그널 핸들러 호출
	printf("main return\n");
	exit(0);
}

void ssu_signal_handler1(int signo){
	printf("SIGINT 시그널 발생\n");
}

void ssu_signal_handler2(int signo){
	printf("SIGUSR1 시그널 발생\n");
}
