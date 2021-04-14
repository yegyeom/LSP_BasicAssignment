#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void ssu_printenv(char *label, char ***envpp);

extern char **environ; //*environ[]

int main(int argc, char *argv[], char *envp[]){
	ssu_printenv("Initially", &envp);
	putenv("TZ=PST8PDT"); //환경 변수 등록
	ssu_printenv("After changing TZ", &envp);
	putenv("WARNING=Don't use envp after putenv()"); //환경 변수 등록
	ssu_printenv("After setting a new variable", &envp);
	printf("value of WARNING is %s\n", getenv("WARNING"));//환경 변수 리스트 중 "이름=값" 형식 문자열 찾아서 값 포인터 리턴 => Don't use envp after putenv()
	exit(0);
}

void ssu_printenv(char *label, char ***envpp){
	char **ptr;

	printf("---- %s ---\n", label);
	printf("envp is at %8o and contains %8o\n", envpp, *envpp);
	printf("environ is at %8o and contains %8o\n", &environ, environ);
	printf("My environment variable are:\n");

	for(ptr = environ ; *ptr ; ptr++) //환경변수 출력
		printf("(%8o) = %8o -> %s\n", ptr, *ptr, *ptr);

	printf("(%8o) = %8o\n", ptr, *ptr);
}
