#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void ssu_addone(void);

extern char **environ; //*environ[]
char glob_var[] = "HOBBY=swimming";

int main(void){
	int i;

	for(i = 0 ; environ[i] != NULL ; i++) //환경 변수 출력
		printf("environ[%d] : %s\n", i, environ[i]);

	putenv(glob_var); //전역변수로 선언된 환경변수 등록
	ssu_addone();
	printf("My hobby is %s\n", getenv("HOBBY"));
	printf("My lover is %s\n", getenv("LOVER")); //지정해주지 않았으므로 null로 출력
	strcpy(glob_var + 6, "fishing"); 

	for(i = 0 ; environ[i] != NULL ; i++)
		printf("environ[%d] : %s\n", i, environ[i]); //등록된 환경 변수 출력
	
	exit(0);
}

void ssu_addone(void){
	char auto_var[10];

	strcpy(auto_var, "LOVER=js");
	putenv(auto_var); //지역변수를 인자로 주어서 소멸될 경우 환경변수가 제대로 출력되지 않음
}
