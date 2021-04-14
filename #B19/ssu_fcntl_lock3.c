#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define NAMESIZE 50

struct employee{
	char name[NAMESIZE];
	int salary;
	int pid;
};

int main(int argc, char* argv[]){
	struct flock lock;
	struct employee record;
	int fd, recnum, pid;
	long position;

	if((fd = open(argv[1], O_RDWR)) == -1){
		perror(argv[1]);
		exit(1);
	}

	pid = getpid();
	for(;;){
		printf("\nEnter record number: ");
		scanf("%d", &recnum);
		if(recnum < 0)
			break;
		position = recnum * sizeof(record);
		lock.l_type = F_WRLCK; //수정 원하는 record에 write 락설정
		lock.l_whence = 0;
		lock.l_start = position;
		lock.l_len = sizeof(record);
		if(fcntl(fd, F_SETLKW, &lock) == -1){
			perror(argv[1]);
			exit(2);
		}
		lseek(fd, position, 0); 
		if(read(fd, (char*)&record, sizeof(record)) == 0){ //파일 record사이즈만큼 읽어서 구조체에 저장
			printf("record %d not found\n", recnum);
			lock.l_type = F_UNLCK; //write 락 해제
			fcntl(fd, F_SETLK, &lock);
			continue;
		}
		printf("Employee: %s, salary: %d\n", record.name, record.salary);
		record.pid = pid;
		printf("Enter new salary: ");
		scanf("%d", &record.salary);
		lseek(fd, position, 0);
		write(fd, (char*)&record, sizeof(record));
		//수정 할 정보 입력 받고 구조체에 저장해서 파일에 씀
		lock.l_type = F_UNLCK; //write 락 해제
		fcntl(fd, F_SETLK, &lock);
	}
	close(fd);
}
