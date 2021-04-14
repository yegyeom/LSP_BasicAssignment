#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
	char c;
	int fd;

	if((fd = open("ssu_test.txt", O_RDONLY)) < 0){ //읽기 전용으로 파일 오픈
		fprintf(stderr, "open error for %s\n", "ssu_test.txt"); //에러 체크
		exit(1);
	}
	while(1){
		if(read(fd, &c, 1) > 0) //내용을 한 글자씩 읽음
			putchar(c); //표준 출력으로 출력
		else 
			break;
	}
	exit(0);
}
