#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	extern char **environ;
	char **str;
	int i;

	for (i = 0 ; i < argc ; i++)
		printf("argv[%d]: %s\n", i, argv[i]); //전달 받은 인자들 모두 출력

	for(str = environ ; *str != 0 ; str++)
		printf("%s\n", *str); //환경변수 모두 출력

	exit(0);
}
