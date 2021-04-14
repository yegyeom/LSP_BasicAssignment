#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main(){
	char buf[BUFFER_SIZE];

	setbuf(stdout, buf); //setbuf로 버퍼 설정 (stdout 버퍼를 1024만큼 설정)
	printf("Hello, ");
	sleep(1);

	printf("OSLAB!!");
	sleep(1);
	printf("\n"); //여기까지 한번에 출력
	sleep(1);

	setbuf(stdout, NULL); //stdout 버퍼를 NULL로 설정
	printf("How"); //즉시 출력
	sleep(1);
	printf(" are"); //즉시 출력
	sleep(1);
	printf(" you?"); //즉시 출력
	sleep(1);
	printf("\n"); //즉시 출력
	exit(0);
}
