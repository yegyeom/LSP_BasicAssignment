#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#define MODE_EXEC (S_IXUSR|S_IXGRP|S_IXOTH)

int main(int argc, char *argv[]){
	struct stat statbuf;
	int i;
	if(argc < 2){
		fprintf(stderr, "usage : %s <file1><file2> ... <fileN>\n", argv[0]);
		exit(1);
	}

	for(i = 1 ; i < argc ; i++){
		if(stat(argv[i], &statbuf) < 0){ //인자로 지정한 파일의 정보 확인
			fprintf(stderr, "%s : stat error\n", argv[i]);
			continue;
		}
		
		statbuf.st_mode |= MODE_EXEC; // MODE_EXEC 모드 설정
		statbuf.st_mode ^= (S_IXGRP | S_IXOTH); //모드 바꾸고 토글

		if(chmod(argv[i], statbuf.st_mode) < 0) //인자로 지정한 모드로 파일 접근 권한을 변경
			fprintf(stderr, "%s : chmod error\n", argv[i]);
		else
			printf("%s : file permission was changed.\n", argv[i]);
	}
	
	exit(0);
}
