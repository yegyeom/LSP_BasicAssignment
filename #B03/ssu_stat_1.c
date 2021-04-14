#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[]){
	struct stat statbuf;

	if(argc != 2){
		fprintf(stderr, "usage : %s <file>\n", argv[0]);
		exit(1);
	}

	if((stat(argv[1], &statbuf)) < 0){ //파일 정보가 stat 구조체를 통해 리턴 된다.
		fprintf(stderr, "stat error\n");
		exit(1);
	}

	printf("%s is %ld bytes\n", argv[1], statbuf.st_size); //파일의 크기 출력
	exit(0);
}
