#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
	char *fname = "ssu_test.txt";
	FILE *fp;

	if((fp = fopen(fname, "r")) == NULL){ //파일을 읽기 전용으로 오픈
		fprintf(stderr, "fopen error for %s\n", fname);
		exit(1);
	}

	else{ //성공 시 출력
		printf("Success!\n");
		printf("Opening \"%s\" in \"r\" mode!\n", fname);
	}

	fclose(fp); //오픈된 파일 닫음
	exit(0);
}
