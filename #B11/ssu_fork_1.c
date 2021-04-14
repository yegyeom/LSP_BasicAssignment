#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char glob_str[] = "write to standard output\n";
int glob_val = 10;

int main(void)
{
	pid_t pid;
	int loc_val;
	
	loc_val = 100;
	if(write(STDOUT_FILENO, glob_str, sizeof(glob_str)-1) != sizeof(glob_str) - 1){ //write error가 발생하지 않는다면 glob_str의 내용 표준출력 (버퍼링 되지 않고 한번 출력됨)
		fprintf(stderr, "write error\n");
		exit(1);
	}

	printf("before fork\n");

	if((pid = fork()) < 0){ //에러처리
		fprintf(stderr, "fork error\n");
		exit(1);
	}
	else if (pid == 0){ //자식 프로세스
		glob_val++;
		loc_val++;
	}
	else //부모 프로세스
		sleep(3);
	//자식 프로세스와 부모 프로세스의 변수 값 출력
	printf("pid = %d, glob_val = %d, loc_val = %d\n", getpid(), glob_val, loc_val);
	exit(0);
}
