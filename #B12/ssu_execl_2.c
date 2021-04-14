#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void){
	if(fork() == 0){ //자식 프로세스 생성
		execl("/bin/echo", "echo", "this is", "message one", (char *)0); // /bin/echo 경로의 파일 실행, 새로 실행될 프로세스의 명령어 echo
		fprintf(stderr, "exec error\n");
		exit(1);
	}

	if(fork() == 0){ //자식 프로세스 수행
		execl("/bin/echo", "echo", "this is", "message two", (char *)0); // /bin/echo 경로의 파일 실행, 새로 실행될 프로세스의 명령어 echo
		fprintf(stderr, "exec error\n");
		exit(1);
	}

	if(fork() == 0){ //자식 프로세스 수행
		execl("/bin/echo", "echo", "this is", "message three", (char*)0);// /bin/echo 경로의 파일 실행, 새로 실행될 프로세스의 명령어 echo
		fprintf(stderr, "exec error\n");
		exit(1);
	}
//execl()가 정상적으로 수행되면 수행된 프로세스가 원래 프로세스를 덮어쓰게 된다.
	printf("Parent program ending\n");
	exit(0);
}
