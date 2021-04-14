#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
	printf("Good afternoon?");
	_exit(0); //표준 입출력 버퍼 비우지 않고 종료
}

