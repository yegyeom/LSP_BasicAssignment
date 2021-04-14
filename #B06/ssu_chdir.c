#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
	if(chdir("/etc") < 0){ //작업 디렉토리를 /etc로 변경
		fprintf(stderr, "chdir error\n");
		exit(1);
	}

	printf("chdir to /etc succeeded. \n"); //변경 디렉토리 출력
	exit(0);
}
