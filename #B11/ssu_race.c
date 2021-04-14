#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void ssu_charatatime(char *str);

int main(void){
	pid_t pid;

	if((pid = fork()) < 0){ //에러 처리
		fprintf(stderr, "fork error\n");
		exit(1);
	}
	else if(pid == 0) //자식 프로세스
		ssu_charatatime("output from child\n");
	else //부모 프로세스
		ssu_charatatime("output from parent\n");

	exit(0);
}

static void ssu_charatatime(char *str){
	char *ptr;
	int print_char;

	setbuf(stdout, NULL); //버퍼링 없어짐

	for(ptr = str ; (print_char = *ptr++) != 0 ; ){
		putc(print_char, stdout); //str의 내용을 표준 출력으로 하나씩 출력
		usleep(10); //10 마이크로 초 대기
	}
}
