#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
	int character;

	while((character = getc(stdin)) != EOF) //표준 입력으로 입력 받음
			if(putc(character, stdout) == EOF) { //입력 받은 문자열을 putc로 출력
				fprintf(stderr, "standard output error\n");
				exit(1);
			}
	if(ferror(stdin)){ //에러 시 문구 출력
		fprintf(stderr, "standard input error\n");
		exit(1);
	}

	exit(0);
}

