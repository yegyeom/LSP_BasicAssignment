#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
	char *fname = "ssu_test.txt";
	int fd;

	printf("First printf : Hello, OSLAB!!\n");

	if((fd = open(fname, O_RDONLY)) < 0){ //파일을 읽기 전용으로 오픈
		fprintf(stderr, "open error for %s\n", fname);
		exit(1);
	}

	if(freopen(fname, "w", stdout) != NULL) //파일로 stdout을 쓰기 모드로 다시 오픈
		printf("Second printf : Hello, OSLAB!!\n"); //freopen 성공 시 표준 출력이 ssu_test.txt의 출력으로 바뀜

	exit(0);
}
