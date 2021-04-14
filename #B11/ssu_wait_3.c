#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void){
	if(fork() == 0) //자식 프로세스
		execl("/bin/echo", "echo", "this is", "message one", (char *)0); //echo 명령어로 this is message one 출력

	if(fork() == 0) //자식 프로세스
		execl("/bin/echo", "echo", "this is", "message Two", (char *)0); //echo 명령어로 this is message Two 출력

	printf("parent : waiting for children\n");

	while(wait((int *)0) != -1); //자식이 없을 때까지 wait() 정상적 호출

	printf("parent : all children terminated\n"); //자식 프로세스의 출력 먼저 수행한 후 출력
	exit(0);
}
