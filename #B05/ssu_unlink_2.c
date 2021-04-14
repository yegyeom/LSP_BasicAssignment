#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
	char buf[64];
	char *fname = "ssu_tempfile";
	int fd;
	int length;

	if((fd = open(fname, O_RDWR | O_CREAT | O_TRUNC, 0600)) < 0){ //파일을 읽기쓰기 용도, 600모드로 만들어서 오픈
		fprintf(stderr, "first open error for %s\n", fname);
		exit(1);
	}

	if(unlink(fname) < 0){ //close안해서 파일 삭제는 일어나지 않음
		fprintf(stderr, "unlink error for %s\n", fname);
		exit(1);
	}

	if(write(fd, "How are you?", 12) != 12){ //unlink는 파일을 닫은 후 삭제되므로 쓰기 정상적 실행
		fprintf(stderr, "write error\n");
		exit(1);
	}

	lseek(fd, 0, 0); //offset 이동

	if((length = read(fd, buf, sizeof(buf))) < 0){
		fprintf(stderr, "buf read error\n");
		exit(1);
	}
	else
		buf[length] = 0; 

	printf("%s\n", buf);
	close(fd); //파일 닫음

	if((fd = open(fname, O_RDWR)) < 0){ //읽기 전용으로 파일 오픈
		fprintf(stderr, "second open error for %s\n", fname); //이미 파일을 닫았으므로 오류 메세지 출력
		exit(1);
	}

	else close(fd);


	exit(0);
}
