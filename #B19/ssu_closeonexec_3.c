#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

int main(void){
	int flag;

	if((flag = fcntl(STDOUT_FILENO, F_DUPFD)) == -1){ //인자가 없으므로 error
		fprintf(stderr, "Error : Checking CLOSE_ON_EXEC\n");
		exit(1);
	}

	printf("CLOSE ON EXEC flag is = %d\n", flag); //인자를 올바르게 주었다면 출력
	exit(0);
}
