#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "ssu_employee.h"

int main(int argc, char *argv[]){
	struct ssu_employee record;
	int fd;
	int record_num;

	if(argc < 2){
		fprintf(stderr, "Usage : %s file\n", argv[0]);
		exit(1);
	}
	if ((fd = open(argv[1], O_RDONLY)) < 0 ){ //데이터 있는 파일 오픈
		fprintf(stderr, "open error for %s\n", argv[1]);
		exit(1);
	}

	while(1){
		printf("Enter record number : ");
		scanf("%d", &record_num);

		if(record_num < 0 )
			break;

		if(lseek(fd, (long)record_num * sizeof(record), 0) < 0){ //해당 레코드 위치로 lseek호출하여 오프셋 이동
				fprintf(stderr, "lseek error\n");
				exit(1);
		}

		if(read(fd, (char *)&record, sizeof(record)) > 0) //record 구조체 크기 만큼 구조체 내용 읽어온 후 변수에 저장
			printf("Employee : %s Salary : %d\n", record.name, record.salary);
		else 
			printf("Record %d not found\n", record_num);
	}

	close(fd);
	exit(0);
}
