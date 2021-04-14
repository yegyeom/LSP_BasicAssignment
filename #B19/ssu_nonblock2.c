#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

#define MAX_CALL 100
#define MAX_BUF 20000

void serror(char *str){
	fprintf(stderr, "%s\n", str);
	exit(1);
}

int main(){
	int nread, nwrite, val, i=0;
	char *ptr;
	char buf[MAX_BUF];

	int call[MAX_CALL];

	nread = read(STDIN_FILENO, buf, sizeof(buf)); //표준입력으로 받은 파일 읽어서 buf에 내용저장 리턴 값은 파일의 byte 수
	fprintf(stderr, "read %d bytes\n", nread);
	//NONBLOCKING 모드로 변경
	if((val = fcntl(STDOUT_FILENO, F_GETFL, 0)) < 0) 
		serror("fcntl F_GETFL error");
	val |= O_NONBLOCK; //플래그 비트 켬
	if(fcntl(STDOUT_FILENO, F_SETFL, val) < 0) //표준 출력을 val변수에 설정된 플래그 값으로 설정
		serror("fcntl F_SETFL error");

	for(ptr = buf ; nread > 0 ; i++){
		errno = 0;
		nwrite = write(STDOUT_FILENO, ptr, nread); //ptr내용을 표준출력으로 출력 리턴 값은 전달한 byte수 

		if(i < MAX_CALL)
			call[i] = nwrite;

		fprintf(stderr, "nwrite = %d, errno = %d\n", nwrite, errno);
		if(nwrite > 0){
			ptr += nwrite;
			nread -= nwrite;
		}
	}

	if((val = fcntl(STDOUT_FILENO, F_GETFL, 0)) < 0)
		serror("fcntl F_GETFL error");
	val &= ~O_NONBLOCK; //플래그 비트 끔
	if(fcntl(STDOUT_FILENO, F_SETFL, val) < 0)
		serror("fcntl F_SETFL error");

	for(i = 0 ; i < MAX_CALL ; i++)
		fprintf(stdout, "call[%d] = %d\n", i, call[i]);

	exit(0);
}
