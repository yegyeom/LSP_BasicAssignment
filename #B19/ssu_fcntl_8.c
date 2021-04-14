#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "ssu_employee.h"

#define DUMMY 0

int main(int argc, char *argv[]){
	struct ssu_employee record;
	int fd;
	int flags;
	int length;
	int pid;

	if(argc < 2){
		fprintf(stderr, "Usage : %s file\n", argv[0]);
		exit(1);
	}

	if((fd = open(argv[1], O_RDWR)) < 0){
		fprintf(stderr, "open error for %s\n", argv[1]);
		exit(1);
	}

	if((flags = fcntl(fd, F_GETFL, DUMMY)) == -1){ //fd로 지정한 파일의 접근권한과 상태 플래그 리턴
		fprintf(stderr, "fcntl F_GETFL error\n");
		exit(1);
	}

	flags |= O_APPEND; //플래그에 O_APPEND 추가

	if(fcntl(fd, F_SETFL, flags) == -1){ //fd로 지정된 파일 상태 플래그를 flags에 지정한 플래그 값으로 재설정 
		fprintf(stderr, "fcntl F_SETFL error\n");
		exit(1);
	}
	
	pid = getpid();

	while(1){
		printf("Enter employee name : ");
		scanf("%s", record.name);

		if(record.name[0] == '.')
			break;

		printf("Enter employee salary : ");
		scanf("%d", &record.salary);
		record.pid = pid;
		length = sizeof(record);
		//레코드 정보 입력 받고 구조체에 저장
		if(write(fd, (char*)&record, length) != length){ //파일에 구조체 씀
			fprintf(stderr, "record write error\n");
			exit(1);
		}
	}

	close(fd);
	exit(0);
}
