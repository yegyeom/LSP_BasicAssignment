#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(){
	struct stat statbuf;
	char *fname = "ssu_myfile";
	int fd;

	if((fd = open(fname, O_RDWR | O_CREAT, 0600)) < 0){ //fname파일을 읽기, 쓰기, 모드 600으로 만듦
		fprintf(stderr, "open error for %s\n", fname);
		exit(1);
	}

	close(fd);
	stat(fname, &statbuf); //파일의 정보는 stat구조체를 통해 리턴됨
	printf("# 1st stat call # UID:%d		GID:%d\n" , statbuf.st_uid, statbuf.st_gid);

	if(chown(fname, 501, 300) < 0){ //UID에서 GID로 id 바꿈
		fprintf(stderr, "chown error for %s\n", fname);
		exit(1);
	}

	stat(fname, &statbuf); //파일의 정보는 stat구조체를 통해 리턴됨
	printf("# 2nd stat call # UID:%d	GID:%d\n", statbuf.st_uid, statbuf.st_gid); 

	if(unlink(fname) < 0){ //링크 제거
		fprintf(stderr, "unlink error for %s\n", fname);
		exit(1);
	}

	exit(0);
}
