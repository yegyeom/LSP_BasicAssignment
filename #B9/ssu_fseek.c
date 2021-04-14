#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
	char *fname = "ssu_test.txt";
	FILE *fp;
	long position;
	int character;

	if((fp = fopen(fname, "r")) == NULL){ //파일을 읽기 전용으로 오픈
		fprintf(stderr, "fopen error for %s\n", fname);
		exit(1);
	}

	printf("Input number >>");
	scanf("%ld", &position);
	fseek(fp, position - 1, SEEK_SET); //입력한 값만큼 떨어진 곳으로 오프셋 이동
	character = getc(fp); //이동한 곳에서 문자 하나 읽음
	printf("%ldth character => %c\n", position, character); //입력한 곳과 그 곳의 문자 출력
	exit(0);
}
