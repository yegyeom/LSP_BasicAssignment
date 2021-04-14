#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void ssu_signal_handler(int signo);

void(**ssu_func)(int);

int main(void){
	ssu_func = signal(SIGINT, ssu_signal_handler); //SIGINT에 대한 시그널 핸들러로 ssu_signal_handler() 등록
//ssu_func변수에 signal의 리턴값인 SIGINT에 대한 이전 시그널 핸들러 저장
	while(1){ 
		printf("process running...\n");
		sleep(1);
	}

	exit(0);
}

void ssu_signal_handler(int signo){ //시그널 발생 시 호출
	printf("SIGINT 시그널 발생.\n");
	printf("SIGINT를 SIG_DFL로 재설정 함.\n");
	signal(SIGINT, ssu_func); //SIGINT에 대한 핸들러를 이전의 시그널 핸들러로 되돌림
}
