#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	int i;

	for(i = 0 ; i < argc ; i++) //입력인자 갯수만큼 내용 출력
		printf("argv[%d] : %s\n", i, argv[i]);

	exit(0);
}
