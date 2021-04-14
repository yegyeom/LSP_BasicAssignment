#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(void){
	int fd, state;

	state = seteuid(1000); //프로세스의 유효사용자 id 1000으로 변경

	if(state < 0){
		fprintf(stderr, "seteuid error\n");
		exit(1);
	}

	if((fd = open("ssu_test.txt", O_CREAT | O_RDWR, S_IRWXU)) < 0){ //ssu_test.txt 파일 오픈 없으면 생성
		fprintf(stderr, "open error\n");
		exit(1);
	}

	close(fd);
	exit(0);
}
