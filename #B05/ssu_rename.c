#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]){
	int fd;

	if(argc != 3){
		fprintf(stderr, "usage : %s <oldname><newname>\n", argv[0]);
		exit(1);
	}

	if((fd = open(argv[1], O_RDONLY)) < 0){ //argv[1]를 읽기 전용으로 오픈
		fprintf(stderr, "first open error for %s\n", argv[1]);
		exit(1);
	}
	else 
		close(fd);

	if(rename(argv[1], argv[2]) < 0){ //rename으로 파일명을 argv[2]로 변경
		fprintf(stderr, "rename error\n");
		exit(1);
	}

	if((fd = open(argv[1], O_RDONLY)) < 0) 
		printf("second open error for %s\n", argv[1]); //이름이 바뀌었으므로 에러 문구 출력
	else{
		fprintf(stderr, "it's very strange!\n");
		exit(1);
	}

	if((fd = open(argv[2], O_RDONLY)) < 0){ //argv[2]를 읽기 전용으로 오픈
		fprintf(stderr, "third open error for %s\n", argv[2]);
		exit(1);
	}

	printf("Everything is good!\n");
	exit(0);
}
