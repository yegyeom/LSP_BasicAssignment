#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	FILE *fp;
	int character;

	if (argc != 2){
		fprintf(stderr, "usage : %s <filename>\n", argv[0]);
		exit(1);
	}

	if((fp = fopen(argv[1], "r")) == NULL){ //입력으로 받은 파일을 읽기 전용으로 오픈
		fprintf(stderr, "fopen error for &s\n", argv[1]);
		exit(1);
	}

	character = fgetc(fp); //fp가 가르키는 문자 리턴

	while(!feof(fp)){ //파일의 마지막까지 읽음
		fputc(character, stdout); //읽은 각 줄을 출력

		if(ferror(fp)){ //에러 시 문구 출력
			fprintf(stderr, "Error detected!!\n");
			clearerr(fp);
		}

		character = fgetc(fp);
	}

	fclose(fp);
	exit(0);
}
