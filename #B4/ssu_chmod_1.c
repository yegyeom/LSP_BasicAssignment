#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

int main(){
	struct stat statbuf;
	char *fname1 = "ssu_file1";
	char *fname2 = "ssu_file2";

	if(stat(fname1, &statbuf) < 0) //파일의 정보확인하여 구조체를 통해 리턴
		fprintf(stderr, "stat error %s\n", fname1);

	if(chmod(fname1, (statbuf.st_mode & ~S_IXGRP) | S_ISUID) < 0) //set user id
		fprintf(stderr, "chmod error %s\n", fname1);

	if(chmod(fname2, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH | S_IXOTH) < 0) //인자로 지정한 모드로 파일의 접근 권한을 변경
		fprintf(stderr, "chmod error %s\n", fname2);

	exit(0);
}
