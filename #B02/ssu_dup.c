#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

int main(){
	char buf[BUFFER_SIZE];
	char *fname = "ssu_test.txt";
	int count;
	int fd1, fd2;

	if((fd1 = open(fname, O_RDONLY, 0644)) < 0){ //읽기 전용으로 파일 오픈
		fprintf(stderr, "open error for %s\n", fname);
		exit(1);
	}

	fd2 = dup(fd1); //파일 오픈하여 리턴받은 fd를 dup()으로 복사
	count = read(fd1, buf, 12);
	buf[count] = 0;
	printf("fd1's printf : %s\n", buf); 
	lseek(fd1, 1, SEEK_CUR); //lseek()으로 파일 포지션 이동
	count = read(fd2, buf, 12);
	buf[count] = 0;
	printf("fd2's printf : %s\n", buf); //복사한 파일 디스크립터는 원본 파일 디스크립터와 오프셋을 공유함
	exit(0);
}
