#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

int main(){
	char buf[BUFFER_SIZE];
	char *fname = "ssu_test.txt";
	int fd;
	int length;

	if ((fd = open(fname, O_RDONLY, 0644)) < 0){
		fprintf(stderr, "open error for %s\n", fname);
		exit(1);
	}

	if(dup2(1,4) != 4){ //1에서 4로 복사
		fprintf(stderr, "dup2 call failed\n");
		exit(1);
	}

	while(1){
		length = read(fd, buf, BUFFER_SIZE); 

		if(length <= 0)
			break;

		write(4, buf, length); //새로 만든 파일에 그대로 쓰게됨 (동일한 내용)
	}

	exit(0);
}
