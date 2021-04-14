#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
	char *fname = "ssu_test.txt";
	int fd;

	if((fd = creat(fname, 0666)) < 0){ //creat()로 파일 생성
		printf("creat error for %s\n", fname);
		exit(1);
	}

	printf("First printf is on the screen.\n");
	dup2(fd, 1); //3이 1로 복사된다
	printf("Second printf is in this file.\n"); //표준 출력으로 출력
	exit(0);
}
