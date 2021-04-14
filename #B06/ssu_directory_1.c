#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

#define DIRECTORY_SIZE MAXNAMLEN

int main(int argc, char *argv[]){
	struct stat statbuf;
	struct dirent *dentry;
	char filename[DIRECTORY_SIZE];
	DIR *dirp; 

	if(argc < 2){
		fprintf(stderr, "usage : %s <directory>\n", argv[0]);
		exit(1);
	}

	if((dirp = opendir(argv[1])) == NULL || chdir(argv[1])==-1){ //opendir로 DIR 구조체를 얻는다, chdir을 호출하여 파일 이름만으로도 접근할 수 있게 작업 디렉토리를 변경
		fprintf(stderr, "opendir, chdir error for %s\n", argv[1]);
		exit(1);
	}

	while((dentry = readdir(dirp)) != NULL){ //위에서 얻은 구조체를 readdir하여 파일 이름을 얻음
		if(dentry->d_ino == 0)
			continue;

		memcpy(filename, dentry->d_name, DIRECTORY_SIZE); //파일이름을 DIRECTORY_SIZE만큼 복사하여 filename에 넣음

		if(stat(filename, &statbuf) == -1){ //filename의 정보가 stat구조체를 통해 리턴됨 
			fprintf(stderr, "stat error for %s\n", filename);
			break;
		}

		if((statbuf.st_mode & S_IFMT) == S_IFREG)//파일 종류가 일반 파일이면
			printf("%-14s %ld\n", filename, statbuf.st_size); //이름과 사이즈 출력
		else //일반 파일이 아닐 경우
			printf("%-14s\n", filename); //이름만 출력
	}

	exit(0);
	}
