#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "ssu_employee.h"

int main(int argc, char *argv[]){
	struct ssu_employee record;
	int fd;

	if(argc < 2){
		fprintf(stderr, "usage : %s file\n", argv[0]); 
		exit(1);
		}

	if((fd = open(argv[1], O_WRONLY | O_CREAT | O_EXCL, 0640)) < 0){ //파일 쓰기 전용, creat, mode 640으로 오픈
		fprintf(stderr, "open error for %s\n", argv[1]); 
		exit(1);
	}
	
	while(1){ //무한루프 돌리면서 입력 받음
		printf("Enter employee name <SPACE> salary : ");
		scanf("%s", record.name);

		if(record.name[0] == '.') //. 입력 받으면 끝
			break;

		scanf("%d", &record.salary);
		record.pid = getpid();
		write(fd, (char *)&record, sizeof(record)); //읽은 파일을 sizeof(record)만큼 write함
	}

	close(fd);
	exit(0);
}
