#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

static void ssu_signal_handler1(int signo);
static void ssu_signal_handler2(int signo);

int main(void){
	struct sigaction act_int, act_quit;

	act_int.sa_handler = ssu_signal_handler1; //sa_handler는 ssu_signal_handler1의 주소를 가짐
	sigemptyset(&act_int.sa_mask); //sa_mask 초기화
	sigaddset(&act_int.sa_mask, SIGQUIT); //SIGQUIT 시그널 추가
	act_quit.sa_flags = 0; //sa_flag 0으로 초기화

	if(sigaction(SIGINT, &act_int, NULL) < 0){ //SIGINT가 발생했을 때의 액션에 대한 정보를 전달
		fprintf(stderr, "sigaction(SIGINT) error\n");
		exit(1);
	}

	act_quit.sa_handler = ssu_signal_handler2; //sa_handler는 ssu_signal_handler2의 주소를 가짐
	sigemptyset(&act_quit.sa_mask); //sa_mask 초기화
	sigaddset(&act_quit.sa_mask, SIGINT); //SIGINT 시그널 추가
	act_int.sa_flags = 0; //sa_flag 0으로 초기화

	if(sigaction(SIGQUIT, &act_quit, NULL) < 0){ //SIGQUIT가 발생했을 때의 액션에 대한 정보를 전달
		fprintf(stderr, "sigaction(SIGQUIT) error\n");
		exit(1);
	}

	pause(); //시그널이 발생할 때까지 실행 중이던 프로세스를 대기상태로
	exit(0);
}

static void ssu_signal_handler1(int signo){
	printf("Signal handler of SIGINT : %d\n", signo);
	printf("SIGQUIT signal is blocked : %d\n", signo);
	printf("sleeping 3 sec\n");
	sleep(3);
	printf("Signal handler of SIGINT ended\n");
}

static void ssu_signal_handler2(int signo){
	printf("Signal handler of SIGQUIT : %d\n", signo);
	printf("SIGINT signal is blocked : %d\n", signo);
	printf("sleeping 3 sec\n");
	sleep(3);
	printf("Signal handler of SIGQUIT ended\n");
}
