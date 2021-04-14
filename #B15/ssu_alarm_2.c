#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define LINE_MAX 2048

static void ssu_alarm(int signo);

int main(void){
	char buf[LINE_MAX];
	int n;

	if(signal(SIGALRM, ssu_alarm) == SIG_ERR){ //SIGALRM에 대한 시그널 핸들러로 ssu_alarm 등록
		fprintf(stderr, "SIGALRM error\n");
		exit(1);
	}

	alarm(10); //10초 후 SIGALRM 발생 => 시그널 핸들러 실행

	if((n = read(STDIN_FILENO, buf, LINE_MAX)) < 0){ //표준 입력으로 받아서 받은 바이트 수가 n
		fprintf(stderr, "read() error\n");
		exit(1);
	}

	alarm(0); //SIGALRM 발생 => 시그널 핸들러 실행
	write(STDOUT_FILENO, buf, n); //표준 입력으로 받은 내용 write
	exit(0);
}

static void ssu_alarm(int signo){
	printf("ssu_alarm() called!\n");
}
