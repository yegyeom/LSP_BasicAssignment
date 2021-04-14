#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void){
	printf("before system()\n");
	system("pwd"); //system()으로 pwd 명령어 실행
	printf("after system()\n");
	exit(0);
}
