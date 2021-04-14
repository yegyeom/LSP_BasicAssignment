#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void ssu_alarm(int signo);

int main(void){
	printf("Alarm Setting\n");
	signal(SIGALRM, ssu_alarm); //SIGALRM에 대한 시그널 핸들러로 ssu_alarm설정
	alarm(2); //2초 후에 SIGALRM 발생 => 시그널 핸들러 실행

	while(1){
		printf("done\n");
		pause(); //프로세스의 실행을 SIGALRM 시그널이 발생할 때까지 중지
		alarm(2); //2초 후에 SIGALRM 시그널  
	}
	exit(0);
}

void ssu_alarm(int signo){
	printf("alarm..!!!\n");
}
