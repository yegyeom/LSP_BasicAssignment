#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	char *arg_directory = NULL;
	char *arg_prefix = NULL;

	if(argc != 3){
		fprintf(stderr, "usage : %s <directory> <prefix>\n", argv[0]);
		exit(1);
	}

	arg_directory = argv[1][0] != ' ' ? argv[1] : NULL; //argv[1][0]이 공백이 아니면 argv[1], 공백이면 NULL
	arg_prefix = argv[2][0] != ' ' ? argv[2] : NULL; //argv[2][0]이 공백이 아니면 argv[2], 공백이면 NULL
	printf("created : %s\n", tempnam(arg_directory, arg_prefix)); //tempnam으로 임시 파일 생성, 입력받은 첫번째 인자가 임시 파일이 생성 될 디렉토리, 입력받은 두번째 인자가 임시 파일 이름의 접두어로 사용됨
	exit(0);
}
