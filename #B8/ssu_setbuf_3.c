#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main(){
	char buf[BUFFER_SIZE];
	int a, b;
	int i;

	setbuf(stdin, buf); //setbuf로 버퍼 설정 (stdin의 버퍼를 1024만큼 설정)
	scanf("%d %d", &a, &b); //표준 입력으로 받아서 버퍼에 입력

	for(i =0 ; buf[i] != '\n' ; i++) //버퍼에 있는 내용 출력
		putchar(buf[i]);

	putchar('\n');
	exit(0);
}
