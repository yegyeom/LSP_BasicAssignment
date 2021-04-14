#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	if (argc < 3){
		fprintf(stderr, "usage : %s <file1><file2>\n", argv[0]);
		exit(1);
	}

	if(link(argv[1], argv[2]) == -1){ //첫번째 인자와 같은 파일을 두번째 인자의 이름으로 새로 생성
		fprintf(stderr, "link error for %s\n", argv[1]);
		exit(1);
	}

	exit(0);
}
