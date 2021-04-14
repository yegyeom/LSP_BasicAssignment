#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PATH_MAX 1024

int main(){
	char *pathname;

	if(chdir("/home/yegyeom") < 0){ //현재 작업 디렉토리 변경
		fprintf(stderr, "chdir error\n");
		exit(1);
	}

	pathname = malloc(PATH_MAX);

	if(getcwd(pathname, PATH_MAX) == NULL){ //현재 작업 디렉토리에 대한 전체 경로를 얻음
		fprintf(stderr, "getcwd error\n");
		exit(1);
	}

	printf("current directory = %s\n", pathname); //현재 작업 디렉토리 출력
	exit(0);

}
