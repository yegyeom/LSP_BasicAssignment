#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <limits.h>
#include <string.h>
#include <sys/stat.h>

#ifdef PATH_MAX
static int pathmax = PATH_MAX;
#else
static int pathmax = 0;
#endif

#define MAX_PATH_GUESSED 1024

#ifndef LINE_MAX
#define LINE_MAX 2048
#endif

char *pathname;
char command[LINE_MAX], grep_cmd[LINE_MAX];

int ssu_do_grep(){ //grep 명령어 수행
	struct dirent *dirp;
	struct stat statbuf;
	char *ptr;
	DIR *dp;

	if(lstat(pathname, &statbuf) < 0){ //심볼릭 링크 파일 구조체
		fprintf(stderr, "lstat error for %s\n", pathname);
		return 0;
	}

	if(S_ISDIR(statbuf.st_mode) == 0){ //디렉토리 아니면
		sprintf(command, "%s %s", grep_cmd, pathname); //command에 grep_cmd pathname 으로 저장 
		printf("%s : \n", pathname); //pathname 출력
		system(command); //grep 명령어 실행하여 찾는 키워드가 파일에 존재하는지 확인
		return 0;
	}

	ptr = pathname + strlen(pathname); //현재 *ptr은 pathname[strlen(pathname)}
	*ptr++ = '/'; // / 삽입
	*ptr = '\0'; // \0 삽입

	if((dp = opendir(pathname)) == NULL){ //DIR 구조체 포인터 리턴 받기
		fprintf(stderr, "opendir error for %s\n", pathname);
		return 0;
	}

	while((dirp = readdir(dp)) != NULL) //readdir로 파일을 듦하나씩 접근하여 파일 이름 얻음
		if(strcmp(dirp->d_name, ".") && strcmp(dirp->d_name, "..")){ //파일이름이 .이나 ..이 아니면
			strcpy(ptr, dirp->d_name); //파일이름을 ptr에 복사

			if(ssu_do_grep() < 0) //grep명령어로 찾는 키워드가 파일에 존재하는지 확인
				break;
		}

	ptr[-1] = 0; // '/'를 널문자로 바꾼다
	closedir(dp);
	return 0;

}

void ssu_make_grep(int argc, char *argv[]){ //grep 명령어 만들기
	int i;
	strcpy(grep_cmd, " grep"); //grep_cmd에 "grep" 복사하기

	for(i = 1 ; i < argc-1 ; i++){
		strcat(grep_cmd, " "); //grep_cmd 뒤에 공백 이어쓰기
		strcat(grep_cmd, argv[i]); //grep_cmd 뒤에 argv[i] 이어쓰기
	}
}

int main(int argc, char *argv[]){
	if(argc < 2){
		fprintf(stderr, "usage : %s <-CVchilnsvwx> <-num> <-A num> <-B num> <-f file> \n"
				"		<-e> expr <directory>\n", argv[0]);
		exit(1);
	}

	if (pathmax == 0){  
		if((pathmax = pathconf("/", _PC_PATH_MAX)) < 0) //현재 디렉토리일 때 패스명의 최대 바이트 수 리턴
			pathmax = MAX_PATH_GUESSED; //에러이면 1024로 설정
		else //다음 디렉토리로 이동
			pathmax++;
	}

	if((pathname = (char *)malloc(pathmax+1)) == NULL){ //pathmax + 1 만큼 동적할당
		fprintf(stderr, "malloc error\n");
		exit(1);
	}

	strcpy(pathname, argv[argc-1]); //가장 마지막 입력인자를 pathname에 복사
	ssu_make_grep(argc, argv); //grep명령어 만듦
	ssu_do_grep(); //grep명령어 실행
	exit(0);
}

