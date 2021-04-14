#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	pid_t pid;
	char character, first, last;
	long i;

	if((pid = fork()) > 0){ //부모 프로세스
		first = 'A';
		last = 'Z';
	}
	else if(pid == 0){ //자식 프로세스
		first = 'a';
		last = 'z';
	}
	else{ //에러 처리
		fprintf(stderr, "%s\n", argv[0]);
		exit(1);
	}

	for(character = first ; character <= last ; character++){
		for(i = 0 ; i <= 100000 ; i++)
			;

		write(1, &character, 1); //표준출력으로 자식 프로세스와 부모 프로세스의 변수 값 출력
	}

	printf("\n");
	exit(0);
}
