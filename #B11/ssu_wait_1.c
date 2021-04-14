#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void ssu_echo_exit(int status);

int main(void){
	pid_t pid;
	int status;

	if((pid = fork()) < 0){ //에러 체크
		fprintf(stderr, "fork error\n");
		exit(1);
	}
	else if(pid == 0) //자식 프로세스
		exit(7);

	if(wait(&status) != pid){ //자식 프로세스의 종료 상태 회수
		fprintf(stderr, "wait error\n");
		exit(1);
	}

	ssu_echo_exit(status); //프로세스의 종료 상태 출력

	if((pid = fork()) < 0){ //에러 체크
		fprintf(stderr, "fork error\n");
		exit(1);
	}
	else if(pid == 0) //자식 프로세스
		abort(); //프로세스는 시그널을 받아 비정상적인 종료함

	if(wait(&status) != pid){ //자식 프로세스의 종료 상태 회수
		fprintf(stderr, "wait error\n");
		exit(1);
	}
	
	ssu_echo_exit(status); //프로세스의 종료 상태 출력

	if((pid = fork()) < 0){
		fprintf(stderr, "fork error\n");
		exit(1);
	}
	else if(pid == 0)
		status /= 0; //프로세스는 시그널을 받아 비정상적인 종료함

	if(wait(&status) != pid){ //자식 프로세스의 종료 상태 회수
		fprintf(stderr, "wait error\n");
		exit(1);
	}

	ssu_echo_exit(status); //프로세스의 종료 상태 출력
	exit(0);
}

void ssu_echo_exit(int status){
	if(WIFEXITED(status)) //자식 프로세스가 정상적으로 종료되었다면
		printf("normal termination, exit status = %d\n", WEXITSTATUS(status)); //exit()의 인자값 출력
	else if(WIFSIGNALED(status)) //자식 프로세스가 시그널을 받았으나 그것을 처리하지 않아 비정상적으로 종료되었으면
		printf("abnormal termination, signal number = %d%s\n", WTERMSIG(status), //시그널 번호 출력
#ifdef WCOREDUMP
				WCOREDUMP(status) ? " (core file generated)" : ""); //코어 파일이 생성된 경우 참 값 출력
#else
				"");
#endif
	else if (WIFSTOPPED(status)) //자식 프로세스가 현재 중지 상태이면
		printf("child stopped, signal number = %d\n", WSTOPSIG(status)); //실행을 일시 중단시킨 시그널 번호 출력
}
