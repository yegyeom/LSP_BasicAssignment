#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main(){
	char buf[BUFFER_SIZE];
	int length;

	length = read(0, buf, BUFFER_SIZE); //표준 입력에서 read호출해서 데이터 읽음
	write(1, buf, length); //표준출력으로 내보냄
	exit(0);
}
