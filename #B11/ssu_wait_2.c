#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define EXIT_CODE 1

int main(void){
	pid_t pid;
	int ret_val, status;

	if((pid = fork()) == 0){ //자식 프로세스
		printf("child: pid = %d ppid = %d exit_code = %d\n", getpid(), getppid(), EXIT_CODE); //자식 프로세스 id, 부모 프로세스 id, EXIT_CODE 출력
		exit(EXIT_CODE); 
	}
	//exit으로 정상적 종료 후 exit() 인자의 하위 8비트는 wait()의 status 인자로 전달됨
	printf("paren: waiting for child = %d\n", pid); 
	ret_val = wait(&status); //자식 프로세스의 종료 상태를 회수
	printf("parent: return value = %d, ", ret_val); //자식 프로세스 종료 후 부모 프로세스 출력
	printf(" child's status = %x", status); //자식 프로세스 출력
	printf(" and shifted = %x\n", (status >> 8)); //status인자 값 2진수 값으로 전환 => 오른쪽으로 8자리 이동 => 2진수 값 얻음 => 10진수로 출력
	exit(0);
}
