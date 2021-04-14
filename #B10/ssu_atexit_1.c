#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void ssu_exit1(void);
static void ssu_exit2(void);

int main(){
	if(atexit(ssu_exit2) != 0){ //ssu_exit2 함수 실행
		fprintf(stderr, "atexit error for ssu_exit2");
		exit(1);
	}

	if(atexit(ssu_exit1) != 0){ //ssu_exit1 함수 실행
		fprintf(stderr, "atexit error for ssu_exit1");
		exit(1);
	}

	if(atexit(ssu_exit1) != 0){ //ssu_exit1 함수 실행
		fprintf(stderr, "atexit error for ssu_exit1");
		exit(1);
	}

	printf("done\n"); //가장 먼저 출력 (메인 함수가 리턴한 후 함수를 호출한 역순으로 함수들이 실행되기 때문에)
	exit(0);
}

static void ssu_exit1(void){
	printf("ssu_exit1 handler\n");
}

static void ssu_exit2(void){
	printf("ssu_exit2 handler\n");
}
