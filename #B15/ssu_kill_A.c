#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main(int argc, char *argv[]){
	if(argc != 2){
		fprintf(stderr, "usage: %s [Process ID]\n", argv[0]);
		exit(1);
	}
	else
		kill(atoi(argv[1]), SIGKILL); //인자로 받은 kill할 pid, SIGKILL로 kill()호출
	
	exit(0);
}
