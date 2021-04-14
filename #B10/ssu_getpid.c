#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(void){
	printf("Process ID		= %d\n", getpid()); //호출한 프로세스의 프로세스 ID
	printf("Parent process ID	= %d\n",getppid()); //호출한 프로세스의 부모 프로세스 ID
	printf("Real user ID		= %d\n", getuid()); //호출한 프로세스의 실제 사용자 ID
	printf("Effective user ID	= %d\n", geteuid()); //호출한 프로세스의 유효 사용자 ID
	printf("Real group ID		= %d\n", getgid()); //호출한 프로세스의 실제 그룹 ID
	printf("Effective group ID	= %d\n", getegid()); //호출한 프로세스의 유효 그룹 ID
	exit(0);
}
