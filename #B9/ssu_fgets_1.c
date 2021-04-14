#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main(){
	char buf[BUFFER_SIZE];

	while(fgets(buf, BUFFER_SIZE, stdin) != NULL)//fgets로 표준입력으로 입력 받고 buf에 저장
		if(fputs(buf, stdout) == EOF){ //입력받은 문자열 표준 출력으로 출력
			fprintf(stderr, "standard output error\n");
			exit(1);
		}

	if(ferror(stdin)){ //에러 시 문구 출력
		fprintf(stderr, "standard input error\n");
		exit(1);
	}

	exit(0);
}
