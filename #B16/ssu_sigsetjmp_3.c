#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <setjmp.h>
#include <signal.h>

static void ssu_signal_handler1(int signo);
static void ssu_signal_handler2(int signo);

sigjmp_buf jmp_buf1;
sigjmp_buf jmp_buf2;

int main(void){
	struct sigaction act_sig1;
	struct sigaction act_sig2;
	int i, ret;

	printf("My PID is %d\n", getpid());
	ret = sigsetjmp(jmp_buf1, 1); //jmp_buf1 jump될 위치를 설정

	if(ret==0){
		act_sig1.sa_handler = ssu_signal_handler1; //sa_handler는 ssu_handler_handler1의 주소를 가짐
		sigaction(SIGINT, &act_sig1, NULL); //SIGINT 시그널에 관한 액션을 변경해서 확인
	}
	else if (ret == 3) //SIGINT 입력시 리턴 값 3
		printf("------------\n");

	printf("Starting\n");
	sigsetjmp(jmp_buf2, 2); //jmp_buf2 jump 될 위치를 설정
	act_sig2.sa_handler = ssu_signal_handler2; //sa_handler는 ssu_signal_handler2의 주소를 가짐
	sigaction(SIGUSR1, &act_sig2, NULL); //SIGUSR1 시그널에 관한 액션을 변경해서 확인

	for(i = 0 ; i< 20 ; i++){
		printf("i = %d\n", i);
		sleep(1);
	}

	exit(0);
}

static void ssu_signal_handler1(int signo){
	fprintf(stderr, "\nInterrupted\n");
	siglongjmp(jmp_buf1, 3); //이전에 지정한 위치로 점프
}

static void ssu_signal_handler2(int signo){
	fprintf(stderr, "\nSIGUSR1\n");
	siglongjmp(jmp_buf2, 2); //이전에 지정한 위치로 점프
}
