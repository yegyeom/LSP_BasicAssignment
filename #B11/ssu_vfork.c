#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>

void ssu_local_func(void);

int main(void){
	printf("Before vfork\n");
	ssu_local_func();
	printf("After ssu_local_func, my PID is %d\n", getpid());
	exit(0);
}

void ssu_local_func(void){
	pid_t pid;

	if((pid = vfork()) == 0) //자식 프로세스 vfork()로 먼저 실행됨을 보장
		printf("I'm child. My PID is %d\n", getpid()); //자식 프로세스의 프로세스 ID 출력
	else if(pid > 0) //부모 프로세스
		sleep(3);
	else //에러 처리
		fprintf(stderr, "vfork error\n");
}
