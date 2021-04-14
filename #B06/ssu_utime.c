#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <utime.h>

int main(int argc, char *argv[]){
	struct utimbuf time_buf;
	struct stat statbuf;
	int fd;
	int i;

	for(i = 1 ; i < argc ; i++){
		if(stat(argv[i], &statbuf) < 0){ //argv[i] 정보가 stat 구조체를 통해 리턴됨
			fprintf(stderr, "stat error for %s\n", argv[i]);
			continue;
		}

		if((fd = open(argv[i], O_RDWR | O_TRUNC)) < 0){ //argv[i] 파일을 읽기쓰기 전용으로 오픈
			fprintf(stderr, "open error for %s\n", argv[i]);
			continue;
		}

		close(fd);
		time_buf.actime = statbuf.st_atime; //파일 접근 시간을 time_buf의 actime에 저장
		time_buf.modtime = statbuf.st_mtime; //파일 수정 시간을 time_buf의 modtime에 저장

		if(utime(argv[i], &time_buf) < 0){ //stat()을 통해 리턴된 시간 값이 지정되었음 따라서 actime과 modtime은 그대로 유지됨
			fprintf(stderr, "utime error for %s\n", argv[i]);
			continue;
		}
	}
	exit(0);
}
