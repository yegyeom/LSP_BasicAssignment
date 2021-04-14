#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void){
	pid_t pgid;
	pid_t pid;

	pid = getpid(); //현재 프로세스의 프로세스 id 
	pgid = getpgrp(); //현재 프로세스의 프로세스 그룹 id 
	printf("pid: %d, pgid: %d\n", pid, pgid);
	exit(0);
}
