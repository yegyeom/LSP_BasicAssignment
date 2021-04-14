#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
	char *fname = "ssu_test.txt";
	int fd;

	if ((fd = creat(fname, 0666)) < 0){ //creat()로 생성한 파일을 open()을 통해 오픈
		fprintf(stderr, "creat error for %s\n", fname); 
		exit(1);
	}
	else {
		close(fd);
		fd = open(fname, O_RDWR); //플래그 사용하여 정상적으로 다시 오픈
		printf("Succeeded!\n<%s> is new readable and writable\n", fname);
	}

	exit(0);
}
