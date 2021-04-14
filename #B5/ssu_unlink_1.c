#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
	char *fname = "ssu_dump.txt";

	if(open(fname, O_RDWR) < 0){ //파일을 읽기, 쓰기 용도로 오픈
		fprintf(stderr, "open error for %s\n", fname);
		exit(1);
	}

	if(unlink(fname) < 0){ //링크 해제, close 안해서 파일 삭제는 안됨
		fprintf(stderr, "unlink error for %s\n", fname);
		exit(1);
	}

	printf("File unlinked\n");
	sleep(20);
	printf("Done\n");
	exit(0);
}
