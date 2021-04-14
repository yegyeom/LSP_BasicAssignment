#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
	char *fname = "ssu_test.txt";
	char *mode = "r";

	if(fopen(fname, mode) == NULL){ //파일을 읽기 전용으로 오픈
		fprintf(stderr, "fopen error for %s\n", fname);
		exit(1);
	}

	else
		printf("Success!\nFilename : <%s>, mode : <%s>\n", fname, mode); //성공시 파일이름, 모드와 함께 문구 출력

	exit(0);
}
