#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define RW_MODE (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH) //0666

int main(void){
	char *fname1 = "ssu_file1";
	char *fname2 = "ssu_file2";

	umask(0); //파일 생성 시 마스크 값 0

	if(creat(fname1, RW_MODE) < 0){
		fprintf(stderr, "creat error for %s\n", fname1);
		exit(1);
	}

	umask(S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH); 

	if(creat(fname2, RW_MODE) < 0){ //마스크 값을 설정해뒀으므로 파일 소유자의 읽기, 쓰기만 가능함
		fprintf(stderr, "creat error for %s\n", fname2);
		exit(1);
	}

	exit(0);
}
