#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define S_MODE 0644
#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
	char buf[BUFFER_SIZE];
	int fd1, fd2;
	int length;

	if(argc != 3){
		fprintf(stderr, "Usage : %s filein fileout\n", argv[0]);
		exit(1);
	}
	
	if((fd1 = open(argv[1], O_RDONLY)) < 0 ){ //첫번째 파일 읽기 전용으로 오픈
		fprintf(stderr, "open error for %s\n", argv[1]); //에러 체크
		exit(1);
	}

	if((fd2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, S_MODE)) < 0){ //두번째 파일 write only, creat, truncation, 모드는 644로 오픈
		fprintf(stderr, "open error for %s\n", argv[2]); //에러체크
		exit(1);
	}
	
	while((length = read(fd1, buf, BUFFER_SIZE)) > 0) //첫번째 파일 read
		write(fd2, buf, length); //첫번째 파일의 내용을 두번째 파일에 넣음

	exit(0);
}
