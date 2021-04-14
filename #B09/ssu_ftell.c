#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
	char *fname = "ssu_test.txt";
	FILE *fp;
	long fsize;

	if((fp = fopen(fname, "r")) == NULL){ //파일을 읽기 전용으로 오픈
		fprintf(stderr, "fopen error for %s\n", fname);
		exit(1);
	}

	fseek(fp, 0, SEEK_END); //파일의 맨 마지막으로 오프셋 이동
	fsize = ftell(fp); //현재 오프셋 위치가 파일의 시작부터 몇 바이트 떨어져있는지 알려줌 (즉 파일의 크기)
	printf("The size of <%s> is %ld bytes\n", fname, fsize); //파일 이름과 크기 출력
	exit(0);
}
