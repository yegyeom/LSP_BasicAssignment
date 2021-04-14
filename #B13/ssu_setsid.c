#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	pid_t pid;

	if((pid = fork()) < 0){ //자식 프로세스 생성
		fprintf(stderr, "fork error\n");
		exit(1);
	}
	else if(pid != 0) //부모 프로세스 종료 시킴
		exit(1);

	printf("before pid = %d, sid = %d\n", getpid(), getsid(getpid())); //프로세스 id, 프로세스 세션 리더의 프로세스 그룹 id 출력
	setsid(); //자식 프로세스가 호출
	printf("after pid = %d, sid = %d\n", getpid(), getsid(getpid())); //프로세스 id, 프로세스 세션 리더의 프로세스 그룹 id 출력
	exit(0);
}
