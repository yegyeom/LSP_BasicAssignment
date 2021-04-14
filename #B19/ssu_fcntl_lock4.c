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

int main(int argc, char *argv[]){
	struct flock lock;
	struct employee record;
	int fd, recnum, pid;
	long position;
	char ans[5];

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
		lock.l_type = F_RDLCK; //입력받은 위치에 read 락 설정
		lock.l_whence = 0;
		lock.l_start = position;
		lock.l_len = sizeof(record);

		if(fcntl(fd, F_SETLKW, &lock) == -1){ //다른 프로세스가 이미 락을 설정 했을 경우 락을 해제할 때까지 기다림
			perror(argv[1]);
			exit(2);
		}

		lseek(fd, position, 0); //입력받은 위치로 이동
		if(read(fd, (char*)&record, sizeof(record)) == 0){ //파일에서 record사이즈만큼 읽어서 구조체에 저장
			printf("record %d not found\n", recnum);
			lock.l_type = F_UNLCK; //read 락 해제
			fcntl(fd, F_SETLK, &lock);
			continue;
		}
		printf("Employee: %s, salary: %d\n", record.name, record.salary);
		printf("Do you want to update salary (y or n)? ");
		scanf("%s", ans);

		if(ans[0] != 'y'){
			lock.l_type = F_UNLCK;
			fcntl(fd, F_SETLK, &lock);
			continue;
		}
		lock.l_type = F_WRLCK; //write 락으로 변경
		if(fcntl(fd, F_SETLKW, &lock) == -1){ //다른 프로세스가 이미 락을 설정 했을 경우 락을 해제할 때까지 기다림
			perror(argv[1]);
			exit(3);
		}
		record.pid = pid;
		printf("Enter new salary: ");
		scanf("%d", &record.salary);

		lseek(fd, position, 0);
		write(fd, (char*)&record, sizeof(record));
		//파일에 수정한 레코드 작성
		lock.l_type = F_UNLCK; //락 해제
		fcntl(fd, F_SETLK, &lock);
	}
	close(fd);
}

