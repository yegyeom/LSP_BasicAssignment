#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
	char *fname = "ssu_test.txt";
	int fd;

	if((fd = creat(fname, 0666)) < 0 ){ //txt파일을 creat()를 통해 파일 생성하고 오픈
		fprintf(stderr, "creat error for %s\n", fname); 
		exit(1);
	}

	else {
		printf("Success!\nFilename : %s\nDescriptor : %d\n", fname, fd); 
		close(fd);
	}

	exit(0);
}
