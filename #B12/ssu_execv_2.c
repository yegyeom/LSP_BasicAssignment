#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void){
	char *argv[] = {
		"ssu_execl_test_1", "param1", "param2", (char *)0
	}; //새로 실행될 프로세스의 파일이 ssu_execl_test_1 , 나머지는 인자

	printf("this is original program\n");
	execv("./ssu_execl_test_1", argv); //새로운 프로세스 수행 => ./ssu_execl_test_1 경로에 있는 파일 실행
	printf("%s\n", "This line should never get printed\n");
	exit(0);
}
