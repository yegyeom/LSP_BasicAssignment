#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void){
	printf("this is the original program\n");
	execl("./ssu_execl_test_1", "ssu_execl_test_1", "param1", "param2", "param3", (char *)0); 
	//./ssu_execl_test_1 경로의 파일 실행, ssu_execl_test_1은 새로 실행될 프로세스의 파일명
	//execl의 arg0 ~ argn 인자들이 ./ssu_execl_test_1(실행될 프로세스의 파일)의 main에서의 argv 
	printf("%s\n", "this line should never get printed\n");
	exit(0);
}
