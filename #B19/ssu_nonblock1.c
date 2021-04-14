#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

void set_flags(int fd, int flags);
void clr_flags(int fd, int flags);

char buf[500000];

int main(){
	int ntowrite, nwrite;
	char *ptr;

	ntowrite = read(STDIN_FILENO, buf, sizeof(buf)); //입력 받은 파일 읽어서 buf에 저장 읽은 바이트 수는 ntowrite
	fprintf(stderr, "reading %d bytes\n", ntowrite);

	set_flags(STDOUT_FILENO, O_NONBLOCK);

	ptr = buf;
	while(ntowrite > 0){
		errno = 0;
		nwrite = write(STDOUT_FILENO, ptr, ntowrite); //ptr을 ntowrite byte만큼 표준출력으로 출력
		fprintf(stderr, "nwrite = %d, errno = %d\n", nwrite, errno);

		if(nwrite > 0){
			ptr += nwrite;
			ntowrite -= nwrite;
		}
	}
	clr_flags(STDOUT_FILENO, O_NONBLOCK);
	exit(0);
}

void set_flags(int fd, int flags){
	int val;
//NONBLOCKING 모드로 변경
	if((val = fcntl(fd, F_GETFL, 0)) < 0){ //열려진 파일에 대한 파일 디스크립터
		fprintf(stderr, "fcntl F_GETFL failed");
		exit(1);
	}

	val |= flags; //플래그 비트 켬

	if(fcntl(fd, F_SETFL, val) < 0){ //flag를 위에서 받은 파일 디스크립터 값으로 설정
		fprintf(stderr, "fcntl F_GETFL failed");
		exit(1);
	}

	val &= ~flags; //플래그 비트 끔

	if(fcntl(fd, F_SETFL, val) < 0){ //flag를 위에서 받은 파일 디스크립터 값으로 설정
		fprintf(stderr, "fcntl F_SETFL failed");
		exit(1);
	}
}

void clr_flags(int fd, int flags){
	int val;

	if((val = fcntl(fd, F_GETFL, 0)) < 0){ //열려진 파일에 대한 파일 디스크립터
		fprintf(stderr, "fcntl F_GETTL failed");
		exit(1);
	}

	val &= ~ flags; //플래그 비트 끔

	if(fcntl(fd, F_SETFL, val) < 0){ //flag를 위에서 받은 파일 디스크립터 값으로 설정
		fprintf(stderr, "fcntl F_SETFL failed");
		exit(1);
	}
}
