#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <termios.h>

#define STDIN_NUMBER 0

static void ssu_sig_hup(int signum);
static void ssu_print_ids(char *name);

int main(void)
{
	pid_t pid;
	char character;

	ssu_print_ids("parent"); //부모 프로세스 정보 출력
	if((pid = fork()) < 0){ //자식 프로세스 생성, 에러처리
		fprintf(stderr, "fork error\n");
		exit(1);
	}
	else if(pid > 0){ //부모 프로세스
		sleep(3);
		exit(0);
	}
	else{ //자식 프로세스 => 부모 프로세스가 먼저 중지되어 고아 프로세스가 됨
		ssu_print_ids("child");
		signal(SIGHUP, ssu_sig_hup); //SIGHUB 시그널 전달 받음
		kill(getpid(), SIGTSTP); //SIGTSTP 시그널을 받아 자식 프로세스 중지
		ssu_print_ids("child"); //자식 프로세스 정보 출력
//부모 프로세스가 종료되고 자식 프로세스는 배경 프로세스 그룹에 놓임
		if(read(STDIN_FILENO, &character, 1) != 1)
			fprintf(stderr, "read error\n");

		exit(0);
	}
}

static void ssu_sig_hup(int signum){
	printf("ssu_SIG_HUP received, pid = %d\n", getpid());
}

static void ssu_print_ids(char *name){
	printf("[%s] : pid = %d, ppid = %d, pgrp = %d, tpgrp = %d\n", name, getpid(), getppid(), getpgrp(), tcgetpgrp(STDIN_NUMBER)); //전달 받은 name, 프로세스 id, 부모 프로세스 id, 프로세스 그룹 id, 전경 프로세스 그룹의 프로세스 그룹 id 출력
	fflush(stdout);
}
