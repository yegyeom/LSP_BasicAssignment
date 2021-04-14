#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void ssu_signal_handler(int signo);

int count = 0;

int main(void){
	signal(SIGALRM, ssu_signal_handler); //SIGALRM에 대한 시그널 핸들러로 ssu_signal_handler 등록
	alarm(1); //1초 후 SIGALRM 발생 => 시그널 핸들러 실행

	while(1);

	exit(0);
}

void ssu_signal_handler(int signo){
	printf("alarm %d\n", count++);
	alarm(1); //새로운 알람 설정 => 1초 후 SIGALRM발생 => 시그널 핸들러 실행
}
