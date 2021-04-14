#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void){
	pid_t child1, child2;
	int pid, status;

	if((child1 = fork()) == 0) //자식 프로세스 1
		execlp("date", "date", (char *)0); //date 파일 실행

	if((child2 = fork()) == 0) //자식 프로세스 2
		execlp("who", "who", (char *)0); //who 파일 실행

	printf("parent: waiting for children\n");

	while((pid = wait(&status)) != -1){ //자식 프로세스의 종료 상태를 회수
		if(child1 == pid)
			printf("parent: first child: %d\n", (status >> 8)); //status의 인자 값 2진수 값으로 전환 => 오른쪽으로 8자리 이동 => 2진수 값 얻음 => 10진수로 출력
		else if(child2 == pid)
			printf("parent: second child: %d\n", (status >> 8)); //status의 인자 값 2진수 값으로 전환 => 오른쪽으로 8자리 이동 => 2진수 값 얻음 => 10진수로 출력
	}

	printf("parent: all children terminated\n"); //자식 프로세스 출력 먼저 수행한 후 출력
	exit(0);
}
