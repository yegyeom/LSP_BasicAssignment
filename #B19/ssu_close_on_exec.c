#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(){
	int fd;
	int val;

	if((fd = open("exec_copy.txt", O_CREAT)) < 0){ //파일 만들고 오픈
		fprintf(stderr, "open error for %s\n", "exec_copy.txt");
		exit(1);
	}

	val = fcntl(fd, F_GETFD, 0); //fd로 지정된 파일 디스크립터의 플래그 리턴

	if(val & FD_CLOEXEC) 
		printf("close-on-exec bit on\n");
	else
		printf("close-on-exec bif off\n");

	val |= FD_CLOEXEC; //플래그 비트 켬

	if(val & FD_CLOEXEC)
		printf("close-on-exec bit on\n");
	else
		printf("close-on-exec bit off\n");

	fcntl(fd, F_SETFD, val); //FD_CLOEXEC 값을 val 값으로 설정
	execl("/home/yegyeom/loop", "./loop", NULL);
}
