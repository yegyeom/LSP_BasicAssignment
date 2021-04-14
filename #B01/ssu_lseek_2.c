#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define CREAT_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

char buf1[] = "1234567890"; //"1234567890" 출력 후 15,000바이트 띄워서
char buf2[] = "ABCDEFGHIJ"; //"ABCDEFGHIJ" 출력하려함

int main(void)
{
	char *fname = "ssu_hole.txt";
	int fd;

	if((fd = creat(fname, CREAT_MODE)) < 0){
		fprintf(stderr, "creat error for %s\n", fname); 
		exit(1);
	}

	if(write(fd, buf1, 12) != 12){ //buf1 스트링 씀
		fprintf(stderr, "buf1 write error\n"); //에러체크 
		exit(1);
	}

	if(lseek(fd, 15000, SEEK_SET) < 0){ //lseek을 사용해 오프셋 위치를 이동
		fprintf(stderr, "lseek error\n"); //에러체크
		exit(1);
	}

	if(write(fd, buf2, 12) != 12){ //buf2 스트링 씀
		fprintf(stderr, "buf2 write error\n"); 
		exit(1);
	}

	exit(0);
}
