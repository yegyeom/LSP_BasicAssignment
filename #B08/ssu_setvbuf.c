#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

void ssu_setbuf(FILE *fp, char *buf);

int main(){
	char buf[BUFFER_SIZE];
	char *fname = "/dev/pts/0";
	FILE *fp;

	if((fp = fopen(fname, "w")) == NULL){ //쓰기전용으로 오픈
		fprintf(stderr, "fopen error for %s", fname);
		exit(1);
	}

	ssu_setbuf(fp, buf);  
	fprintf(fp, "Hello, ");
	sleep(1);
	fprintf(fp, "UNIX!!");
	sleep(1);
	fprintf(fp, "\n"); //여기까지 한번에 출력
	sleep(1);
	ssu_setbuf(fp, NULL); //버퍼가 NULL로 설정
	fprintf(fp, "HOW");
	sleep(1);
	fprintf(fp, " ARE");
	sleep(1);
	fprintf(fp, " YOU?");
	sleep(1);
	fprintf(fp, "\n"); //버퍼에 넣지 않고 바로 출력
	sleep(1);
	exit(0);
}

void ssu_setbuf(FILE *fp, char *buf){
	size_t size;
	int fd;
	int mode;

	fd = fileno(fp); //파일 디스크립터 얻음
	
	if(isatty(fd)) //터미널의 번호 확인
		mode = _IOLBF; //버퍼링 종류 line-buffered
	else
		mode = _IOFBF; //버퍼링 종류 full-buffered
//fd를 통해 모드와 크기 설정
	if(buf == NULL){
		mode = _IONBF; //버퍼링 종류 non-buffered
		size = 0;
	}
	else
		size = BUFFER_SIZE;

	setvbuf(fp, buf, mode, size); //해당 파일의 버퍼 설정
}
