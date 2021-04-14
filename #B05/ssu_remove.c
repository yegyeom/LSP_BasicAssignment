#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	if(argc != 3){
		fprintf(stderr, "usage : %s <oldname> <newname>\n", argv[0]);
		exit(1);
	}

	if(link(argv[1], argv[2]) < 0){ //첫번째 인자와 같은 파일을 두번째 인자의 이름으로 새로운 파일을 만든다
		fprintf(stderr, "link error\n");
		exit(1);
	}

	else 
		printf("step1 passed.\n");

	if(remove(argv[1]) < 0){ //argv[1] unlink
		fprintf(stderr, "remove error\n");
		remove(argv[2]); 
		exit(1);
	}
	else
		printf("step2 passed.\n"); //remove(argv[2])가 되지 않은 경우

	printf("Success!\n");
	exit(0);
}
