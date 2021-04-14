#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main(){
	char *fname = "ssu_test.dat";
	char name[BUFFER_SIZE];
	FILE *fp;
	int age;

	fp = fopen(fname, "r"); //읽기 전용으로 파일 오픈
	fscanf(fp, "%s%d", name, &age); //이름과 나이 입력 받음
	fclose(fp);
	fp = fopen(fname, "w"); //쓰기 전용으로 파일 오픈
	fprintf(fp, "%s is %d years old\n", name, age); //입력 받았던 이름과 나이 호출
	fclose(fp);
	exit(0);
}
