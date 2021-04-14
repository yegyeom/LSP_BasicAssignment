#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void){
	char *argv[] = {
		"ssu_execl_test_1", "param1", "param2", (char*)0
	}; //실행될 프로세스 파일(ssu_execl_test_1)에서의 argv가 됨

	char *env[] = { //환경변수
		"NAME = value",
		"nextname=nextvalue",
		"HOME=/home/oslab",
		(char*)0
	};

	printf("this is original program\n");
	execve("./ssu_execl_test_1", argv, env); //./ssu_execl_test_1 파일의 환경 변수 지정
	printf("%s\n", "This line should never get printed\n");
	exit(0);
}
