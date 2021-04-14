#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void ssu_out(void);

int main(void){
	if(atexit(ssu_out)){ //ssu_out 함수 자동 실행
		fprintf(stderr, "atexit error\n");
		exit(1);
	}
	exit(0);
}

void ssu_out(void){
	printf("atexit succeeded!\n");
}
