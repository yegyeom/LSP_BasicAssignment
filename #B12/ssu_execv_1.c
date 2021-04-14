#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/resource.h>
#include <sys/wait.h>

double ssu_maketime(struct timeval *time);

void term_stat(int stat);

void ssu_print_child_info(int stat, struct rusage *rusage);

int main(void){
	struct rusage rusage;
	pid_t pid;
	int status;

	if((pid = fork()) == 0){ //자식 프로세스
		char *args[] = {"find", "/", "-maxdepth", "4", "-name", "stdio.h", NULL}; //문자 스트링에 대한 포인터들의 배열 / find는 명령어, 나머지는 인자
						//하위 디렉토리를 검색의 깊이를 4로 제한하여 stdio.h를 검색
		if(execv("/usr/bin/find", args) < 0){ // /usr/bin/find 경로에 있는 파일실행하여 새로운 프로세스 수행
			fprintf(stderr, "execv error\n");
			exit(1);
		}
	}

	if(wait3(&status, 0, &rusage) == pid) //종료된 프로세스와 그 자식 프로세스의 자원 사용에 관한 추가 정보 리턴
		ssu_print_child_info(status, &rusage); //자식프로세스에서의 사용된 CPU시간, 시스템 시간 출력
	else{
		fprintf(stderr, "wait3 error\n");
		exit(1);
	}

	exit(0);
}

double ssu_maketime(struct timeval *time){ //시간 sec단위로 설정
	return ((double)time -> tv_sec + (double)time -> tv_usec/1000000.0);
}

void term_stat(int stat){
	if(WIFEXITED(stat)) //자식 프로세스가 정상적으로 종료되었으면
		printf("normally terminated. exit status = %d\n", WEXITSTATUS(stat)); //exit의 인자에서 하위 8비트 값 출력
	else if(WIFSIGNALED(stat)) //자식 프로세스가 시그널을 받았으나 그것을 처리하지 않아 비정상적으로 종료 되었으면
		printf("abnormal termination by signal %d. %s\n", WTERMSIG(stat), //시그널 번호 출력
#ifdef WCOREDUMP
				WCOREDUMP(stat)?"core dumped":"no core" //코어 파일이 생성된 경우 
#else 
				NULL
#endif
			  );
	else if(WIFSTOPPED(stat)) //자식 프로세스가 현재 중지 상태이면
		printf("stopped by signal %d\n", WSTOPSIG(stat)); //실행을 일시 중단시킨 시그널 번호 출력
}

void ssu_print_child_info(int stat, struct rusage *rusage){
	printf("Termination info follows\n");
	term_stat(stat);
	printf("user CPU time : %.2f(sec)\n", ssu_maketime(&rusage->ru_utime)); //사용된 유저 시간(CPU) 출력
	printf("system CPU time : %.2f(sec)\n", ssu_maketime(&rusage->ru_stime)); //사용된 시스템 시간 출력
}
