#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

int main(void){
	int testfd;
	int fd;

	fd = open("test.txt", O_CREAT); //파일 생성하고 오픈

	testfd = fcntl(fd, F_DUPFD, 5); //파일 디스크립터 복사
	printf("testfd :%d\n", testfd);
	testfd = fcntl(fd, F_DUPFD, 5); //파일 디스크립터 복사(5는 사용 되었으므로 6 리턴)
	printf("testfd :%d\n", testfd);

	getchar();
}
