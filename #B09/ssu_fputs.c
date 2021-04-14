#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]){
	char buf[BUFFER_SIZE];
	FILE *fp;

	if(argc != 2){
		fprintf(stderr, "usage : %s <file>\n", argv[0]);
		exit(1);
	}

	if((fp = fopen(argv[1], "w+")) == NULL){ //파일 읽기쓰기 가능하게 오픈, 파일이 존재하지 않는다면 새로 만듦
		fprintf(stderr, "fopen error for %s\n", argv[1]);
		exit(1);
	}

	fputs("Input String >> ", stdout);
	gets(buf); //개행포함하여 입력을 읽어서 buf에 저장
	fputs(buf, fp); //buf의 내용을 fp에 씀 (개행문자 추가 X)
	rewind(fp); //offset 맨 앞으로 이동
	fgets(buf, sizeof(buf), fp); //파일로부터 sizeof(buf)만큼 읽어서 buf에 저장
	puts(buf); //buf 내용 출력(문자열의 끝인 NULL은 개행문자로 대체 => 자동 줄바꿈)
	fclose(fp);

	exit(0);
}
