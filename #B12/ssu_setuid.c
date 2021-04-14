#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	char line[256];
	FILE *fp;
	int uid;

	if(argc < 2){
		fprintf(stderr, "usage: %s file_name\n", argv[0]);
		exit(1);
	}

	printf("initially uid = %d and euid = %d\n", getuid(), geteuid()); //호출한 프로세스의 프로세스 id, 유효 사용자 id 출력
	fp = fopen(argv[1], "r"); //파일 읽기 전용으로 오픈

	if(fp == NULL){
		fprintf(stderr, "first open error for %s\n", argv[1]);
		exit(1);
	}
	else{
		printf("first open successful:\n");

		while(fgets(line, 255, fp) != NULL) //오픈한 파일에서 255만큼 문자를 line으로 읽어옴
			fputs(line, stdout); //읽어온 내용을 표준출력으로 출력

		fclose(fp);
	}
	
	setuid(uid = getuid()); 
	//루트 권한 O: 실제 사용자 id, 유효 사용자 id, 저장된 사용자 id를 uid로 설정
	//루트 권한 X, uid가 실제 사용자 id와 같을 때: 유효 사용자 id를 uid로 설정
	printf("after setuid(%d):\n uid=%d and euid=%d\n", uid, getuid(), geteuid()); //uid, 프로세스 id, 유효 사용자 id 출력
	fp = fopen(argv[1], "r"); //파일 읽기 전용으로 오픈

	if(fp == NULL){
		fprintf(stderr, "second open error for %s\n", argv[1]);
		exit(1);
	}
	else{
		printf("second open successful:\n");

		while(fgets(line, 255, fp) != NULL) //오픈한 파일에서 255만큼 문자를 line으로 읽어옴
			fputs(line, stdout); //읽어온 내용을 표준출력으로 출력

		fclose(fp);
	}

	exit(0);
}
