#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

int main(){
	char operator;
	FILE *fp;
	int character;
	int number = 0;

	if((fp = fopen("ssu_expr.txt", "r")) == NULL){ //파일을 읽기 전용으로 오픈
		fprintf(stderr, "fopen error for ssu_expr.txt\n");
		exit(1);
	}

	while(!feof(fp)){ //파일의 끝에 다다를 때까지
		while((character = fgetc(fp)) != EOF && isdigit(character)) //파일의 문자 읽으면서 문자가 숫자인지 검사(숫자가 아니거나 파일 끝에 다다르면 while문 끝)
			number = 10 * number + character - 48;

		fprintf(stdout, " %d\n", number);
		number = 0;

		if(character != EOF){ //숫자가 아닌 문자를 만나면
			ungetc(character, fp); //문자를 다시 스트림에 넣음
			operator = fgetc(fp); //위에서 다시 넣은 문자를 operator 변수에 넣음
			printf("Operator => %c\n", operator); //연산자 출력
		}
	}
	fclose(fp);
	exit(0);
}
