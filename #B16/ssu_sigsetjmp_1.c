#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <setjmp.h>

void ssu_signal_handler(int signo);

jmp_buf jump_buffer;

int main(void){
	signal(SIGINT, ssu_signal_handler); //SIGINT에 대한 시그널 핸들러로 ssu_signal_handler 등록

	while(1){
		if(setjmp(jump_buffer) == 0){ //longjmp() 호출 시 jump 될 위치 설정
			printf("Hit Ctrl-c at anytime...\n");
			pause(); //시그널이 발생할 때까지 실행 중이던 프로세스를 대기상태로
		}
	}
	exit(0);
}

void ssu_signal_handler(int signo){
	char character;

	signal(signo, SIG_IGN); //SIGINT 발생 시 무시
	printf("Did you hit Ctrl-c?\n" "Do you really want to quit? [y/n] ");
	character = getchar(); //문자 하나 입력 받음

	if(character == 'y' || character == 'Y')
		exit(0); //y 면 종료
	else{
		signal(SIGINT, ssu_signal_handler); //SIGINT에 대한 시그널 핸들러롤 ssu_signal_handler 등록
		longjmp(jump_buffer, 1); //이전에 설정한 위치로 점프 => 1을 setjmp의 리턴 값으로 사용
	}
}
